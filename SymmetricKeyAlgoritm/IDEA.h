#pragma once
#include <string>
#include <vector>

using namespace std;

#define ROL32(a, n) (((a) << (n)) | ((a) >> (32 - (n))))

constexpr auto MAX_LIMIT = 65536;
typedef uint16_t PART;
typedef unsigned char BIT;
typedef unsigned char POSITION;
class IDEA
{
private:
	string message = "";
	string key = "";
	vector<PART> subkeys;
	static const int PARTSIZE = 8;


	static BIT getBit(PART var, POSITION pos) {
		var = var >> (pos - 1);
		if (var % 2 == 0)
			return 0;
		return 1;
	}

	static void setBit(PART& var, POSITION pos, BIT val) {
		PART temp = val;
		temp = temp << (pos - 1);
		var = var | temp;
	}

	static BIT getBit(unsigned char var, POSITION pos) {
		var = var >> (pos - 1);
		if (var % 2 == 0)
			return 0;
		return 1;
	}

	static void setBit(unsigned char& var, POSITION pos, BIT val) {
		unsigned char temp = val;
		temp = temp << (pos - 1);
		var = var | temp;
	}

	static void TwoCharsToPART(PART& P, unsigned char ch[]) {
		int charCounter = 1;
		int counter = 1;
		for (int i = 1; i < 17; i++) {
			unsigned char character = ch[charCounter];
			setBit(P, i, getBit(character, counter));
			counter++;
			if (counter == 9) {
				counter = 1;
				charCounter--;
			}
		}

	}

	static string PARTtoChars(PART p) {
		string result = "";

		unsigned char a = 0;
		unsigned char b = 0;

		for (int i = 1; i < 9; i++) {
			setBit(a, i, getBit(p, i));
			setBit(b, i, getBit(p, i + 8));
		}
		if (b != 0)
			result += (char)b;
		if (a != 0)
			result += (char)a;
		return result;
	}

	static uint16_t multiplyModulus(uint16_t a, uint16_t b) {
		uint32_t temp;
		temp = a * b;

		if (temp != 0) {
			temp = ((ROL32(temp, 16) - temp) >> 16) + 1;
		}
		else {
			temp = 1 - a - b;
		}
		return temp & 0xFFFF;
	}

	static uint16_t inverseMultiply(uint16_t a) {
		uint32_t b;
		uint32_t q;
		uint32_t r;
		int32_t t;
		int32_t u;
		int32_t v;
		b = 0x10001;
		u = 0;
		v = 1;

		while (a > 0) {
			q = b / a;
			r = b % a;

			b = a;
			a = r;

			t = v;
			v = u - q * v;
			u = t;
		}

		if (u < 0) {
			u += 0x10001;
		}
		return u;
	}



	static PART additionModulus(PART a, PART b) {
		return ((uint32_t)a + (uint32_t)b) % MAX_LIMIT;
	}

	static string encrypt_16in4(unsigned char buffer[], vector<PART> subkeys) {
		string result = "";

		PART P1 = 0, P2 = 0, P3 = 0, P4 = 0;

		unsigned char TwoCH[2] = { 0 };

		int p_counter = 1;
		int counter = 0;
		for (int i = 0; i < sizeof(buffer); i++) {
			TwoCH[counter] = buffer[i];
			counter++;
			if (counter == 2) {
				if (p_counter == 1)
					TwoCharsToPART(P1, TwoCH);
				else if (p_counter == 2)
					TwoCharsToPART(P2, TwoCH);
				else if (p_counter == 3)
					TwoCharsToPART(P3, TwoCH);
				else if (p_counter == 4)
					TwoCharsToPART(P4, TwoCH);
				p_counter++;
				counter = 0;
			}
		}
		PART K1 = 0;
		PART K2 = 0;
		PART K3 = 0;
		PART K4 = 0;
		PART K5 = 0;
		PART K6 = 0;
		PART temp_1 = 0;
		PART temp_2 = 0;
		for (int key_counter = 0; key_counter < subkeys.size(); key_counter += 6) {
			if (key_counter < 48) {
				K1 = subkeys[key_counter + 0];
				K2 = subkeys[key_counter + 1];
				K3 = subkeys[key_counter + 2];
				K4 = subkeys[key_counter + 3];
				K5 = subkeys[key_counter + 4];
				K6 = subkeys[key_counter + 5];

				P1 = multiplyModulus(P1, K1);				// stepbro 1
				P2 = additionModulus(P2, K2);;				// stepbro 2
				P3 = additionModulus(P3, K3);;				// stepbro 3
				P4 = multiplyModulus(P4, K4);;				// stepbro 4
				temp_1 = P1 ^ P3;							// stepbro 5
				temp_2 = P2 ^ P4;							// stepbro 6

				temp_1 = multiplyModulus(temp_1, K5);		// stepbro 7
				temp_2 = additionModulus(temp_1, temp_2);	// stepbro 8 

				temp_2 = multiplyModulus(temp_2, K6);		// stepbro 9
				temp_1 = additionModulus(temp_1, temp_2);	// stepbro 10

				P1 = P1 ^ temp_2;							// stepbro 11
				P3 = P3 ^ temp_2;							// stepbro 12
				P2 = P2 ^ temp_1;							// stepbro 13
				P4 = P4 ^ temp_1;							// stepbro 14
			}
		}
		P1 = multiplyModulus(P1, subkeys[48]);
		P2 = additionModulus(P2, subkeys[49]);
		P3 = additionModulus(P3, subkeys[50]);
		P4 = multiplyModulus(P4, subkeys[51]);

		result += PARTtoChars(P1);
		result += PARTtoChars(P2);
		result += PARTtoChars(P3);
		result += PARTtoChars(P4);

		return result;
	}

	static vector<PART> subkeyGeneration(string key) {
		if (!key.compare("") || key.length() != 16) {
			throw "The key must be exactly 16 characters long!";
		}
		vector<PART> result;
		PART parts[8] = { 0 };

		unsigned char temp[2] = { 0 };
		int counter = 0;
		int partCounter = 0;
		for (unsigned char i : key) {
			temp[counter] = i;
			counter++;
			if (counter > 1) {
				TwoCharsToPART(parts[partCounter], temp);
				partCounter++;
				counter = 0;
			}
		}
		for (PART i : parts) {
			result.push_back(i);
		}


		return result;
	}

	/*static void printInBit(PART item) {
		for ( int i = 16; i > 0; i-- ) {
			if ( i % 8 == 0 && i!=16 ) {
				cout << " ";
			}
			cout << to_string(getBit(item, i));
		}
		cout << " ";
	}*/


	static void shift25left(vector<PART>& subkey) {
		int subkey_length = subkey.size();
		BIT last_bit = 0;
		BIT first_bit = 0;
		for (int i = 0; i < 25; i++) {
			for (int j = subkey_length - 1; j >= 0; j--) {
				last_bit = getBit(subkey[j], 16);
				subkey[j] = subkey[j] << 1;
				if (first_bit == 1) {
					setBit(subkey[j], 1, first_bit);
				}
				if (j == 0 && last_bit == 1) {
					setBit(subkey[subkey_length - 1], 1, last_bit);
				}
				first_bit = last_bit;
			}
		}
	}
	static string decrypt8chars(unsigned char buffer[], vector<PART> subkeys) {
		string result = "";

		PART P1 = 0, P2 = 0, P3 = 0, P4 = 0;

		unsigned char TwoCH[2] = { 0 };

		int p_counter = 1;
		int counter = 0;
		for (int i = 0; i < sizeof(buffer); i++) {
			TwoCH[counter] = buffer[i];
			counter++;
			if (counter == 2) {
				if (p_counter == 1)
					TwoCharsToPART(P1, TwoCH);
				else if (p_counter == 2)
					TwoCharsToPART(P2, TwoCH);
				else if (p_counter == 3)
					TwoCharsToPART(P3, TwoCH);
				else if (p_counter == 4)
					TwoCharsToPART(P4, TwoCH);
				p_counter++;
				counter = 0;
			}
		}

		PART K1 = 0;
		PART K2 = 0;
		PART K3 = 0;
		PART K4 = 0;
		PART K5 = 0;
		PART K6 = 0;
		PART temp_1 = 0;
		PART temp_2 = 0;


		for (int key_counter = 51; key_counter >= 0; key_counter -= 6) {
			if (key_counter > 3) {
				K1 = inverseMultiply(subkeys[key_counter - 3]);
				K2 = -subkeys[key_counter - 2];
				K3 = -subkeys[key_counter - 1];
				K4 = inverseMultiply(subkeys[key_counter - 0]);
				K5 = subkeys[key_counter - 5];
				K6 = subkeys[key_counter - 4];

				P1 = multiplyModulus(P1, K1);					// stepbro 1
				P2 = additionModulus(P2, K2);					// stepbro 2
				P3 = additionModulus(P3, K3);					// stepbro 3
				P4 = multiplyModulus(P4, K4);					// stepbro 4
				temp_1 = P1 ^ P3;								// stepbro 5
				temp_2 = P2 ^ P4;								// stepbro 6

				temp_1 = multiplyModulus(temp_1, K5);			// stepbro 7
				temp_2 += temp_1;		// stepbro 8 

				temp_2 = multiplyModulus(temp_2, K6);			// stepbro 9
				temp_1 += temp_2;		// stepbro 10

				P1 = P1 ^ temp_2;								// stepbro 11
				P3 = P3 ^ temp_2;								// stepbro 12
				P2 = P2 ^ temp_1;								// stepbro 13
				P4 = P4 ^ temp_1;								// stepbro 14
			}
		}

		P1 = multiplyModulus(P1, inverseMultiply(subkeys[0]));
		P2 = additionModulus(P2, -subkeys[1]);
		P3 = additionModulus(P3, -subkeys[2]);
		P4 = multiplyModulus(P4, inverseMultiply(subkeys[3]));

		result += PARTtoChars(P1);
		result += PARTtoChars(P2);
		result += PARTtoChars(P3);
		result += PARTtoChars(P4);

		return result;
	}


public:
	IDEA(string message, string key) {
		setMessage(message);
		setKey(key);
	}

	IDEA() {}

	~IDEA() {}

	string getMessage() {
		return this->message;
	}
	string getKey() {
		return this->key;
	}

	void setMessage(string message) {
		int msgLength = message.length();
		if (msgLength < 16) {
			for (int i = msgLength; i < 16; i++) {
				message = message + ' ';
			}
		}
		this->message = message;
	}

	void setKey(string key) {
		if (key.length() != 16) {
			throw "The key must have exactly 16 characters";
		}
		this->key = key;
		this->subkeys.clear();
		vector<PART> subkey;
		for (int i = 0; i < 7; i++) {
			if (i == 0) {
				subkey = subkeyGeneration(this->key);
				for (PART k : subkey) {
					this->subkeys.push_back(k);
				}
				continue;
			}
			shift25left(subkey);
			for (PART k : subkey) {
				this->subkeys.push_back(k);
			}
		}

	}

	string encrypt() {
		string result = "";

		unsigned char buffer[PARTSIZE] = { 0 };
		int bufcounter = 0;
		for (char i : this->message) {
			buffer[bufcounter] = i;
			bufcounter++;
			if (bufcounter == PARTSIZE) {
				result += encrypt_16in4(buffer, this->subkeys);
				bufcounter = 0;
				continue;
			}
		}

		if (bufcounter != 0) {
			for (int i = bufcounter; i < PARTSIZE; i++) {
				buffer[i] = ' ';
			}
			result += encrypt_16in4(buffer, this->subkeys);
		}

		return result;
	}

	string decrypt(string encrypted_message, vector<PART> subkeys) {
		string result = "";
		unsigned char buffer[PARTSIZE] = { 0 };
		int bufcounter = 0;
		for (char i : encrypted_message) {
			buffer[bufcounter] = i;
			bufcounter++;
			if (bufcounter == PARTSIZE) {
				result += decrypt8chars(buffer, subkeys);
				bufcounter = 0;
				continue;
			}
		}

		if (bufcounter != 0) {
			for (int i = bufcounter; i < PARTSIZE; i++) {
				buffer[i] = ' ';
			}
			result += decrypt8chars(buffer, subkeys);
		}

		return result;
	}
	string decrypt(string encrypted_message) {
		string result = "";

		unsigned char buffer[PARTSIZE] = { 0 };
		int bufcounter = 0;
		for (char i : encrypted_message) {
			buffer[bufcounter] = i;
			bufcounter++;
			if (bufcounter == PARTSIZE) {
				result += decrypt8chars(buffer, this->subkeys);
				bufcounter = 0;
				continue;
			}
		}

		if (bufcounter != 0) {
			for (int i = bufcounter; i < PARTSIZE; i++) {
				buffer[i] = ' ';
			}
			result += decrypt8chars(buffer, this->subkeys);
		}

		return result;
	}




};

