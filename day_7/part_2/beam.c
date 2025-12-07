#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 142
#define COLS 142

long long memo[ROWS][COLS];

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

int find_s(char gridmap[ROWS][COLS])
{
    for (int i = 0; i < COLS; i++)
    {
        if (gridmap[0][i] == 'S')
            return(i);
    }
    return(0);
}

long long explore(char grid[ROWS][COLS], int i, int j)
{

    char cell = grid[i][j];

    if (cell == '.')
        return 0;

    if (i == ROWS - 1)
        return 1;

    if (memo[i][j] != -1)
        return memo[i][j];
    long long result = 0;
    if (cell == '^') 
    {
        long long left = explore(grid, i + 1, j - 1);
        long long right = explore(grid, i + 1, j + 1);
        memo[i][j] = left + right;
        return memo[i][j];
    }

    if (cell == 'S' || cell == '|')
        result = explore(grid, i + 1, j);
    memo[i][j] = result;
    return result;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int rows = 0;
    char gridmap[ROWS][COLS];
    long long total = 0;

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
            memo[r][c] = -1;
    }
    
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
    int s = 0;
    s = find_s(gridmap);
    total = explore(gridmap, 0, s);
    printf("Total is %lld\n", total);
    return 0;
}