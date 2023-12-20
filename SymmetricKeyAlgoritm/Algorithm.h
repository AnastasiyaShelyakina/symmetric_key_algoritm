#pragma once
#include <string>
#include <vector>

using Algorithm = std::string(*)(const std::string&);

std::string RS5_encryptString(const std::string& input);
std::string RS5_decryptString(const std::string& input);
//
//std::string encryptCAST128(const std::string& input);
//std::string decryptCAST128(const std::vector<Cast128::Block>& encryptedBlocks);
void Run(const std::string& inputt);
using Algorithm = std::string(*)(const std::string&);

std::string AES_encryptString(const std::string& input);
std::string AES_decryptString(const std::string & input);
std::string Blowfish_encryptString(const std::string& input);
std::string Blowfish_decryptString(const std::string& input);
//std::string DES_encryptString(const std::string& input);
//std::string DES_decryptString(const std::string & input);
/// Òàê æå êàê ó ìåíÿ ïèùèòå íàçâàíèå ôóíêöèè øèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó)
/// È íàçâàíèå ôóíêöèè äåøèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó ÂÀÆÍÎ!!! ñòðîêà ýòî âàø øèôð)
