//#include <iostream>
//#include <string>
//#include "Algorithm.h"
//
//void encryptBlock(std::string& block) {
//        // Логика шифрования
//        // Например, простая замена каждого символа на следующий в алфавите
//        for (char& ch : block) {
//            if (ch == 'z') {
//                ch = 'a';
//            }
//            else {
//                ch = ch + 1;
//            }
//        }
// }
//
// void decryptBlock(std::string& block) {
//        // Логика дешифрования
//        // Например, простая замена каждого символа на предыдущий в алфавите
//        for (char& ch : block) {
//            if (ch == 'a') {
//                ch = 'z';
//            }
//            else {
//                ch = ch - 1;
//            }
//        }
// }
//
//
//// Функция для шифрования слова "algorithm" с использованием шифратора
//std::string DEA_encryption(std::string word) {
//
//    // Разделение слова на блоки
//    const int blockSize = 3;
//    const int numBlocks = word.length() / blockSize;
//    std::string encryptedWord;
//
//    for (int i = 0; i < numBlocks; ++i) {
//        // Получение текущего блока
//        std::string block = word.substr(i * blockSize, blockSize);
//
//        // Шифрование текущего блока
//        encryptBlock(block);
//
//        // Добавление зашифрованного блока к результату
//        encryptedWord += block;
//    }
//    return encryptedWord;
//}
//
////std::string DEA_decryption(std::string word) {
////
////    // Дешифрование зашифрованного слова
////    std::string decryptedWord;
////    for (int i = 0; i < numBlocks; ++i) {
////        // Получение текущего зашифрованного блока
////        std::string encryptedBlock = encryptedWord.substr(i * blockSize, blockSize);
////
////       // Дешифрование текущего блока
////        decryptBlock(encryptedBlock);
////
////       // Добавление дешифрованного блока к результату
////       decryptedWord += encryptedBlock;
////    }
////
////    // Вывод дешифрованного слова
////    return encryptedWord;
////}