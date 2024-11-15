/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#ifndef ENCRYPT_ENTRY_ADD_DATABASE_H
#define ENCRYPT_ENTRY_ADD_DATABASE_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdint>
#include <blowfish/blowfish.h>

std::string from_uint(uint32_t sh);

std::string encryptEntry(std::string key, std::string message);

void encryptDatabaseAddEntry(std::string loginPassword, std::map<std::string, std::string>* databaseArray);

#endif

