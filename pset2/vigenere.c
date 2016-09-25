#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check (int , char* []);                                 // �������� �������� ����� ������� ������
int k_smesheniya (char* [], int);                           // ���������� ��������
int get_numb_of_crypto_char(int , char [], int, int);       // ���������� ������� �������������� �������

int main(int argc, char* argv[]){

    int array_size = 100;                                    // ������ ������� ��������� ������

    if(check(argc, argv)){                                   // �������� �� ���������� ���������� � ������������ ���������� ��������
        printf ("usage : ./vigenere + k\n");
        return 1;
    }

    printf("plaintext: \n");                                 // ���� ������ ��� ����������

    char text[array_size];
    fgets( text, array_size, stdin );                        // ���� ������ ��� ����������

    int j, k, p = 0;
    for (int i = 0, n = strlen(text); i < n; i++){            // ���� �������� �� �������
        int numb_c;                                           // ���������� � ������� �������������� �������
        if (isalpha(text[i])){                                // �������� �� ������������ �������� �������� ������ ���������� ��������
            j = p%strlen(argv[1]);                            // ��������� ������� ������ �������� �����

            k = k_smesheniya(argv, j);                        // ���������� ����������� �������� ������� ������������ ������

            if (isupper(text[i]))                                       // �������� �� ��������� �����
                numb_c = get_numb_of_crypto_char(k, text, i, 64);       // ���������� ������� �������������� �������
            else
                numb_c = get_numb_of_crypto_char(k, text, i, 96);

            p++;                                                        // ���������� ������� ������� �������� ����� ��� ��������� ��������
            text[i] = numb_c;
        }

    }

    printf("ciphertext: %s", text);

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
