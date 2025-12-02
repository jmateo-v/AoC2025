#ifndef ID_FILTER_H
#define ID_FILTER_H
#define INITIAL_SIZE 32
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_input_data
{
    long long lowest;
    long long highest;
    size_t len_lowest;
    size_t len_highest;
} t_input_data;

char *read_token(FILE *input);
t_input_data *parse_token(const char *token);
long long smallest_even_length(long long new_len);
bool first_half_bigger(char *first_half, char *second_half);
size_t digit_count(long long n);

#endif