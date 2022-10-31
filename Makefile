PROGRAMS = zombiebox

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)

%: %.c
	$(CC) -std=c99 -Wall -Werror -static -s -o $@ $<
