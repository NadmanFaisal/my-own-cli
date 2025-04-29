#include "BashCommands.h"

DIR *verify_path(char *path, PathConfirmation *status) {
    DIR *dir;

    if(path == NULL) {
        dir = opendir(".");
    } else {
        dir = opendir(path);
    }

    if(dir == NULL) {
        *status = PATH_UNRECOGNISED;
    } else {
        *status = PATH_RECOGNISED;
    }

    return dir;
}

void list_dir(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";
    
    char *command = strtok(string, delimiter);
    char *path = strtok(NULL, delimiter);
    
    PathConfirmation *status = (PathConfirmation *)malloc(sizeof(PathConfirmation));
    DIR *dir = verify_path(path, status);

    if(*status == PATH_UNRECOGNISED) {
        printf("Error: Path not recognizes or directory '%s' not found.\n", path);
        exit(EXIT_FAILURE);
    }

    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL) {
        if (!(strcmp(dp->d_name, ".") == 0) && (!strcmp(dp->d_name, "..") == 0)) {
            printf("%s  ", dp->d_name);
        }
    }
    printf("\n");
    closedir(dir);
    free(status);
}

void change_dir(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";
    
    char *command = strtok(string, delimiter);
    char *path = strtok(NULL, delimiter);

    if (path == NULL) {
        printf("Error: No path provided for 'cd' command.\n");
        return;
    }
    
    PathConfirmation *status = (PathConfirmation *)malloc(sizeof(PathConfirmation));
    DIR *dir = verify_path(path, status);

    if(*status == PATH_UNRECOGNISED) {
        printf("Error: Path not recognizes or directory '%s' not found.\n", path);
        exit(EXIT_FAILURE);
    }

    chdir(path);
    char s[100];
    printf("%s\n", getcwd(s, 100)); 
    closedir(dir);
    free(status);
}

void make_dir(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";
    
    char *command = strtok(string, delimiter);
    char *folder_name = strtok(NULL, delimiter);

    if (folder_name == NULL) {
        printf("Error: No file name provided for 'mkdir' command.\n");
        return;
    }

    mkdir(folder_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void touch_file(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";
    
    char *command = strtok(string, delimiter);
    char *file_name = strtok(NULL, delimiter);

    int fd = open(file_name, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("touch failed");
        return;
    }
    close(fd);
}

int remove_file_dir_path(const char *path) {
    DIR *dir = opendir(path);
    int r = -1;

    if (dir) {
        struct dirent *p;
        r = 0;
        while ((p = readdir(dir))) {
            int r2 = -1;
            char *buf;
            size_t len;

            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = strlen(path) + strlen(p->d_name) + 2;
            buf = malloc(len);

            if (buf) {
                struct stat statbuf;

                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode))
                        r2 = remove_file_dir_path(buf);
                    else
                        r2 = unlink(buf);
                }
                free(buf);
            }
            if (r2 != 0)
                r = r2;
        }
        closedir(dir);

        if (rmdir(path) != 0) {
            perror("Error removing directory");
            return -1;
        }
        printf("Removed directory: %s\n", path);
    } else {
        if (remove(path) != 0) {
            perror("Error removing file or directory");
            return -1;
        }
    }

    return r;
}

int remove_file_dir(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";

    char *command = strtok(string, delimiter);
    char *path = strtok(NULL, delimiter);

    if (path == NULL) {
        printf("Error: No path provided.\n");
        return -1;
    }

    return remove_file_dir_path(path);
}

int rename_file_or_dir(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";

    char *command = strtok(string, delimiter);
    char *original_name = strtok(NULL, delimiter);
    char *new_name = strtok(NULL, delimiter);

    if(original_name == NULL) {
        printf("No Original name provided.\n");
        return -1;
    } else if(new_name == NULL) {
        printf("No new name provided.\n");
        return -1;
    }

    if(access(original_name, F_OK) != 0) {
        printf("File or folder '%s' does not exist.\n", original_name);
        return -1;
    }

    if(access(new_name, F_OK) == 0) {
        printf("File or folder name '%s' already exists.\n", new_name);
        return -1;
    }

    if(rename(original_name, new_name) != 0) {
        printf("Error renaming '%s' file or folder.\n", original_name);
        return -1;
    }

    return 0;
}

int copy_to_curr_dir(InputBuffer *buffer) {
    FILE *fptr1, *fptr2;
    
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";

    char *command = strtok(string, delimiter);
    char *original_name = strtok(NULL, delimiter);
    char *dst_file_name = strtok(NULL, delimiter);
    
    int c;

    fptr1 = fopen(original_name, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s\n", original_name);
        return -1;
    }

    if(access(dst_file_name, F_OK) == 0) {
        printf("File or folder '%s' already exists.\n", dst_file_name);
        return -1;
    }

    fptr2 = fopen(dst_file_name, "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s\n", dst_file_name);
        fclose(fptr1);
        return -1;
    }

    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

void print_help() {
    printf("\nAvailable Commands:\n");
    printf("--------------------------------------------------\n");
    printf("ls [path]\n");
    printf("    List the contents of the current directory.\n");
    printf("    Optionally specify a path to list that directory's contents.\n\n");

    printf("cd <path>\n");
    printf("    Change the current working directory to the specified path.\n\n");

    printf("mkdir <folder_name>\n");
    printf("    Create a new directory with the specified name.\n\n");

    printf("touch <file_name>\n");
    printf("    Create a new empty file, or update the timestamp of an existing file.\n\n");

    printf("rm <path>\n");
    printf("    Remove a file or directory.\n");
    printf("    If a directory is specified, it will be removed recursively.\n\n");

    printf("cp <source_file> <destination_file>\n");
    printf("    Copy a file to a new file in the current directory.\n\n");

    printf("mv <original_name> <new_name>\n");
    printf("    Rename a file or directory.\n\n");

    printf("help\n");
    printf("    Display this help message.\n\n");

    printf("exit\n");
    printf("    Exit the CLI application.\n");
    printf("--------------------------------------------------\n\n");
}