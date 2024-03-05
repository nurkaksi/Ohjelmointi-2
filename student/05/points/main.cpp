#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    string file_name = "";
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream open_file(file_name);
    if ( not open_file ) {
        cout << "Error! The file " << file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        map<string, int> players;
        string line;
        while (getline(open_file, line)) {
            string name;
            int score;
            // Splitting the name into name and score
            size_t pos = line.find(':');
            if ( pos != string::npos) {
                name = line.substr(0, pos);
                score = stoi(line.substr(pos +1));

                // Updating the score if it alreay exists, or add a new one
                if ( players.find(name) != players.end()) {
                    players[name] += score;
                } else {
                    players[name] = score;
                }
            }
        }

        cout << "Final scores:" << endl;
        for ( auto entry : players ) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    open_file.close();

    return 0;
}
