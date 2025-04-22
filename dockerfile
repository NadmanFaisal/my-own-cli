FROM gcc:latest
COPY . /src
WORKDIR /src/
RUN gcc -o src main.c
CMD ["./src"]