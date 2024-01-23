#include <iostream>

using namespace std;

long int factorial(int number) {
    if (number == 0 ) {
        return 1;
    } else {
        long int result = 1;
        for (int i = 1; i < number + 1; ++i) {
            result *= i;
        }
    return result;
    }
}


long int odd(int number_of_balls, int drawn_balls) {
    long int number_of_balls_fac = factorial(number_of_balls);
    long int drawn_balls_fac = factorial(drawn_balls);
    long int minus = factorial(number_of_balls - drawn_balls);
    long int res = number_of_balls_fac / ( minus * drawn_balls_fac );
    return res;
}


int main()
{
    int number_of_balls = 0;
    int drawn_balls = 0;

    cout << "Enter the total number of lottery balls: ";
    cin >> number_of_balls;

    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    if ( number_of_balls < 0 ) {
        cout << "The number of balls must be a positive number." << endl;
    } else if ( drawn_balls > number_of_balls ) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << odd(number_of_balls, drawn_balls) << endl;
    }

    return 0;
}
