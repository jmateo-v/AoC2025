#include "forklift.h"

int in_bounds(int i, int j)
{
    return (i >= 0 && i < ROWS && j >= 0 && j < COLUMNS);
}

int check_forklift(char grid[ROWS][COLUMNS])
{
    int total = 0;
    int di[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dj[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLUMNS; j++) 
        {
            if (grid[i][j] == '@')
            {
                int adjacent = 0;
                for (int k = 0; k < 8; k++)
                {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (in_bounds(ni, nj))
                    {
                        if (grid[ni][nj] == '@')
                            adjacent++;
                    }
                }
                if (adjacent < 4)
                {
                    grid[i][j] = '.';
                    total++;
                }
            }
        }
    }

    return total;
}

int main(void)
{
    int valid = 0;
    FILE *input = fopen("input.txt", "r");
    if (!input)
        return(perror("fopen"), 1);
    char gridmap[ROWS][COLUMNS];
    int rows = 0;
    int cols = 0;
    char line[COLUMNS + 2];
    while (rows < ROWS && fgets(line, sizeof(line), input))
    {
        line[strcspn(line, "\n")] = '\0';
        cols = COLUMNS;
        for (int j = 0; j < cols; j++)
        {
            gridmap[rows][j] = line[j];
        }
        rows++;
    }
    int i = 0;
    while((i = check_forklift(gridmap)) > 0)
        valid += i;
    printf("Total accesible rolls by forklift: %d\n", valid);
    fclose(input);
    return (0);
}