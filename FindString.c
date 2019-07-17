#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char FILE_NOT_FOUND_MSG[291] = "grep: %s: No such file or directory";
char NOT_ENOUGH_ARGS[46] = "Not enough arguments: wright at least three.";
// difference between big and small letter in ascii table is 97-65 = 32
int ASCII_DIFF = 32;

/**
 * returns 1 if there is an error in the argument.
 */
int filesError(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, NOT_ENOUGH_ARGS);
        return 1;
    }
    for (int i = 2; i < argc; ++i)
    {
        char *fileName = argv[i];
        FILE *file = fopen(fileName, "r");
        if (file == NULL)
        {
            fprintf(stderr, FILE_NOT_FOUND_MSG, fileName);
            exit(1);
        }
        fclose(file);
    }
    return 0;
}


/**
 * gets two chars and compares them. returns 1 if the chars are the same. non sensitive.
 */
int compareChar(char ch1, char ch2)
{
    if (ch1 == ch2)
    {
        return 1;
    }
// checks if the letters are the same. if one is upper and the other is lower.
    else if ((ch1 >= 'A') && (ch1 <= 'Z'))
    {
        if ((ch1 + ASCII_DIFF == ch2))
        {
            return 1;
        }
    }

    else if ((ch2 >= 'A') && (ch2 <= 'Z'))
    {
        if ((ch2 + ASCII_DIFF == ch1))
        {
            return 1;
        }

    }

    return 0;
}


/**
 * Looks for the word in the line.
 * returns 1 if it is inside, 0 otherwise.
 */
int lineCheck(char *wordToFind, char line[])
{
    unsigned int wordIndex = 0;
    unsigned int lineSearchIndex = 0;

    while ((wordIndex < strlen(wordToFind)) && (line[lineSearchIndex] != '\n')
           && (line[lineSearchIndex] != '\0'))
    {
        if (compareChar(wordToFind[wordIndex], line[lineSearchIndex]))
        {
            wordIndex++;
            lineSearchIndex++;
        }
        else
        {
            wordIndex = 0;
            lineSearchIndex++;
            // keep going until the word ends.
            while ((line[lineSearchIndex] != ' ') && (line[lineSearchIndex] != '\n')
                   && (line[lineSearchIndex] != '\0'))
            {
                lineSearchIndex++;
            }
            lineSearchIndex++;
        }
    }
    // if wordIndex == strlen(wordToFind) it means the hole word is found.
    if (wordIndex == strlen(wordToFind))
    {
        if ((compareChar(' ', line[lineSearchIndex]))
            || ((compareChar('\n', line[lineSearchIndex])))
            || ((compareChar('\0', line[lineSearchIndex]))))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


/**
 * checks if a word is in a file. checks line by line. prints without
 * the path if there only 1 file, with the path if there is more than that.
 */
void checkFile(int argc, FILE *file, char *wordToFind, char fileName[])
{
    char line[256];
    int printCheck = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (lineCheck(wordToFind, line) == 1)
        {
            if (argc == 3)
            {
                printf("%s", line);
                printCheck++;
            }
            else
            {
                printf("%s:%s", fileName, line);
            }
        }
    }
}


/**
 * main function of the program.
 */
int main(int argc, char *argv[])
{
    char *wordToFind = argv[1];
    if (filesError(argc, argv))
    {
        return 1;
    }
    else
    {
        for (int i = 2; i < argc; ++i)
        {
            char *fileName = argv[i];
            FILE *file = fopen(fileName, "r");
            checkFile(argc, file, wordToFind, fileName);
            fclose(file);
        }
    }
    return 0;
}
