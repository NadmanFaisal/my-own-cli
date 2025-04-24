# my-own-cli

To build the docker using the docker file:-

docker build -t test/helloworld:latest .

to run the docker:-

docker run --rm test/helloworld

To export the docker image:

docker image save test/helloworld:latest > test-image.tar

To view the files in the docker:

docker run -it --name helloworld_container test/helloworld:latest /bin/sh

Then immediately remove it for reuse:

docker rm /helloworld_container

To delete the docker:-

docker rmi test/helloworld:latest

To delete docker forcefully:-

docker rmi -f test/helloworld:latest

To run the program locally:

gcc -IHeaders main.c src/*.c -o exec/main && ./exec/main