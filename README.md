# Zombiebox

Container image to demonstrate the zombie reaping problem which can occur inside containers.

## Usage

Run a container of this image:\
`docker container run -d --name zombiebox --rm ghcr.io/heptalium/zombiebox:latest`

Run htop inside the container and watch what is happening:\
`docker container exec -it zombiebox /usr/bin/htop`

Quit htop by pressing `q`, then stop the container:\
`docker container kill zombiebox`

Run a new container with the `--init` option:\
`docker container run -d --init --name zombiebox --rm ghcr.io/heptalium/zombiebox:latest`

Run htop again:\
`docker container exec -it zombiebox /usr/bin/htop`
