#include <iostream>
#include <string>
#include "Algorithm.h"

using namespace std;

void Run_encryption(Algorithm a, std::string author) {
    string word=a("algorithm");
    // Вывод зашифрованного слова
    std::cout << "Encrypted word: " << word <<"  " << author << std::endl;

}

int main() {
    Run_encryption(DEA_encryption, "Shelyakina Anastasiya");
    // Допишите сюда функцию шифрования
    // Run(название функции, "Ваше имя");
    return 0;
}
