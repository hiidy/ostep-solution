#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: file1 [file2 ...]\n");
            exit(EXIT_FAILURE);
        }
        int count = 0;
        char character;
        while (fread(&count, sizeof(int), 1, fp) == 1) {
            if (fread(&character, sizeof(char), 1, fp) != 1) {
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j < count; j++) {
                printf("%c", character);
            }
        }
        fclose(fp);
    }
}