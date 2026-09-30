#include <stdio.h>
#include <string.h>

#define MAX 100

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Funcionario {
    char nome[100];
    char endereco[100];
    char telefone[20];
    char email[100];
    struct Data nascimento;
    int anoEntrada;
    char observacoes[200];
};

void cadastrar(struct Funcionario funcionarios[], int quantidade) {
    int i;

    for (i = 0; i < quantidade; i++) {
        printf("\nFuncionario %d\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", funcionarios[i].nome);

        printf("Endereco: ");
        scanf(" %[^\n]", funcionarios[i].endereco);

        printf("Telefone: ");
        scanf(" %[^\n]", funcionarios[i].telefone);

        printf("E-mail: ");
        scanf(" %[^\n]", funcionarios[i].email);

        printf("Data de nascimento (dia mes ano): ");
        scanf("%d %d %d",
              &funcionarios[i].nascimento.dia,
              &funcionarios[i].nascimento.mes,
              &funcionarios[i].nascimento.ano);

        printf("Ano de chegada na empresa: ");
        scanf("%d", &funcionarios[i].anoEntrada);

        printf("Observacoes: ");
        scanf(" %[^\n]", funcionarios[i].observacoes);
    }
}

void nascimentoMes(struct Funcionario funcionarios[], int quantidade) {
    int mes, i;

    printf("Digite o mes: ");
    scanf("%d", &mes);

    for (i = 0; i < quantidade; i++) {
        if (funcionarios[i].nascimento.mes == mes) {
            printf("%s - %02d/%02d/%d\n",
                   funcionarios[i].nome,
                   funcionarios[i].nascimento.dia,
                   funcionarios[i].nascimento.mes,
                   funcionarios[i].nascimento.ano);
        }
    }
}

void tempoEmpresa(struct Funcionario funcionarios[], int quantidade) {
    int anos, i;

    printf("Digite a quantidade de anos de empresa: ");
    scanf("%d", &anos);

    for (i = 0; i < quantidade; i++) {
        if (2026 - funcionarios[i].anoEntrada == anos) {
            printf("Nome: %s | Telefone: %s\n",
                   funcionarios[i].nome,
                   funcionarios[i].telefone);
        }
    }
}

void maiorObservacao(struct Funcionario funcionarios[], int quantidade) {
    int i;
    int maior = 0;

    for (i = 1; i < quantidade; i++) {
        if (strlen(funcionarios[i].observacoes) >
            strlen(funcionarios[maior].observacoes)) {
            maior = i;
        }
    }

    printf("\nFuncionario com maior observacao:\n");
    printf("Nome: %s\n", funcionarios[maior].nome);
    printf("Observacao: %s\n", funcionarios[maior].observacoes);
}

void verificarEmail(struct Funcionario funcionarios[], int quantidade) {
    char email[100];
    int i;

    printf("Digite o e-mail: ");
    scanf(" %[^\n]", email);

    for (i = 0; i < quantidade; i++) {
        if (strcmp(funcionarios[i].email, email) == 0) {

            if (strstr(email, "@") != NULL &&
                strstr(email, ".com") != NULL) {
                printf("O e-mail possui @ e .com.\n");
            } else {
                printf("O e-mail nao possui @ e .com.\n");
            }

            return;
        }
    }

    printf("E-mail nao encontrado.\n");
}

void imprimirTodos(struct Funcionario funcionarios[], int quantidade) {
    int i;

    for (i = 0; i < quantidade; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Endereco: %s\n", funcionarios[i].endereco);
        printf("Telefone: %s\n", funcionarios[i].telefone);
        printf("E-mail: %s\n", funcionarios[i].email);

        printf("Nascimento: %02d/%02d/%d\n",
               funcionarios[i].nascimento.dia,
               funcionarios[i].nascimento.mes,
               funcionarios[i].nascimento.ano);

        printf("Ano de chegada: %d\n", funcionarios[i].anoEntrada);
        printf("Observacoes: %s\n", funcionarios[i].observacoes);
    }
}

int main() {
    struct Funcionario funcionarios[MAX];

    int quantidade = 0;
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Ler quantidade de funcionarios\n");
        printf("2 - Cadastrar funcionarios\n");
        printf("3 - Nascimentos por mes\n");
        printf("4 - Funcionarios por tempo de empresa\n");
        printf("5 - Maior observacao\n");
        printf("6 - Verificar e-mail\n");
        printf("7 - Imprimir todos os funcionarios\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("Quantidade: ");
                scanf("%d", &quantidade);

                if (quantidade < 1 || quantidade > MAX) {
                    printf("Quantidade invalida.\n");
                    quantidade = 0;
                }
                break;

            case 2:
                if (quantidade == 0)
                    printf("Informe primeiro a quantidade.\n");
                else
                    cadastrar(funcionarios, quantidade);
                break;

            case 3:
                nascimentoMes(funcionarios, quantidade);
                break;

            case 4:
                tempoEmpresa(funcionarios, quantidade);
                break;

            case 5:
                maiorObservacao(funcionarios, quantidade);
                break;

            case 6:
                verificarEmail(funcionarios, quantidade);
                break;

            case 7:
                imprimirTodos(funcionarios, quantidade);
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}