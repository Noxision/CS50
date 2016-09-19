#include <stdio.h>
#include <stdlib.h>
int coins_count (int, int, int, int, int []);

int main() {
    int array[4] = {[0] = 25, [1] = 10, [2] = 5, [3] = 1}; // Массив с номиналами монет от большего к меньшему
    float in;                                              // Переменная, в которую поступает входное число
    int coins = 0;                                         // Переменная, которая будет содержать результат

    do {                                                   // Проверка входного числа на положительный знак
        printf("How much change is owed?\n");
        scanf("%f", &in);
    }
    while(in <= 0);

    int greedy = in*100;                                   // Преобразовываем число в натуральное
    int rest = 1;                                          // Переманная, которая содержит в себе остаток от деления (для запуска цикла любое числовое начальное значение != 0)
    int i = 0;                                             // Переменная для пересчёта ячеек массива

    coins = coins_count (i, rest, greedy, coins, array);   // Вычисляем количество монет

    /*while(rest != 0){                                    // Цикл в котором происходят основные расчёты
        rest = greedy%array[i];                            // Получаем остаток от деления
        coins += (greedy-rest)/array[i];                   // Вычисление количества монет
        greedy = rest;                                     // Изменение значение входного числа для следующей итерации
        i++;                                               // Переход к следующей ячейке массива в следующей итерации
    }*/

    printf("Coins: %d\n", coins);                          // Вывод результата
    return 0;
}

int coins_count (int i, int rest, int greedy, int coins, int array[]) {
    if (rest == 0)
        return coins;
    rest = greedy%array[i];                            // Получаем остаток от деления
    coins += (greedy-rest)/array[i];                   // Вычисление количества монет
    greedy = rest;                                     // Изменение значение входного числа для следующей итерации
    i++;
    //printf("%d, %d, %d", i, rest, coins);
    coins_count(i, rest, greedy, coins, array);
}
