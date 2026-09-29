#include <iostream>

using namespace std;

int main(){
    float altura, peso, imc;

    cout << "\nIndice de Massa corporal";
    cout << "\nInforme seu peso kg: ";
    cin >> peso;
    cout << "\nInforme sua altura M: ";
    cin >> altura;
    imc = (peso)/altura*altura;
    cout << "Seu IMC: "<< imc;
    return 0 ;
}
