#include "AES.h"
#include "blowfish.h"
#include "DES.h"
#include <fstream>
#include <string>
#include "Algorithm.h"
#include "cast128.h"
#include <iomanip>
#include <iostream>


void Run(Algorithm a, Algorithm b, std::string author) {

    std::string input = "Hello, World";
    std::cout << "Original: " << input << std::endl;
    std::string encryptedString = a(input);
   std::cout << "Encrypted: " << encryptedString << std::endl;
    std::string decryptedString = b(encryptedString);
    std::cout << "Decrypted: " << decryptedString << std::endl;
}
int main() {
    std::string input = "Hello, World!";
    /*DES des;
    std::string a = des.DES_encryptString(input);
    std::string res = des.DES_decryptString(a);
    std::cout << res;*/
    std::cout << "Original: " << input << std::endl;
    Run(input);

    /*Run(AES_encryptString, AES_decryptString, "Shelyakina Anastasiya");
    Run(Blowfish_encryptString, Blowfish_decryptString, "Saifullin Bulat");*/
    //Run(des.DES_encryptString, DES_decryptString, "Razin Iliya");
    ///Дописываете здесь себя  Run(функция шифровки, функция дешифровки, "имя");
    
    return 0;
}
