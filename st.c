#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef char *string;

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

void create_files(int n, string lang);

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Error: not 2 arguments\nUsage: ./qc [x] [lang]\n\tx: int - 1..26 - the number of problems\n\tlang: string - c or cpp or py\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    string lang = argv[2];

    create_files(n, lang);

    return 0;
}

void create_files(int n, string lang)
{
    if (n > 26 || n < 1)
    {
        printf("Error: Wrong value\nUsage: ./qc [x]\n\tx: int - 1..26 - the number of problems\n");
        exit(1);
    }

    char stub_filename[10];
    if (strcmp(lang, "c") == 0)
    {
        sprintf(stub_filename, "stub.c");
    }
    else if (strcmp(lang, "cpp") == 0)
    {
        sprintf(stub_filename, "stub.cpp");
    }
    else if (strcmp(lang, "py") == 0)
    {
        sprintf(stub_filename, "stub.py");
    }
    else
    {
        printf("Error: No stub for specified language\nUsage: ./qc [x] [lang]\n\tlang: str - c or cpp or py\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        // Open the stub file
        FILE *stub_file = fopen(stub_filename, "r");
        if (stub_file == NULL)
        {
            printf("Could not open file %s\n", stub_filename);
            exit(1);
        }

        // Get the size of the stub file
        fseek(stub_file, 0, SEEK_END);
        long stub_size = ftell(stub_file);
        rewind(stub_file);

        // Read the contents of the stub file
        char *stub_contents = malloc(stub_size + 1);
        if (stub_contents == NULL)
        {
            printf("Could not allocate memory for stub contents\n");
            exit(1);
        }
        fread(stub_contents, 1, stub_size, stub_file);
        stub_contents[stub_size] = '\0'; // Null-terminate the string

        fclose(stub_file);

        char filename[10];
        sprintf(filename, "%c.%s", alphabet[i], lang);
        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Could not open file %s\n", filename);
            exit(1);
        }

        // Write the stub contents to the file
        fprintf(fp, "%s", stub_contents);

        fclose(fp);

        free(stub_contents); // Free the allocated memory
    }

    remove(stub_filename); // Remove the stub file
}