#ifndef AVL_H
#define AVL_H

typedef struct No {
    char espanhol[50];
    char portugues[50];
    char conjugacoes[100];
    char significado[100];
    int altura;
    struct No *esq;
    struct No *dir;
} No;

No* criarVazia();
int altura(No *raiz);
int fatorBalanceamento(No *raiz);
No* rotacaoDireita(No *raiz);
No* rotacaoEsquerda(No *raiz);
No* balancear(No *raiz);
No* inserirAvl(No *raiz, char *espanhol, char *portugues, char *conjugacoes, char *significado);
No* removerAvl(No *raiz, char *espanhol);
No* buscarEspanhol(No *raiz, char *espanhol);
No* buscarPortugues(No *raiz, char *portugues);
void listarAvl(No *raiz);
void salvarAvl(FILE *file, No *raiz);
void destruirAvl(No *raiz);

#endif
