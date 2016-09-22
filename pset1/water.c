#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main() {

    int min = 0, bottles = 0;

    printf("Minutes integer:\n");
    min = get_int();

    bottles = 192*min/16;

    printf("Bottles:%d\n", bottles);
}
