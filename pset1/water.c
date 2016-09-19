#include <stdio.h>
#include <stdlib.h>

int main() {

    int min = 0;                                // Переменная, в которую поступает входное число
    int bottles = 0;

    do {                                        // Проверка входного числа
        printf("Minutes integer:\n");
        scanf("%d", &min);
    }
    while(min < 1);

    bottles = 192*min/16;                       // Вычисление количества бутылок

    printf("Bottles:%d\n", bottles);            // Вывод результата
    return 0;
}
