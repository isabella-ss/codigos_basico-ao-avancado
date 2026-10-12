#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int ANO_ATUAL = 2026;
const int MAX_FUNCIONARIOS = 100;

bool lerInteiro(string mensagem, int &valor, int minimo, int maximo) {
    string linha;

    while (true) {
        cout << mensagem;

        if (!getline(cin, linha))
            return false;

        stringstream ss(linha);
        char extra;

        if (ss >> valor && !(ss >> extra) &&
            valor >= minimo && valor <= maximo)
            return true;

        cout << "Valor invalido! Tente novamente.\n";
    }
}

bool lerTexto(string mensagem, string &texto) {
    while (true) {
        cout << mensagem;

        if (!getline(cin, texto))
            return false;

        if (!texto.empty())
            return true;

        cout << "O campo nao pode ficar vazio.\n";
    }
}

bool lerData(int &dia, int &mes, int &ano) {
    string linha;

    while (true) {
        cout << "Data de nascimento (DD/MM/AAAA): ";

        if (!getline(cin, linha))
            return false;

        stringstream ss(linha);
        int d, m, a;
        char barra1, barra2, extra;

        if (!(ss >> d >> barra1 >> m >> barra2 >> a) ||
            barra1 != '/' || barra2 != '/' || (ss >> extra)) {
            cout << "Formato invalido! Use DD/MM/AAAA.\n";
            continue;
        }

        if (a < 1900 || a > ANO_ATUAL || m < 1 || m > 12) {
            cout << "Data invalida! Verifique dia, mes e ano.\n";
            continue;
        }

        int diasMes[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

        bool bissexto = (a % 400 == 0) ||
                        (a % 4 == 0 && a % 100 != 0);

        if (bissexto)
            diasMes[1] = 29;

        if (d < 1 || d > diasMes[m - 1]) {
            cout << "Dia invalido para esse mes!\n";
            continue;
        }

        dia = d;
        mes = m;
        ano = a;
        return true;
    }
}

class Funcionario {
public:
    string nome, endereco, telefone, email, observacoes;
    int dia, mes, ano, entrada;

    bool cadastrar() {
        if (!lerTexto("Nome: ", nome)) return false;
        if (!lerTexto("Endereco: ", endereco)) return false;
        if (!lerTexto("Telefone: ", telefone)) return false;
        if (!lerTexto("Email: ", email)) return false;
        if (!lerData(dia, mes, ano)) return false;

        if (!lerInteiro("Ano de entrada na empresa: ",
                        entrada, 1900, ANO_ATUAL))
            return false;

        if (entrada < ano) {
            cout << "Aviso: confira o ano de entrada na empresa.\n";
        }

        return lerTexto("Observacoes: ", observacoes);
    }

    void imprimir() const {
        cout << "\nNome: " << nome
             << "\nEndereco: " << endereco
             << "\nTelefone: " << telefone
             << "\nEmail: " << email
             << "\nNascimento: ";

        if (dia < 10) cout << '0';
        cout << dia << '/';

        if (mes < 10) cout << '0';
        cout << mes << '/' << ano;

        cout << "\nEntrada na empresa: " << entrada
             << "\nObservacoes: " << observacoes << "\n";
    }
};

int main() {
    vector<Funcionario> funcionarios;
    int quantidade = 0, opcao;
    bool definida = false;

    while (true) {
        cout << "\n========== MENU ==========\n"
             << "1 - Informar quantidade de funcionarios\n"
             << "2 - Cadastrar funcionarios\n"
             << "3 - Buscar aniversariantes por mes\n"
             << "4 - Buscar por tempo de empresa\n"
             << "5 - Maior observacao\n"
             << "6 - Verificar email\n"
             << "7 - Imprimir todos os funcionarios\n"
             << "0 - Sair\n"
             << "==========================\n";

        if (!lerInteiro("Opcao: ", opcao, 0, 7))
            break;

        switch (opcao) {
        case 1:
            if (!funcionarios.empty()) {
                cout << "A quantidade nao pode ser alterada "
                     << "apos iniciar os cadastros.\n";
                break;
            }

            if (!lerInteiro("Quantidade (1 a 100): ",
                            quantidade, 1, MAX_FUNCIONARIOS))
                return 0;

            definida = true;
            cout << "Quantidade definida com sucesso!\n";
            break;

        case 2:
            if (!definida) {
                cout << "Informe a quantidade primeiro!\n";
                break;
            }

            if ((int)funcionarios.size() == quantidade) {
                cout << "Todos os funcionarios ja foram cadastrados.\n";
                break;
            }

            while ((int)funcionarios.size() < quantidade) {
                Funcionario f;

                cout << "\nFuncionario "
                     << funcionarios.size() + 1 << ":\n";

                if (!f.cadastrar()) {
                    cout << "\nEntrada encerrada.\n";
                    return 0;
                }

                funcionarios.push_back(f);
                cout << "Cadastro realizado com sucesso!\n";
            }
            break;

        case 3: {
            if (funcionarios.empty()) {
                cout << "Nenhum funcionario cadastrado.\n";
                break;
            }

            int mes;

            if (!lerInteiro("Mes desejado (1 a 12): ", mes, 1, 12))
                return 0;

            bool encontrou = false;

            for (const auto &f : funcionarios) {
                if (f.mes == mes) {
                    cout << f.nome << " - ";

                    if (f.dia < 10) cout << '0';
                    cout << f.dia << '/';

                    if (f.mes < 10) cout << '0';
                    cout << f.mes << '/' << f.ano << '\n';

                    encontrou = true;
                }
            }

            if (!encontrou)
                cout << "Nenhum aniversariante encontrado.\n";

            break;
        }

        case 4: {
            if (funcionarios.empty()) {
                cout << "Nenhum funcionario cadastrado.\n";
                break;
            }

            int anos;

            if (!lerInteiro("Anos de empresa: ", anos, 0, 200))
                return 0;

            bool encontrou = false;

            for (const auto &f : funcionarios) {
                if (ANO_ATUAL - f.entrada == anos) {
                    cout << f.nome << " - " << f.telefone << '\n';
                    encontrou = true;
                }
            }

            if (!encontrou)
                cout << "Nenhum funcionario encontrado.\n";

            break;
        }

        case 5:
            if (funcionarios.empty()) {
                cout << "Nenhum funcionario cadastrado.\n";
                break;
            } else {
                int maior = 0;

                for (int i = 1; i < (int)funcionarios.size(); i++) {
                    if (funcionarios[i].observacoes.size() >
                        funcionarios[maior].observacoes.size()) {
                        maior = i;
                    }
                }

                cout << funcionarios[maior].nome
                     << " possui a maior observacao.\n";
            }
            break;

        case 6: {
            if (funcionarios.empty()) {
                cout << "Nenhum funcionario cadastrado.\n";
                break;
            }

            int numero;

            if (!lerInteiro("Numero do funcionario: ",
                            numero, 1, funcionarios.size()))
                return 0;

            string email = funcionarios[numero - 1].email;

            if (email.find('@') != string::npos &&
                email.find(".com") != string::npos) {
                cout << "Email valido segundo os criterios.\n";
            } else {
                cout << "Email invalido segundo os criterios.\n";
            }

            break;
        }

        case 7:
            if (funcionarios.empty()) {
                cout << "Nenhum funcionario cadastrado.\n";
            } else {
                for (const auto &f : funcionarios)
                    f.imprimir();
            }
            break;

        case 0:
            cout << "Programa encerrado!\n";
            return 0;
        }
    }

    cout << "Programa finalizado.\n";
    return 0;
}
