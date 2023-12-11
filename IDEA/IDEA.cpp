﻿#include <iostream>
#include <fstream>
using namespace std;
#include "IDEA.h"
#include <windows.h>
#include <iomanip>
#include <cstring>

class IDEA
{
public:
	void setKey(byte in[]);
	void setPlainText(byte in[]);
	word16 invMul(word16 x);
	word16 mul(word16 x, word16 y);
	void encryption(word16 in[], word16 out[], word16* Ek);
	void enc();
	void IDEATest();

private:
	void getEncRoundKey(word16* encRoundKey);
	void getDecRoundKey(word16* EK, word16 DK[]);
	byte key[16];
	word16 cipherText[4];
	word16 plainText[4];
	word16 deCipherText[4];
	word16 encRoundKey[52];
	word16 decRoundKey[52];
	void checkRoundKey();
};

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

void IDEA::IDEATest() {
	cout << "The input key is:" << endl;
	int i;
	for (i = 0; i < 16; i++) {
		cout << hex << int(key[i]) << " ";
	}
	cout << endl;
	cout << "The plain text is:" << endl;
	for (i = 0; i < 4; i++) {
		cout << hex << plainText[i] << " ";
	}
	cout << endl;

		
	cout << "The cipherText is:" << endl;
	for (i = 0; i < 4; i++) {
		cout << hex << cipherText[i] << " ";
	}
	cout << endl;

	cout << "The deCipherText is:" << endl;
	for (i = 0; i < 4; i++) {
		cout << hex << deCipherText[i] << " ";
	}
	cout << endl;
}

//std::string Encrypt(std::string& Text) {
//	IDEA idea;
//	if (Text.size() < 8) {
//		Text.resize(8, ' ');
//	}
//	const size_t size = 8;
//	byte plainText[size];
//
//	// Копирование данных из строки в массив байтов
//	std::memcpy(plainText, Text.c_str(), size);
//	idea.setPlainText(plainText);
//	idea.enc();
//	stringstream ss;
//	ss << cipherText; // Записываем значение в строковый поток
//
//	std::string strValue = ss.str(); // Получаем строковое представление
//
//	std::cout << "Значение в виде строки: " << strValue << std::endl;
//	return 
//}

int main(int argc, char const* argv[])
{
	SetConsoleOutputCP(1251);
	IDEA idea;
	byte key[16] = { 0x10, 0x1A, 0x0C, 0x0B, 0x01, 0x11, 0x09, 0x07, 0x32, 0xA1,
		0xB3, 0x06, 0x23, 0x12, 0xD3, 0xF1 };
	idea.setKey(key);
	byte plainText[8] = { 'H','e','l','l','o',' ',' ',' '};
	idea.setPlainText(plainText);
	idea.enc();
	idea.IDEATest();
	return 0;
}