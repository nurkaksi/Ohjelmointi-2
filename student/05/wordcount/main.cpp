#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    string file_from = "";
    cout << "Input file: ";
    getline(cin, file_from);


    ifstream open_file(file_from);

        if ( not open_file ) {
            cout << "Error! The file " << file_from << " cannot be opened." << endl;
            return EXIT_FAILURE;
        }

        map<string, set<int>> words;
        string line = "";
        unsigned int line_number = 1;
        while (getline(open_file, line)) {
            string word = "";
            istringstream rowstream(line);
            while ( rowstream >> word ) {
                words[word].insert(line_number);
            }
            ++line_number;

        }

    for ( map<string, set<int>>::iterator word_iter = words.begin() ;
          word_iter != words.end() ;
            ++word_iter ) {
        cout << word_iter->first << " ";
        cout << word_iter->second.size() << ": ";

        for ( set<int>::iterator line_num_iter = word_iter->second.begin() ;
            line_num_iter != word_iter->second.end() ;
            ++line_num_iter )
        {
            if ( line_num_iter != word_iter->second.begin() ){
                cout << ", ";
            }
            cout <<  *line_num_iter;
        }
        cout << endl;
    }



   open_file.close();


    return 0;
}
