//Monoalphabetic substitution cipher by Alex Hoerr and Emily Baker

#include <iostream>
#include <string>
#include <random>
#include <ctime>

using std::string;
using std::cout;
using std::cin;
using std::endl;

//Skip user input and use a randomly generated key(debug)
bool SKIP_USER_INPUT = false;

//Debug String
string DEBUG_STRING = "The fitness gram pacer test, is a multi stage test, that...";
//string DEBUG_STRING = "ABCD";

//Debug mode
bool DEBUG_MODE = true;
bool DEBUG_ENCRYPT = false;

bool validateUserKeyInput(string);
string grabUserInputKey();
string generateRandomKey();
string toUpperCase(string);
string monoSubEncrypt(string, string, int);
int grabUserSpacing();
bool isValidChar(char);
void validatePlaintext(string&, int spacing);


int main()
{
    cout << "Testing Monoalphabetic Substitution Cipher (MASC) program: " << endl << endl;
        
    int userOption = 0
    string userInputKey;
        
    //Asks the user to make a selection
    do 
    {
        cout << "Please make a selection: " << endl << "(1)Type in a key" << endl << "(2)Have a key generated for you" << endl << endl << "Choice: ";
        std::cin >> userOption;
        std::cin.ignore();
    } 
    while (userOption != 1 && userOption != 2);

    //Generates randomkey or asks for key input based on response
    if(userOption == 1)
    {
        userInputKey = grabUserInputKey();
    }
    else
    {
        userInputKey = generateRandomKey();
    }

    //uppercases input
    userInputKey = toUpperCase(userInputKey);
    
    //debug information
    if (DEBUG_MODE)
    {
        cout << userInputKey << endl;
        cout << "Size: " << userInputKey.length() << endl;
    }

    //Promts user to enter a new key is the key was invalid
    bool keyInputSuccessful = validateUserKeyInput(userInputKey);

    while (keyInputSuccessful != true)
    {
        userInputKey = grabUserInputKey();
        userInputKey = toUpperCase(userInputKey);
        keyInputSuccessful = validateUserKeyInput(userInputKey);
    }

    cout << "Key is now: " << userInputKey << endl << endl;

    //Prompts user to enter plaintext for encryption
    cout << "Enter the plaintext: " << endl;
    string plaintext = "";
    std::getline(cin , plaintext);
     
    //debug information
    if(DEBUG_MODE)
    {
        cout << "Plaintext: " << plaintext << endl;
    }
    
    //prompts user for spacing parameter
    cout << endl << "We will now disguise the original spacing." << endl << "How many letters should appear in each grouping? " << endl << "(Press enter for a default spacing of 5, negative entry provides original spacing.)";
    
    int userSpacing = grabUserSpacing();
    
    validatePlaintext(plaintext,userSpacing);
    
        //debug information
    if(DEBUG_MODE)
    {
        cout << "User Spacing: " << userSpacing << endl;
    }
    
     if (DEBUG_MODE)
     {
         cout << "Message: " << plaintext << endl;
     }
       
    //outputs encrypted plaintext
    cout << endl << endl << "Ciphertext is: " << monoSubEncrypt(plaintext, userInputKey, userSpacing)<<endl;
    
}

//Puts string in all uppercase
string toUpperCase(string inputString)
{
    for (char& c : inputString)
    {
        c = toupper(c);
    }
        
    return inputString;
}

//generates an uppercase MASC key by shuffling the English alphabet
std::string generateRandomKey() 
{
    std::string randomKey{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    std::random_device rnd; const auto seed = rnd.entropy() ? rnd() : time(nullptr);
    std::mt19937_64 eng(static_cast<std::mt19937_64::result_type>(seed));
    std::cout << "\nGenerating random key..." << std::endl;
    shuffle(randomKey.begin(), randomKey.end(), eng);
    return randomKey;
}

//asks for a key from the user
string grabUserInputKey()
{
    cout << endl << endl << "Enter a key to be used for ecryption. Include each letter of the alphabet, none repeated: " << endl;
    string inputKey = "";
    std::getline(cin, inputKey);
    return inputKey;
}

//Determines if the user input key is valid, meaning all 26 letters, none repeating, only letters
bool validateUserKeyInput(string key)
{
    //checks key length for 26
    if (key.length() != 26)
    {
        cout << "Incorrect key length. Must be 26 characters." << endl;
        return false;
    }
    

    //Checks if each character is within an ENGLISH ASCII uppercase character
    for (char c : key)
    {
        //debug information
        if (DEBUG_MODE) 
        {
            cout << "Character: " << c << endl;
        }
            
        if (c > 64 && c < 91) 
        {
            continue;
        }
        else
        {
            cout << "Error: invalid character in key." << endl;
            return false;
        }
    }

    //Does an iterative search to check that all characters are unique
    char character;
    for (unsigned index{ 0 }; index < key.length() - 1; index++) 
    {
        character = key.at(index);
        for (unsigned searchIndex{ index + 1 }; searchIndex < key.length(); searchIndex++) 
        {
            if (character == key.at(searchIndex)) 
            {
                cout << "Error: Duplicate characters found" << endl;
                return false;
            }
        }
    }

    return true;
}

//prompts the user for amount of letters before a space is added in the encryption
int grabUserSpacing()
{
    int spacing = 5;
    int inputSpace;
    
    cout << "Spacing: ";
    if (cin.peek() == '\n') 
    {
         return spacing;
    }
        
    cin >> inputSpace;

    if (inputSpace == 0) 
    {
        return spacing;
    }
        spacing = inputSpace;

    
    return spacing;
}

//determines if a character is plaintext
bool isValidChar(char c) 
{
    if ((c > 96 && c < 123) || (c > 64 && c < 91)) 
    {
         return true;
    }
        
    return false;
}

//determines if a string is valid plaintext using isValidChar
void validatePlaintext(string& plaintext, int spacing) 
{
    for (unsigned index = 0; index < plaintext.length(); index++) 
    {
        if (isValidChar(plaintext.at(index))) 
        {
               continue;
        }
        else if (plaintext.at(index) == ' ' && spacing <= -1) 
        {
                continue;
        }
        else 
        {
            plaintext.erase(plaintext.begin() + index);
            index--;
        }
    }
}

//encrypts the valid plaintext using spacing and key
string monoSubEncrypt(string message, string key, int spacing) 
{

    int index = 0;
    char c;
    string encryptedMessage = "";
    int spacingIndex = 0;
    int encryptedLength = message.length() + (message.length() / spacing);

    for (unsigned index{ 0 }; index < message.length(); index++) 
    {
        //Checks if character is valid and uppercase/lowercase, otherwise skip encryption
        c = message.at(index);

        if (spacing <= -1 && c == ' ') 
        {
            encryptedMessage += ' ';
            continue;
        }

        if (c > 96 && c < 123)
        {
            c -= 97;
        }
        else if (c > 64 && c < 91)
        {
            c -= 65;
        }

        if (DEBUG_MODE) 
        {
            cout << "c: "<< message.at(index) << " = "<< static_cast<int>(c) << endl;
        }

        if ((spacingIndex % spacing == 0 && index != 0) && spacing >= 1) 
        {
            encryptedMessage += ' ';
            spacingIndex = 0;
        }

        encryptedMessage += key.at(static_cast<int>(c));
        spacingIndex++;

    }

    return encryptedMessage;
}

