// Proiect_SC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IDEA.h"
#include <string>

#define TEST_STRING "aLorem"


using namespace std;

string IDEA_Encrypt(string input) {
    IDEA ideatest = IDEA();
    ideatest.setMessage(input);
    ideatest.setKey("ZZZZefghijklmnop");
    string ideaencr = ideatest.encrypt();
    return ideaencr;
}
string IDEA_Decrypt(string input) {
    IDEA ideatest = IDEA();
    ideatest.setMessage(input);
    ideatest.setKey("ZZZZefghijklmnop");
    string ideadecr = ideatest.decrypt(IDEA_Encrypt(input));
    return ideadecr;
}

int main()
{
    //  IDEA ---------------------------------------
    cout << "IDEA ALGORITHM:" << endl;
    string input = "Kakdela";
    string ideaencr = IDEA_Encrypt(input);
    string ideadecr = IDEA_Decrypt(input);
    cout << "Encrypted: " << ideaencr << endl;
    cout << "Decrypted: " << ideadecr << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
