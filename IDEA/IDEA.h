//define the type of data
typedef unsigned char byte;
typedef unsigned short word16;//16bit
typedef unsigned long word32;//32bit

class IDEA
{
public:
	void setKey(byte in[]);
	void setPlainText(byte in[]);
	word16 invMul(word16 x);
	word16 mul(word16 x, word16 y);
	void encryption(word16 in[], word16 out[], word16* Ek);
	void enc();
	string IDEATest(std::string text);
	string IDEADecTest(std::string text);

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