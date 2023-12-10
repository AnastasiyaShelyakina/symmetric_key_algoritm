#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>


typedef unsigned long long ull;

typedef unsigned short int word;

const double e = exp(1);
const double phi = (1 + sqrt(5)) / 2;

const unsigned int key_length = 8;
const unsigned int width = 32;
const unsigned int rounds = 16;
std::vector<word> key = { 1234, 4321 };


template<class T>
T cycleLeft(T x, unsigned int shift)
{
    shift %= sizeof(T) * CHAR_BIT;
    return (x << shift) | (x >> (sizeof(T) * CHAR_BIT - shift));
}

template<class T>
T cycleRight(T x, unsigned int shift)
{
    shift %= sizeof(T) * CHAR_BIT;
    return (x >> shift) | (x << (sizeof(T) * CHAR_BIT - shift));
}

std::pair<word, word> generateMagicNumbers(const unsigned int& width) {
    word P;
    word Q;
    P = (word)((e - 2) * ((ull)1 << width));
    P += (1 - P % 2);
    Q = (word)((phi - 2) * ((ull)1 << width));
    Q -= (1 - Q % 2);
    return std::make_pair(P, Q);
}

std::vector<word> initializeSubkeys(
    const std::pair<ull, ull>& magic_numbers,
    const unsigned int& rounds
) {
    std::vector<word> subkeys(2 * (rounds + 1));
    subkeys[0] = magic_numbers.first;
    for (long i = 1; i < subkeys.size(); i++) {
        subkeys[i] = subkeys[i - 1] + magic_numbers.second;
    }
    return subkeys;
}

std::vector<word> mixSubkeys(const std::vector<word>& subkeys, const std::vector<word>& key) {
    word A = 0, B = 0;
    std::vector<word> s = subkeys;
    std::vector<word> k = key;
    for (long z = 0, i = 0, j = 0;
        z < 3 * std::max(s.size(), k.size());
        z++,
        i = (i + 1) % s.size(),
        j = (j + 1) % k.size()) {
        A = s[i] = cycleLeft((s[i] + A + B), 3);
        B = k[j] = cycleLeft((k[j] + A + B), A + B);
    }
    return s;
}

std::pair<word, word> encryptBlock(word left, word right, const std::vector<word>& subkeys) {
    left += subkeys[0];
    right += subkeys[1];
    for (long i = 1; i < subkeys.size() / 2; i++) {
        left ^= right;
        left = cycleLeft(left, right);
        left += subkeys[2 * i];
        right ^= left;
        right = cycleLeft(right, left);
        right += subkeys[2 * i + 1];
    }
    return std::make_pair(left, right);
}

std::pair<word, word> decryptBlock(word left, word right, const std::vector<word>& subkeys) {
    for (long i = (subkeys.size() / 2) - 1; i >= 1; i--) {
        right -= subkeys[2 * i + 1];
        right = cycleRight(right, left);
        right ^= left;
        left -= subkeys[2 * i];
        left = cycleRight(left, right);
        left ^= right;
    }
    right -= subkeys[1];
    left -= subkeys[0];
    return std::make_pair(left, right);
}

std::string encrypt(
    const std::string& start_message
) {

    std::vector<word> message;
    for (char c : start_message) {
        int ss = static_cast<int>(c);
        message.push_back(ss);
    }

    std::vector<word> encrypted(message.size());
    std::pair<word, word> magic_numbers = generateMagicNumbers(width);

    std::vector<word> subkeys = initializeSubkeys(magic_numbers, rounds);
    subkeys = mixSubkeys(subkeys, key);

    for (long i = 0; i < message.size() / 2; i++) {
        std::pair<word, word> encrypted_block = encryptBlock(message[2 * i],
            message[2 * i + 1],
            subkeys);
        encrypted[2 * i] = encrypted_block.first;
        encrypted[2 * i + 1] = encrypted_block.second;
    }

    std::ostringstream oss;

    for (const auto& word : encrypted) {
        oss << word << " ";
    }

    return oss.str();
}

std::string decrypt(const std::string& start_message){
    std::vector<word> message;
    std::istringstream iss(start_message);
    int num;

    while (iss >> num) {
        message.push_back(num);
    }

    
    std::string result;
    std::vector<word> decrypted(message.size());
    std::pair<word, word> magic_numbers = generateMagicNumbers(width);

    std::vector<word> subkeys = initializeSubkeys(magic_numbers, rounds);
    subkeys = mixSubkeys(subkeys, key);

    for (long i = 0; i < message.size() / 2; i++) {
        std::pair<word, word> decrypted_block = decryptBlock(message[2 * i],
            message[2 * i + 1],
            subkeys);
        decrypted[2 * i] = decrypted_block.first;
        decrypted[2 * i + 1] = decrypted_block.second;
    }
    for (int num : decrypted) {
        char ch = static_cast<char>(num);
        result += ch;
    }
    return result;
}


int main(int argc, const char* argv[]) {
    std::cout << "Algorithm RC5-" << width / CHAR_BIT << "/" << rounds << "/" << key_length << std::endl;
    std::string user_message = "Алгоритм";
    std::string encodedMessage;


    std::cout << "User Message: " << user_message << std::endl;
    encodedMessage = encrypt(user_message);
    std::cout << "Encoded Message: " << encodedMessage << std::endl;
    std::cout << "Decoded Message: " << decrypt(encodedMessage) << std::endl;

    return 0;
}