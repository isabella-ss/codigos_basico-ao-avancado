<div align="center">
# 🚀 Aprenda C++ do Zero ao Avançado
 
### Lógica de programação • Fundamentos • Programação Orientada a Objetos
 
![C++](https://img.shields.io/badge/C++-17%2F20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Nível](https://img.shields.io/badge/N%C3%ADvel-Iniciante%20ao%20Avan%C3%A7ado-success?style=for-the-badge)
![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-blue?style=for-the-badge)
![Contribuições](https://img.shields.io/badge/Contribui%C3%A7%C3%B5es-bem--vindas-orange?style=for-the-badge)
 
**Um caminho completo, prático e progressivo para você pensar como programador(a) e escrever código C++ de qualidade.**
 
</div>
---
 
## 📖 Sobre o projeto
 
Este repositório reúne **exemplos comentados, exercícios e mini projetos** que levam você desde o primeiro `Hello, World!` até conceitos avançados de **Programação Orientada a Objetos (POO)** em C++.
 
A ideia é simples: **aprender fazendo**. Cada tópico traz teoria curta, código funcional e desafios para praticar.
 
## 🎯 Para quem é?
 
| Você é... | O que vai encontrar aqui |
|---|---|
| 🌱 **Iniciante** | Uma trilha guiada, sem pular etapas, com foco em lógica de programação |
| 📚 **Estudante** | Exemplos organizados por tema, ótimos para revisar antes de provas |
| 🔁 **Em transição de carreira** | Base sólida de C++ e POO, muito cobrada no mercado |
| 💼 **Recrutador(a)** | Um portfólio real de código, organização, boas práticas e evolução técnica |
 
## 🗺️ Trilha de aprendizado
 
```text
Conceitos ──► Aulas ──► Básico ──► Lógica ──► Estruturas ──► Funções ──► POO ──► Avançado ──► Projetos
```
 
### 🟢 Nível 1 — Fundamentos - Códigos base e Conceitos
- Estrutura de um programa em C++
- Variáveis, tipos de dados e operadores
- Entrada e saída (`cin`, `cout`)
- Condicionais (`if`, `else`, `switch`)
- Laços de repetição (`for`, `while`, `do-while`)

### 🟡 Nível 2 — Lógica e estruturas de dados
- Raciocínio lógico e resolução de problemas
- Vetores e matrizes
- Strings
- Funções e recursão
- Ponteiros e referências
- Alocação dinâmica de memória
  
### 🔵 Nível 3 — POO (Programação Orientada a Objetos)
- Classes e objetos
- Construtores e destrutores
- Encapsulamento
- Herança
- Polimorfismo
- Abstração e classes abstratas
- Sobrecarga de operadores
  
### 🔴 Nível 4 — Avançado
- STL (`vector`, `map`, `set`, algoritmos)
- Templates
- Tratamento de exceções
- Smart pointers
- Manipulação de arquivos
- Boas práticas e código limpo
### 🏆 Nível 5 — Projetos práticos
Aplicações que juntam tudo o que foi aprendido (ex.: sistema de cadastro, jogo no terminal, gerenciador de tarefas e outros).
 
## 📂 Estrutura do repositório
 
```text
📦 nome-do-repositorio
 ┣ 📁 01-aulas (0 ao 10) 
 ┣ 📁 02-logica-e-estruturas
 ┣ 📁 03-poo (programacao-orientada-a-objetos)
 ┣ 📁 04-avancado
 ┣ 📁 05-codigos-basicos
 ┣ 📁 exercicios
 ┣ 📁 
 ┗ 📄 README.md
```
 
 
 
### 🛠️ Ferramentas recomendadas
- [VS Code](https://code.visualstudio.com/) ou [CodeBlocks](https://www.codeblocks.org/)
- [Git](https://git-scm.com/)
  
## 💡 Exemplo rápido de POO
 
```cpp
#include <iostream>
#include <string>
using namespace std;
 
class Animal {
protected:
    string nome;
public:
    Animal(string n) : nome(n) {}
    virtual void emitirSom() const = 0; // método puro (abstração)
    virtual ~Animal() {}
};
 
class Cachorro : public Animal {
public:
    Cachorro(string n) : Animal(n) {}
    void emitirSom() const override {
        cout << nome << " diz: Au au!" << endl;
    }
};
 
int main() {
    Cachorro rex("Rex");
    rex.emitirSom();
    return 0;
}
```
 
## 🧠 Como aproveitar melhor
 
1. **Siga a ordem** das pastas — cada nível se apoia no anterior.
2. **Leia o código, depois reescreva sozinho(a)** sem olhar.
3. **Resolva os exercícios** antes de ver a solução.
4. **Modifique os exemplos**: quebrar o código é uma ótima forma de aprender.
5. **Crie seus próprios projetos** ao final de cada nível.
## 👨‍💻 Para recrutadores
 
Este repositório demonstra:
 
- ✅ Domínio de **C++ moderno** e de **POO**
- ✅ Capacidade de **explicar conceitos** de forma clara (didática e comunicação)
- ✅ **Organização e documentação** de código
- ✅ Evolução constante e **disciplina de estudo**
- ✅ Uso de **Git/GitHub** no dia a dia
 
 
## 🗒️ Roadmap
 
- [x] Fundamentos de C++
- [x] Lógica de programação
- [x] Programação Orientada a Objetos
- [ ] Mais exercícios com gabarito
- [ ] Estruturas de dados clássicas (listas, pilhas, filas, árvores)
- [ ] Algoritmos de ordenação e busca
- [ ] Projetos completos passo a passo
## 📜 Licença
 
Distribuído sob a licença **MIT**. Veja o arquivo `LICENSE` para mais detalhes.
 
---
 
<div align="center">
### ⭐ Se este projeto te ajudou, deixe uma estrela no repositório!
 
Feito por **(https://github.com/isabella-ss)**
 
</div>
 
