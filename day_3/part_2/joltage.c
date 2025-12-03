#include "joltage.h"

#include <string.h>

void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n')
        s[len-1] = '\0';
}

long long build_joltage(const char *digits)
{
    int len = strlen(digits);
    int invalid = len - 12;
    char stack[len];
    int highest_index = 0;

    for (int i = 0; i < len; i++)
    {
        char current = digits[i];
        while (highest_index > 0 && stack[highest_index-1] < current && invalid > 0)
        {
            highest_index--;
            invalid--;
        }
        stack[highest_index++] = current;
    }

    if (highest_index > 12)
        highest_index = 12;
    stack[highest_index] = '\0';
    
    long long joltage = atoll(stack);
    return(joltage);
}
int main(void)
{
    FILE *input = fopen("input.txt", "r");
    long long joltage = 0;
    if (!input)
        return(printf("invalid file.\n"), 1);
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, input)) != -1)
    {
        trim_newline(line);
        joltage += build_joltage(line);
        
    }
    free(line);
    printf("Sum of joltage is %lld\n", joltage);
    fclose(input);
    return 0;
}