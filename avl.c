/***************************************************************
* Alunos: Anna Júlia Oliveira de Sousa e Erick Batista dos Santos
* Curso: Ciência da Computação - Bacharelado
*
*
* Trabalho 2: Dicionário de palavras Espanhol-Português*
* organizado com uma AVL
*
*
*
* Estrutura de Dados I-- 2025-- DACC/UNIR, Profa. Carolina Watanabe *
* Compilador: MinGW-w64 (GCC – GNU Compiler Collection) versao  6.3.0
*
* Sistema Operacional: Windows 10/11 – 64 bits
*
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

//cria uma arvore vazia
No* criarVazia(){
    return NULL;
}

//retorna a altura da arvore
int altura(No *raiz){
    if(raiz == NULL) return 0;
    return raiz->altura;
}

//retorna o fator de balanceamento
int fatorBalanceamento(No *raiz){
    if (raiz == NULL) return 0;
    return altura(raiz->esq) - altura(raiz->dir);
}

//rotações para balanceamento
No* rotacaoDireita(No *y){
    No *x = y->esq;
    No *T2 = x->dir;

    // rotacao
    x->dir = y;
    y->esq = T2;

    // atualizar alturas
    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));
    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));

    return x;
}

No* rotacaoEsquerda(No *x){
    No *y = x->dir;
    No *T2 = y->esq;

    // rotacao
    y->esq = x;
    x->dir = T2;

    // atualizar alturas
    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));
    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));

    return y;
}

// balancear a arvore
No* balancear(No *raiz){
    if (raiz == NULL) return raiz;

    int bal = fatorBalanceamento(raiz);

    if (bal > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (bal > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (bal < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (bal < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

//inserir na arvore AVL
int inserirAvl(No **raiz, const char *esp, const char *por) {

    if (*raiz == NULL) {
        No *novo = malloc(sizeof(No));
        strcpy(novo->espanhol, esp);
        strcpy(novo->portugues, por);
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        *raiz = novo;
        return 0;  // inserido
    }

    int cmp = strcmp(esp, (*raiz)->espanhol);
    int r;

    if (cmp < 0) {
        r = inserirAvl(&(*raiz)->esq, esp, por);
    }
    else if (cmp > 0) {
        r = inserirAvl(&(*raiz)->dir, esp, por);
    }
    else {
        return 1; // já existe
    }

    // atualizar altura
    int ae = altura((*raiz)->esq);
    int ad = altura((*raiz)->dir);

    int maior;
    if (ae > ad)
        maior = ae;
    else
        maior = ad;

    (*raiz)->altura = 1 + maior;

    // balancear
    *raiz = balancear(*raiz);

    return r;
}

//retorna o nó com o menor valor
static No* menorNo(No* raiz) {
    No* atual = raiz;

    while (atual != NULL && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

//remover da arvore AVL
No* removerAvl(No *raiz, const char *espanhol){
    if (raiz == NULL) return raiz;

    int cmp = strcmp(espanhol, raiz->espanhol);
    if (cmp < 0)
        raiz->esq = removerAvl(raiz->esq, espanhol);
    else if (cmp > 0)
        raiz->dir = removerAvl(raiz->dir, espanhol);
    else {
        // nó com 1 ou 0 filhos
        if (raiz->esq == NULL || raiz->dir == NULL){
            No *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL){
                // sem filhos
                temp = raiz;
                raiz = NULL;
            } else {
                // um filho
                *raiz = *temp; // copia conteúdo
            }
            free(temp);
        } else {
            // 2 filhos: pegar sucessor inorder (menor da subárvore direita)
            No *temp = menorNo(raiz->dir);
            // copiar dados
            strncpy(raiz->espanhol, temp->espanhol, sizeof(raiz->espanhol)-1);
            raiz->espanhol[sizeof(raiz->espanhol)-1] = '\0';
            strncpy(raiz->portugues, temp->portugues, sizeof(raiz->portugues)-1);
            raiz->portugues[sizeof(raiz->portugues)-1] = '\0';
            // remover o sucessor
            raiz->dir = removerAvl(raiz->dir, temp->espanhol);
        }
    }

    if (raiz == NULL)
        return raiz;

    // atualizar altura
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));

    // balancear
    return balancear(raiz);
}

//buscar em espanhol
No* buscarEspanhol(No *raiz, const char *espanhol){
    if (raiz == NULL) return NULL;
    int cmp = strcmp(espanhol, raiz->espanhol);
    if (cmp == 0) return raiz;
    else if (cmp < 0) return buscarEspanhol(raiz->esq, espanhol);
    else return buscarEspanhol(raiz->dir, espanhol);
}

//buscar em portugues
No* buscarPortugues(No *raiz, const char *portugues){
    if (raiz == NULL) return NULL;

    int cmp = strcmp(portugues, raiz->espanhol); 
    if (cmp == 0) return raiz;
    else if (cmp < 0) return buscarPortugues(raiz->esq, portugues);
    else return buscarPortugues(raiz->dir, portugues);
}


//listar em ordem (ordenado por espanhol)
void listarAvl(No *raiz){
    if (raiz == NULL) return;
    listarAvl(raiz->esq);
    printf("ES: %-20s | PT: %s\n", raiz->espanhol, raiz->portugues);
    listarAvl(raiz->dir);
}

//salvar em ordem (ordenado por espanhol)
void salvarAvl(FILE *file, No *raiz) {
    if (raiz == NULL) return;
    salvarAvl(file, raiz->esq);
    fprintf(file, "%s %s\n", raiz->espanhol, raiz->portugues);
    salvarAvl(file, raiz->dir);
}


//carregar do arquivo para a arvore AVL
void carregarAvl(FILE *file, No **raiz) {
    char linha[200];
    char esp[64], por[64];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        // ignora linhas vazias
        if (linha[0] == '\n' || linha[0] == '\r')
            continue;

        // lê as duas palavras separadas por espaço
        if (sscanf(linha, "%s %s", esp, por) == 2) {
            inserirAvl(raiz, esp, por);
        }
    }
}

//destruir a arvore AVL
void destruirAvl(No *raiz){
    if (raiz == NULL) return;
    destruirAvl(raiz->esq);
    destruirAvl(raiz->dir);
    free(raiz);
}

//funcoes de exibicao
void paragrafacao(No *raiz, int nivel) {
    if (raiz == NULL) return;

    // imprime os pontinhos do nível
    for (int i = 0; i < nivel; i++)
        printf("..");

    // imprime a palavra
    printf("%s\n", raiz->espanhol);

    // percorre a esquerda e direita
    paragrafacao(raiz->esq, nivel + 1);
    paragrafacao(raiz->dir, nivel + 1);
}


//exibição ASCII da árvore AVL fica melhor para visualização
void exibirAscii(No *raiz, const char *prefixo, int ehEsq) {
    if (raiz == NULL) return;

    printf("%s", prefixo);

    printf("%s", ehEsq ? "├── " : "└── ");

    printf("%s\n", raiz->espanhol);

    char novoPrefixo[200];
    strcpy(novoPrefixo, prefixo);
    strcat(novoPrefixo, ehEsq ? "│   " : "    ");

    if (raiz->esq)
        exibirAscii(raiz->esq, novoPrefixo, 1);

    if (raiz->dir)
        exibirAscii(raiz->dir, novoPrefixo, 0);
}
