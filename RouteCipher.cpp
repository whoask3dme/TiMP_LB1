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

    // Удаляем пробелы из исходного текста
    std::wstring text_without_spaces;
    for (wchar_t c : open_text) {
        if (c != L' ') {
            text_without_spaces += c;
        }
    }

    if (text_without_spaces.empty()) {
        return L"";
    }

    // Определяем количество строк
    int text_len = text_without_spaces.length();
    int rows = (text_len + key - 1) / key;

    // Создаем таблицу для записи
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    // Записываем текст по горизонтали слева направо, сверху вниз
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < text_len) {
                table[i][j] = text_without_spaces[index++];
            } else {
                table[i][j] = L'*'; // заполняем пустые ячейки специальным символом
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
    int rows = text_len / key;

    if (rows * key != text_len) {
        throw std::invalid_argument("Некорректная длина зашифрованного текста");
    }

    // Создаем таблицу для расшифровки
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    // Заполняем таблицу по маршруту считывания (сверху вниз, справа налево)
    int index = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            table[i][j] = cipher_text[index++];
        }
    }

    // Считываем по маршруту записи (по горизонтали слева направо, сверху вниз)
    std::wstring result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            // Пропускаем символы-заполнители
            if (table[i][j] != L'*') {
                result += table[i][j];
            }
        }
    }

    return result;
}
