CREATE DATABASE IF NOT EXISTS erp_estoque
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE erp_estoque;

CREATE TABLE IF NOT EXISTS fornecedores (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(150) NOT NULL,
    documento VARCHAR(20) UNIQUE,
    telefone VARCHAR(25),
    email VARCHAR(150),
    endereco VARCHAR(255),
    ativo BOOLEAN NOT NULL DEFAULT TRUE,
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS clientes (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(150) NOT NULL,
    documento VARCHAR(20) UNIQUE,
    telefone VARCHAR(25),
    email VARCHAR(150),
    endereco VARCHAR(255),
    ativo BOOLEAN NOT NULL DEFAULT TRUE,
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS produtos (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    fornecedor_id BIGINT UNSIGNED,
    sku VARCHAR(50) NOT NULL UNIQUE,
    nome VARCHAR(150) NOT NULL,
    descricao TEXT,
    preco_custo DECIMAL(12,2) NOT NULL DEFAULT 0,
    preco_venda DECIMAL(12,2) NOT NULL DEFAULT 0,
    estoque_atual INT NOT NULL DEFAULT 0,
    estoque_minimo INT NOT NULL DEFAULT 0,
    ativo BOOLEAN NOT NULL DEFAULT TRUE,
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_produto_fornecedor
        FOREIGN KEY (fornecedor_id)
        REFERENCES fornecedores(id)
        ON DELETE SET NULL,

    CONSTRAINT chk_preco_custo
        CHECK (preco_custo >= 0),

    CONSTRAINT chk_preco_venda
        CHECK (preco_venda >= 0),

    CONSTRAINT chk_estoque
        CHECK (estoque_atual >= 0 AND estoque_minimo >= 0)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS pedidos (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    cliente_id BIGINT UNSIGNED NOT NULL,
    data_pedido TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM(
        'ABERTO',
        'CONFIRMADO',
        'CANCELADO'
    ) NOT NULL DEFAULT 'ABERTO',
    valor_total DECIMAL(12,2) NOT NULL DEFAULT 0,

    CONSTRAINT fk_pedido_cliente
        FOREIGN KEY (cliente_id)
        REFERENCES clientes(id),

    CONSTRAINT chk_pedido_total
        CHECK (valor_total >= 0)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS itens_pedido (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    pedido_id BIGINT UNSIGNED NOT NULL,
    produto_id BIGINT UNSIGNED NOT NULL,
    quantidade INT NOT NULL,
    preco_unitario DECIMAL(12,2) NOT NULL,

    CONSTRAINT fk_item_pedido
        FOREIGN KEY (pedido_id)
        REFERENCES pedidos(id),

    CONSTRAINT fk_item_produto
        FOREIGN KEY (produto_id)
        REFERENCES produtos(id),

    CONSTRAINT chk_item_quantidade
        CHECK (quantidade > 0),

    CONSTRAINT chk_item_preco
        CHECK (preco_unitario >= 0)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS movimentacoes_estoque (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    produto_id BIGINT UNSIGNED NOT NULL,
    tipo ENUM('ENTRADA', 'SAIDA', 'AJUSTE') NOT NULL,
    quantidade INT NOT NULL,
    motivo VARCHAR(255) NOT NULL,
    pedido_id BIGINT UNSIGNED NULL,
    data_movimentacao TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_mov_produto
        FOREIGN KEY (produto_id)
        REFERENCES produtos(id),

    CONSTRAINT fk_mov_pedido
        FOREIGN KEY (pedido_id)
        REFERENCES pedidos(id),

    CONSTRAINT chk_mov_quantidade
        CHECK (quantidade > 0)
) ENGINE=InnoDB;

CREATE INDEX idx_produto_nome ON produtos(nome);
CREATE INDEX idx_pedido_data ON pedidos(data_pedido);
CREATE INDEX idx_mov_data ON movimentacoes_estoque(data_movimentacao);