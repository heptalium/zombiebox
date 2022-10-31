#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/prctl.h>
#include <sys/wait.h>

#define MAX_PROCESSES 16
#define MAIN_LOOP_SLEEP 2
#define PROCESS_SLEEP 10
#define SUBPROCESS_SLEEP 15
#define NAME_SIZE 32

/* set process name */
void setname(char *argv[], int argl, const char *name) {
	prctl(PR_SET_NAME, name);
	memset(argv[0], 0, argl + 1);
	strncpy(argv[0], name, argl);
}

int main(int argc, char *argv[]) {
	pid_t children[MAX_PROCESSES] = {};
	char name[NAME_SIZE];

	/* exit on signal 15 */
	signal(SIGTERM, exit);

	/* maximum length of process name */
	int argl = strlen(argv[0]);

	setname(argv, argl, "main");

	/* main loop */
	for (int n = 0;; n++) {

		pid_t pid = fork();

		if (!pid) {
			/* child */
			if (fork()) {
				snprintf(name, NAME_SIZE, "process(%d)", n);
				setname(argv, argl, name);
				sleep(PROCESS_SLEEP);
				return EXIT_SUCCESS;
			}

			/* grandchild */
			else {
				snprintf(name, NAME_SIZE, "subprocess(%d)", n);
				setname(argv, argl, name);
				sleep(SUBPROCESS_SLEEP);
				return EXIT_SUCCESS;
			}
		}

		/* Add child to process list */
		for (int i = 0; i < MAX_PROCESSES; i++) {
			if (!children[i]) {
				children[i] = pid;
				break;
			}
		}

		sleep(MAIN_LOOP_SLEEP);

		/* check process list for finished processes */
		for (int i = 0; i < MAX_PROCESSES; i++) {
			if (children[i]) {
				if (waitpid(children[i], NULL, WNOHANG)) {
					children[i] = 0;
				}
			}
		}
	}
}
