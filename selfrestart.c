#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void restart(const Arg *arg) {
    char *argv[2] = {"dwm", NULL};
    printf("%s\n", argv[0]);
    if(argv[0] == NULL) {
        printf("error\n");
        return;
    }
    execvp(argv[0], argv);
}
