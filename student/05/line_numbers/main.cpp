#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string InputFileName = "";
    string OutputFileName = "";
    cout << "Input file: ";
    getline(cin, InputFileName);
    cout << "Output file: ";
    getline(cin, OutputFileName);

    ifstream InputFile(InputFileName);
    if ( not InputFile ) {
            cout << "Error! The file "<< InputFileName <<" cannot be opened." << endl;
            return EXIT_FAILURE;
        }
        ofstream outputFile(OutputFileName);

        int LineNumber = 1;
        string line;

        while (getline(InputFile, line)) {
            // Kirjoitetaan rivi tulostiedostoon rivinumeron kera
            outputFile << LineNumber << " " << line << endl;
            LineNumber++;
        InputFile.close();
        outputFile.close();

    }



    return 0;
}
