#include <iostream>

using namespace std;

int main()
{   double temperature = 0;
    cout << "Enter a temperature: ";
    cin >> temperature;

    cout << temperature << " degrees Celsius is " << (temperature * 9 / 5) + 32 << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << (temperature - 32)* 5 / 9 << " degrees Celsius" << endl;


    return 0;
}
