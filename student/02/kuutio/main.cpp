#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number ;
    int cube = number * number * number;
    if (cube < 0) {
        cout << "The cube of " << number << " is not " << cube << "." << endl;
    }
    else if (cube < 2147483647 and cube > 0) {
        cout << "The cube of " << number << " is " << cube << "." << endl;
    }
    else {
        cout << "The cube of " << number << " is not " << cube << "." << endl;
    }
    return 0;
}
