#include "joltage.h"

int build_joltage(t_input_data *data)
{
    int units = 0;
    int tenths = 0;
    if (data->is_last)
    {
        units = data->highest_val - '0';
        tenths = data->second_highest - '0';
    }
    else
    {
        tenths = data->highest_val - '0';
        units = data->second_highest - '0';
    }
    return (10 * tenths + units);
}
int main(void)
{
    FILE *input = fopen("input.txt", "r");
    int joltage = 0;
    if (!input)
        return(printf("invalid file.\n"), 1);
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, input)) != -1)
    {
        t_input_data *data = parse_line(line);
        joltage += build_joltage(data);
        free(data);
    }
    free(line);
    printf("Sum of joltage is %d\n", joltage);
    fclose(input);
    return 0;
}