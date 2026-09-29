#include <iostream>

using namespace std;

int main(){
    float celsius;
    cout << "\nTemperatura em Celsius ";
    cin >> celsius;
    cout << "\n" << celsius << "equivale a em: " << ((9*celsius+160)/5);
    return 0 ;
}
