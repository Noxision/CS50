#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

int main() {
    int height;                                             // The variable that contains the input number

    do {                                                    // Check the input number
        printf("height:\n");
        height = get_int();
    }
    while(height < 0 || height > 23 || isdigit(height));

    for(int i = 1; i <= height; i++){                        // The loop for number of rows

        for(int j = height - i; j > 0; j--)                  // The loop for number of spaces
            printf(" ");

        for(int k = i; k > 0; k--)                           // The loop for output "#"
            printf("#");

        printf("#\n");                                       // Output additional sign "#"
    }
}
