#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10000

typedef char *string;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char fpth[] = "~/cst/templates/template.";

void create_files(int n, char lang[]);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error: not 2 arguments\nUsage: cst [x] [lang]\n\t"
               "x: int - 1..26 - the number of problems\n\t"
               "lang: str - e.g. c, cpp\n");
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

    unsigned long template_file_path_size = strlen(fpth) + strlen(lang);
    string template_file_path = malloc(template_file_path_size + 1);

    sprintf(template_file_path, "%s%s", fpth, lang);

    FILE *template_file = fopen(template_file_path, "r");

    if (template_file == NULL)
    {
        printf("Could not open file %s\n", template_file_path);
        exit(1);
    }
    free(template_file_path);

    // Get the size of the template file
    fseek(template_file, 0, SEEK_END);
    unsigned long template_size = ftell(template_file);
    rewind(template_file);

    // Read the contents of the template file
    if (template_size == 0 || template_size + 1 == 0) // SonarLint tricks
    {
        printf("Memory for template contents not properly allocated");
        exit(1);
    }

    string template_contents = malloc(template_size + 1);

    fread(template_contents, MAXLEN, template_size, template_file);

    fclose(template_file);

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

        fputs(template_contents, fp);

        fclose(fp);
        free(filename);
    }

    free(template_contents);
}
