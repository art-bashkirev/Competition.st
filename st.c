#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef char *string;

const string alphabet = "abcdefghijklmnopqrstuvwxyz";
const string fpth = "/usr/local/bin/stubs/stub.";

void create_files(int n, string lang);

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Error: not 2 arguments\nUsage: st [x] [lang]\n\tx: int - 1..26 - the number of problems\n\tlang: str - c, cpp, java, py\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    string lang = argv[2];

    printf("Starting");

    create_files(n, lang);

    return 0;
}

void create_files(int n, string lang)
{
    if (n > 26 || n < 1)
    {
        printf("Error: Wrong value\nUsage: ./st [x]\n\tx: int - 1..26 - the number of problems\n");
        exit(1);
    }

    printf("Allocating stub_file_ptr...");
    string stub_file_ptr = malloc(strlen(fpth) + strlen(lang) + 32);
    if (stub_file_ptr == NULL) {
        printf("Could not allocate memory for stub file pointer\n");
        exit(1);
    }
    printf("Copying fpth to stub_file_ptr...");
    strcpy(stub_file_ptr, fpth);
    printf("Appending the file extension to stub_file_ptr...");
    strcat(stub_file_ptr, lang);

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
        string filename = "", tmp = "";
        sprintf(tmp, "%c.%s", alphabet[i], lang);
        strcpy(filename, tmp);
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