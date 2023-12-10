//#include <iostream>
//#include <string>
//#include "Algorithm.h"
//
//void encryptBlock(std::string& block) {
//        // ������ ����������
//        // ��������, ������� ������ ������� ������� �� ��������� � ��������
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
//        // ������ ������������
//        // ��������, ������� ������ ������� ������� �� ���������� � ��������
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
//// ������� ��� ���������� ����� "algorithm" � �������������� ���������
//std::string DEA_encryption(std::string word) {
//
//    // ���������� ����� �� �����
//    const int blockSize = 3;
//    const int numBlocks = word.length() / blockSize;
//    std::string encryptedWord;
//
//    for (int i = 0; i < numBlocks; ++i) {
//        // ��������� �������� �����
//        std::string block = word.substr(i * blockSize, blockSize);
//
//        // ���������� �������� �����
//        encryptBlock(block);
//
//        // ���������� �������������� ����� � ����������
//        encryptedWord += block;
//    }
//    return encryptedWord;
//}
//
////std::string DEA_decryption(std::string word) {
////
////    // ������������ �������������� �����
////    std::string decryptedWord;
////    for (int i = 0; i < numBlocks; ++i) {
////        // ��������� �������� �������������� �����
////        std::string encryptedBlock = encryptedWord.substr(i * blockSize, blockSize);
////
////       // ������������ �������� �����
////        decryptBlock(encryptedBlock);
////
////       // ���������� �������������� ����� � ����������
////       decryptedWord += encryptedBlock;
////    }
////
////    // ����� �������������� �����
////    return encryptedWord;
////}