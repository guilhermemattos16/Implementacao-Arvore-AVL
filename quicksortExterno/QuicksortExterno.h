#ifndef QUICKSORT_EXTERNO
#define QUICKSORT_EXTERNO

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMAREA 100
#define TRUE 1
#define FALSE 0

typedef struct TipoCelula {
    void* info;
    int prox, ant;
} TipoCelula;

typedef struct TipoArea {
    TipoCelula itens[TAMAREA];
    int celulasDisp, primeiro, ultimo;
    int numCelOcupadas;
} TipoArea;

FILE *ArqLEs;   /* Gerencia o Ls e o Es */
FILE *ArqLi;    /* Gerencia o Li */
FILE *ArqEi;    /* Gerencia o Ei */
int tamanhoDado;

void FAVazia(TipoArea *area);
int ObterNumCelOcupadas(TipoArea *area);
void InsereItem(void* info, TipoArea *area, int (*compa)(void*, void*));
void RetiraPrimeiro(TipoArea *area, void* *info);
void RetiraUltimo(TipoArea *area, void* *info);
void LeSup(FILE **ArqLEs, void* *UltLido, int *Ls, short *OndeLer);
void LeInf(FILE **ArqLi,  void* *UltLido, int *Li, short *OndeLer);
void InserirArea(TipoArea *area, void* *UltLido, int *NRArea, int (*compa)(void*, void*));
void EscreveMax(FILE **ArqLEs, void* R, int *Es);
void EscreveMin(FILE **ArqEi,  void* R, int *Ei);
void RetiraMax(TipoArea *area,  void* *R, int *NRArea);
void RetiraMin(TipoArea *area, void* *R, int *NRArea);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea area, int Esq, int Dir, int *i, int *j, int (*compa)(void*, void*));
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, int (*compa)(void*, void*), int tamanhoDados);

#endif