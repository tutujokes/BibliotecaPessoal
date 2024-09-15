# Biblioteca Pessoal

## Descrição

Este é um projeto colaborativo de faculdade para a gestão de uma biblioteca pessoal. O programa permite aos usuários cadastrar novos livros, marcar livros como lidos, remover livros e gerenciar a biblioteca pessoal de forma interativa. A interface é baseada em texto e utiliza cores para facilitar a visualização das mensagens.

## Funcionalidades

- **Cadastrar Usuário**: Permite adicionar novos usuários ao sistema com um nome único.
- **Autenticar Usuário**: Permite a autenticação dos usuários existentes por nome ou ID.
- **Cadastrar Livros**: Permite adicionar livros à biblioteca pessoal de um usuário.
- **Procurar Livros**: Permite visualizar a lista de livros cadastrados e marcar livros como lidos.
- **Remover Livros**: Permite remover livros da biblioteca pessoal de um usuário.

## Tecnologias Utilizadas

- **Linguagem de Programação**: C
- **Bibliotecas**: `locale.h`, `stdio.h`, `stdlib.h`, `string.h`, `time.h`

## Como Executar

### Requisitos

- Um compilador C (por exemplo, `gcc`).

### Compilação e Execução

1. **Compile o código**:

   ```bash
   gcc -o biblioteca biblioteca.c
