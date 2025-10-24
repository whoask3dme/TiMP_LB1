#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

using namespace std;

// Функция для проверки работы шифра
void check(const wstring& text, const wstring& key)
{
    wstring cipherText;
    wstring decryptedText;

    modAlphaCipher cipher(key);
    cipherText = cipher.encrypt(text);
    decryptedText = cipher.decrypt(cipherText);

    wcout << L"Ключ: " << key << endl;
    wcout << L"Исходный текст: '" << text << L"'" << endl;
    wcout << L"Зашифрованный текст: '" << cipherText << L"'" << endl;
    wcout << L"Расшифрованный текст: '" << decryptedText << L"'" << endl;

    // Сравниваем без учета пробелов и не-букв
    wstring text_filtered, decrypted_filtered;
    for (auto c : text) if (iswalpha(c)) text_filtered += c;
    for (auto c : decryptedText) if (iswalpha(c)) decrypted_filtered += c;
    
    if (text_filtered == decrypted_filtered)
        wcout << L"✓ Тест пройден успешно" << endl;
    else
        wcout << L"✗ Ошибка в работе шифра" << endl;
    wcout << endl;
}

int main()
{
    // Установка локали для поддержки русского языка
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));

    // Тестирование на различных ключах
    check(L"ПРИВЕТ", L"ЭХО");
    check(L"ПРОГРАММИРОВАНИЕ", L"КОМПЬЮТЕР");
    check(L"ШИФРОВАНИЕ", L"КЛЮЧ");
    // Тест с пробелами
    check(L"ПРИВЕТ МИР", L"КЛЮЧ");
    check(L"Я ЛЮБЛЮ ПРОГРАММИРОВАНИЕ", L"СЛОВО");

    return 0;
}
