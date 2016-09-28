/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)                          // Проверка количества элементов массива
        return false;

    int bot = 0, top = n, mid;          // Переменные для смещения в массиве

    while (bot <= top) {

    mid = (bot + top)/2;                // Нахождение средины диапазона поиска в массиве

    if (values[mid] == value)           // Смотрим в центр диапазона
        return true;

    if (values[mid] > value)            // Смещаем диапазон влево
        top = mid-1;

    if (values[mid] < value)            // Смещаем диапазон вправо
        bot = mid + 1;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int p;
    for (int i = 0; i < n-1; i++){
        int min = i;                            // Переменная для содержания индекса минимального значения в массиве
        for (int j = i+1; j < n; j++) {
            if (values[j] < values[min])        // Нахождение минимального элемента массива 
                min = j;
        }
        if (min != i) {                         // Если найден элемент в массиве меньший за элемент в последовательности меняем их местами
            p = values[min];
            values[min] = values[i];
            values[i] = p;
        }
    }
    return;
}

