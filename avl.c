#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

No* criarVazia(){
    return NULL;
}

int altura(No *raiz){
    if(raiz==NULL)
        return 0;
    return raiz->altura;
}

int fatorBalanceamento(No *raiz){
    return altura(raiz->esq) - altura(raiz->dir);
}

No* rotacaoDireita(No *raiz){
    No *n = raiz->esq;
    No *aux = n->dir;

    n->dir = raiz;
    raiz->esq = aux;

    if(altura(raiz->esq) > altura(raiz->dir))
        raiz->altura = 1 + altura(raiz->esq);
    else
        raiz->altura = 1 + altura(raiz->dir);

    if(altura(n->esq) > altura(n->dir))
        n->altura = 1 + altura(n->esq);
    else
        n->altura = 1 + altura(n->dir);

    return n;
}

No* rotacaoEsquerda(No *raiz){
    No *n = raiz->dir;
    No *aux = n->esq;

    n->esq = raiz;
    raiz->dir = aux;

    if(altura(raiz->esq) > altura(raiz->dir))
        raiz->altura = 1 + altura(raiz->esq);
    else
        raiz->altura = 1 + altura(raiz->dir);

    if(altura(n->esq) > altura(n->dir))
        n->altura = 1 + altura(n->esq);
    else
        n->altura = 1 + altura(n->dir);

    return n;
}

No* balancear(No *raiz){
    int bal = fatorBalanceamento(raiz);

    if(bal > 1){
        if(fatorBalanceamento(raiz->esq) < 0){
            raiz->esq = rotacaoEsquerda(raiz->esq);
        }
        return rotacaoDireita(raiz);
    }

    if(bal < -1){
        if(fatorBalanceamento(raiz->dir) > 0){
            raiz->dir = rotacaoDireita(raiz->dir);
        }
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

No* inserirAvl(No *raiz, char *espanhol, char *portugues, char *conjugacoes, char *significado){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        strcpy(novo->espanhol, espanhol);
        strcpy(novo->portugues, portugues);
        strcpy(novo->conjugacoes, conjugacoes);
        strcpy(novo->significado, significado);
        novo->dir = NULL;
        novo->esq = NULL;
        novo->altura = 1;
        return novo;
    }

    if(strcmp(espanhol, raiz->espanhol) < 0){
        raiz->esq = inserirAvl(raiz->esq, espanhol, portugues, conjugacoes, significado);
    } else if(strcmp(espanhol, raiz->espanhol) > 0){
        raiz->dir = inserirAvl(raiz->dir, espanhol, portugues, conjugacoes, significado);
    } else {
        return raiz;
    }

    if(altura(raiz->esq) > altura(raiz->dir))
        raiz->altura = 1 + altura(raiz->esq);
    else
        raiz->altura = 1 + altura(raiz->dir);

    return balancear(raiz);
}

No* removerAvl(No *raiz, char *espanhol){
    if(raiz == NULL)
        return raiz;

    if(strcmp(espanhol, raiz->espanhol) < 0){
        raiz->esq = removerAvl(raiz->esq, espanhol);
    }
    else if(strcmp(espanhol, raiz->espanhol) > 0){
        raiz->dir = removerAvl(raiz->dir, espanhol);
    }
    else {
        if(raiz->esq == NULL || raiz->dir == NULL){
            No *temp;

            if (raiz->esq != NULL)
                temp = raiz->esq;
            else
                temp = raiz->dir;

            free(raiz);
            return temp;
        }
        else {
            No *temp = raiz->dir;
            while(temp->esq != NULL){
                temp = temp->esq;
            }

            strcpy(raiz->espanhol, temp->espanhol);
            strcpy(raiz->portugues, temp->portugues);
            strcpy(raiz->conjugacoes, temp->conjugacoes);
            strcpy(raiz->significado, temp->significado);

            raiz->dir = removerAvl(raiz->dir, temp->espanhol);
        }
    }

    if (raiz == NULL)
        return raiz;

    if(altura(raiz->esq) > altura(raiz->dir))
        raiz->altura = 1 + altura(raiz->esq);
    else
        raiz->altura = 1 + altura(raiz->dir);

    return balancear(raiz);
}

//fun��es de busca tem que ter duas
//uma pesquisa em espanhol e mostra a tradu��o em portugues
// a outra o inverso;
No* buscarEspanhol(No *raiz, char *espanhol);
No* buscarPortugues(No *raiz, char *portugues);

void listarAvl(No *raiz){
    if(raiz == NULL){
        return;
    }

    listarAvl(raiz->esq);
    printf("Espanhol: %s\tPortugues: %s\tConjucoes: %s\tSgnificado: %s\n", raiz->espanhol, raiz->portugues, raiz->conjugacoes, raiz->significado);
    listarAvl(raiz->dir);
}

void salvarAvl(FILE *file, No *raiz){
    if(raiz != NULL){
        fprintf(file, "%s|%s|%s|%s\n", raiz->espanhol, raiz->portugues, raiz->conjugacoes, raiz->significado);
        salvarAvl(file, raiz->esq);
        salvarAvl(file, raiz->dir);
    }
}

void carregarAvl(FILE *file, No **raiz){
    char linha[300];
    char esp[50], por[50], conj[100], sig[100];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *token = strtok(linha, "|");
        if (token == NULL) continue;
        strcpy(esp, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(por, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(conj, token);

        token = strtok(NULL, "\n");
        if (token == NULL) continue;
        strcpy(sig, token);

        *raiz = inserirAvl(*raiz, esp, por, conj, sig);
    }
}


void destruirAvl(No *raiz){
    if(raiz != NULL){
        destruirAvl(raiz->esq);
        destruirAvl(raiz->dir);
        free(raiz);
    }
}
