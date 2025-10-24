#include "RouteCipher.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

RouteCipher::RouteCipher(int k) : key(k)
{
    if (key <= 0) {
        throw std::invalid_argument("Ключ должен быть положительным числом");
    }
}

std::wstring RouteCipher::encrypt(const std::wstring& open_text)
{
    if (open_text.empty()) {
        return L"";
    }

    // Определяем количество строк
    int text_len = open_text.length();
    int rows = (text_len + key - 1) / key;

    // Создаем таблицу для записи
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    // Записываем текст по горизонтали слева направо, сверху вниз
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < text_len) {
                table[i][j] = open_text[index++];
            } else {
                table[i][j] = L' '; // заполняем пустые ячейки пробелами
            }
        }
    }

    // Считываем по маршруту: сверху вниз, справа налево
    std::wstring result;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            result += table[i][j];
        }
    }

    return result;
}

std::wstring RouteCipher::decrypt(const std::wstring& cipher_text)
{
    if (cipher_text.empty()) {
        return L"";
    }

    // Определяем количество строк
    int text_len = cipher_text.length();
    int rows = (text_len + key - 1) / key;

    // Создаем таблицу для расшифровки
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    // Заполняем таблицу по маршруту считывания (сверху вниз, справа налево)
    int index = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (index < text_len) {
                table[i][j] = cipher_text[index++];
            }
        }
    }

    // Считываем по маршруту записи (по горизонтали слева направо, сверху вниз)
    std::wstring result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            result += table[i][j];
        }
    }

    // Убираем лишние пробелы в конце
    while (!result.empty() && result.back() == L' ') {
        result.pop_back();
    }

    return result;
}
