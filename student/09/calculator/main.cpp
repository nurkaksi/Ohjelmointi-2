#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // for std::toupper
#include <cmath>

using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool is_exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"DIVIDE", 2, false, division},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr},
    {"^", 2, false, power},
    {"POWER", 2, false, power},
    {"EXP", 2, false, power}
};

// Utility function to sections a string at delimiters
vector<string> split(const string& s,
                     const char delimiter,
                     bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);

// Function to perform power operation
double power(double base, double exponent) {
    return pow(base, exponent);
}

int main() {
    cout.precision(2);
    cout << fixed;

    while (true) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if (line.empty()) {
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if (pieces.size() == 0) {
            continue;
        }

        string command_to_be_executed = pieces.at(0);
        transform(command_to_be_executed.begin(), command_to_be_executed.end(), command_to_be_executed.begin(), ::toupper);

        bool command_found = false;
        for (const auto& cmd : COMMANDS) {
            if (cmd.str == command_to_be_executed) {
                command_found = true;
                if (cmd.parameter_number != pieces.size() - 1) {
                    cout << "Error: wrong number of parameters." << endl;
                } else {
                    if (cmd.is_exit) {
                        cout << GREETING_AT_END << endl;
                        return 0;
                    }
                    double operand1, operand2;
                    if (string_to_double(pieces.at(1), operand1) && string_to_double(pieces.at(2), operand2)) {
                        cout << cmd.action(operand1, operand2) << endl;
                    } else {
                        cout << "Error: a non-number operand." << endl;
                    }
                }
                break;
            }
        }

        if (!command_found) {
            cout << "Error: unknown command." << endl;
        }
    }
    return 0;
}

vector<string> split(const string& s,
                     const char delimiter,
                     bool ignore_empty) {
    vector<string> result;
    string tmp = s;

    while (tmp.find(delimiter) != string::npos) {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (!(ignore_empty && word.empty())) {
            result.push_back(word);
        }
    }
    if (!(ignore_empty && tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

bool string_to_double(const string& s, double& result) {
    istringstream stream(s);
    double tmp;
    stream >> tmp;
    if (!stream) {
        return false;
    }
    stream >> ws;
    stream.get();
    if (stream) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

