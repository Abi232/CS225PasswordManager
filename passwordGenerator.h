/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <string>
#include <random>

class passwordGenerator
{
private:
    std::mt19937 &randomEngine;
    char generateRandomChar();

public:
    passwordGenerator(std::mt19937 &engine);
    std::string getPassword();
};

#endif // PASSWORDGENERATOR_H
