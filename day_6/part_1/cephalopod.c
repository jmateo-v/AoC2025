#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 1000

long long get_result(long long matrix[ROWS][COLS], char *ops)
{
    long long total = 0;

    for (int j = 0; j < COLS; j++)
    {
        long long value;
        if (ops[j] == '+')
        {
            value = 0;
            for (int i = 0; i < ROWS; i++)
                value += matrix[i][j];
        }
        else if (ops[j] == '*')
        {
            value = 1;
            for (int i = 0; i < ROWS; i++)
                value *= matrix[i][j];
        }
        else
        {
            value = 0;
        }
        total += value;
    }
    return total;
}

int main(void)
{
    long long total = 0;
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
        printf("Invalid file.\n");
        return(1);
    }
    long long matrix[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (fscanf(input, "%lld", &matrix[i][j]) != 1)
            {
                printf("Error reading number at [%d][%d]\n", i, j);
                fclose(input);
                return (1);
            }
        }
    }
    char ops[COLS];
    for (int j = 0; j < COLS; j++)
        fscanf(input, " %c", &ops[j]);

    total = get_result(matrix, ops);
    printf("Final result is %lld\n", total);
    fclose(input);
    return (0);
}
