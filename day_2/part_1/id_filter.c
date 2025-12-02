#include "id_filter.h"

long long find_valid(long long lowest, size_t len_lowest)
{
    long long valid = 0;
    if (len_lowest % 2 != 0)
    {
        lowest = smallest_even_length(len_lowest + 1);
        len_lowest++;
    }
    char buf[len_lowest + 1];
    snprintf(buf, sizeof(buf), "%lld", lowest);
    char *tmp = strdup(buf);
    if (!tmp)
        return(-1);
    char *first_half, *second_half;
    first_half = malloc((len_lowest / 2) + 1);
    second_half = malloc((len_lowest / 2) + 1);
    if (!first_half || !second_half)
        return(-1);
    first_half = strncpy(first_half, tmp, len_lowest / 2);
    first_half[len_lowest / 2] = '\0';
    second_half = strncpy(second_half, tmp + (len_lowest / 2), len_lowest / 2);
    second_half[len_lowest / 2] = '\0';

    free(tmp);
    char *chosen;
    if(first_half_bigger(first_half, second_half))
    {
        free(second_half);
        chosen = first_half;
    }
    else
    {
        free(second_half);
        long long tmp = atoll(first_half);
        tmp++;
        snprintf(buf, sizeof(buf), "%lld", tmp);
        strncpy(first_half, buf, len_lowest / 2);
        first_half[len_lowest / 2] = '\0';
        chosen = first_half;
    }
    char *joined = malloc(len_lowest + 1);
    if (!joined)
    {
        free(chosen);
        return(-1);
    }
    strcpy(joined, chosen);
    strcat(joined, chosen);
    valid = atoll(joined);
    free(chosen);
    free(joined);
    return (valid);
}
long long find_next_valid(long long lowest, size_t len_lowest)
{
    lowest += 1;
    len_lowest = digit_count(lowest);
    return(find_valid(lowest, len_lowest));
}
long long return_invalid_sum(t_input_data *data)
{
    long long sum = 0;
    
    if (data->len_lowest == data->len_highest && data->len_highest % 2 != 0)
        return(0);
    data->lowest = find_valid(data->lowest, data->len_lowest);
    if (data->lowest == -1)
        return(printf("memory allocation failed.\n") , 0);
    while(data->lowest <= data->highest)
    {
        sum += data->lowest;
        data->lowest = find_next_valid(data->lowest, data->len_lowest);
    }
    return(sum);
}
int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
        printf("invalid file\n");
        return 1;
    }
    long long sum = 0;
    char *token;
    while ((token = read_token(input)) != NULL)
    {
        t_input_data *data = parse_token(token);
        sum += return_invalid_sum(data);
        free(token);
        free(data);
    }
    printf("Invalid ID sum is:%lld\n", sum);
    fclose(input);
    return (0);
}