#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int handle_rotation(char *line, int curr_pos)
{
    char direction = line[0];
    int rotation = atoi(&line[1]);
    while (rotation >= 100)
        rotation -= 100;
    if (direction == 'R')
        curr_pos = (curr_pos + rotation) % 100;
    else if (direction == 'L')
        curr_pos = (curr_pos - rotation + 100) % 100;
    return (curr_pos);
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    char* line = NULL;
    int curr_pos = 50;
    int password_val = 0;
    ssize_t read;
    size_t len = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        curr_pos = handle_rotation(line, curr_pos);
        if (curr_pos == 0)
            password_val++;
    }
    printf("pass is %d\n", password_val);
    free(line);
    fclose(input);
    return(0);
}