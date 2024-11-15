/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#include "encryptEntryAddDatabase.h"

// converts a 32-bit unsigned int to a string of 4 bytes
// sh is any int
// iterates over int
// returns string
std::string from_uint(uint32_t sh)
{
    std::string re("");
    for (int i = 0; i < 4; i++)
    {
        re += (unsigned char)(sh >> i * 8);
    }
    return re;
}

// encryption function taken from https://github.com/avinal/blowfish/blob/main/tests/Main.cpp
// modified by Abigail Geiger to create database encryption
// uses blowfish library to encrypt
// returns ciphertext
std::string encryptEntry(std::string key, std::string message) {
    std::string cipher("");

    int len = message.length();
    int j = sizeof(uint32_t);
    int rem =
        ((len > j * 2) ? (((len / j * 2) + 1) * j * 2 - len) : (j * 2 - len));
    
    message.append(rem, '\0');
    len = message.length();
    Blowfish blowfish(key);

    uint32_t lm, rm;
    
    for (size_t i = 0; i < len; i += 8)
    {
        lm = 0;
        rm = 0;
        lm = *reinterpret_cast<unsigned int *>(const_cast<char *>(message.substr(i, j).c_str()));
        rm = *reinterpret_cast<unsigned int *>(const_cast<char *>(message.substr(i + 4, j).c_str()));
        blowfish.encrypt(lm, rm);
        cipher += from_uint(lm) + from_uint(rm);
    }

    return cipher;
}

// takes in loginPassword and databaseArray map
// Opens file to write to database, verify open
// tempMap is an iterator through databaseArray
// use encrypt function and the value of the tempMap
// writes key value pair to file
// close file
void encryptDatabaseAddEntry(std::string loginPassword, std::map<std::string, std::string>* databaseArray) {
    std::map<std::string, std::string>::iterator tempMap;
    std::string singleEncryptedString;
    std::cout << "Opening database to write new password" << std::endl;
    std::string filePath = "PassDatabase.csv";
    std::ofstream encryptedDatabase(filePath);
    if (!encryptedDatabase.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    for (tempMap = databaseArray->begin(); tempMap != databaseArray->end(); tempMap++)
    {
        singleEncryptedString = encryptEntry(loginPassword, tempMap->second);
        encryptedDatabase << tempMap->first << ",";
        encryptedDatabase << singleEncryptedString << ",\n";
    }

    encryptedDatabase.close();
}
