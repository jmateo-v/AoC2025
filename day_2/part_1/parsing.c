#include "id_filter.h"


size_t digit_count(long long n)
{
    size_t len = 0;

    if (n == 0)
        return 1;
    if(n < 0)
        n *= -1;
    while (n > 0)
    {
        len++;
        n /= 10;
    }
    return len;
}

char *read_token(FILE *input)
{
    size_t size = INITIAL_SIZE;
    size_t len = 0;
    char *buf = malloc(size);
    if (!buf)
        return NULL;
    
    int c;
    while((c = fgetc(input)) != EOF)
    {
        if (c == ',')
            break;
        if (len + 1 >= size)
        {
            size *=2;
            char *tmp = realloc(buf, size);
            if (!tmp)
            {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0 && c == EOF)
    {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}
t_input_data *parse_token(const char *token)
{
    long long lowest, highest;

    if (sscanf(token, "%lld-%lld", &lowest, &highest) != 2)
    {
        printf("parse failed\n");
        return NULL;
    }
    t_input_data *node = malloc(sizeof(*node));
    node->lowest = lowest;
    node->highest = highest;
    node->len_lowest = digit_count(lowest);
    node->len_highest = digit_count(highest);
    return node;
}