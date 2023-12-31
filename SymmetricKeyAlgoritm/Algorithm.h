#pragma once
#include <string>
#include <vector>
//
//std::string encryptCAST128(const std::string& input);
//std::string decryptCAST128(const std::vector<Cast128::Block>& encryptedBlocks);
void Run(const std::string& inputt);
using Algorithm = std::string(*)(const std::string&);

std::string AES_encryptString(const std::string& input);
std::string AES_decryptString(const std::string & input);
std::string Blowfish_encryptString(const std::string& input);
std::string Blowfish_decryptString(const std::string& input);
std::string RS5_encryptString(const std::string& start_message);
std::string RS5_decryptString(const std::string& start_message);


std::string encryptMessage(const std::string& message);
std::string decryptMessage(const std::string& encryptedMessage);

std::string IDEA_EncryptString(const std::string& input);
std::string IDEA_DecryptString(const std::string& input);
//std::string DES_encryptString(const std::string& input);
//std::string DES_decryptString(const std::string & input);
/// Òàê æå êàê ó ìåíÿ ïèùèòå íàçâàíèå ôóíêöèè øèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó)
/// È íàçâàíèå ôóíêöèè äåøèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó ÂÀÆÍÎ!!! ñòðîêà ýòî âàø øèôð)
