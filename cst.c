#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // For error reporting

// --- Function Prototypes ---
void create_files(int n, const char *lang, const char *mode);
char *read_template(const char *lang, long *file_size);

// --- Main ---
int main(int argc, char *argv[])
{
    // Check for the correct number of arguments
    if (argc != 4)
    {
        // Print a more detailed usage message
        fprintf(stderr, "Usage: %s <num_problems> <language_extension> <mode>\n", argv[0]);
        fprintf(stderr, "Example: %s 5 cpp letters\n", argv[0]);
        fprintf(stderr, "  <num_problems>: An integer from 1 to 26.\n");
        fprintf(stderr, "  <language_extension>: The file extension (e.g., c, cpp, py).\n");
        fprintf(stderr, "  <mode>: letters, digits, or both.\n");
        return 1; // Use return 1 for error
    }

    // Use strtol for safer string-to-integer conversion
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);

    // Check if the conversion was successful and the value is in range
    if (endptr == argv[1] || *endptr != '\0' || n < 1 || n > 26)
    {
        fprintf(stderr, "Error: Invalid number of problems. Must be an integer between 1 and 26.\n");
        return 1;
    }

    const char *lang = argv[2];
    const char *mode = argv[3];

    create_files((int)n, lang, mode);

    return 0;
}

/**
 * @brief Reads the content of the specified template file into a buffer.
 *
 * @param lang The language extension (e.g., "c", "cpp") to find the template.
 * @param file_size Pointer to a long to store the size of the file.
 * @return A dynamically allocated buffer with the file contents, or NULL on error.
 * The caller is responsible for freeing this buffer.
 */
char *read_template(const char *lang, long *file_size)
{
    char path_buffer[1024];
    const char *home_dir = getenv("HOME");

    // Handle cases where HOME environment variable might not be set
    if (home_dir == NULL)
    {
        fprintf(stderr, "Error: Could not resolve HOME directory.\n");
        return NULL;
    }

    // Construct the full path to the template file
    // snprintf is safer than sprintf as it prevents buffer overflows.
    snprintf(path_buffer, sizeof(path_buffer), "%s/cst/templates/template.%s", home_dir, lang);

    FILE *template_file = fopen(path_buffer, "r");
    if (template_file == NULL)
    {
        // perror provides a more descriptive error message (e.g., "No such file or directory")
        fprintf(stderr, "Error opening template file '%s': ", path_buffer);
        perror("");
        return NULL;
    }

    // Get the size of the template file
    fseek(template_file, 0, SEEK_END);
    *file_size = ftell(template_file);
    rewind(template_file);

    if (*file_size <= 0)
    {
        fprintf(stderr, "Error: Template file is empty or cannot be read.\n");
        fclose(template_file);
        return NULL;
    }

    // Allocate memory for the template contents (+1 for the null terminator)
    char *template_contents = malloc(*file_size + 1);
    if (template_contents == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for template.\n");
        fclose(template_file);
        return NULL;
    }

    // Read the file. Note the corrected parameters for fread.
    // We read *file_size items of 1 byte each.
    size_t bytes_read = fread(template_contents, 1, *file_size, template_file);
    if (bytes_read != (size_t)*file_size)
    {
        fprintf(stderr, "Error: Failed to read the entire template file.\n");
        free(template_contents);
        fclose(template_file);
        return NULL;
    }

    // IMPORTANT: Null-terminate the buffer after reading.
    template_contents[*file_size] = '\0';

    fclose(template_file);
    return template_contents;
}

/**
 * @brief Creates N new files based on the template content.
 *
 * @param n The number of files to create (1-26).
 * @param lang The language extension for the new files.
 * @param mode The mode for naming files: "letters", "digits", or "both".
 */
void create_files(int n, const char *lang, const char *mode)
{
    long template_size = 0;
    char *template_contents = read_template(lang, &template_size);

    if (template_contents == NULL)
    {
        exit(1);
    }

    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Creating %d file(s) with extension '.%s' in %s mode...\n", n, lang, mode);

    for (int i = 0; i < n; i++)
    {
        char filename[32];
        if (strcmp(mode, "l") == 0) // letters
        {
            snprintf(filename, sizeof(filename), "%c.%s", alphabet[i], lang);
        }
        else if (strcmp(mode, "d") == 0) // digits
        {
            snprintf(filename, sizeof(filename), "%d.%s", i + 1, lang);
        }
        else if (strcmp(mode, "ld") == 0) // letter+digit
        {
            snprintf(filename, sizeof(filename), "%c%d.%s", alphabet[i], i + 1, lang);
        }
        else
        {
            fprintf(stderr, "Unknown mode '%s'. Use 'l', 'd', or 'ld'.\n", mode);
            free(template_contents);
            exit(1);
        }

        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            fprintf(stderr, "Could not create file '%s'. Skipping.\n", filename);
            continue;
        }
        fputs(template_contents, fp);
        fclose(fp);
        printf(" -> Created %s\n", filename);
    }

    free(template_contents);
    printf("Done.\n");
}
