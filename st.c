#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10000

typedef char *string;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char fpth[] = "/usr/local/bin/stubs/stub.";

void create_files(int n, char lang[]);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error: not 2 arguments\nUsage: st [x] [lang]\n\t"
               "x: int - 1..26 - the number of problems\n\t"
               "lang: str - e.g. c, cpp, "
               "java, py\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    char lang[strlen(argv[2]) + 1];

    strncpy(lang, argv[2], 4);

    create_files(n, lang);

    return 0;
}

void create_files(int n, char lang[])
{
    // Checks
    if (n < 1 || n > 26)
    {
        printf("Error: Wrong value\nx: int - 1..26 - the number of problems\n");
        exit(1);
    }

    unsigned long stub_file_path_size = strlen(fpth) + strlen(lang);
    string stub_file_path = malloc(stub_file_path_size + 1);

    sprintf(stub_file_path, "%s%s", fpth, lang);

    FILE *stub_file = fopen(stub_file_path, "r");

    if (stub_file == NULL)
    {
        printf("Could not open file %s\n", stub_file_path);
        exit(1);
    }
    free(stub_file_path);

    // Get the size of the stub file
    fseek(stub_file, 0, SEEK_END);
    unsigned long stub_size = ftell(stub_file);
    rewind(stub_file);

    // Read the contents of the stub file
    if (stub_size == 0 || stub_size + 1 == 0) // SonarLint tricks
    {
        printf("Memory for stub contents not properly allocated");
        exit(1);
    }

    string stub_contents = malloc(stub_size + 1);

    fread(stub_contents, MAXLEN, stub_size, stub_file);

    fclose(stub_file);

    for (int i = 0; i < n; i++)
    {
        string filename = malloc(MAXLEN);

        sprintf(filename, "%c.%s", alphabet[i], lang);

        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Could not open file %s\n", filename);
            free(filename);
            continue;
        }

        fputs(stub_contents, fp);

        fclose(fp);
        free(filename);
    }

    free(stub_contents);
}
