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

/* FUN��O mostreerro
O QUE FAZ? exibe uma mensagem de erro no terminal
mensagem � a string de erro que ser� exibida
A fun��o imprime "ERRO:" seguido da mensagem passada, para indicar que algo deu errado */
void mostreerro(const char *mensagem) { printf(RED "ERRO: %s\n" RESET, mensagem); }

/* FUN��O idAleatorio
O QUE FAZ? Gera um ID aleat�rio entre 0 e 10000. */
int idAleatorio() {
  return rand() % 10001;
  // aqui usamos rand() para gerar um n�mero aleat�rio
  // o % 10001 garante que o n�mero fique entre 0 e 10000
}

/* FUN��O contadorLidos
O QUE FAZ? calcula quantos livros um usu�rio espec�fico j� leu.
usuario � o ID do usu�rio para o qual estamos contando os livros lidos
a fun��o percorre todos os livros desse usu�rio (at� o total de 'quantidade_De_Livros[usuario]')
para cada livro, ela soma o valor correspondente em 'livros_Lidos[usuario][i]'
se o livro foi lido, o valor em 'livros_Lidos[usuario][i]' ser� 1, e 0 se n�o foi lidoo total de livros lidos � retornado no final.*/
int contadorLidos(int usuario) {
  int contar = 0;
  for (int i = 0; i < quantidade_De_Livros[usuario]; i++) {
    contar += livros_Lidos[usuario][i];
  }
  return contar;
}

/* FUN��O autenticar_Usuario
O QUE FAZ? Autentica um usu�rio com base no nome ou ID. */
int autenticar_Usuario() {
  char tipo_De_Login[maximo_Letras_Livro];
  // cria um espa�o para guardar o nome ou ID que o usu�rio vai digitar
  printf(CYAN "Digite o nome ou ID do usu�rio: \n" RESET);
  fgets(tipo_De_Login, maximo_Letras_Livro, stdin);
  // pede para o usu�rio digitar o nome ou ID e l� o que ele digitou
  tipo_De_Login[strcspn(tipo_De_Login, "\n")] = 0;
  // remove o caractere de nova linha que vem com o input

  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    // agora vamos dar uma olhada em todos os usu�rios que j� est�o cadastrados
    if ((tipo_De_Login[0] >= '0' && tipo_De_Login[0] <= '9' && Id_Usario[i] == atoi(tipo_De_Login)) || strcmp(nome_De_Usuario[i], tipo_De_Login) == 0) {
      return i;
      // se o ID ou o nome do usu�rio bater com algum cadastrado, retorna o �ndice do usu�rio
    }
  }
  return -1;
  // se n�o encontrar ningu�m, retorna -1 para indicar que n�o deu certo
}

/* FUN��O verificar_Usuario_Existente
O QUE FAZ? Verifica se um usu�rio j� est� cadastrado. */
int verificar_Usuario_Existente(const char *nome) {
  for (int i = 0; i < quantidade_De_Usuarios; i++) {
    // checa se o nome que a gente recebeu j� est� na lista
    if (strcmp(nome_De_Usuario[i], nome) == 0) {
      return i;
      // se achar, retorna o �ndice do usu�rio que j� existe
    }
  }
  return -1;
  // se n�o achar nada, retorna -1 para indicar que o usu�rio n�o est� cadastrado
}

/* FUN��O cadastrar_Usuario
O QUE FAZ? Cadastra um novo usu�rio. */
void cadastrar_Usuario() {
  if (quantidade_De_Usuarios < maximo_De_Usuarios) {
    char nome[maximo_Letras_Livro];
    // espa�o para o nome do novo usu�rio
    printf(CYAN "Digite o nome do usu�rio: " RESET);
    fgets(nome, maximo_Letras_Livro, stdin);
    // l� o nome que o usu�rio digitou
    nome[strcspn(nome, "\n")] = 0;
    // remove o enter do final, porque a gente n�o quer isso

    if (verificar_Usuario_Existente(nome) != -1) {
      mostreerro("Usu�rio j� cadastrado.");
      // se o nome j� estiver na lista, mostra um erro e volta
      return;
    }
    strcpy(nome_De_Usuario[quantidade_De_Usuarios], nome);
    // se o nome for novo, copia para a lista de usu�rios
    Id_Usario[quantidade_De_Usuarios] = idAleatorio();
    // gera um ID aleat�rio para o novo usu�rio
    quantidade_De_Livros[quantidade_De_Usuarios] = 0;
    // inicializa a quantidade de livros desse novo usu�rio como zero
    system("clear || cls");
    // limpa a tela para ficar mais bonito.
    printf(GREEN "Usu�rio cadastrado com sucesso! ID: %d\n" RESET, Id_Usario[quantidade_De_Usuarios]);
    // mensagem de sucesso mostrando o ID do novo usu�rio
    quantidade_De_Usuarios++;
    // aumenta o contador de usu�rios cadastrados
  } else {
    mostreerro("N�mero m�ximo de usu�rios atingido.");
    // se j� tiver o n�mero m�ximo de usu�rios, mostra um erro
  }
}

/*FUN��O cadastrar_Livro
O QUE FAZ? 1. Pergunta os livros do usu�rio; 2. Armazena os livros em titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online].*/
void cadastrar_Livro(int usuario_Online) {
  if (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
    // checa se o usu�rio n�o atingiu o limite de livros
    while (quantidade_De_Livros[usuario_Online] < maximo_De_Livros) {
      printf(CYAN "Insira o t�tulo do livro %d (0 para retornar ao menu): " RESET, quantidade_De_Livros[usuario_Online] + 1);
      fgets(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], maximo_Letras_Livro, stdin);
      // guarda o t�tulo do livro em titulo_Livros, usando fgets para capturar a entrada do teclado
      int posicaoEnter = strcspn(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "\n");
      // strscpn ir� ver a primeira ocorr�ncia do enter ("\n") e retornar como valor a posi��o da ocorr�ncia;
      // posicaoEnter recebera o valor deste strcspn
      titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]][posicaoEnter] = 0;
      // essa linha remove anula/zera o caractere na posicaoEnter do titulo_Livros;
      // isso impede que o enter do input seja inserido na hora de ler
      if (strcmp(titulo_Livros[usuario_Online][quantidade_De_Livros[usuario_Online]], "0") == 0) {
        // caso o usuario digite 0 o loop de cadastro ir� encerrar
        break;
      }
      quantidade_De_Livros[usuario_Online]++;
    }
    printf(GREEN "\n-------------------------------\n         LIVROS CADASTRADOS!\n-------------------------------" RESET);
  } else {
    mostreerro("Limite de livros atingido.");
  }
}

/*FUN��O procurar_Livro
O QUE FAZ? Exibe um menu que possibilita o usu�rio: 1. Listar livros cadastrados 2. Marcar os livros como lidos 3. Remover livros*/
void procurar_Livro(int usuario_Online) {
  int escolhaProcurarLivos;
  printf(CYAN "\n-------------------------------\n         PROCURAR LIVROS\n-------------------------------" RESET "\nVoc� deseja:\n1. Exibir Livros\n2. Exibir Livros Lidos\n3. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua op��o: " RESET);
  scanf("%d", &escolhaProcurarLivos);
  getchar();

  switch (escolhaProcurarLivos) {
    // Exibir livros:
    case 1:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
        // printa os livros em lista, e, CASO o livro na posi��o i seja um livro marcado como lido, ser� printado "Lido" em sequ�ncia ao titulo
      }
      do {
        printf(CYAN "\nVoc� tem %d livros na sua biblioteca e %d livros lidos.\nInsira o n�mero do livro que deseja marcar como lido (ou 0 para voltar ao menu): " RESET, quantidade_De_Livros[usuario_Online], contadorLidos(usuario_Online), RESET);
        // armazena a escolha do usuario ao final do loop
        scanf("%d", &escolhaLivro);
        getchar();

        // Processo de marca��o de livros lidos:
        if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
          livros_Lidos[usuario_Online][escolhaLivro - 1] = 1;
          // o livro que o usuario desejar marcar ter� o seu indice em livros_Lidos incrementado
          printf(GREEN "Livro '%s' marcado como lido.\n" RESET, titulo_Livros[usuario_Online][escolhaLivro - 1]);
        } else if (escolhaLivro != 0) {
          mostreerro("\nOp��o Inv�lida.");
        }
      } while (escolhaLivro != 0);
      // loop executado at� o usu�rio digitar 0
      break;
    // Exibir livros lidos:
    case 2:
      for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
        if (livros_Lidos[usuario_Online][i]) {
          // se o livros_Lidos na posi��o i n�o for 0 (se ele for marcado como lido):
          printf("%d. %s (Lido)\n", i + 1, titulo_Livros[usuario_Online][i]);
          // exibe apenas os livros lidos em lista
        }
      }
      printf(CYAN "\nVoc� tem %d livros lidos. Insira ENTER para voltar ao menu..." RESET, contadorLidos(usuario_Online));
      getchar();
      break;
  }
}

/*FUN��O remover_Livro
O QUE FAZ? Remove os livros cadastrados do usu�rio usando o m�todo do strcpy*/
void remover_Livro(int usuario_Online) {
  int escolhaLivro;
  printf(CYAN "\n-------------------------------\n         REMOVER LIVRO\n-------------------------------\n" RESET);
  for (int i = 0; i < quantidade_De_Livros[usuario_Online]; i++) {
    printf("%d. %s%s\n", i + 1, titulo_Livros[usuario_Online][i], livros_Lidos[usuario_Online][i] ? " (Lido)" : "");
    // exibe a lista de livros do usu�rio com seu estado, lido ou n�o
  }
  do {
    printf(CYAN "\nEscolha o n�mero do livro que voc� quer " RED "remover" CYAN " (ou 0 para voltar ao menu): " RESET);
    // verifica em loop se o usuario quer remover algum livro e armazena o n�mero do livro que deseja remover em escolhaLivro
    scanf("%d", &escolhaLivro);
    getchar();

    // Processo de remo��o dos livros:
    if (escolhaLivro > 0 && escolhaLivro <= quantidade_De_Livros[usuario_Online]) {
      // come�a do livro que deseja remover at� o �ltimo livro cadastrado
      for (int i = escolhaLivro - 1; i < quantidade_De_Livros[usuario_Online] - 1; i++) {
        strcpy(titulo_Livros[usuario_Online][i], titulo_Livros[usuario_Online][i + 1]);
        // copia o t�tulo do pr�ximo livro para o livro atual e subsequentemente, at� o final do loop, utilizando o strcpy
        // desta forma o livro que deseja remover � sobrescrito com o livro que o sucede
        livros_Lidos[usuario_Online][i] = livros_Lidos[usuario_Online][i + 1];
        // mesmo processo para os livros lidos
      }
      quantidade_De_Livros[usuario_Online]--;
      printf(GREEN "\nLivro removido com sucesso.\n" RESET);
    } else if (escolhaLivro != 0) {
      mostreerro("\nOp��o Inv�lida.");
    }
  } while (escolhaLivro != 0);
}

/*FUN��O menuBiblioteca
O QUE FAZ? Exibe a interface do Menu Principal*/
int menuBiblioteca(char *nome_De_Usuario) {
  int escolhaMenuBiblioteca;
  printf(CYAN "\n-------------------------------\n         MENU BIBLIOTECA\n-------------------------------\nOl�, %s!\nO que deseja fazer?" RESET "\n1. Cadastrar Livros\n2. Procurar Livros\n3. Remover Livros\n4. Retornar ao Menu" CYAN "\n-------------------------------\nInsira sua op��o: " RESET, nome_De_Usuario);
  scanf("%d", &escolhaMenuBiblioteca);
  getchar();
  return escolhaMenuBiblioteca;
}

/*FUN��O menuBiblioteca
O QUE FAZ? Exibe a interface do Menu Secund�rio, exibido p�s Login*/
int menuOpcoes() {
  int escolhaMenu;
  printf(CYAN "\n-------------------------------\n         MENU DE OP��ES\n-------------------------------\nOl�! Bem-vindo(a) � biblioteca pessoal.\nO que deseja realizar?\n" RESET "\n1. Cadastrar Usu�rio\n2. Fazer Login\n3. Sair do Menu" CYAN "\n-------------------------------\nInsira sua op��o: " RESET);
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
          mostreerro("Usu�rio n�o encontrado.");
        }
        break;

      case 3:
        printf(RED "\nSaindo...\n" RESET);
        break;

      default:
        system("clear || cls");
        mostreerro("Op��o Inv�lida.");
    }
  } while (escolhaMenu != 3);

  return 0;
}
