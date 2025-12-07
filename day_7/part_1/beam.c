#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 142
#define COLS 142

void beam(char grid[ROWS][COLS])
{
    for (int i = 1; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if (grid[i][j] == '.' && grid[i - 1][j] == 'S')
                grid[i][j] = '|';
            if (grid[i][j] == '|')
            {
                if (grid[i+1][j] == '^')
                {
                    if (grid[i + 1][j - 1])
                        grid[i + 1][j - 1] = '|';
                    if (grid[i + 1][j + 1])
                        grid[i + 1][j + 1] = '|';
                }
                else if (grid[i+1][j] == '.')
                    grid[i + 1][j] = '|';
            }
        }
    }
}
int check_split(char grid[ROWS][COLS])
{
    int split = 0;
    for (int i = 1; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j] == '^' && grid[i - 1][j] == '|')
                split++;
        }
    }
    return (split);
}
int main(void)
{
    FILE *input = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int rows = 0;
    char gridmap[ROWS][COLS];
    int total = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        line[strcspn(line, "\n")] = '\0';
        strncpy(gridmap[rows], line, COLS-1);
        gridmap[rows][COLS-1] = '\0';
        rows++;
    }
    free(line);
    fclose(input);
    beam(gridmap);
    total = check_split(gridmap);
    printf("Total is %d\n", total);

    return 0;
}