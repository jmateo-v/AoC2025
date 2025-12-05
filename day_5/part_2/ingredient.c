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

long long check_ingredient(t_range *range)
{
    if (!range)
        return 0;

    long long total = 0;
    long long current_lower = range->lower;
    long long current_upper = range->upper;

    t_range *cur = range->next;
    while (cur)
    {
        if (cur->lower <= current_upper + 1)
        {
            if (cur->upper > current_upper)
                current_upper = cur->upper;
        }
        else
        {
            total += (current_upper - current_lower + 1);
            current_lower = cur->lower;
            current_upper = cur->upper;
        }
        cur = cur->next;
    }
    total += (current_upper - current_lower + 1);
    return total;
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
            break;
    }
    sort_ranges(&range);
    fresh += check_ingredient(range);
    printf("Number of fresh ingredients %lld\n", fresh);
    free(line);
    free_range(range);
    fclose(input);
    return 0;
}