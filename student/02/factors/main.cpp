#include <iostream>
#include <cmath>

using namespace std;

void finding_numbers(int number) {
    int i = 1;
    int f1 = 0;
    int f2 = 0;
    for ( i = 1; i <= sqrt(number); ++i) {
        if ( number % i == 0 ) {
            f1 = i;
            f2 = number / i;
        }
    }
    cout << number << " = " << f1 << " * " << f2 << endl;
}

int main()
{
    int number = 0;
    cout << "Enter a positive number: ";
    cin >> number;
    if ( number <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        finding_numbers(number);
    }

    return 0;
}
