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

//estrutura do nó da AVL
typedef struct no {
    char espanhol[64];
    char portugues[64];
    int altura;
    struct no *esq;
    struct no *dir;
} No;

//cria uma arvore vazia
No* criarVazia();

//funcoes de balanceamento/altura da arvore
int altura(No *raiz);
int fatorBalanceamento(No *raiz);
No* rotacaoDireita(No *raiz);
No* rotacaoEsquerda(No *raiz);
No* balancear(No *raiz);

//operacoes basicas
int inserirAvl(No **raiz, const char *espanhol, const char *portugues);
No* removerAvl(No *raiz, const char *espanhol);

//buscas
No* buscarEspanhol(No *raiz, const char *espanhol);
No* buscarPortugues(No *raiz, const char *portugues);

//utilitários
void listarAvl(No *raiz);
void salvarAvl(FILE *file, No *raiz);
void carregarAvl(FILE *file, No **raiz);
void destruirAvl(No *raiz);

//funcoes de exibicao
void paragrafacao(No *raiz, int nivel);
void exibirAscii(No *raiz, const char *prefixo, int ehEsq);

static No* menorNo(No* raiz);

