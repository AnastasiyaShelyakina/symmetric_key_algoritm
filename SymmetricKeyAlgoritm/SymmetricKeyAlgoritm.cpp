#include <fstream>
#include <string>
#include "Algorithm.h"
#include "cast128.h"
#include <iostream>
#include <iomanip>


//void Run(Algorithm a, Algorithm b, std::string author) {
//
//    std::string input = "Hello, World";
//    std::cout << "Original: " << input << std::endl;
//    std::string encryptedString = a(input);
//    std::cout << "Encrypted: " << encryptedString << std::endl;
//    std::string decryptedString = b(encryptedString);
//    std::cout << "Decrypted: " << decryptedString << std::endl;
//}
//

int main() {
    std::string input = "Hello, World";
    std::cout << "Original: " << input << std::endl;
    Run(input);
    return 0;
}