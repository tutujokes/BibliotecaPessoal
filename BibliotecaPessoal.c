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

/* FUNÇÃO mostreerro
O QUE FAZ? exibe uma mensagem de erro no terminal
mensagem é a string de erro que será exibida
A função imprime "ERRO:" seguido da mensagem passada, para indicar que algo deu errado */
void mostreerro(const char *mensagem) { printf(RED "ERRO: %s\n" RESET, mensagem); }

/* FUNÇÃO idAleatorio
O QUE FAZ? Gera um ID aleatório entre 0 e 10000. */
int idAleatorio() {
  return rand() % 10001;
  // aqui usamos rand() para gerar um número aleatório
  // o % 10001 garante que o número fique entre 0 e 10000
}

/* FUNÇÃO contadorLidos
O QUE FAZ? calcula quantos livros um usuário específico já leu.
usuario é o ID do usuário para o qual estamos contando os livros lidos
a função percorre todos os livros desse usuário (até o total de 'quantidade_De_Livros[usuario]')
para cada livro, ela soma o valor correspondente em 'livros_Lidos[usuario][i]'
se o livro foi lido, o valor em 'livros_Lidos[usuario][i]' será 1, e 0 se não foi lidoo total de livros lidos é retornado no final.*/
int contadorLidos(int usuario) {
  int contar = 0;
  for (int i = 0; i < quantidade_De_Livros[usuario]; i++) {
    contar += livros_Lidos[usuario][i];
  }
  return contar;
}

/* FUNÇÃO autenticar_Usuario
O QUE FAZ? Autentica um usuário com base no nome ou ID. */
int autenticar_Usuario() {
  char tipo_De_Login[maximo_Letras_Livro];
  // cria um espaço para guardar o nome ou ID que o usuário vai digitar
  printf(CYAN "Digite o nome ou ID do usuário: \n" RESET);
  fgets(tipo_De_Login, maximo_Letras_Livro, stdin);
  // pede para o usuário digitar o nome ou ID e lê o que ele digitou
  tipo_De_Login[strcspn(tipo_De_Login, "\n")] = 0;
  // remove o caractere de nova linha que vem com o input

  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    // agora vamos dar uma olhada em todos os usuários que já estão cadastrados
    if ((tipo_De_Login[0] >= '0' && tipo_De_Login[0] <= '9' && Id_Usario[i] == atoi(tipo_De_Login)) || strcmp(nome_De_Usuario[i], tipo_De_Login) == 0) {
      return i;
      // se o ID ou o nome do usuário bater com algum cadastrado, retorna o índice do usuário
    }
  }
  return -1;
  // se não encontrar ninguém, retorna -1 para indicar que não deu certo
}

/* FUNÇÃO verificar_Usuario_Existente
O QUE FAZ? Verifica se um usuário já está cadastrado. */
int verificar_Usuario_Existente(const char *nome) {
  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    // checa se o nome que a gente recebeu já está na lista
    if (strcmp(nome_De_Usuario[i], nome) == 0) {
      return i;
      // se achar, retorna o índice do usuário que já existe
    }
  }
  return -1;
  // se não achar nada, retorna -1 para indicar que o usuário não está cadastrado
}

/* FUNÇÃO cadastrar_Usuario
O QUE FAZ? Cadastra um novo usuário. */
void cadastrar_Usuario() {
  if (quantidade_De_Usuarios < maximo_De_Usuarios) {
    char nome[maximo_Letras_Livro];
    // espaço para o nome do novo usuário
    printf(CYAN "Digite o nome do usuário: " RESET);
    fgets(nome, maximo_Letras_Livro, stdin);
    // lê o nome que o usuário digitou
    nome[strcspn(nome, "\n")] = 0;
    // remove o enter do final, porque a gente não quer isso

    if (verificar_Usuario_Existente(nome) != -1) {
      mostreerro("Usuário já cadastrado.");
      // se o nome já estiver na lista, mostra um erro e volta
      return;
    }
    strcpy(nome_De_Usuario[quantidade_De_Usuarios], nome);
    // se o nome for novo, copia para a lista de usuários
    Id_Usario[quantidade_De_Usuarios] = idAleatorio();
    // gera um ID aleatório para o novo usuário
    quantidade_De_Livros[quantidade_De_Usuarios] = 0;
    // inicializa a quantidade de livros desse novo usuário como zero
    system("clear || cls");
    // limpa a tela para ficar mais bonito.
    printf(GREEN "Usuário cadastrado com sucesso! ID: %d\n" RESET, Id_Usario[quantidade_De_Usuarios]);
    // mensagem de sucesso mostrando o ID do novo usuário
    quantidade_De_Usuarios++;
    // aumenta o contador de usuários cadastrados
  } else {
    mostreerro("Número máximo de usuários atingido.");
    // se já tiver o número máximo de usuários, mostra um erro
  }
}

/*FUNÇÃO cadastrar_Livro
O QUE FAZ? 1. Pergunta os livros do usuário; 2. Armazena os livros em titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online].*/
void cadastrar_Livro(int usuario_Online) {
  if (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
    // checa se o usuário não atingiu o limite de livros
    while (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
      printf(CYAN "Insira o título do livro %d (0 para retornar ao menu): " RESET, quantidade_De_Livros[usuario_Online] + 1);
      fgets(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], maximo_Letras_Livro, stdin);
      // guarda o título do livro em titulo_Livros, usando fgets para capturar a entrada do teclado
      int posicaoEnter = strcspn(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "\n");
      // strscpn irá ver a primeira ocorrência do enter ("\n") e retornar como valor a posição da ocorrência;
      // posicaoEnter recebera o valor deste strcspn
      titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]][posicaoEnter] = 0;
      // essa linha remove anula/zera o caractere na posicaoEnter do titulo_Livros;
      // isso impede que o enter do input seja inserido na hora de ler
      if (strcmp(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "0") == 0) {
        // caso o usuario digite 0 o loop de cadastro irá encerrar
        break;
      }
      quantidade_De_Livros[usuario_Online]++;
    }
    printf(GREEN "\n-------------------------------\n         LIVROS CADASTRADOS!\n-------------------------------" RESET);
  } else {
    mostreerro("Limite de livros atingido.");
  }
}

/*FUNÇÃO procurar_Livro
O QUE FAZ? Exibe um menu que possibilita o usuário: 1. Listar livros cadastrados 2. Marcar os livros como lidos 3. Remover livros*/
void procurar_Livro(int usuario_Online) {
  int escolhaProcurarLivos;
  printf(CYAN "\n-------------------------------\n         PROCURAR LIVROS\n-------------------------------" RESET "\nVocê deseja:\n1. Exibir Livros\n2. Exibir Livros Lidos\n3. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET);
  scanf("%d", &escolhaProcurarLivos);
  getchar();

  switch (escolhaProcurarLivos) {
    // Exibir livros:
    case 1:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
        // printa os livros em lista, e, CASO o livro na posição i seja um livro marcado como lido, será printado "Lido" em sequência ao titulo
      }
      do {
        printf(CYAN "\nVocê tem %d livros na sua biblioteca e %d livros lidos.\nInsira o número do livro que deseja marcar como lido (ou 0 para voltar ao menu): " RESET, quantidade_De_Livros[usuario_Online], contadorLidos(usuario_Online), RESET);
        // armazena a escolha do usuario ao final do loop
        scanf("%d", &escolhaLivro);
        getchar();

        // Processo de marcação de livros lidos:
        if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
          livros_Lidos[usuario_Online][escolhaLivro - 1] = 1;
          // o livro que o usuario desejar marcar terá o seu indice em livros_Lidos incrementado
          printf(GREEN "Livro '%s' marcado como lido.\n" RESET, titulo_Livros[usuario_Online][escolhaLivro - 1]);
        } else if (escolhaLivro != 0) {
          mostreerro("\nOpção Inválida.");
        }
      } while (escolhaLivro != 0);
      // loop executado até o usuário digitar 0
      break;
    // Exibir livros lidos:
    case 2:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        if (livros_Lidos[usuario_Online][i]) {
          // se o livros_Lidos na posição i não for 0 (se ele for marcado como lido):
          printf("%d. %s (Lido)\n", i + 1, titulo_Livros[usuario_Online][i]);
          // exibe apenas os livros lidos em lista
        }
      }
      printf(CYAN "\nVocê tem %d livros lidos. Insira ENTER para voltar ao menu..." RESET, contadorLidos(usuario_Online));
      getchar();
      break;
  }
}

/*FUNÇÃO remover_Livro
O QUE FAZ? Remove os livros cadastrados do usuário usando o método do strcpy*/
void remover_Livro(int usuario_Online) {
  int escolhaLivro;
  printf(CYAN "\n-------------------------------\n         REMOVER LIVRO\n-------------------------------\n" RESET);
  for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
    printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
    // exibe a lista de livros do usuário com seu estado, lido ou não
  }
  do {
    printf(CYAN "\nEscolha o número do livro que você quer " RED "remover" CYAN " (ou 0 para voltar ao menu): " RESET);
    // verifica em loop se o usuario quer remover algum livro e armazena o número do livro que deseja remover em escolhaLivro
    scanf("%d", &escolhaLivro);
    getchar();

    // Processo de remoção dos livros:
    if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
      // começa do livro que deseja remover até o último livro cadastrado
      for (int i = escolhaLivro - 1; i < quantidade_De_Livros[usuario_Online] - 1; i++) {
        strcpy(titulo_Livros[usuario_Online][i], titulo_Livros[usuario_Online][i + 1]);
        // copia o título do próximo livro para o livro atual e subsequentemente, até o final do loop, utilizando o strcpy
        // desta forma o livro que deseja remover é sobrescrito com o livro que o sucede
        livros_Lidos[usuario_Online][i] = livros_Lidos[usuario_Online][i + 1];
        // mesmo processo para os livros lidos
      }
      quantidade_De_Livros[usuario_Online]--;
      printf(GREEN "\nLivro removido com sucesso.\n" RESET);
    } else if (escolhaLivro != 0) {
      mostreerro("\nOpção Inválida.");
    }
  } while (escolhaLivro != 0);
}

/*FUNÇÃO menuBiblioteca
O QUE FAZ? Exibe a interface do Menu Principal*/
int menuBiblioteca(char *nome_De_Usuario) {
  int escolhaMenuBiblioteca;
  printf(CYAN "\n-------------------------------\n         MENU BIBLIOTECA\n-------------------------------\nOlá, %s!\nO que deseja fazer?" RESET "\n1. Cadastrar Livros\n2. Procurar Livros\n3. Remover Livros\n4. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET, nome_De_Usuario);
  scanf("%d", &escolhaMenuBiblioteca);
  getchar();
  return escolhaMenuBiblioteca;
}

/*FUNÇÃO menuBiblioteca
O QUE FAZ? Exibe a interface do Menu Secundário, exibido pós Login*/
int menuOpcoes() {
  int escolhaMenu;
  printf(CYAN "\n-------------------------------\n         MENU DE OPÇÕES\n-------------------------------\nOlá! Bem-vindo(a) à biblioteca pessoal.\nO que deseja realizar?\n" RESET "\n1. Cadastrar Usuário\n2. Fazer Login\n3. Sair do Menu" CYAN "\n-------------------------------\nInsira sua opção: " RESET);
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
        system("clear || cls");
        mostreerro("Opção Inválida.");
    }
  } while (escolhaMenu != 3);

  return 0;
}
