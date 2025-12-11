#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "avl.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *file;
    No* avl = criarVazia();
    file = fopen("dicionario.txt", "r");
    if(file != NULL){
        carregarAvl(file, &avl);
        fclose(file);
    }

    int opcao;
    char espanhol[50];
    char portugues[50];
    char conjugacoes[100];
    char significado[100];

    do {
    printf("\n--------------- MENU DICION�RIO ESPANHOL/PORTUG�ES ---------------");
    printf("\n1 - Exibir �rvore");
    printf("\n2 - Inserir nova palavra");
    printf("\n3 - Remover palavra");
    printf("\n4 - Buscar palavra em espanhol (mostra a traducao em portugu�s)");
    printf("\n5 - Buscar palavra em portugu�s (mostra a traducao em espanhol)");
    printf("\n0 - Salvar e sair"); //antes de sair, salvar altera��es no arquivo txt, depois destruir
    printf("\n------------------------------------------------------------------");
    printf("\nDigite a op��o desejada: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao){
    case 0:
        file = fopen("dicionario.txt", "w");
        if(file == NULL){
            printf("\nErro ao abrir o arquivo dicionario.txt para escrita.");
        } else {
            salvarAvl(file, avl);
            fclose(file);
            printf("\nDados salvos com sucesso!");
        }
        printf("\nSalvando altera��es e fechando o programa!");
        break;

    case 1:
        if(avl == NULL)
            printf("\nDicion�rio vazio!");
        else
            listarAvl(avl);
        break;

    case 2:
        printf("\nDigite a palavra em espanhol: ");
        fgets(espanhol, 50, stdin);
        espanhol[strcspn(espanhol, "\n")] = 0;

        printf("\nDigite a palavra em portug�es: ");
        fgets(portugues, 50, stdin);
        portugues[strcspn(portugues, "\n")] = 0;

        printf("\nDigite as conjuga��es: ");
        fgets(conjugacoes, 100, stdin);
        conjugacoes[strcspn(conjugacoes, "\n")] = 0;

        printf("\nDigite o significado: ");
        fgets(significado, 100, stdin);
        significado[strcspn(significado, "\n")] = 0;

        avl = inserirAvl(avl, espanhol, portugues, conjugacoes, significado);
        printf("\nPalavra inserida com sucesso!");
        break;

    case 3:
        printf("\nDigite a palavra em espanhol a ser removida: ");
        fgets(espanhol, 50, stdin);
        espanhol[strcspn(espanhol, "\n")] = 0;
        avl = removerAvl(avl, espanhol);
        printf("\nPalavra removida com sucesso!");
        break;

    case 4:
        break;

    case 5:
        break;

    default:
        printf("\nOp��o inv�lida!");
        break;
        }

    } while (opcao != 0);

    return 0;
}
