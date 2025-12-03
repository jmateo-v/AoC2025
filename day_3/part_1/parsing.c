#include "joltage.h"

char get_highest(char *line)
{
    char current_highest = 0;
    for(int i = 0; line[i] && isdigit(line[i]); i++)
    {
        if (line[i] > current_highest)
            current_highest = line[i]; 
    }
    return(current_highest);
}
int get_highest_pos(char *line)
{
    int index = 0;
    char current_highest = 0;
    for(int i = 0; line[i] && isdigit(line[i]); i++)
    {
        if (line[i] > current_highest)
        {
            current_highest = line[i];
            index = i;
        } 
    }
    return(index);
}
char get_relevant_second(char *line, int highest_index, bool is_last)
{
    char second = 0;
    if (is_last)
    {
        for (int i = 0; i < highest_index; i++)
        {
            if (line[i] > second)
                second = line[i];
        }
    }
    else
    {
        for (int i = highest_index + 1; line[i] && isdigit(line[i]); i++)
        {
            if (line[i] > second)
                second = line[i];
        }
    }
    return(second);
}
t_input_data *parse_line(char *line)
{
    t_input_data *data = malloc(sizeof(*data));
    if (!data)
        return (NULL);
    data->len = strlen(line) - 1; //get_line grabs a \n from the file
    data->highest_val = get_highest(line);
    data->highest_index = get_highest_pos(line);
    data->is_last = false;
    if (data->len == (size_t)data->highest_index + 1)
        data->is_last = true;
    data->second_highest = get_relevant_second(line, data->highest_index, data->is_last);

    return(data);
}