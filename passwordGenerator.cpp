/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#include "RandomPasswordGenerator.h"

// Constructor that accepts seeded engine from main
// tried to seed here, but created the same password
// so seed from main is required
passwordGenerator::passwordGenerator(std::mt19937 &engine)
    : randomEngine(engine) {}


// Generate a random character
char passwordGenerator::generateRandomChar()
{
    std::uniform_int_distribution<int> dist(0, 61);
    int randomIndex = dist(randomEngine);

    if (randomIndex < 26)
    {
        return 'a' + randomIndex; 
    }
    else if (randomIndex < 52)
    {
        return 'A' + (randomIndex - 26); 
    }
    else
    {
        return '0' + (randomIndex - 52); 
    }
}

// iterates through password length 
// Generates the password based on random from above
std::string passwordGenerator::getPassword()
{
    std::string password;
    const int passwordLength = 16;

    for (int i = 0; i < passwordLength; ++i)
    {
        password += generateRandomChar();
    }

    return password;
}
