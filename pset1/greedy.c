#include <stdio.h>
#include <stdlib.h>
int coins_count (int, int, int, int, int []);

int main() {
    int array[4] = {[0] = 25, [1] = 10, [2] = 5, [3] = 1}; // ������ � ���������� ����� �� �������� � ��������
    float in;                                              // ����������, � ������� ��������� ������� �����
    int coins = 0;                                         // ����������, ������� ����� ��������� ���������

    do {                                                   // �������� �������� ����� �� ������������� ����
        printf("How much change is owed?\n");
        scanf("%f", &in);
    }
    while(in <= 0);

    int greedy = in*100;                                   // ��������������� ����� � �����������
    int rest = 1;                                          // ����������, ������� �������� � ���� ������� �� ������� (��� ������� ����� ����� �������� ��������� �������� != 0)
    int i = 0;                                             // ���������� ��� ��������� ����� �������

    coins = coins_count (i, rest, greedy, coins, array);   // ��������� ���������� �����

    /*while(rest != 0){                                    // ���� � ������� ���������� �������� �������
        rest = greedy%array[i];                            // �������� ������� �� �������
        coins += (greedy-rest)/array[i];                   // ���������� ���������� �����
        greedy = rest;                                     // ��������� �������� �������� ����� ��� ��������� ��������
        i++;                                               // ������� � ��������� ������ ������� � ��������� ��������
    }*/

    printf("Coins: %d\n", coins);                          // ����� ����������
    return 0;
}

int coins_count (int i, int rest, int greedy, int coins, int array[]) {
    if (rest == 0)
        return coins;
    rest = greedy%array[i];                            // �������� ������� �� �������
    coins += (greedy-rest)/array[i];                   // ���������� ���������� �����
    greedy = rest;                                     // ��������� �������� �������� ����� ��� ��������� ��������
    i++;
    //printf("%d, %d, %d", i, rest, coins);
    coins_count(i, rest, greedy, coins, array);
}
