/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#include "databaseReadValidate.h"

// encryption function taken from https://github.com/avinal/blowfish/blob/main/tests/Main.cpp
// modified by Abigail Geiger to create database encryption
// uses blowfish and reinterprets the value with the blowfish key
// returns deciphered text
std::string decryptCipher(std::string key, std::string cipher)
{
    Blowfish blowfish(key);
    std::string decipher("");

    uint32_t lm, rm;
    int len = cipher.length();
    for (size_t i = 0; i < len; i += 8)
    {
        lm = 0;
        rm = 0;
        lm = *reinterpret_cast<unsigned int *>(
            const_cast<char *>(cipher.substr(i, 4).c_str()));
        rm = *reinterpret_cast<unsigned int *>(
            const_cast<char *>(cipher.substr(i + 4, 4).c_str()));
        blowfish.decrypt(lm, rm);
        decipher += from_uint(lm) + from_uint(rm);
    }

    return decipher;
}

// Decryption function
// Read file, verify is open
// gets line from encrypted database
// separate the key from the value with ,
// decrypts the password (value)
// insert to databaseArray
void databaseReadValidate(std::string loginPassword, std::map<std::string, 
                        std::string> *databaseArray)
{
    std::string filePath = "PassDatabase.csv";
    std::ifstream encryptedDatabase(filePath);
    if (!encryptedDatabase.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line, key, value;
    std::string decryptedPassword;
    while (std::getline(encryptedDatabase, line))
    {
        std::stringstream processingStream(line);
        std::getline(processingStream, key, ',');
        std::getline(processingStream, value, ',');

        decryptedPassword = decryptCipher(loginPassword, value);

        (*databaseArray).insert({key, decryptedPassword});
    }

    encryptedDatabase.close();
}
