#include <iostream>
#include <fstream>
#include <string>
#include "Algorithm.h"
#include "AES.h"
/// Если у вас есть заголовочные файлы добавляйте их сюда


void Run(Algorithm a, Algorithm b, std::string author) {

    std::string input = "Hello, World";
    std::cout << "Original: " << input << std::endl;
    std::string encryptedString = a(input);
   std::cout << "Encrypted: " << encryptedString << std::endl;
    std::string decryptedString = b(encryptedString);
    std::cout << "Decrypted: " << decryptedString << std::endl;
}
int main() {
    Run(AES_encryptString, AES_decryptString, "Shelyakina Anastasiya");
    ///Дописываете здесь себя  Run(функция шифровки, функция дешифровки, "имя");
    
    return 0;
}

