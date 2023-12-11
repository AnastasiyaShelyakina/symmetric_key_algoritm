#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ullong;  //64 байт
typedef unsigned long ulong;        //32 байт

class int256 {
    ullong bits[4];
public:
    int256(ullong b0, ullong b1, ullong b2, ullong b3) :bits{ b0, b1, b2, b3 } {}
    ullong get(int i) {
        return bits[i];
    }
};

class Magma {
    int256 key;
    ullong mod32 = 0xffffffff;
    ulong keys[8];
    ulong xkey[32];
    const int piBlock[8][16] = {
        {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2},
        {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
        {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
        {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
        {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
        {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
        {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
        {12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
    };
    void setKeys() {
        for (int i = 0; i < 4; ++i) {
            ullong left = key.get(i);
            ullong right = left & mod32;
            left >>= 32;
            keys[i * 2] = left;
            keys[i * 2 + 1] = right;
        }
    }
    ulong f(ullong a, ullong x, int pi) {  //выполнение функцией f одного раунда шифрования
        a += x;
        a &= mod32;
        int un[8];
        for (int i = 0; i < 8; ++i) {
            x = a & 0xf;
            un[8 - i - 1] = x;
            a >>= 4;
        }
        for (int i = 0; i < 8; ++i) {
            un[i] = piBlock[i][un[i]];
        }
        for (int i = 0; i < 8; ++i) {
            a += un[i];
            a <<= 4;
        }
        a >>= 4;
        a = (a << 11) | (a >> 21);
        a &= mod32;
        return a;
    }
    ullong round(ullong& left, ullong& right) {
        ullong old;
        for (int i = 0; i < 31; ++i) {
            old = right;
            right = left ^ f(right, xkey[i], i);//применение xor
            left = old;
        }
        left = left ^ f(right, xkey[31], 31);
        left <<= 32;
        left += right;
        return left;
    }
    void setXkey() {
        for (int i = 0; i < 24; ++i) {
            xkey[i] = keys[i % 8];
        }
        for (int i = 7; i >= 0; --i) {
            xkey[32 - i - 1] = keys[i];
        }
    }
public:
    Magma(int256 key) : key{ key } {
        setKeys();
    }
    ullong encrypt(ullong data) { //алгоритм шифровки ГОСТ-28147-89
        ullong left = data;
        ullong right = left & mod32;
        left >>= 32;
        setXkey();
        data = round(left, right);
        return data;
    }
    ullong decrypt(ullong data) { //алгоритм дешифровки ГОСТ-28147-89
        ullong left = data;
        ullong right = left & mod32;
        left >>= 32;
        setXkey();
        for (int i = 8; i < 16; ++i) {
            std::swap(xkey[i], xkey[32 - i - 1]);
        }
        data = round(left, right);
        return data;
    }
    int256 getKey() {
        return key;
    }
};

string encryptMessage(const string& message, const int256& key) {  //шифровка сообщения
    Magma cipher(key);
    string encryptedMessage;
    for (char c : message) {
        ullong encryptedChar = cipher.encrypt(c);
        encryptedMessage += to_string(encryptedChar) + " ";
    }
    return encryptedMessage;
}

string decryptMessage(const string& encryptedMessage, const int256& key) { //дешифровка сообщения
    Magma cipher(key);
    string decryptedMessage;
    vector<string> tokens;
    string token;
    for (char c : encryptedMessage) {
        if (c == ' ') {
            tokens.push_back(token);
            token.clear();
        }
        else {
            token += c;
        }
    }
    for (const string& token : tokens) {
        ullong encryptedChar = stoull(token);
        char decryptedChar = cipher.decrypt(encryptedChar);
        decryptedMessage += decryptedChar;
    }
    return decryptedMessage;
}

int main() {
    cout << hex;
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    string message = "Hello, World!";
    cout << "message: " << message << endl;
    string encryptedMessage = encryptMessage(message, key); //вывод слова
    cout << "Encrypted message: " << encryptedMessage << endl; //вывод зашифровонного слова
    string decryptedMessage = decryptMessage(encryptedMessage, key);
    cout << "Decrypted message: " << decryptedMessage << endl; //вывод расшифровонного слова
    return 0;
}