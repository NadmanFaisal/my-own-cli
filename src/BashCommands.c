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
        printf("%s  ", dp->d_name);
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
