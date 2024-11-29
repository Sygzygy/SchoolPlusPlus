/*
* Menu class for the code 39 cryptograph by Jason Joseph
* Created on October 20, 2024
* 
* This class provides a simple user interface for accessing the Code39 cryptography features.
* It allows the user to choose between decrypting binary or hex files, or encrypting a text file into binary or hex.
*/

#pragma once
#include "Code39Cryptograph.h"
#include <iostream>
#include <string>

using namespace std;

/* *********************************************************************************************** */
/*                                          Menu Class                                             */
/*                           Menu implementation for easy user access                              */
/* *********************************************************************************************** */

class Menu {
public:
    Menu() {
        cin.clear();
        int userInput = -1;

        while (userInput != 0) {
            cout << "Code 39 Cryptograph by Jason Joseph\n\n"
                << "Please choose an option:\n"
                << "1: Decrypt a binary text file\n"
                << "2: Decrypt a text file containing hex3 values\n"
                << "3: Encrypt a text file into binary or hex3\n"
                << "0: Exit Program\n"
                << endl << "> ";

            cout.flush(); // Fix for issue with flushing the output buffer

            userInput = getValidIntInput();
            cout << endl;

            switch (userInput) {
            default:
                cout << "Invalid option. Please try again." << endl;
                break;

            case 0:
                cout << "Thank you for using my program, now exiting..." << endl;
                break;

            case 1:
                processFile(false); // Decrypt binary file
                break;

            case 2:
                processFile(true); // Decrypt hex3 file
                break;

            case 3:
                encryptionMenuHelper();
                break;
            }
        }
    }

private:
    // Helper function to handle the encryption menu
    void encryptionMenuHelper() {
        string fileName;
        int userMethod = -1;
        bool encryption = true;

        while (encryption) {
            cout << "Please select an output file method: \n"
                << "1: Binary text file\n"
                << "2: Hex code text file\n"
                << "0: Return to main menu\n"
                << "> ";

            userMethod = getValidIntInput();

            switch (userMethod) {
            default:
                cout << "Invalid option, please try again." << endl;
                break;

            case 0:
                cout << endl;
                encryption = false;  // Return to main menu
                break;

            case 1: {
                bool backout = encryptionFileHelper(fileName);  // Check if the user backs out
                if (!backout) {
                    Code39Encryptor encryptor(fileName, false); // Encrypt to binary file
                    cout << "File encrypted successfully to binary format." << endl;
                    encryption = false;  // Exit encryption menu after successful encryption
                }
                break;  // Stay in the encryption menu if backout
            }

            case 2: {
                bool backout = encryptionFileHelper(fileName);  // Check if the user backs out
                if (!backout) {
                    Code39Encryptor encryptor(fileName, true); // Encrypt to hex file
                    cout << "File encrypted successfully to hex format." << endl;
                    encryption = false;  // Exit encryption menu after successful encryption
                }
                break;  // Stay in the encryption menu if backout
            }
            }
        }
    }

    // Helper function to handle file input and allow the user to back out to the encryption menu
    bool encryptionFileHelper(string& fileName) {
        cout << "Please enter the name of your file or enter 'x' to return to encryption menu: " << endl << "> ";
        getline(cin, fileName);

        // Check if the user wants to return to the encryption selection menu
        if (fileName == "x" || fileName == "X") {
            cout << "Returning to encryption selection menu..." << endl << endl;
            return true;  // Return true to indicate backout
        }

        return false;  // Return false if the user proceeds with encryption
    }

    // Helper function to process file for decryption
    void processFile(bool isHex) {
        string fileName;

        if (isHex) {
            cout << "Please enter the name of your hex3 file or enter 'x' to return to main menu: " << endl << "> ";
        }
        else {
            cout << "Please enter the name of your binary text file or enter 'x' to return to main menu: " << endl << "> ";
        }

        getline(cin, fileName);

        // Check if the user wants to return to the main menu
        if (fileName != "x" && fileName != "X") {
            try {
                Code39Decryptor decryptor(fileName, isHex); // Decrypt the file (hex or binary based on input)
            }
            catch (const runtime_error& e) {
                cerr << "Error decrypting file: " << e.what() << endl;
            }
        }
        else {
            cout << endl;
        }
    }

    // Helper function to get and validate integer input from the user
    int getValidIntInput() {
        int input;
        while (true) {
            cin >> input;

            // Check if the input is invalid
            if (cin.fail()) {
                cin.clear(); // Clear the error flag on cin
                cin.ignore(10000, '\n'); // Discard invalid input up to the newline
                cout << "Invalid input. Please enter an integer: ";
            }
            else {
                cin.ignore(10000, '\n'); // Discard any extra input, like leftover newlines
                return input; // Valid integer, return it
            }
        }
    }
}; // end of class Menu
