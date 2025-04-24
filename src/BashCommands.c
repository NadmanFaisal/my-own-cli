#include <dirent.h>

#include "BashCommands.h"

void list_dir() {
    DIR *dir = opendir(".");
    while(dir) {
        struct dirent *dp;
        if ((dp = readdir(dir)) != NULL) {
            printf("%s  ", dp->d_name);
        } else {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
    }
    closedir(dir);
}