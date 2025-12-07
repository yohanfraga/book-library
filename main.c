/*
 * Sistema de Gerenciamento de Livros - Biblioteca
 * 
 * Este programa permite cadastrar, pesquisar, ordenar e gerenciar
 * um acervo de até 20 livros de uma biblioteca.
 * 
 * Conceitos aplicados: structs, vetores, funções, strings,
 * estruturas de repetição e condicionais.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 // Definição da constante para o tamanho máximo do acervo
 #define TAMANHO_ACERVO 20
 
 // Estrutura para armazenar os dados de cada livro
 struct Livro {
     int codigo;           // Código único do livro
     char titulo[50];      // Título do livro
     char autor[30];       // Nome do autor
     char area[30];        // Área do conhecimento
     int ano;              // Ano de publicação
     char editora[30];     // Nome da editora
 };
 
 // Protótipos das funções
 void cadastrarLivros(struct Livro acervo[], int tamanho);
 void imprimirLivros(struct Livro acervo[], int tamanho);
 void pesquisarLivro(struct Livro acervo[], int tamanho, int codigoBusca);
 void ordenarLivros(struct Livro acervo[], int tamanho);
 void exibirMenu();
 void limparBuffer();
 
 /*
  * Função principal - controla o fluxo do programa
  */
 int main() {
     struct Livro acervo[TAMANHO_ACERVO];  // Vetor de livros
     int opcao;                             // Opção escolhida pelo usuário
     int codigoBusca;                       // Código para pesquisa
     
     // Inicializa o vetor com códigos -1 (indica posição vazia)
     for(int i = 0; i < TAMANHO_ACERVO; i++) {
         acervo[i].codigo = -1;
     }
     
     printf("========================================\n");
     printf("  SISTEMA DE GERENCIAMENTO DE LIVROS  \n");
     printf("========================================\n\n");
     
     // Loop principal do programa
     do {
         exibirMenu();
         printf("Escolha uma opcao: ");
         scanf("%d", &opcao);
         limparBuffer();
         
         printf("\n");
         
         // Estrutura de seleção para processar a opção escolhida
         switch(opcao) {
             case 1:
                 printf("--- CADASTRAR LIVROS ---\n");
                 cadastrarLivros(acervo, TAMANHO_ACERVO);
                 break;
                 
             case 2:
                 printf("--- LISTA DE TODOS OS LIVROS ---\n");
                 imprimirLivros(acervo, TAMANHO_ACERVO);
                 break;
                 
             case 3:
                 printf("--- PESQUISAR LIVRO ---\n");
                 printf("Digite o codigo do livro: ");
                 scanf("%d", &codigoBusca);
                 limparBuffer();
                 pesquisarLivro(acervo, TAMANHO_ACERVO, codigoBusca);
                 break;
                 
             case 4:
                 printf("--- ORDENAR LIVROS POR ANO ---\n");
                 ordenarLivros(acervo, TAMANHO_ACERVO);
                 printf("Livros ordenados com sucesso!\n");
                 break;
                 
             case 5:
                 printf("Encerrando o sistema...\n");
                 printf("Obrigado por usar o sistema!\n");
                 break;
                 
             default:
                 printf("Opcao invalida! Tente novamente.\n");
         }
         
         printf("\n");
         
     } while(opcao != 5);  // Continua até o usuário escolher sair
     
     return 0;
 }
 
 /*
  * Função: exibirMenu
  * Descrição: Exibe o menu principal com as opções disponíveis
  */
 void exibirMenu() {
     printf("========================================\n");
     printf("              MENU PRINCIPAL            \n");
     printf("========================================\n");
     printf("1 - Cadastrar livros\n");
     printf("2 - Imprimir todos os livros\n");
     printf("3 - Pesquisar livro por codigo\n");
     printf("4 - Ordenar livros por ano de publicacao\n");
     printf("5 - Sair do programa\n");
     printf("========================================\n");
 }
 
 /*
  * Função: limparBuffer
  * Descrição: Limpa o buffer do teclado para evitar problemas com scanf
  */
 void limparBuffer() {
     int c;
     while ((c = getchar()) != '\n' && c != EOF);
 }
 
 /*
  * Função: cadastrarLivros
  * Descrição: Cadastra os dados de cada livro no acervo
  * Parâmetros:
  *   - acervo[]: vetor de structs onde os livros serão armazenados
  *   - tamanho: quantidade máxima de livros no acervo
  */
 void cadastrarLivros(struct Livro acervo[], int tamanho) {
     int quantidade;
     
     printf("Quantos livros deseja cadastrar? (maximo %d): ", tamanho);
     scanf("%d", &quantidade);
     limparBuffer();
     
     // Valida a quantidade informada
     if(quantidade < 1 || quantidade > tamanho) {
         printf("Quantidade invalida!\n");
         return;
     }
     
     // Loop para cadastrar cada livro
     for(int i = 0; i < quantidade; i++) {
         printf("\n--- Livro %d ---\n", i + 1);
         
         printf("Codigo: ");
         scanf("%d", &acervo[i].codigo);
         limparBuffer();
         
         printf("Titulo: ");
         fgets(acervo[i].titulo, 50, stdin);
         acervo[i].titulo[strcspn(acervo[i].titulo, "\n")] = '\0';  // Remove o \n
         
         printf("Autor: ");
         fgets(acervo[i].autor, 30, stdin);
         acervo[i].autor[strcspn(acervo[i].autor, "\n")] = '\0';
         
         printf("Area: ");
         fgets(acervo[i].area, 30, stdin);
         acervo[i].area[strcspn(acervo[i].area, "\n")] = '\0';
         
         printf("Ano de publicacao: ");
         scanf("%d", &acervo[i].ano);
         limparBuffer();
         
         printf("Editora: ");
         fgets(acervo[i].editora, 30, stdin);
         acervo[i].editora[strcspn(acervo[i].editora, "\n")] = '\0';
     }
     
     printf("\n%d livro(s) cadastrado(s) com sucesso!\n", quantidade);
 }
 
 /*
  * Função: imprimirLivros
  * Descrição: Imprime todos os livros cadastrados no acervo
  * Parâmetros:
  *   - acervo[]: vetor de structs com os livros
  *   - tamanho: quantidade de posições no vetor
  */
 void imprimirLivros(struct Livro acervo[], int tamanho) {
     int encontrou = 0;  // Flag para verificar se há livros cadastrados
     
     // Percorre todo o vetor procurando livros cadastrados
     for(int i = 0; i < tamanho; i++) {
         // Código -1 indica posição vazia
         if(acervo[i].codigo != -1) {
             encontrou = 1;
             printf("\n--- Livro %d ---\n", i + 1);
             printf("Codigo: %d\n", acervo[i].codigo);
             printf("Titulo: %s\n", acervo[i].titulo);
             printf("Autor: %s\n", acervo[i].autor);
             printf("Area: %s\n", acervo[i].area);
             printf("Ano: %d\n", acervo[i].ano);
             printf("Editora: %s\n", acervo[i].editora);
         }
     }
     
     // Se não encontrou nenhum livro cadastrado
     if(!encontrou) {
         printf("Nenhum livro cadastrado no acervo.\n");
     }
 }
 
 /*
  * Função: pesquisarLivro
  * Descrição: Busca um livro específico pelo código
  * Parâmetros:
  *   - acervo[]: vetor de structs com os livros
  *   - tamanho: quantidade de posições no vetor
  *   - codigoBusca: código do livro a ser encontrado
  */
 void pesquisarLivro(struct Livro acervo[], int tamanho, int codigoBusca) {
     int i = 0;
     int encontrado = 0;  // Flag para indicar se o livro foi encontrado
     
     // Loop while para buscar o livro
     while(i < tamanho && !encontrado) {
         if(acervo[i].codigo == codigoBusca) {
             encontrado = 1;
             printf("\nLivro encontrado!\n");
             printf("--- Detalhes do Livro ---\n");
             printf("Codigo: %d\n", acervo[i].codigo);
             printf("Titulo: %s\n", acervo[i].titulo);
             printf("Autor: %s\n", acervo[i].autor);
             printf("Area: %s\n", acervo[i].area);
             printf("Ano: %d\n", acervo[i].ano);
             printf("Editora: %s\n", acervo[i].editora);
         }
         i++;
     }
     
     // Se o livro não foi encontrado
     if(!encontrado) {
         printf("\nLivro com codigo %d nao encontrado.\n", codigoBusca);
     }
 }
 
 /*
  * Função: ordenarLivros
  * Descrição: Ordena os livros por ano de publicação usando Bubble Sort
  * Parâmetros:
  *   - acervo[]: vetor de structs com os livros
  *   - tamanho: quantidade de posições no vetor
  * 
  * Algoritmo: Bubble Sort compara elementos adjacentes e os troca
  * se estiverem na ordem errada. O processo se repete até que
  * nenhuma troca seja necessária.
  */
 void ordenarLivros(struct Livro acervo[], int tamanho) {
     struct Livro temp;  // Variável temporária para a troca
     
     // Loop externo: controla o número de passagens
     for(int i = 0; i < tamanho - 1; i++) {
         // Loop interno: compara elementos adjacentes
         for(int j = 0; j < tamanho - i - 1; j++) {
             // Verifica se ambos os livros estão cadastrados e compara os anos
             if(acervo[j].codigo != -1 && acervo[j + 1].codigo != -1) {
                 if(acervo[j].ano > acervo[j + 1].ano) {
                     // Troca os livros de posição
                     temp = acervo[j];
                     acervo[j] = acervo[j + 1];
                     acervo[j + 1] = temp;
                 }
             }
         }
     }
 }