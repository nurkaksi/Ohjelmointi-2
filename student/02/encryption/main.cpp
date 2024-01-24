#include <iostream>
#include <string>
#include <cctype>

using namespace std;


int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    cin >> key;
    if ( key.length() != 26 ) {
        cout << "Error! The encryption key must contain 26 characters."<< endl;
        return EXIT_FAILURE;
    }

    for ( char letter : key ) {
        if (!islower(letter)) {
            cout << "Error! The encryption key must contain only lower case characters."<< endl;
            return EXIT_FAILURE;
        }
    }

    string text = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text;

    for (char letter : text) {
        if(!islower(letter)) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    string alpha = "abcdefghijklmnopqrstuvwxyz";

    string encryption = "";
    for (char letter : text) {
        encryption += key.at(alpha.find(letter));
        }
    cout << "Encrypted text: " << encryption << endl;


    return 0;
}
