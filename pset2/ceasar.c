#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_ASCII(int, int, char);

const int array_size = 100;                         // Размер массива вводимого текста

int main(int argc, char** argv){

    if(argc!=2){                                     // Проверка на количество аргументов
        printf ("usage : ./caesar + k\n");
        return 1;
    }

    int k = atoi(argv[1]);                          // Преобразование аргумента в число

    printf("plaintext: ");

    char text[array_size];
    fgets(text, array_size, stdin);                 // Ввод текста для шифрования

    for (int i = 0, n = strlen(text); i < n; i++){  // Цикл перебора элементов вводимого текста
        if (isalpha(text[i])){                      // Проверка элементов на соответствие латинскому алфавиту
            int numb_c;                             // Переменная для записи номера ASCII зашифрованного элемента
            if (isupper(text[i]))                   // Проверка на заглавные буквы
                numb_c = get_ASCII(64, k, text[i]); // Получение зашифрованного элемента
            else
                numb_c = get_ASCII(96, k, text[i]);
            text[i] = numb_c;                       // Перезапись элемента в строку
        }
    }

    printf("ciphertext: %s", text);                 // Вывод новой строки
}

int get_ASCII (int x, int k, char y){               // Функция получения номера зашифрованного элемента
    int calc = y-x+k;
    if (calc == 26)
        return y+k;
    return (((y-x)+k)%26)+x;
}
