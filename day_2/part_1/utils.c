#include "id_filter.h"

long long smallest_even_length(long long new_len)
{
    long long n = 1;
    for (long long i = 0; i < new_len; i++)
        n *= 10;
    return n;
}
bool first_half_bigger(char *first_half, char *second_half)
{
    if (atoll(first_half) >= atoll(second_half))
        return(1);
    return (0);
}