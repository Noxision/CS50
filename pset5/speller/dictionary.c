/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

const int DICSIZE = 26;                                             // Размер массива указателей типа node
int diccount = 0;                                                   // Количество слов в словаре 

typedef struct node{                                                // Структура списка
    char val[LENGTH+1];
    struct node* next;
    struct node* last;
} node;

node* table[DICSIZE];                                               // Массив указателей на списки

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    char dicword[LENGTH+1];                                         
    
    for(int i = 0, j = strlen(word); i < j; i++){                   // Форматируем входное слово для сравнения (переводим все буквы в прописные)
        if(isalpha(word[i])){
            dicword[i] = word[i];
            dicword[i+1] = '\0';
            if (isupper(dicword[i]))
                dicword[i] = tolower(dicword[i]);
        } 
        else {
            dicword[i] = word[i];
            dicword[i+1] = '\0';
        }
    }
    
    int place = dicword[0]%97;                                      // Определяем индекс необходимой ячейки со списком по первой букве
    
    if(place < 0 || place > 25)
        return false;
    
    int identical = 1;                                              // Результат сравнения
    
    node* tmp = table[place];
    
    do{                                                             // Проходим списком и ищем совпадения
        identical = strcmp(dicword, tmp->val);
        if(identical == 0)
            return true;
        tmp = tmp->next;
    } while (tmp != NULL);
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    for(int i = 0; i < DICSIZE; i++){                               // Заполнение массива указателей на списки
        table[i] = (node*) malloc(sizeof(node));
        table[i]->next = NULL;
        table[i]->last = table[i];
    }
    
    FILE *fd = fopen(dictionary, "r");
    
    char dicword[LENGTH+1];
    int index = 0;
    char ch;
    int place = 0;

    while((ch=fgetc(fd)) != EOF){                                   // Чтение из файла по знаку, пока не будет достигнут конец файла
        if(ch == '\n'){                                             // При обнаружении конца слова, выделение памяти для следующего за последним в списке элемента
            dicword[index] = '\0';
            index = 0;
            
            place = dicword[index]%97;

            table[place]->last->next = (node*) malloc(sizeof(node));        
            for(int i = 0, j = strlen(dicword); i < j; i++){            // Копирование в новый элемент слова
                table[place]->last->next->val[i] = dicword[i];
                table[place]->last->next->val[i+1] = '\0';
            }
            table[place]->last->next->next = NULL;
            table[place]->last = table[place]->last->next;              // Перемещение указателя на последний элемент
            diccount++;                                                 // Увеличение счетчика слов в словаре на 1
            
        }
        else {
            dicword[index] = ch;
            index++; 
        }
    }
    
    fclose(fd);
    fd = NULL;

    if(ch == EOF)
        return true;
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return diccount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    node* tmp = NULL;
    for(int i = 0; i < DICSIZE; i++){               // Удаление первого элемента списка за итерацию, пока список полностью не будет удален
        while(table[i] != NULL){
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
