#include <cstdint>
#include "cast128.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;


vector<Cast128::Block> encryptBlocks(const string& input, const Cast128::Key& key)
{
    vector<Cast128::Block> encryptedBlocks;

    for (size_t i = 0; i < input.size(); i += 2)
    {
        Cast128::Block msg;
        msg.Msg[0] = static_cast<uint8_t>(input[i]);
        msg.Msg[1] = static_cast<uint8_t>(input[i + 1]);

        Cast128::Block encryptedMsg = Cast128::encrypt(key, msg);
        encryptedBlocks.push_back(encryptedMsg);
    }

    return encryptedBlocks;
}

string decryptBlocks(const vector<Cast128::Block>& encryptedBlocks, const Cast128::Key& key)
{
    string decryptedText;

    for (const auto& encryptedMsg : encryptedBlocks)
    {
        Cast128::Block decryptedMsg = Cast128::decrypt(key, encryptedMsg);
        decryptedText += static_cast<char>(decryptedMsg.Msg[0]);
        decryptedText += static_cast<char>(decryptedMsg.Msg[1]);
    }

    return decryptedText;
}

//int main()
//{
//    Cast128::Key key = {
//        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
//    };
//
//    string input = "Hello, World";
//
//        vector<Cast128::Block> encryptedBlocks = encryptBlocks(input, key);
//
//        cout << "Encrypted text: ";
//        for (const auto& encryptedMsg : encryptedBlocks)
//        {
//            cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[0]);
//            cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[1]);
//        }
//        cout << dec << endl;
//
//        string decryptedText = decryptBlocks(encryptedBlocks, key);
//
//        cout << "Decrypted text: " << decryptedText << endl;
//
//    return 0;
//}

void Run(const string& input)
{
    Cast128::Key key = {
                0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
            };

    vector<Cast128::Block> encryptedBlocks = encryptBlocks(input, key);

    stringstream encryptedStream;
    for (const auto& encryptedMsg : encryptedBlocks)
    {
        encryptedStream << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[0]);
        encryptedStream << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[1]);
    }
    std::string encryptedText;
    std::string decryptedText;
    encryptedText = encryptedStream.str();

    decryptedText = decryptBlocks(encryptedBlocks, key);

    std::cout << "Encrypted: " << encryptedText << std::endl;
    std::cout << "Decrypted: " << decryptedText << std::endl;


}

//int main()
//{
//    string input = "Hello, World";
//    string encryptedText;
//    string decryptedText;
//
//    Run(input, encryptedText, decryptedText);
//
//    cout << "Encrypted text: " << encryptedText << endl;
//    cout << "Decrypted text: " << decryptedText << endl;
//
//    return 0;
//}
