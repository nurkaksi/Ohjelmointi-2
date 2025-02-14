#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using Network = std::map<std::string, std::vector<std::string>>;


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store(Network& web, std::string& parent, std::string& child) {
    if ( web.find(parent) ==  web.end() ) {
        web[parent] = std::vector<std::string>();
    }
    if ( find(web.at(parent).begin(), web.at(parent).end(),
              child) != web.at(parent).end()) {
        return;
    }
    web[parent].push_back(child);
}

void print(Network& web, std::string& id, int merkki =0) {
    for (int i = 0 ; i < merkki; ++i){
        std::cout << "..";
    }
    std::cout<< id << std::endl;

    if(web.find(id) != web.end()){
        for(std:: string child : web.at(id)){
            print(web, child, merkki+1);
        }
    }
}
int count(Network& web, std::string& id){
    int size = 0;
    if (web.find(id) != web.end()) {
        for (std::string child : web.at(id)){
            ++size;
            size += count(web, child);
        }
    }
    return size;
}

int depth(Network& web, std::string id){
    int max_depth = 0;
    if (web.find(id) != web.end()){
        for(std::string child : web.at(id)){
        int child_depth = depth(web, child);
        max_depth = std::max(max_depth, child_depth);
        }
    }
    else {
        return max_depth +1;
    }
    return max_depth +1;
}

int main()
{
    // TODO: Implement the datastructure here
    Network web;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(web, id1, id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(web, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout<< count(web, id) <<std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout<< depth(web, id) <<std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
