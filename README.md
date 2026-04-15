#  Dicionário Espanhol–Português com Árvore AVL

##  Descrição

Este projeto consiste em um sistema de dicionário bilíngue (Espanhol ↔ Português) desenvolvido em linguagem C, utilizando **árvores AVL** como estrutura de dados principal.

O sistema permite armazenar, buscar, inserir e remover palavras de forma eficiente, mantendo a árvore sempre balanceada automaticamente através de rotações.

O projeto foi desenvolvido na disciplina de Estrutura de Dados I, no curso de Ciência da Computação.

---

##  Funcionalidades

-  Listar todas as palavras (ordenadas por espanhol)
-  Inserir novas palavras no dicionário
-  Remover palavras existentes
-  Buscar tradução:
  - Espanhol → Português
  - Português → Espanhol
-  Exibir árvore em formato hierárquico (paragrafação)
-  Exibir árvore em formato ASCII
-  Persistência de dados em arquivo (`dicionario.txt`)

---

##  Tecnologias Utilizadas

- Linguagem C
- Programação estruturada
- Manipulação de arquivos
- Alocação dinâmica de memória
- Strings (`string.h`)

---

##  Estruturas de Dados Utilizadas

- Árvore AVL (auto-balanceada)
- Nós com:
  - Palavra em espanhol
  - Palavra em português
  - Altura
  - Ponteiros para filhos

 O sistema utiliza **duas árvores AVL**:
- Uma ordenada por espanhol
- Outra ordenada por português

Isso permite buscas eficientes nos dois sentidos.

---

##  Funcionamento

Ao iniciar o programa:

- Os dados são carregados do arquivo `dicionario.txt`
- As palavras são inseridas nas duas árvores AVL

Durante a execução:

- Inserções e remoções mantêm a árvore balanceada automaticamente
- Buscas são realizadas em tempo eficiente (O(log n))

Ao encerrar:

- Os dados são salvos novamente no arquivo

---

##  Balanceamento da Árvore

O sistema implementa:

- Rotação à direita
- Rotação à esquerda
- Rotações duplas

Garantindo que a árvore permaneça balanceada após inserções e remoções.



---

##  Como Executar

### Compilar
gcc main.c avl.c -o dicionario


### Executar
./dicionario


---

##  Formato do Arquivo

O arquivo `dicionario.txt` deve conter:
palavraEspanhol palavraPortugues

### Exemplo:

hola ola
casa casa
perro cachorro



##  Autores

Erick Batista dos Santos  
Anna Júlia Oliveira de Sousa  

 Ciência da Computação - Bacharelado  
 Estrutura de Dados I - UNIR
