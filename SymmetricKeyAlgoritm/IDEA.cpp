#include <iostream>
#include <fstream>
using namespace std;
#include "IDEA.h"


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



//int main(int argc, char const* argv[])
//{
//	IDEA idea;
//	byte key[16] = { 0x10, 0x1A, 0x0C, 0x0B, 0x01, 0x11, 0x09, 0x07, 0x32, 0xA1,
//		0xB3, 0x06, 0x23, 0x12, 0xD3, 0xF1 };
//	idea.setKey(key);
//	byte plainText[8] = { 0xA7, 0x95, 0x87, 0x23, 0x1F, 0x2C, 0x6D, 0x73 };
//	return 0;
//}