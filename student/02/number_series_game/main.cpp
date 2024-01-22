#include <iostream>
using namespace std;

int main()
{
    int luku = 0;
    int counter = 1;
    std::cout << "How many numbers would you like to have? ";
    cin >> luku;
    while (counter <= luku) {
        if (counter % 3 == 0 and counter % 7 == 0) {
            cout << "zip boing";
        }
        else if (counter % 3 ==0) {
            cout << "zip";
        }
        else if (counter % 7 ==0) {
            cout << "boing";
        }
        else {
            cout << counter;
        }
        cout << endl;
        ++counter;
    }


    return 0;
}
