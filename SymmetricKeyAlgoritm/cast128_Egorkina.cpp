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
        msg.Msg[0] = input[i];
        msg.Msg[1] = input[i + 1];

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
        decryptedText += decryptedMsg.Msg[0];
        decryptedText += decryptedMsg.Msg[1];
    }

    return decryptedText;
}

std::string readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    Cast128::Key key;
    Cast128::generateKey(key); // Generate a key

    std::string filename;
    cout << "Enter the name of the file to read data from: ";

    //string input;
    //cout << "Enter the word to encrypt: ";
    getline(cin, filename);

    try
    {

        std::string input = readDataFromFile(filename);

        // Засечка времени начала
        auto start_time = chrono::steady_clock::now();

        vector<Cast128::Block> encryptedBlocks = encryptBlocks(input, key);

        /*cout << "Encrypted text: ";
        for (const auto& encryptedMsg : encryptedBlocks)
        {
            cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[0]);
            cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(encryptedMsg.Msg[1]);
        }
        cout << dec << endl;*/

        string decryptedText = decryptBlocks(encryptedBlocks, key);

        // Засечка времени окончания
        auto end_time = chrono::steady_clock::now();

        // Вывод времени выполнения
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;


        //cout << "Decrypted text: " << decryptedText << endl;
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
