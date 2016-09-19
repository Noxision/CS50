
#include <stdio.h>
#include <stdlib.h>

int main() {
    int height;                                             // Переменная, в которую поступает входное число

    do {                                                    // Проверка входного числа согласно условию задания (1 <= x <= 23)
        printf("Give me a number between 1 and 23:\n");
        scanf("%d", &height);
    }
    while(height < 1 || height > 23);

    int i;
    for( i = 0; i < height; i++){                           // Цикл количества строк (высота полупирамиды)

        int j;
        for( j = 0; j < height-i; j++)                      // Цикл вывода пробелов в строке
            printf(" ");

        int k;
        for( k = i; k >= 0; k--)                            // Цикл вывода # в строке
            printf("#");

        printf("#\n");                                      // Вывод дополнительного # для обеспечения платформы на верху полупирамиды и переход на новую строку
    }
    return 0;
}

