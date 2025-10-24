#include <iostream>
#include <locale>
#include <codecvt>
#include "RouteCipher.h"

using namespace std;

void testRouteCipher()
{
    wcout << L"Тестирование шифра маршрутной перестановки:" << endl;
    wcout << L"============================================" << endl;

    // Тест 1
    try {
        RouteCipher cipher(3);
        wstring original = L"ПРИВЕТМИР";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);

        wcout << L"Ключ: 3" << endl;
        wcout << L"Исходный текст: " << original << endl;
        wcout << L"Зашифрованный: " << encrypted << endl;
        wcout << L"Расшифрованный: " << decrypted << endl;

        if (original == decrypted) {
            wcout << L"✓ Тест пройден" << endl;
        } else {
            wcout << L"✗ Ошибка" << endl;
        }
    } catch (const exception& e) {
        wcout << L"Ошибка: " << e.what() << endl;
    }
    wcout << endl;

    // Тест 2
    try {
        RouteCipher cipher(4);
        wstring original = L"ПРОГРАММИРОВАНИЕ";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);

        wcout << L"Ключ: 4" << endl;
        wcout << L"Исходный текст: " << original << endl;
        wcout << L"Зашифрованный: " << encrypted << endl;
        wcout << L"Расшифрованный: " << decrypted << endl;

        if (original == decrypted) {
            wcout << L"✓ Тест пройден" << endl;
        } else {
            wcout << L"✗ Ошибка" << endl;
        }
    } catch (const exception& e) {
        wcout << L"Ошибка: " << e.what() << endl;
    }
}

int main()
{
    // Установка локали для поддержки русского языка
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));

    testRouteCipher();
    return 0;
}
