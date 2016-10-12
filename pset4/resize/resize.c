#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

BITMAPFILEHEADER* give_resize_bf(BITMAPFILEHEADER, BITMAPINFOHEADER, int, int);     // Функции создания структур исходящего файла
BITMAPINFOHEADER* give_resize_bi(BITMAPINFOHEADER, int, int);

int main(int argc, char *argv[])
{
    // Проверка на ввод
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./rezice n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: n must be more than 0 and less than 100\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    // открытие оригинального файла 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // открытие исходящего файла
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // чтение BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // чтение BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Проверка на 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Отступы исходящего файла
    int padding = (4 - (n*bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Получаем указатель на структуру исходящего файла
    BITMAPFILEHEADER* resize_bf = give_resize_bf(bf, bi, n, padding);
    
    // Запись измененной структуры в исходящий файл
    fwrite(resize_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Получаем указатель на структуру исходящего файла
    BITMAPINFOHEADER* resize_bi = give_resize_bi(bi, n, padding);

    // Запись измененной структуры в исходящий файл
    fwrite(resize_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Освобождаем память для хранения исходящих структур и обнуляем указатели
    free(resize_bi);
    free(resize_bf);
    resize_bi = NULL;
    resize_bf = NULL;    
    
    // отступы оригинального файла
    int padding_origin = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // цикл для генерации и записи дополнительных пикселей 
    for (int i_origin = 0, biHeight = abs(bi.biHeight); i_origin < biHeight; i_origin++)
    {
        for (int i_resize = 0; i_resize < n; i_resize++)
        {
            for (int j_origin = 0; j_origin < bi.biWidth; j_origin++)
            {
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int j_resize = 0; j_resize < n; j_resize++)
                {    
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            fseek(inptr, padding_origin, SEEK_CUR);
            
            if (i_resize < n-1) 
            {
                fseek(inptr, bf.bfOffBits+i_origin*(bi.biWidth*3+padding_origin), SEEK_SET);
            }
        }
    }

    fclose(inptr);

    fclose(outptr);

    return 0;
}

BITMAPFILEHEADER* give_resize_bf(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int n, int padding){
    
    BITMAPFILEHEADER* resize_bf = (BITMAPFILEHEADER *) malloc (sizeof(*resize_bf));
    
    resize_bf->bfType = bf.bfType;
    resize_bf->bfSize = bf.bfOffBits + (n*3*bi.biWidth+padding)*n*abs(bi.biHeight);
    resize_bf->bfReserved1 = bf.bfReserved1; 
    resize_bf->bfReserved2 = bf.bfReserved2; 
    resize_bf->bfOffBits = bf.bfOffBits; 
    
    return resize_bf;
}

BITMAPINFOHEADER* give_resize_bi(BITMAPINFOHEADER bi, int n, int padding){
 
    BITMAPINFOHEADER* resize_bi = (BITMAPINFOHEADER *) malloc (sizeof(*resize_bi));
    
    resize_bi->biSize = bi.biSize; 
    resize_bi->biWidth = bi.biWidth*n; 
    resize_bi->biHeight = bi.biHeight*n; 
    resize_bi->biPlanes = bi.biPlanes; 
    resize_bi->biBitCount = bi.biBitCount; 
    resize_bi->biCompression = bi.biCompression; 
    resize_bi->biSizeImage = (n*3*bi.biWidth+padding)*n*abs(bi.biHeight);  
    resize_bi->biXPelsPerMeter = bi.biXPelsPerMeter; 
    resize_bi->biYPelsPerMeter = bi.biYPelsPerMeter; 
    resize_bi->biClrUsed = bi.biClrUsed; 
    resize_bi->biClrImportant = bi.biClrImportant; 
    
    return resize_bi;
}