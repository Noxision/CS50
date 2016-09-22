#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cs50.h>
void coins_count (int, int, int, int, int [], int*);

int main() {
    int array[4] = {[0] = 25, [1] = 10, [2] = 5, [3] = 1};  // An array of denominations of coins from highest to lowest
    float in;                                               // The variable that contains the input number
    int coins = 0;                                          // The variable that will contain the result
    int* pointer = &coins;

    do {                                                    // Check the input number
        printf("How much change is owed?\n");
        in = get_float();
    }
    while(in <= 0);

    int greedy = roundf(in*100);                            // Convert number into natural
    int rest = 1;                                           // The variable that contains the remainder of the division ( to start the cycle needs any numeric initial value ! = 0 )
    int i = 0;                                              // The variable for walking through the array in loop

    coins_count (i, rest, greedy, coins, array, pointer);   // Calculate the number of coins

    printf("%d\n", coins);                                  // Output result
}

void coins_count (int i, int rest, int greedy, int coins, int array[], int* pointer) {

    if (rest == 0) {                                        // Condition of the termination
        *pointer = coins;
        return;
    }

    rest = greedy%array[i];                                 // Getting the remainder of the division
    coins += (greedy-rest)/array[i];                        // Calculating the number of coins
    greedy = rest;                                          // Changing the value of the input for the next iteration
    i++;
    coins_count(i, rest, greedy, coins, array, pointer);
}
