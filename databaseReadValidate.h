/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#ifndef DATABASE_READ_VALIDATE_H
#define DATABASE_READ_VALIDATE_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "blowfish/blowfish.h"

std::string from_uint(uint32_t sh);

std::string decryptCipher(std::string key, std::string cipher);

void databaseReadValidate(std::string loginPassword, std::map<std::string, std::string>* databaseArray);

#endif
