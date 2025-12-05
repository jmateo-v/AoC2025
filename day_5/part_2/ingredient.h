#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_range
{
    long long lower;
    long long upper;
    struct s_range *next;
} t_range;

t_range *add_range(t_range *range, const char *line);
void    free_range(t_range *head);
void    sort_ranges(t_range **head_ref);

#endif