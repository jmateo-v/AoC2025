#ifndef JOLTAGE_H
#define JOLTAGE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_input_data
{
    size_t len;
    char highest_val;
    char second_highest;
    int highest_index;
    bool is_last;
}   t_input_data;

t_input_data *parse_line(char *line);
#endif