/***************************************************************
* Alunos: Anna Júlia Oliveira de Sousa e Erick Batista dos Santos
* Curso: Ciência da Computação - Bacharelado
*
* Trabalho 2: Dicionário de palavras Espanhol-Português
* organizado com uma AVL
*
* Estrutura de Dados I – 2025 – DACC/UNIR, Profa. Carolina Watanabe
* Compilador: MinGW-w64 (GCC – GNU Compiler Collection) versão 6.3.0
* Sistema Operacional: Windows 10/11 – 64 bits
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#include "avl.h"

int main() {

    // Configurações para permitir acentos no Windows (UTF-8)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // DUAS árvores AVL:
    No *avlEs = criarVazia(); // ordenada por espanhol
    No *avlPt = criarVazia(); // ordenada por português

    // Carregar arquivo
    FILE *file = fopen("dicionario.txt", "r");
    if (file != NULL) {

        char esp[64], por[64];

        // Cada linha do arquivo contém: espanhol portugues
        while (fscanf(file, "%s %s", esp, por) == 2) {
            inserirAvl(&avlEs, esp, por); //insere na árvore espanhol->português
            inserirAvl(&avlPt, por, esp); //insere na árvore português->espanhol

        }

        fclose(file);
    } else {
        printf("Arquivo dicionario.txt nao encontrado. Um novo será criado ao sair.\n");
    }

    int opcao;
    char espanhol[64];
    char portugues[64];

    do {
        // Menu
        printf("\n----- DICIONÁRIO Espanhol <-> Português -----\n");
        printf("1 - Exibir árvore (ordenada por espanhol)\n");
        printf("2 - Inserir nova palavra (espanhol -> português)\n");
        printf("3 - Remover palavra (por espanhol)\n");
        printf("4 - Buscar por espanhol\n");
        printf("5 - Buscar por português\n");
        printf("6 - Exibir paragrafação\n");
        printf("7 - Exibir árvore ASCII\n");
        printf("0 - Salvar e sair\n");
        printf("---------------------------------------------\n");
        printf("Opção: ");

        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {

            // Listar árvore por espanhol
            case 1:
                if (avlEs == NULL) printf("Dicionário vazio.\n");
                else listarAvl(avlEs);
                break;

            // Inserir nova palavra
            case 2:{

            
                printf("Espanhol: ");
                fgets(espanhol, sizeof(espanhol), stdin);
                espanhol[strcspn(espanhol, "\r\n")] = 0;

                printf("Português: ");
                fgets(portugues, sizeof(portugues), stdin);
                portugues[strcspn(portugues, "\r\n")] = 0;

                int arvoreEspanhol = inserirAvl(&avlEs, espanhol, portugues);
                int arvorePortugues = inserirAvl(&avlPt, portugues, espanhol);

                if (arvoreEspanhol == 1 || arvorePortugues == 1) {
                    printf("Não foi possível inserir: a palavra já está no dicionário.\n");
                } else {
                    printf("Inserido: %s -> %s\n", espanhol, portugues);
                }
                break;
            }

            // Remover palavra por espanhol
            case 3: {
                printf("Palavra em espanhol a remover: ");
                fgets(espanhol, sizeof(espanhol), stdin);
                espanhol[strcspn(espanhol, "\r\n")] = 0;

                No *aux = buscarEspanhol(avlEs, espanhol);

                if (aux == NULL) {
                    printf("'%s' não existe no dicionário.\n", espanhol);
                } else {
                    avlEs = removerAvl(avlEs, espanhol);
                    avlPt = removerAvl(avlPt, aux->portugues);
                    printf("'%s' removida com sucesso.\n", espanhol);
                }
                break;
            }

            // Buscar espanhol > português
            case 4:
                printf("Digite a palavra em espanhol: ");
                fgets(espanhol, sizeof(espanhol), stdin);
                espanhol[strcspn(espanhol, "\r\n")] = 0;

                No *r1 = buscarEspanhol(avlEs, espanhol);
                if (r1) printf("PT: %s\n", r1->portugues);
                else printf("Palavra não encontrada.\n");
                break;

            // Buscar português > espanhol
            case 5:
                printf("Digite a palavra em português: ");
                fgets(portugues, sizeof(portugues), stdin);
                portugues[strcspn(portugues, "\r\n")] = 0;

                No *r2 = buscarPortugues(avlPt, portugues);
                if (r2) printf("ES: %s\n", r2->portugues);
                else printf("Palavra não encontrada.\n");
                break;

            // Paragrafação
            case 6:
                paragrafacao(avlEs, 0);
                break;

            // ASCII melhor visualização da árvore
            case 7:
                exibirAscii(avlEs, "", 0);
                break;

            // Salvar e sair
            case 0:
                file = fopen("dicionario.txt", "w");
                if (!file) {
                    printf("Erro ao abrir arquivo para salvar.\n");
                } else {
                    salvarAvl(file, avlEs);
                    fclose(file);
                    printf("Dados salvos.\n");
                }
                destruirAvl(avlEs);
                destruirAvl(avlPt);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0); // sair
    system("pause");

    return 0;
}
