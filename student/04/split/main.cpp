#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string& str, char separator, bool ignore_empty = false) {
    std::vector<std::string> parts;
    std::string part;

    for (char c : str) {
        if (c == separator) {
            if (!ignore_empty || !part.empty()) {
                parts.push_back(part);
                part.clear();
            }
        } else {
            part += c;
        }
    }
    // Add the last part if it's not empty
    if (!ignore_empty || !part.empty()) {
        parts.push_back(part);
    }
    return parts;
}

int main() {
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector<std::string> parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for (const auto& part : parts) {
        std::cout << part << std::endl;
    }

    std::vector<std::string> parts_no_empty = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for (const auto& part : parts_no_empty) {
        std::cout << part << std::endl;
    }

    return 0;
}
