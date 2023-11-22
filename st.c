#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef char *string;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char fpth[] = "/usr/local/bin/stubs/stub.";

void create_files(int n, string lang);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error: not 2 arguments\nUsage: st [x] [lang]\n\tx: int - 1..26 - the number of problems\n\tlang: str - c, cpp, java, py\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    char lang[5];

    strncpy(lang, argv[2], 4);

    create_files(n, lang);

    return 0;
}

void create_files(int n, char lang[])
{
    if (n > 26 || n < 1)
    {
        printf("Error: Wrong value\nUsage: ./st [x]\n\tx: int - 1..26 - the number of problems\n");
        exit(1);
    }

    char stub_file_ptr[32];

    sprintf(stub_file_ptr, "%s%s", fpth, lang);

    FILE *stub_file = fopen(stub_file_ptr, "r");
    if (stub_file == NULL)
    {
        printf("Could not open file %s\n", stub_file_ptr);
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

    for (int i = 0; i < n; i++)
    {
        char filename[7];
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
    }

    free(stub_contents); // Free the allocated memory
}