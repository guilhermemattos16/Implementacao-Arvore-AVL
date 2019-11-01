
#ifndef _REDBLACK_TREE
#define _REDBLACK_TREE
 
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

#define TAM 10

struct node{
	void *chave;
	int cor;
	struct node *pai;
	struct node *esq;
	struct node *dir;
};

/* Global, todas as funções terão acesso a eles */
struct node *ROOT;
struct node *NILL;

void rotacaoEsquerda(struct node *x);
void rotacaoDireita(struct node *x);
void imprimir(struct node *x);
void insercao(void *chave, int(*comp)(void*, void*));
void insercao_fixup(struct node *z);
struct node *busca(void *chave, int(*comp)(void*, void*));
struct node *sucessor(struct node *x);
void troca(struct node *u, struct node *v);
void remocao(struct node *z);
void remocao_fixup(struct node *x);
int compara (void* x, void* y);

#endif