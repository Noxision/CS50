#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check (int , char* []);                                 // Проверка кодового слова условию задачи
int k_smesheniya (char* [], int);                           // Вычисление смещения
int get_numb_of_crypto_char(int , char [], int, int);       // Вычисление индекса зашифрованного символа

int main(int argc, char* argv[]){

    int array_size = 100;                           // Размер массива вводимого текста

    if(check(argc, argv))                           // Проверка на количество аргументов и соответствие латинскому алфавиту
        return 1;

    printf("plaintext: \n");                        // Ввод текста для шифрования
    //printf("%s\n", argv[1]);


    char text[array_size];
    fgets( text, array_size, stdin );               // Ввод текста для шифрования

    int i, j, k, p = 0;
    for (i = 0 ; i < strlen(text); i++){            // Цикл движения по массиву
        int numb_c;                                 // Переменная с номером зашифрованного символа
        if (isalpha(text[i])){                      // Проверка на соответствие символов вводимой строки латинскому алфавиту
            j = p%strlen(argv[1]);                  // Получение индекса знаков кодового слова

            k = k_smesheniya(argv, j);              // Вычисление коэфициента смещения символа оригинальной строки

            if (isupper(text[i]))                                       // Проверка на заглавную букву
                numb_c = get_numb_of_crypto_char(k, text, i, 64);       // Вычисление индекса зашифрованного символа
            else
                numb_c = get_numb_of_crypto_char(k, text, i, 96);

            p++;                                                                            // Увеличение индекса массива кодового слова для следующей итерации
            //printf("char %c - %d | %c | k = %d\n", text[i], text[i], argv[1][j], k);      // Проверка контрольных значений оригинальной строки
            text[i] = numb_c;
            //printf("char %c - %d | %c \n", text[i], text[i], argv[1][j]);                 // Проверка контрольных значений зашифрованной строки
        }

    }

    printf("%s", text);

  return 0;
}

int get_numb_of_crypto_char(int k, char x[], int i, int z){
    int calc = x[i] - z + k;
    if (calc != 26)
        calc = ((x[i]-z)+k)%26;
    return calc + z;
}

int k_smesheniya (char* x[], int y){
    int k;
    if (isupper(x[1][y]))
        return k = x[1][y] - 65;
    else
        return k = x[1][y] - 97;

}

int check (int y, char* x[]){
    if (y!=2)
        return 1;
    int i;
    for (i = 0; i < strlen(x[1]); i++)
        if (isalpha(x[1][i]) == 0)
            return 1;
        return 0;
}
