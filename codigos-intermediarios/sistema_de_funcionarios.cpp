#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Funcionario {
public:
    string nome, endereco, telefone, email, observacoes;
    int dia, mes, ano, entrada;

    void cadastrar() {
        cout << "Nome: "; getline(cin, nome);
        cout << "Endereco: "; getline(cin, endereco);
        cout << "Telefone: "; getline(cin, telefone);
        cout << "Email: "; getline(cin, email);
        cout << "Data de nascimento (dia mes ano): ";
        cin >> dia >> mes >> ano;
        cout << "Ano de entrada na empresa: "; cin >> entrada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Observacoes: "; getline(cin, observacoes);
    }

    void imprimir() {
        cout << "\nNome: " << nome
             << "\nEndereco: " << endereco
             << "\nTelefone: " << telefone
             << "\nEmail: " << email
             << "\nNascimento: " << dia << "/" << mes << "/" << ano
             << "\nEntrada na empresa: " << entrada
             << "\nObservacoes: " << observacoes << "\n";
    }
};

int main() {
    vector<Funcionario> funcionarios;
    int quantidade = 0, opcao, anoAtual = 2026;

    do {
        cout << "\n--- MENU ---\n"
             << "1 - Informar quantidade de funcionarios\n"
             << "2 - Cadastrar funcionarios\n"
             << "3 - Buscar aniversariantes por mes\n"
             << "4 - Buscar por tempo de empresa\n"
             << "5 - Maior observacao\n"
             << "6 - Verificar email\n"
             << "7 - Imprimir todos\n"
             << "0 - Sair\nOpcao: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
        case 1:
            cout << "Quantidade: ";
            cin >> quantidade;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            funcionarios.clear();
            break;

        case 2:
            for (int i = 0; i < quantidade; i++) {
                cout << "\nFuncionario " << i + 1 << ":\n";
                Funcionario f;
                f.cadastrar();
                funcionarios.push_back(f);
            }
            break;

        case 3: {
            int mes;
            cout << "Mes desejado: ";
            cin >> mes;
            for (auto f : funcionarios)
                if (f.mes == mes)
                    cout << f.nome << " - " << f.dia << "/"
                         << f.mes << "/" << f.ano << "\n";
            break;
        }

        case 4: {
            int anos;
            cout << "Anos de empresa: ";
            cin >> anos;
            for (auto f : funcionarios)
                if (anoAtual - f.entrada == anos)
                    cout << f.nome << " - " << f.telefone << "\n";
            break;
        }

        case 5:
            if (!funcionarios.empty()) {
                int maior = 0;
                for (int i = 1; i < (int)funcionarios.size(); i++)
                    if (funcionarios[i].observacoes.size() >
                        funcionarios[maior].observacoes.size())
                        maior = i;
                cout << funcionarios[maior].nome
                     << " possui a maior observacao.\n";
            }
            break;

        case 6: {
            int i;
            cout << "Numero do funcionario (1 a "
                 << funcionarios.size() << "): ";
            cin >> i;
            if (i >= 1 && i <= (int)funcionarios.size()) {
                string e = funcionarios[i - 1].email;
                cout << (e.find('@') != string::npos &&
                         e.find(".com") != string::npos
                         ? "Email valido\n" : "Email invalido\n");
            } else cout << "Funcionario inexistente.\n";
            break;
        }

        case 7:
            for (auto f : funcionarios) f.imprimir();
            break;

        case 0:
            cout << "Programa encerrado!\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);

    return 0;
}
