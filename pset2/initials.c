#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void if_isupper (char [], int );
void to_each_char (char []);

const int array_size = 100;                     // ������ �������� �������

int main()
{
    char text[array_size];
    fgets( text, array_size, stdin );           // ���� �����

    to_each_char(text);

    return 0;
}

void if_isupper (char text[], int i){           // ������ ������ ���� ����������
    if (isupper(text[i]))
        printf("%c", text[i]);
    else
        printf("%c", text[i]-32);
}

void to_each_char (char text[]){                // ���������� ������ ���� ���� ����������� ���������
    int i;
    for (i = 0; i < strlen(text); i++){
        if (i-1 < 0)
            if_isupper(text, i);
        if (!isalpha(text[i-1]))
            if_isupper(text, i);
    }
}
