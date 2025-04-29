# my-own-cli

A simple command-line interface built entirely on C programming language, supporting basic UNIX-life (base-like) file system operations. This program supports commands like `ls`, `cd`, `mkdir`, `touch`, `rm`, `cp`, and `mv`.

# List of commands supported

- Help command (`help`) — prints all available commands
- List directories (`ls [path]`)
- Change directory (`cd <path>`)
- Make directories (`mkdir <folder_name>`)
- Create or update files (`touch <file_name>`)
- Remove files or folders (`rm <path>`) — recursive for directories
- Copy files (`cp <source_file> <destination_file>`)
- Rename or move files/folders (`mv <original_name> <new_name>`)
- Exit (`exit`) — to quit the CLI

# Dockerization

This project is containerized using Docker to ensure consistent behavior across different environments and make it easily accessible for everyone.

The docker follows multi-stage build, which uses a lightweight base image for both the stages, ensuring a small docker file size.

A Docker image has been built and pushed to Docker Hub, allowing you to run the CLI without needing to manually compile the source code.

## Supported Platforms for Docker

Currently, the dockers only run on the following platforms:

- macOS
- Linux
- Windows Bash

## Running docker from Docker Hub

Pull the docker from docker hub:

```
docker pull carbonatedwaterr/my-own-cli:latest
```

Run the docker in the current working directory:

```
docker run --rm -it \
  --mount type=bind,src="$(pwd)",target="$(pwd)" \
  -w "$(pwd)" \
  carbonatedwaterr/my-own-cli:latest
```

## Running Docker Manually

To build the docker using the docker file:-

```
docker build -t test/helloworld:latest .
```

To run the docker on the current working directory:-

```
docker run --rm -it -v "$PWD":"$PWD" -w "$PWD" test/helloworld
```

To run the docker in the container environment:

```
docker run --rm -it test/helloworld
```

To delete the docker:-

```
docker rmi test/helloworld:latest
```

To delete docker forcefully:-

```
docker rmi -f test/helloworld:latest
```

# Run the program locally

Clone the repo:

```
git clone https://github.com/NadmanFaisal/my-own-cli.git
cd my-own-cli
```

Compile and the project:

```
gcc -IHeaders main.c src/*.c -o exec/main && ./exec/main
```

# Usage Flow

```
> ls
> mkdir test_folder
> cd test_folder
> touch file.txt
> ls
> cp file.txt copy_file.txt
> mv copy_file.txt renamed_file.txt
> rm renamed_file.txt
> cd ..
> rm test_folder
> help
> exit
```

# Developers flow

- Add the type of command (StatementType enum) in Statement.h (Also remember to add comment)
- Return the type of statement in Statement.c (execute_statement method)
- Add the case block for the type of command in main.c
- Add the method decleration in BashCommand.h
- Implement the method in BashCommand.c
- Adjust the method `print_help()` in `BashCommands.h` and `BashCommands.c` accordingly
- Adjust the readme as needed.

# File Structure

```
my-own-cli/
├── exec/
│   ├── .gitkeep
|
├── Headers/
│   ├── .gitkeep
│   ├── BashCommands.h
│   ├── Constants.h
│   ├── InputBuffer.h
│   ├── Statement.h
|
├── src/
│   ├── BashCommands.c
│   ├── InputBuffer.c
│   ├── Statement.c
│
├── main.c
├── Dockerfile
├── .gitignore
├── README.md
├── LICENSE
```