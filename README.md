# Zombiebox

Container image to demonstrate the zombie reaping problem which can occur inside containers.

## Usage

Run a container of this image:
```
docker container run -d --name zombiebox --rm ghcr.io/heptalium/zombiebox:latest
```

Run _htop_ inside the container and watch what is happening:
```
docker container exec -it zombiebox /usr/bin/htop
```

Quit _htop_ by pressing `q`, then stop the container:
```
docker container stop zombiebox
```

Run a new container with the `--init` option:
```
docker container run -d --init --name zombiebox --rm ghcr.io/heptalium/zombiebox:latest
```

Run _htop_ again:
```
docker container exec -it zombiebox /usr/bin/htop
```
