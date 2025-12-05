#include "ingredient.h"

#include <stdio.h>

int is_range(char *line)
{
    if (!line || *line == '\0')
        return(-1);
    while(*line)
    {
        if (*line == '-')
            return(1);
        line++;
    }
    return(0);
}

long long check_ingredient(char *line, t_range *range)
{
    long long id = atoll(line);
    while(range != NULL)
    {
        if(id >= range->lower && id <= range->upper)
            return(1);
        range = range->next;    
    }
    return (0);
}

int main (void)
{
    long long fresh = 0;
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
        printf("Invalid file.\n");
        return (1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    t_range *range = NULL;

    while ((read = getline(&line, &len, input)) != -1)
    {
        line[strcspn(line, "\n")] = '\0';
        if(is_range(line) == -1)
            continue;
        else if(is_range(line))
            range = add_range(range, line);
        else
            fresh += check_ingredient(line, range);
    }
    printf("Number of fresh ingredients %lld\n", fresh);
    free(line);
    free_range(range);
    fclose(input);
    return 0;
}