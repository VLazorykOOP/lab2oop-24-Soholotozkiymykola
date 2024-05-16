#include <iostream>
#include <string>

// Функція для шифрування тексту
void Crypt(std::string text[4], unsigned short rez[4][16]) {
    short i, j, l; // Змінні для циклів

    // Введення чотирьох рядків тексту від користувача
    for (int i = 0; i < 4; i++) {
        std::cout << "enter line " << i + 1 << ":";
        std::getline(std::cin, text[i]);
    }

    // Виведення введеного тексту та доповнення рядків до 16 символів пробілами
    std::cout << "You entered:\n";
    for (i = 0; i < 4; i++) {
        while (text[i].length() < 16) {
            text[i] += ' ';
        }
        std::cout << text[i] << std::endl;
    }

    // Шифрування тексту
    std::cout << "\nCrypted info:\n";
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            unsigned char c;
            unsigned short r, t, b;
            r = 0; // Очищення змінної r
            c = text[i][j]; // Отримання символу з тексту

            // Розділення символу на дві частини: старші і молодші біти
            int asciiValue = static_cast<int>(c);
            int higherPart = asciiValue >> 4;
            int lowerPart = asciiValue & 0xF;

            // Побудова шифрованого значення
            r |= lowerPart; // Запис молодших бітів символу
            r |= (i << 4); // Запис номеру рядка
            r |= (j << 6); // Запис номеру символу в рядку
            r |= (higherPart << 10); // Запис старших бітів символу

            // Обчислення парності бітів з 4 по 8 і запис в 14-й біт
            t = 1;
            b = 0;
            for (l = 4; l < 9; l++) {
                if (r & t) {
                    b = !b; // Інверсія b при кожному встановленому біті
                }
                t <<= 1; // Зсув вліво для перевірки наступного біта
            }
            r |= b << 14; // Запис парності в 14-й біт

            // Обчислення парності всіх бітів і запис в 15-й біт
            t = 1;
            b = 0;
            for (l = 0; l < 16; l++) {
                if (r & t) {
                    b = !b; // Інверсія b при кожному встановленому біті
                }
                t <<= 1; // Зсув вліво для перевірки наступного біта
            }
            r |= b << 15; // Запис парності в 15-й біт

            // Збереження шифрованого значення і виведення його в шістнадцятковому форматі
            rez[i][j] = r;
            std::cout << std::hex << rez[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функція для розшифрування тексту
void Decrypt(unsigned short rez[4][16]) {
    std::cout << "\nDecrypted info:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 16; ++j) {
            unsigned short r = rez[i][j]; // Отримання шифрованого значення
            // Витяг старших і молодших бітів символу
            unsigned char higherPart = (r >> 10) & 0b1111;
            unsigned char lowerPart = (r >> 0) & 0b1111;
            // Відновлення символу
            char decryptedChar = (higherPart << 4) | lowerPart;
            std::cout << decryptedChar; // Виведення розшифрованого символу
        }
        std::cout << std::endl;
    }
}

// Основна функція
int main() {
    std::string text[4]; // Масив для зберігання введеного тексту
    unsigned short rez[4][16]; // Масив для зберігання шифрованого тексту
    Crypt(text, rez); // Виклик функції шифрування
    Decrypt(rez); // Виклик функції розшифрування
    return 0; // Завершення програми
}
//Друге завдання