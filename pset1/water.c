#include <stdio.h>
#include <stdlib.h>

int main() {

    int min = 0;                                // ����������, � ������� ��������� ������� �����
    int bottles = 0;

    do {                                        // �������� �������� �����
        printf("Minutes integer:\n");
        scanf("%d", &min);
    }
    while(min < 1);

    bottles = 192*min/16;                       // ���������� ���������� �������

    printf("Bottles:%d\n", bottles);            // ����� ����������
    return 0;
}
