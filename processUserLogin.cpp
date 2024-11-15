/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#include "processUserLogin.h"

// Hash the login password using hash
// this will used to either save hash to file (don't save plaintext passwords)
// or to compare resulting hash against the hash from file 
// returns resulting string 
std::string LoginManager::hashPassword(const std::string &password) {
    const auto hashResult = hasher(password);
    return std::to_string(hashResult);
}

// used to save hashed password to file
// only used when first entering password
// verify if file open
void LoginManager::savePasswordHash(const std::string &hashedPassword) {
    std::ofstream hashfile("userPasswordHash.txt");

    if (hashfile.is_open()) {
        hashfile << hashedPassword;
        std::cout << "Saved password hash to file." << std::endl;
    } else {
        std::cerr << "Failed to open file for saving hash!" << std::endl;
    }
}

// read the stored password hash from a file
// verify file open
// read stored hash into storedPasswordHash var
bool LoginManager::readStoredPasswordHash() {
    std::ifstream hashfile("userPasswordHash.txt");

    if (!hashfile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return false;
    }

    std::getline(hashfile, storedPasswordHash);
    hashfile.close();
    
    return true;
}

// initialization
UserLogin::UserLogin() {}

// Overriding processLogin to UserLogin
// read stored hash from file
// get hashed password 
// if storedpasswordhash is empty, then new user, return success
// if previous user, compare hashes
int UserLogin::processLogin(const std::string &loginPassword) {
    if (!readStoredPasswordHash()) {
        std::cout << "Error reading the stored password hash." << std::endl;
        return 1;
    }

    std::string hashedLoginString = hashPassword(loginPassword); 

    if (storedPasswordHash.empty()) {
        std::cout << "No known user, creating now..." << std::endl;
        savePasswordHash(hashedLoginString);
        std::cout << "New user created and logged in!" << std::endl;
        return 2;
    }

    if (hashedLoginString == storedPasswordHash) {
        return 0;
    } else {
        return 1;
    }
}
