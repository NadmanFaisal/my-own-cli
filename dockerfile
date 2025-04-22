# Build stage using alpine latest image
FROM alpine:latest AS build-stage
# Runs necessary command for gcc and musl lib
RUN apk add --no-cache gcc musl-dev
# Copies everything in the current root to src
COPY . /src
# Sets the working directory to src to prevent changing directory
WORKDIR /src/
# Compiles the main.c to binary exec file
RUN gcc -IHeaders main.c src/*.c -o exec/main

# Running stage using alpine image
FROM alpine:latest as final-stage
# Copies the binary exec file from the build stage and sets it as env var
COPY --from=build-stage /src/exec/main /usr/local/bin/main
# Compiles the main exec file
ENTRYPOINT [ "main" ]