#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char *get_dwm_path() {
    char *buf = NULL;
    int r,
        len = 1,
        inc = 32;

    do {
        len += inc;
        free(buf);
        buf = malloc(sizeof(char) * len);
        if (buf == NULL) {
            perror("malloc");
            return NULL;
        }
        r = readlink("/proc/self/exe", buf, len);
        if (r == -1) {
            perror("readlink");
            return NULL;
        }
    } while(r >= len);
    buf[r] = '\0';
    return buf;
}

void restart(const Arg *arg) {
    char *const argv[] = {get_dwm_path(), NULL};
    printf("%s\n", argv[0]);
    if(argv[0] == NULL) {
        printf("error\n");
        return;
    }
    execvp(argv[0], argv);
}
