#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    size_t len = 0;
    const char *search_term = argv[1];

    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    if (argc == 2) {
        while (getline(&buffer, &len, stdin) != -1) {
            if (strstr(buffer, search_term) != NULL) {
                printf("%s", buffer);
            }
        }

    } else {
        FILE *fp = 0;
        for (int i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");

            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            while (getline(&buffer, &len, fp) != -1) {
                if (strstr(buffer, search_term) != NULL) {
                    printf("%s", buffer);
                }
            }
            fclose(fp);

        }
    }

    free(buffer);
    return 0;
}
