#include <iostream>
#include <string>
using namespace std;
//declaração inicial 
int main() {
    int idade = 20;
    double altura = 1.80;
    bool ativo = true;
    string nome = "luis";
//aqui acontece a parada de exibir
    cin >> idade;
    cout << idade << endl;
//condição para acontecer
    if (idade >= 18) {
        cout << "Maior de idade" << endl;
    } else {
        cout << "Menor de idade" << endl;
    }
//repetição do laço 
    for (int i = 0; i < 10; i++) {
        cout << i << endl;
    }

    return 0;
}
