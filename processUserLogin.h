/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#ifndef PROCESS_USER_LOGIN_H
#define PROCESS_USER_LOGIN_H

#include <string>
#include <iostream>
#include <fstream>
#include <functional>

// base class
class LoginManager {
protected:
    std::string storedPasswordHash;
    std::hash<std::string> hasher;
    
    std::string hashPassword(const std::string &password);

    bool readStoredPasswordHash();

    void savePasswordHash(const std::string &hashedPassword);

public:
    virtual int processLogin(const std::string &loginPassword) = 0;
};

class UserLogin : public LoginManager {
public:
    UserLogin(); 
    int processLogin(const std::string &loginPassword) override;
};

#endif
