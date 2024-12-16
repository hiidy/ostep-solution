#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 512

int main(int argc, char *argv[]) {
    FILE *fp = NULL;

    if (argc == 1) {
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char buffer[MAX_LEN];
        fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }

        while (fgets(buffer, MAX_LEN, fp)) {
            printf("%s", buffer);
        }
        fclose(fp);
    }

    return 0;
}