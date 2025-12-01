#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int handle_rotation(char *line, int curr_pos, int *password_val)
{
    char direction = line[0];
    int rotation = atoi(&line[1]);

    while (rotation >= 100)
    {
        (*password_val)++;
        rotation -= 100;
    }
    
    if (direction == 'R')
    {
        while (rotation--)
        {
            curr_pos++;
            if (curr_pos == 100)
            {
                curr_pos = 0;
                (*password_val)++;
            }
        }
    }
    else if (direction == 'L')
    {
        while (rotation--)
        {
            curr_pos--;
            if (curr_pos < 0)
                curr_pos = 99;
            if (curr_pos == 0)
                (*password_val)++;
        }
    }
    return curr_pos;
}


int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
        printf("invalid file.\n");
        return(1);
    }
    char* line = NULL;
    int curr_pos = 50;
    int password_val = 0;
    ssize_t read;
    size_t len = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        curr_pos = handle_rotation(line, curr_pos, &password_val);
    }
    printf("curr pos is %d\n", curr_pos);
    printf("pass is %d\n", password_val);
    free(line);
    fclose(input);
    return(0);
}