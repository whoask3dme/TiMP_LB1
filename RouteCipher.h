#pragma once
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

class RouteCipher
{
private:
    int key; // количество столбцов таблицы
public:
    RouteCipher() = delete; // запрет конструктора без параметров
    RouteCipher(int k); // конструктор с установкой ключа
    std::wstring encrypt(const std::wstring& open_text); // зашифрование
    std::wstring decrypt(const std::wstring& cipher_text); // расшифрование
};
