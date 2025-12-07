#include <stdio.h>

typedef struct no {
    char espanhol[50];
    char portugues[50];
    char conjugacoes[100];
    int altura;

    struct no *esq;
    struct no *dir;
} No;

typedef struct {
    No *raiz;
} ArvAVL;

void criarVazia(ArvAVL *arvore);
int altura(No *n);
int fatorBalanceamento(No *n);
int max(int a, int b);
No* rotacaoDireita(No *y);
No* rotacaoEsquerda(No *x);
No* rotacaoEsqDir(No *n);
No* rotacaoDirEsq(No *n);
No* inserirAvl(No *raiz, char esp[], char por[], char conj[]);
No* removerAvl(No *raiz, char esp[]);
No* buscarEspanhol(No *raiz, char esp[]);
void buscarPortugues(No *raiz, char por[], int *encontrado);
void listarAvl(No *raiz);
void exibirArvore(No *raiz, int nivel);
No* carregarDoArquivo(No *raiz, const char *nome);
void salvarAvl(No *raiz, FILE  *f);

void destruirAvl(No *raiz);
