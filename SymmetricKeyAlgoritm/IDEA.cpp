// Proiect_SC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IDEA.h"
#include <string>

#define TEST_STRING "aLorem"


using namespace std;

string IDEA_EncryptString(const std::string& input) {
    IDEA ideatest = IDEA();
    ideatest.setMessage(input);
    ideatest.setKey("ZZZZefghijklmnop");
    string ideaencr = ideatest.encrypt();
    return ideaencr;
}
string IDEA_DecryptString(const std::string& input) {
    IDEA ideatest = IDEA();
    ideatest.setMessage(input);
    ideatest.setKey("ZZZZefghijklmnop");
    string ideadecr = ideatest.decrypt(input);
    return ideadecr;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
