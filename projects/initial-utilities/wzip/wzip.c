#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int cur;
    int count = 0;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        int next;
        fp = fopen(argv[i], "r");

        if (i == 1) {
            cur = fgetc(fp);
            count = 1;
        }

        while ((next = fgetc(fp)) != EOF) {
            if (next == cur) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(cur, stdout);
                count = 1;
                cur = next;
            }
        }
        fclose(fp);
    }
    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(cur, stdout);
    }

    return 0;
}