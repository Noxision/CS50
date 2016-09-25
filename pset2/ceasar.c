#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_ASCII(int, int, char);

const int array_size = 100;                         // ������ ������� ��������� ������

int main(int argc, char** argv){

    if(argc!=2){                                     // �������� �� ���������� ����������
        printf ("usage : ./caesar + k\n");
        return 1;
    }

    int k = atoi(argv[1]);                          // �������������� ��������� � �����

    printf("plaintext: ");

    char text[array_size];
    fgets(text, array_size, stdin);                 // ���� ������ ��� ����������

    for (int i = 0, n = strlen(text); i < n; i++){  // ���� �������� ��������� ��������� ������
        if (isalpha(text[i])){                      // �������� ��������� �� ������������ ���������� ��������
            int numb_c;                             // ���������� ��� ������ ������ ASCII �������������� ��������
            if (isupper(text[i]))                   // �������� �� ��������� �����
                numb_c = get_ASCII(64, k, text[i]); // ��������� �������������� ��������
            else
                numb_c = get_ASCII(96, k, text[i]);
            text[i] = numb_c;                       // ���������� �������� � ������
        }
    }

    printf("ciphertext: %s", text);                 // ����� ����� ������
}

int get_ASCII (int x, int k, char y){               // ������� ��������� ������ �������������� ��������
    int calc = y-x+k;
    if (calc == 26)
        return y+k;
    return (((y-x)+k)%26)+x;
}
