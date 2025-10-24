#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <algorithm>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    // Формирование ключа - только буквы из алфавита
    for (auto c : skey) {
        if (alphaNum.count(c) > 0) { // проверяем, что символ есть в алфавите
            key.push_back(alphaNum[c]);
        }
    }
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    // Фильтруем только символы из алфавита
    std::wstring filtered_text;
    for (auto c : open_text) {
        if (alphaNum.count(c) > 0) {
            filtered_text += c;
        }
        // Пробелы и другие символы просто игнорируем
    }
    
    if (filtered_text.empty()) return L"";
    
    std::vector<int> work = convert(filtered_text);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        if (alphaNum.count(c) > 0) { // безопасное преобразование
            result.push_back(alphaNum[c]);
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        if (i >= 0 && i < numAlpha.size()) { // безопасное преобразование
            result.push_back(numAlpha[i]);
        }
    }
    return result;
}
