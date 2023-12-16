#pragma once
#include <string>
using Algorithm = std::string(*)(const std::string&);

std::string AES_encryptString(const std::string& input);
std::string AES_decryptString(const std::string & input);
std::string Blowfish_encryptString(const std::string& input);
std::string Blowfish_decryptString(const std::string& input);
/// Òàê æå êàê ó ìåíÿ ïèùèòå íàçâàíèå ôóíêöèè øèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó)
/// È íàçâàíèå ôóíêöèè äåøèôðîâàíèÿ (îíà ïðèíèìàåò ñòðîêó è âîçâðàùàåò ñòðîêó ÂÀÆÍÎ!!! ñòðîêà ýòî âàø øèôð)
