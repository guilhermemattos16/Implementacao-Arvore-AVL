/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#ifndef _ARVORE_B
#define _ARVORE_B


#include <stdlib.h>
#include <stdio.h>
#define ORDEM 2 //árvore de ordem 2
#define FALSE 0
#define TRUE 1

typedef struct Artigo
{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
} Artigo;

typedef struct Pagina *Apontador;

typedef struct Pagina
{
    char n;
    Artigo r[2 * ORDEM];          //VETOR DE CHAVES
    Apontador p[(2 * ORDEM) + 1]; //VETOR DE PONTEIROS
} Pagina;

void Inicializa(Apontador *Pag);
void InsereNaPagina(Apontador Ap, Artigo Art, Apontador ApDir);
void Ins(Artigo Art, Apontador Ap, short *Cresceu, Artigo *ArtRetorno, Apontador *ApRetorno);
void Insere(Artigo Art, Apontador *Ap);
void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, short *Diminuiu);
void Antecessor(Apontador Ap, int Ind, Apontador ApPai, short *Diminuiu);
void Ret(int id, Apontador *Ap, short *Diminuiu);
void Retira(int id, Apontador *Ap);
void ImprimeI(Apontador p, int nivel);
void Imprime(Apontador p);
int Pesquisa(int id, Apontador Ap);

#endif