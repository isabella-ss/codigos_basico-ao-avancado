# ERP de Estoque e Vendas

Aplicação desktop em C++/Qt com MySQL para estudo de cadastro de produtos, clientes, fornecedores, pedidos e movimentações de estoque.

> **Status:** projeto em desenvolvimento. A estrutura de compilação foi adicionada, mas a execução real depende de Qt, do driver QMYSQL e de um servidor MySQL configurado. O fluxo de vendas existe como serviço e ainda não está conectado a uma tela de vendas.

## Tecnologias

- C++17
- Qt Widgets e Qt SQL (Qt 5 ou Qt 6)
- MySQL com mecanismo InnoDB
- CMake

## Requisitos

- CMake 3.16 ou superior
- Compilador C++17 (MSVC, GCC ou Clang)
- Qt 5 ou Qt 6 com os módulos Widgets e Sql
- MySQL 8 recomendado
- Driver Qt `QMYSQL` instalado e compatível com a versão do Qt

## Preparar o banco

1. Inicie o servidor MySQL.
2. Execute o script `database/schema.sql` com uma conta autorizada a criar banco e tabelas. O script cria o banco `erp_estoque`.
3. Crie um usuário de aplicação com permissões apenas nesse banco. Exemplo (execute como administrador no MySQL e escolha sua própria senha):

```sql
CREATE USER 'erp_app'@'localhost' IDENTIFIED BY 'defina_uma_senha_forte';
GRANT SELECT, INSERT, UPDATE, DELETE ON erp_estoque.* TO 'erp_app'@'localhost';
FLUSH PRIVILEGES;
```

Se o aplicativo se conectar por `127.0.0.1` e a configuração de usuários do seu MySQL distinguir `localhost` de `127.0.0.1`, ajuste o host da conta ou a configuração de conexão.

## Configurar conexão

O aplicativo lê estas variáveis de ambiente:

- `ERP_DB_HOST` (padrão `127.0.0.1`)
- `ERP_DB_PORT` (padrão `3306`)
- `ERP_DB_NAME` (padrão `erp_estoque`)
- `ERP_DB_USER` (padrão `erp_app`)
- `ERP_DB_PASSWORD` (obrigatória; não há senha padrão)

Defina-as no ambiente do sistema antes de executar. O arquivo `.env.example` é apenas um modelo e não é carregado automaticamente. **Não publique senhas no GitHub.**

## Compilar

Na raiz do projeto:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Execute o binário produzido em `build/` (no Windows com geradores multi-config, normalmente em `build/Release/`). Se o Qt não for encontrado, configure `CMAKE_PREFIX_PATH` para a pasta de instalação do Qt. Se a conexão falhar com erro de driver, instale/compile o plugin `QMYSQL` compatível com a sua instalação do Qt.

## Recursos presentes

- Abas para produtos, clientes, fornecedores, pedidos, itens dos pedidos e movimentações.
- Inclusão, edição manual, salvamento explícito e exclusão de registros nas tabelas.
- Serviço transacional de confirmação de pedido, com validação de estoque e registro dos itens e das movimentações.

## Limitações conhecidas

- Ainda não há uma tela guiada de vendas; o serviço de confirmação não é acionado pela interface.
- Não há autenticação, controle de permissões por usuário, relatórios ou suíte automatizada de testes.
- O esquema SQL deve ser validado na versão específica do MySQL usada no ambiente.
- Este projeto é educacional e não deve ser tratado como pronto para produção sem revisão de segurança, testes e validação operacional.

## Estrutura

```text
ERP/
├── CMakeLists.txt
├── README.md
├── database/schema.sql
└── src/
    ├── database/
    ├── services/
    └── ui/
```
