      Aula de POO 

 Objeto \= dados \+ operações sobre esses dados

Tópicos:

Objetos  
Métodos  
Mensagem  
Classe  
Classificação  
Generalização  
Especialização  
Herança  
Encapsulamento  
Polimorfismo

Conceitos:

 \>\> Métodos são procedimentos que determinam como o objeto se  
comporta

\>\> Objetos são entidades que possuem dados e instruções sobre  
como manipular estes dados.

\>\> Na POO a solução do problema consiste em um primeiro  
momento,  
estabelecer quais os objetos serão necessários.

\>\> Abstração é o princípio de representar APENAS as  
características essenciais de um objeto , escondendo detalhes  
internos que NAO são necessários para quem o utiliza.

       \<\<classe\>\>

\<\<primeiro código abaixo\>\>

\#include \<iostream\>

// classe Pessoa \-- idade e nome  
// Objeto "Joao"  
using namespace std;  
class Pessoa {  
public:  
	string nome;  
	int idade;  
};

// classe \-- molde para criar objetos(objeto \-- algo criado a partir do molde)  
// exibindo quem é a pessoa  
int main()  
{  
    Pessoa p1;  
	p1.nome \= "João";  
	p1.idade \= 35;  
	cout \<\< p1.nome \<\< endl;  
	cout \<\< p1.idade \<\< endl;  
	return 0;  
}

      \<\<ATRIBUTO\>\>  
        \<\<explicando o segundo código\>\>

\#include \<iostream\>  
// As variaveis pertencentes a classe são chamadas de atributos  
// classe Carro \-- modelo, cor, velocidade  
// Objeto "Civic" 

using namespace std;  
class Carro{  
public:  
	string modelo;  
	string cor;  
	int velocidade;  
};

// classe \-- molde para criar objetos(objeto \-- algo criado a partir do molde)  
// exibindo quem é o carro, qual a cor e a velocidade

int main()  
{  
    Carro carro1;  
	carro1.modelo \= "civic";  
	carro1.cor \= "preto";  
	carro1.velocidade \= 80;  
	cout \<\< carro1.modelo \<\< endl;  
	cout \<\< carro1.cor \<\< endl;  
	cout \<\< carro1.velocidade \<\< endl;  
	return 0;  
}

     \<\<Método\>\>  
  \<\<explicando métodos no códigos\>\>

\#include \<iostream\>  
// As classes tambem possuem funções, que são chamadas de métodos  
// classe Carro   
using namespace std;  
class Carro {  
public:  
	int velocidade \= 0;

	void acelerar() {  
		velocidade \+= 10;  
	};  
};

// classe \-- molde para criar objetos(objeto \-- algo criado a partir do molde)  
// velocidade \= 0  \---\> acelerar() \---\> velocidade \= 10 (CHAMANDO NOVAMENTE CARRO.ACELERAR(); \--\> TEREMOS: VELOC \= 20\)

int main()  
{  
    Carro carro;  
	carro.acelerar();  
	return 0;  
}

