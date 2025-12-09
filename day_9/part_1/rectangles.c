#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N_COORDS 496

typedef struct coords
{
    long long x;
    long long y;
} coords;

long long rect_area(coords a, coords b)
{
    long long width  = llabs(a.x - b.x) + 1;
    long long height = llabs(a.y - b.y) + 1;
    return width * height;
}

long long max_area(coords *arr, long long n)
{
    long long max = 0;
    for (long long i = 0; i < n; i++)
    {
        for (long long j = i + 1; j < n; j++)
        {
            long long area = rect_area(arr[i], arr[j]); 
            if (area > max)
                max = area;
        }
    }
    return max;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
        return(1);
    long long x, y;
    long long i = 0;
    long long area = 0;
    coords *coord_array = malloc(sizeof(coords) * N_COORDS);
    if (!coord_array)
    {
        fclose(input);
        return(1);
    }
    while (fscanf(input, "%lld,%lld", &x, &y) == 2)
    {
        coord_array[i].x = x;
        coord_array[i].y = y;
        i++;
    }
    area = max_area(coord_array, N_COORDS);
    printf("Max area is: %lld\n", area);
    free(coord_array);
    fclose(input);
    return (0);
}