#include <iostream>

using namespace std;

int main()
{   double temperature = 0;
    cout << "Enter a temperature: ";
    cin >> temperature;

    cout << temperature << " degrees Celcius is " << (temperature * 9 / 5) + 32 << " degrees Fahrenheit" << endl;
    cout << temperature << " dehrees Fahrenheit is " << (temperature - 32)* 5 / 9 << " degrees Celcius" << endl;


    return 0;
}
