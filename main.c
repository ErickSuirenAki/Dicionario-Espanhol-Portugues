#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
    printf("\n--------------- MENU DICIONÁRIO ESPANHOL/PORTUGUÊS ---------------");
    printf("\n1 - Ler arquivo texto");
    printf("\n2 - Exibir árvore");
    printf("\n3 - Inserir nova palavra");
    printf("\n4 - Remover palavra");
    printf("\n5 - Buscar palavra em espanhol (mostra a traducao em português)");
    printf("\n6 - Buscar palavra em português (mostra a traducao em espanhol)");
    printf("\n0 - Sair"); 
    printf("\n------------------------------------------------------------------");
    printf("\nDigite a opção desejada: ");
    scanf("%d", &opcao);

    switch(opcao){
    case 0:
        printf("\nSalvando alterações e fechando o programa!");
        break;
    default:
        printf("\nOpção inválida!");
        break;
        }

    } while (opcao != 0);

    return 0;
}
