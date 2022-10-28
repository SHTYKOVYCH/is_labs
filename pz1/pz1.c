#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int main() {
    setlocale(LC_ALL, "rus");

    wchar_t alp1[] = L"абвгдежзиклмнопрстуфхцчшщъыьэюя";
    wchar_t alp2[] = L"абвгдежзийклмнопрстуфхцчшщъыьэюя";
    wchar_t alp3[] = L"абвгдеёжзиклмнопрстуфхцчшщъыьэюя";
    wchar_t alp4[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    wchar_t input[2048] = {0};
    int choise;

    wprintf(L"Зашифровать(0) или расшифровать(1)?: ");
    wscanf(L"%d", &choise);


    return 0;
}
