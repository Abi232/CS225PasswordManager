/*
 Abigail Geiger
CS225 Project
11/10/2024
*/

#include <iostream>
#include "databaseReadValidate.h"
#include "encryptEntryAddDatabase.h"
#include "RandomPasswordGenerator.h"
#include "processUserLogin.h"

// check if number
bool isNumber(const std::string &userInputNumber)
{
    try
    {
        std::stoi(userInputNumber);
        return true;
    }
    catch (std::invalid_argument &)
    {
        return false;
    }
}

// seed based on device hardware
// initial login to fail
// go to processUserLogin after password 
// verify with databaseReadValidate
// can see passwords, add password, or quit
int main()
{
    std::string loginPassword;
    std::string tempNewPassword;
    std::map<std::string, std::string> databaseArray;
    std::map<std::string, std::string> *databaseArrayPtr = &databaseArray;
    int returnCode;
    std::string userInputSwitch;
    std::string specificUsername;
    std::map<std::string, std::string>::iterator tempMap;
    int passwordLength = 16; // hardcode secure password length
    std::random_device rd;
    std::mt19937 randomEngine(rd());

    passwordGenerator passwordGen(randomEngine);

    std::cout << "Welcome to Password Manager" << std::endl;
    UserLogin userLogin;

    int result = 1;  
    
    while (result != 0) {
        std::cout << "Enter your password: ";
        std::cin >> loginPassword; 

        result = userLogin.processLogin(loginPassword);

        if (result == 0) {
            std::cout << "Login successful!" << std::endl;
        } else if (result == 1) {
            std::cout << "Incorrect password. Please try again." << std::endl;
        } else if (result == 2) {
            std::cout << "New user created and logged in!" << std::endl;
            break;
        }
    }

    databaseReadValidate(loginPassword, databaseArrayPtr);
    do
    {
        std::cout << "Type 1 for viewing passwords. Type 2 for adding passwords. Type 3 to quit: " << std::endl;
        std::cin >> userInputSwitch;

        while (!isNumber(userInputSwitch))
        {
            std::cout << "error, enter a digit: ";
            std::cin >> userInputSwitch;
        }

        int selectionChoice = std::stoi(userInputSwitch);
        if (selectionChoice == 1 || selectionChoice == 2 || selectionChoice == 3)
        {
            switch (selectionChoice)
            {
            case 1:
                std::cout << "username:      , password:     " << std::endl;
                for (tempMap = databaseArray.begin(); tempMap != databaseArray.end(); tempMap++)
                {
                    std::cout << tempMap->first << "," << tempMap->second << std::endl;
                }
                break;
            case 2:
                std::cout << "Please enter a username to be associated with the password: ";
                std::cin >> specificUsername;

                tempNewPassword = passwordGen.getPassword();

                databaseArray.insert(databaseArray.begin(), std::make_pair(specificUsername, tempNewPassword));

                encryptDatabaseAddEntry(loginPassword, databaseArrayPtr);
                break;
            case 3:
                std::exit(1);
            default:
                break;
            }
        }
    } while (1);
}
