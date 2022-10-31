FROM alpine AS build
RUN apk add --no-cache gcc make musl-dev
WORKDIR /work
COPY Makefile *.c ./
RUN make

FROM alpine
RUN apk add --no-cache htop
COPY htoprc /root/.config/htop/htoprc
COPY --from=build /work/zombiebox /usr/bin/
CMD ["/usr/bin/zombiebox"]
