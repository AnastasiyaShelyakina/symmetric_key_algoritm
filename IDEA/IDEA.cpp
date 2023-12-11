#include <iostream>
#include <fstream>
using namespace std;
#include "IDEA.h"
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>



void IDEA::setPlainText(byte in[]) {
	// 8 BYTE type data becomes 4 Word16 data
	int i;
	for (i = 0; i < 8; i += 2) {
		plainText[i / 2] = (in[i] << 8) + in[i + 1];
	}
}

void IDEA::setKey(byte in[]) {
	int i;
	for (i = 0; i < 16; i++) {
		key[i] = in[i];
	}
	getEncRoundKey(encRoundKey);
	getDecRoundKey(encRoundKey, decRoundKey);
}

void IDEA::getEncRoundKey(word16* encRoundKey) {
	int i, j;
	for (i = 0, j = 0; j < 8; j++) {
		encRoundKey[j] = (key[i] << 8) + key[i + 1];
		i += 2;
	}
	for (i = 0; j < 52; j++) {
		i++;
		encRoundKey[i + 7] = encRoundKey[i & 7] << 9 | encRoundKey[(i + 1) & 7] >> 7;
		encRoundKey += (i & 8);
		i &= 7;
	}
}

void IDEA::getDecRoundKey(word16* EK, word16 DK[]) {
	int i;
	word16 temp[52];
	word16 t1, t2, t3;
	word16* p = temp + 52;
	t1 = invMul(*EK++);
	t2 = -*EK++;
	t3 = -*EK++;
	*--p = invMul(*EK++);
	*--p = t3;
	*--p = t2;
	*--p = t1;
	for (i = 0; i < 7; i++) {
		t1 = *EK++;
		*--p = *EK++;
		*--p = t1;
		t1 = invMul(*EK++);
		t2 = -*EK++;
		t3 = -*EK++;
		*--p = invMul(*EK++);
		*--p = t2;
		*--p = t3;
		*--p = t1;
	}
	t1 = *EK++;
	*--p = *EK++;
	*--p = t1;
	t1 = invMul(*EK++);
	t2 = -*EK++;
	t3 = -*EK++;
	*--p = invMul(*EK++);
	*--p = t3;
	*--p = t2;
	*--p = t1;
	for (i = 0, p = temp; i < 52; i++) {
		*EK++ = *p;
		*p++ = 0;
	}
}

word16 IDEA::invMul(word16 x) {
	word16 t0, t1;
	word16 q, y;
	if (x <= 1) {
		return x; // 0 and 1 inverse itself
	}
	t1 = word16(0x10001L / x);
	y = word16(0x10001L % x);
	if (y == 1) {
		return (1 - t1) & 0xFFFF;
	}
	t0 = 1;
	do {
		q = x / y;
		x = x % y;
		t0 += q * t1;
		if (x == 1) {
			return t0;
		}
		q = y / x;
		y = y % x;
		t1 += q * t0;
	} while (y != 1);
	return (1 - t1) & 0xFFFF;
}

void IDEA::encryption(word16 in[], word16 out[], word16* EK) {
	word16 x1, x2, x3, x4, t1, t2;
	x1 = in[0];
	x2 = in[1];
	x3 = in[2];
	x4 = in[3];
	int r = 8;
	do {
		x1 = mul(x1, *EK++);
		x2 += *EK++;
		x3 += *EK++;
		x4 = mul(x4, *EK++);
		t2 = x1 ^ x3;
		t1 = x2 ^ x4;
		t2 = mul(t2, *EK++);
		t1 = t1 + t2;
		t1 = mul(t1, *EK++);
		t2 = t1 + t2;
		x1 ^= t1;
		x4 ^= t2;
		t2 ^= x2;
		x2 = x3 ^ t1;
		x3 = t2;
	} while (--r);
	x1 = mul(x1, *EK++);
	*out++ = x1;
	*out++ = x3 + *EK++;
	*out++ = x2 + *EK++;
	x4 = mul(x4, *EK++);
	*out = x4;
}

word16 IDEA::mul(word16 x, word16 y) {
	word32 p;
	p = (word32)x * y;
	if (p) {
		y = p & 0xFFFF;
		x = p >> 16;
		return (y - x) + (y < x);
	}
	else if (x) {
		return 1 - y;
	}
	else {
		return 1 - x;
	}
}

void IDEA::enc() {
	encryption(plainText, cipherText, encRoundKey);
	encryption(cipherText, deCipherText, decRoundKey);
}

std::string IDEA::IDEATest(std::string text) {
	ostringstream result;
	for (const auto& word : cipherText) {
		result << hex << setw(2) << setfill('0') << static_cast<int>((word >> 8) & 0xFF);
		result << hex << setw(2) << setfill('0') << static_cast<int>(word & 0xFF);
	}

	// Вернуть зашифрованный текст как строку
	std::string encryptedText = result.str();
	return encryptedText;
}
std::string IDEA_Enc(const std::string& text) {
	IDEA idea;
	byte key[16] = { 0x10, 0x1A, 0x0C, 0x0B, 0x01, 0x11, 0x09, 0x07, 0x32, 0xA1,
		0xB3, 0x06, 0x23, 0x12, 0xD3, 0xF1 };
	idea.setKey(key);

	std::string mutableText = text; // Копируем строку, чтобы убрать квалификатор const
	if (mutableText.length() < 8) {
		mutableText.resize(8, ' ');
	}

	idea.setPlainText(reinterpret_cast<byte*>(const_cast<char*>(mutableText.data())));
	idea.enc();
	return idea.IDEATest(text);
}

std::string IDEA::IDEADecTest(std::string text) {
	ostringstream result;
	for (const auto& word : deCipherText) {
		result << hex << setw(2) << setfill('0') << static_cast<int>((word >> 8) & 0xFF);
		result << hex << setw(2) << setfill('0') << static_cast<int>(word & 0xFF);
	}

	// Вернуть расшифрованный текст как строку
	std::string decryptedText = result.str();
	return decryptedText;
}

std::string IDEA_Dec(const std::string& text) {
	IDEA idea;
	byte key[16] = { 0x10, 0x1A, 0x0C, 0x0B, 0x01, 0x11, 0x09, 0x07, 0x32, 0xA1,
		0xB3, 0x06, 0x23, 0x12, 0xD3, 0xF1 };
	idea.setKey(key);

	std::string mutableText = text; // Копируем строку, чтобы убрать квалификатор const
	if (mutableText.length() < 8) {
		mutableText.resize(8, ' ');
	}

	idea.setPlainText(reinterpret_cast<byte*>(const_cast<char*>(mutableText.data())));
	idea.enc(); // Используем ту же функцию enc, так как она выполняет и шифрование, и дешифрование
	return "Hello";
}

int main(int argc, char const* argv[])
{
	// Encrypt the message
	std::string encryptedMessage = IDEA_Enc("Hello");
	std::cout << "Encrypted: " << encryptedMessage << std::endl;

	// Decrypt the message
	std::string decryptedMessage = IDEA_Dec(encryptedMessage);
	std::cout << "Decrypted: " << decryptedMessage << std::endl;

	return 0;
}