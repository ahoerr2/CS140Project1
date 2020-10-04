//Monoalphabetic substitution cipher by Alex Hoerr and Emily Baker

/*TODO: (* finished) ($ finished needs review) (- work in progress)
*
		Accept Input(Key) from user *
		Check if input is valid(Make uppercase) *
		Store the substitution key *
		Accept a plaintext message from user
		Encrypt the message
		Display message to user

*/

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
string DEBUG_STRING = "All poets, all writers are political. They either maintain the status quo, or they say, ’Something’s wrong, let’s change it for the better.";


//Debug mode
bool DEBUG_MODE = true;

bool validateUserKeyInput(string);
string grabUserInputKey();
string generateRandomKey();
string toUpperCase(string);
string monoSubEncrypt(string message, string key);


int main()
{
	//Asks the user for the key and stores the key in an uppercase string
	cout << "Hello, enter a monoalphabetic key for encryption (26 letters long)." << endl;
	cout << "Leave the key black to use a randomly generated key." << endl;
	string userInputKey = grabUserInputKey();
	userInputKey = toUpperCase(userInputKey);


	if (userInputKey.length() == 0) userInputKey = generateRandomKey();

	if (DEBUG_MODE)
	{
		cout << userInputKey << endl;
		cout << "Size: " << userInputKey.length() << endl;
	}

	//Promts user to enter a new key is the key was invalid
	bool keyInputSuccessful = validateUserKeyInput(userInputKey);

	while (keyInputSuccessful != true)
	{
		cout << "The key is invalid, please input another key." << endl;
		userInputKey = grabUserInputKey();
		keyInputSuccessful = validateUserKeyInput(userInputKey);
	}

	cout << "Key input successful" << endl;
	cout << "Key: " << userInputKey << "\n" << endl;


}

string toUpperCase(string inputString) {
	for (char& c : inputString) c = toupper(c);
}

//generates an uppercase MASC key by shuffling the English alphabet
std::string generateRandomKey() {
	std::string randomKey{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	std::random_device rnd; const auto seed = rnd.entropy() ? rnd() : time(nullptr);
	std::mt19937_64 eng(static_cast<std::mt19937_64::result_type>(seed));
	std::cout << "\nGenerating random key..." << std::endl;
	shuffle(randomKey.begin(), randomKey.end(), eng);
	return randomKey;
}
string grabUserInputKey()
{
	cout << "Key(26 unique letters): ";
	string inputKey = "";
	std::getline(cin, inputKey);
	return inputKey;
}

bool validateUserKeyInput(string key)
{
	if (key.length() != 26) return false;

	//Checks if each character is within an ENGLISH ASCII uppercase character
	for (char c : key)
	{
		if (DEBUG_MODE) cout << "Character: " << c << endl;
		if (c > 64 && c < 91) continue;
		else return false;
	}

	return true;
}


string monoSubEncrypt(string message, string key) {

}