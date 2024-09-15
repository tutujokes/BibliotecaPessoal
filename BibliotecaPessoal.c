#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maximo_De_Livros 20
#define maximo_Letras_Livro 300
#define maximo_De_Usuarios 20
#define maximo_Letras_Usuarios 100

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

char nome_De_Usuario[maximo_De_Usuarios][maximo_Letras_Livro];
char titulo_Livros[maximo_De_Usuarios][maximo_Letras_Livro][maximo_Letras_Livro];
int Id_Usario[maximo_De_Usuarios];
int escolhaLivro, quantidade_De_Usuarios = 0;
int quantidade_De_Livros[maximo_De_Usuarios];
int livros_Lidos[maximo_De_Usuarios][maximo_Letras_Livro];

void mostreerro(const char *mensagem) { printf(RED "ERRO: %s\n" RESET, mensagem); }

int idAleatorio() { return rand() % 10001; }

int contadorLivrosUsuario(int usuario) { return Id_Usario[usuario] == usuario ? quantidade_De_Livros[usuario] : 0; }

int contadorLidos(int usuario) {
  int contar = 0;
  for (int i = 0; i < quantidade_De_Livros[usuario]; i++) {
    contar += livros_Lidos[usuario][i];
  }
  return contar;
}

int autenticar_Usuario() {
  char tipo_De_Login[maximo_Letras_Livro];
  printf(CYAN "Digite o nome ou ID do usuário: \n" RESET);
  fgets(tipo_De_Login, maximo_Letras_Livro, stdin);
  tipo_De_Login[strcspn(tipo_De_Login, "\n")] = 0;

  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    if ((tipo_De_Login[0] >= '0' && tipo_De_Login[0] <= '9' && Id_Usario[i] == atoi(tipo_De_Login)) || strcmp(nome_De_Usuario[i], tipo_De_Login) == 0) {
      return i;
    }
  }
  return -1;
}

int verificar_Usuario_Existente(const char *nome) {
  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    if (strcmp(nome_De_Usuario[i], nome) == 0) {
      return i;
    }
  }
  return -1;
}

void cadastrar_Usuario() {
  if (quantidade_De_Usuarios < maximo_De_Usuarios) {
    char nome[maximo_Letras_Livro];
    printf(CYAN "Digite o nome do usuário: " RESET);
    fgets(nome, maximo_Letras_Livro, stdin);
    nome[strcspn(nome, "\n")] = 0;

    if (verificar_Usuario_Existente(nome) != -1) {
      mostreerro("Usuário já cadastrado.");
      return;
    }
    strcpy(nome_De_Usuario[quantidade_De_Usuarios], nome);
    Id_Usario[quantidade_De_Usuarios] = idAleatorio();
    quantidade_De_Livros[quantidade_De_Usuarios] = 0;
    system("clear || cls");
    printf(GREEN "Usuário cadastrado com sucesso! ID: %d\n" RESET, Id_Usario[quantidade_De_Usuarios]);
    quantidade_De_Usuarios++;
  } else {
    mostreerro("Número máximo de usuários atingido.");
  }
}

void cadastrar_Livro(int usuario_Online) {
  if (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
    while (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
      printf(CYAN "Insira o título do livro %d (0 para retornar ao menu): " RESET, quantidade_De_Livros[usuario_Online] + 1);
      fgets(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], maximo_Letras_Livro, stdin);
      int posicaoEnter = strcspn(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "\n");
      titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]][posicaoEnter] = 0;
      if (strcmp(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "0") == 0) {
        break;
      }
      quantidade_De_Livros[usuario_Online]++;
    }
    printf(GREEN "\n-------------------------------\n         LIVROS CADASTRADOS!\n-------------------------------" RESET);
  } else {
    mostreerro("Limite de livros atingido.");
  }
}

void procurar_Livro(int usuario_Online) {
  int escolhaProcurarLivos;
  printf(CYAN "\n-------------------------------\n         PROCURAR LIVROS\n-------------------------------" RESET "\nVocê deseja:\n1. Exibir Livros\n2. Exibir Livros Lidos\n3. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET);
  scanf("%d", &escolhaProcurarLivos);
  getchar();

  switch (escolhaProcurarLivos) {
    case 1:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
      }
      do {
        printf(CYAN "\nVocê tem %d livros na sua biblioteca.\nInsira o número do livro que deseja marcar como lido (ou 0 para voltar ao menu): ", quantidade_De_Livros[usuario_Online], RESET);
        scanf("%d", &escolhaLivro);
        getchar();

        if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
          livros_Lidos[usuario_Online][escolhaLivro - 1] = 1;
          printf(GREEN "Livro '%s' marcado como lido.\n" RESET, titulo_Livros[usuario_Online][escolhaLivro - 1]);
        } else if (escolhaLivro != 0) {
          mostreerro("\nOpção Inválida.");
        }
      } while (escolhaLivro != 0);
      break;

    case 2:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        if (livros_Lidos[usuario_Online][i]) {
          printf("%d. %s (Lido)\n", i + 1, titulo_Livros[usuario_Online][i]);
        }
      }
      printf(CYAN "\nInsira ENTER para voltar ao menu..." RESET);
      getchar();
      break;
  }
}

void remover_Livro(int usuario_Online) {
  int escolhaLivro;
  printf(CYAN "\n-------------------------------\n         REMOVER LIVRO\n-------------------------------\n" RESET);
  for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
    printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
  }
  do {
    printf(CYAN "\nEscolha o número do livro que você quer " RED "remover" CYAN " (ou 0 para voltar ao menu): " RESET);
    scanf("%d", &escolhaLivro);
    getchar();

    if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
      for (int i = escolhaLivro - 1; i < quantidade_De_Livros[usuario_Online] - 1; i++) {
        strcpy(titulo_Livros[usuario_Online][i], titulo_Livros[usuario_Online][i + 1]);
        livros_Lidos[usuario_Online][i] = livros_Lidos[usuario_Online][i + 1];
      }
      quantidade_De_Livros[usuario_Online]--;
      printf(GREEN "\nLivro removido com sucesso.\n" RESET);
    } else if (escolhaLivro != 0) {
      mostreerro("\nOpção Inválida.");
    }
  } while (escolhaLivro != 0);
}

int menuBiblioteca(char *nome_De_Usuario) {
  int escolhaMenuBiblioteca;
  printf(CYAN "\n-------------------------------\n         MENU BIBLIOTECA\n-------------------------------\nOlá, %s!\nO que deseja fazer?" RESET "\n1. Cadastrar Livros\n2. Procurar Livros\n3. Remover Livros\n4. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET, nome_De_Usuario);
  scanf("%d", &escolhaMenuBiblioteca);
  getchar();
  return escolhaMenuBiblioteca;
}

int menuOpcoes() {
  int escolhaMenu;
  printf(CYAN "\n-------------------------------\n         MENU DE OPÇÕES\n-------------------------------\nOlá! Bem-vindo(a) à biblioteca pessoal.\nO que deseja realizar?\n" RESET "\n1. Cadastrar Usuário\n2. Autenticar Usuário\n3. Sair do Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET);
  scanf("%d", &escolhaMenu);
  getchar();
  printf(RESET);
  return escolhaMenu;
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));
  int escolhaMenu, usuario_Online;

  do {
    escolhaMenu = menuOpcoes();

    switch (escolhaMenu) {
      case 1:
        cadastrar_Usuario();
        break;

      case 2:
        usuario_Online = autenticar_Usuario();

        if (usuario_Online != -1) {
          system("clear || cls");
          printf(GREEN "\nAutenticado com sucesso!\n" RESET);

          while (1) {
            int escolha = menuBiblioteca(nome_De_Usuario[usuario_Online]);

            if (escolha == 1)
              cadastrar_Livro(usuario_Online);
            else if (escolha == 2) {
              system("clear || cls");
              procurar_Livro(usuario_Online);
            } else if (escolha == 3) {
              system("clear || cls");
              remover_Livro(usuario_Online);
            } else if (escolha == 4) {
              system("clear || cls");
              break;
            }
          }
        } else {
          mostreerro("Usuário não encontrado.");
        }
        break;

      case 3:
        printf(RED "\nSaindo...\n" RESET);
        break;

      default:
        mostreerro("Opção inválida.");
    }
  } while (escolhaMenu != 3);

  return 0;
}
