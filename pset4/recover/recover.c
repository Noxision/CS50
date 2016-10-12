#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int const SIZE = 512;                                               // Размер одного сектора
int const SIZE_TITLE = 10;                                          // Размер массива названия исходящего файла

char* get_title(int, char*);                                        // Функция генерации названия исходящего файла

int main(int argc, char *argv[])
{
    if (argc != 2)                                                  // Проверка входных данных
    {
        fprintf(stderr, "Usage: ./recover cardfile\n");
        return 1;
    }
    
    char *cardfile = argv[1];
    
    FILE *cardptr = fopen(cardfile, "r");                           // Открытие и проверка файла с фотографиями

    if (cardptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cardfile);
        return 2;
    }

    uint8_t buffer[SIZE];                                           // Буфер для обработки считаных секторов
    int title_count = 0;                                            // Счетчик для названия исходящих файлов
    char title_arr[SIZE_TITLE];                                     // Название исходящего файла
    char* title = &title_arr[0];
    FILE* jpgptr = NULL;                                            // Указатель на исходящий файл
    
    while (fread(&buffer, sizeof(buffer), 1, cardptr) == 1)         
    { 
        
        if(buffer[0] == 0xff &&                                     // Проверка на начало jpg
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0)
           {
                if (jpgptr != NULL)                                 // Если файл открыт, то закрываем
                    fclose(jpgptr);
                
                title = get_title(title_count, title);              
                title_count++;
                
                jpgptr = fopen(title, "w");         
                
                if (jpgptr == NULL)
                {
                    fclose(cardptr);
                    fprintf(stderr, "Could not create %s.\n", title);
                    return 3;
                }
                
                fwrite(buffer, SIZE, 1, jpgptr);                    // Пишем в исходящий файл
           }
        else
        { 
            if (jpgptr != NULL)                                     // Если начало jpg не найдено, просто пишем в открытый файл
                fwrite(buffer, SIZE, 1, jpgptr);
        }
    }
    
    fclose(cardptr);
    fclose(jpgptr);
    
    return 0;
}

char* get_title(int title_count, char* title)
{
    if (title_count < 10)
        sprintf(title, "00%d.jpg", title_count);
    else if (10 <= title_count && title_count < 100)
        sprintf(title, "0%d.jpg", title_count);
    else
        sprintf(title, "%d.jpg", title_count);
    return title;
}