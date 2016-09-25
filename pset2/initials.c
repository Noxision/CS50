#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

void if_isupper (string, int, char [], int*);
void to_each_char (string, char [], int*);

int main()
{
    string text = get_string();
    char initials[strlen(text)];
    int j = 0;
    int* place = &j;

    to_each_char(text, initials, place);

    return 0;
}

void if_isupper (string text, int i, char initials[], int* place){           // «амена мелких букв заглавными
    if (isupper(text[i]))
        initials[*place] = text[i];
    else
        initials[*place] = text[i]-32;
    *place += 1;
}

void to_each_char (string text, char initials[], int* place){                // Ќахождение первых букв слов разделенных пробелами
    for (int i = 0, n = strlen(text); i < n; i++){
        if (i == 0) {
            if_isupper(text, i, initials, place);
            continue;
        }
        if (!isalpha(text[i-1]))
            if_isupper(text, i, initials, place);
    }
    printf("%s\n", initials);
}
