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

int tamanhoDado;

void FAVazia(TipoArea *area);
//Argumento: Area de armazenamento da memoria interna
//Objetivo: Iniciar a variaveis da area, com a area vazia
int ObterNumCelOcupadas(TipoArea *area);
//Argumento: Area de armazenamento da memoria interna
//Objetivo: Retornar o numero de celulas ocupadas na Area
void InsereItem(void* info, TipoArea *area, int (*compara)(void*, void*));
//Argumentos: Informacao a ser inserida na area, A aream e a funcao de comparacao de dados genericos
//Objetivo: inserir a informacao na area, de forma ordenada
void RetiraPrimeiro(TipoArea *area, void* *info);
//Argumentos: Area e ponteiro para informacao a ser retirada da area
//Objetivo: Retirar a primeira celula de informacao da area de armazenamento da memoria interna
void RetiraUltimo(TipoArea *area, void* *info);
//Argumentos: Area e ponteiro para informacao a ser retirada da area
//Objetivo: Retirar a ultima celula de informacao da area de armazenamento da memoria interna
void LeSup(FILE **ArqLEs, void* *UltLido, int *Ls, short *OndeLer);
//Argumentos: Arquivo de leitura e escrita superior, ultima informacao lida e a posicao de leitura superior
//Objetivo: Ler e atribuir a UltLido, o resgistro na posicao apontado por Ls 
void LeInf(FILE **ArqLi,  void* *UltLido, int *Li, short *OndeLer);
//Argumentos: Arquivo de leitura e escrita superior, ultima informacao lida e a posicao de leitura inferior
//Objetivo: Ler e atribuir a UltLido, o resgistro na posicao apontado por Li 
void InserirArea(TipoArea *area, void* *UltLido, int *NRArea, int (*compara)(void*, void*));

void EscreveMax(FILE **ArqLEs, void* R, int *Es);
//Argumentos: Arquivo de leitura e escrita superior, registro a ser escrito, posicao de escritra superior do registro
//Objetivo: Escrever o Registro R no arquivo ArqLES, na posicao apontado por Es
void EscreveMin(FILE **ArqEi,  void* R, int *Ei);
//Argumentos: Arquivo de escrita inferior, registro a ser escrito, posicao de escritra inferior do registro
//Objetivo: Escrever o Registro R no arquivo ArqEi, na posicao apontado por Ei
void RetiraMax(TipoArea *area,  void* *R, int *NRArea);
//Argumentos: Area de armazenamento de memoria interna, registro a ser retirado e numero de registros  na area de armazenamento
//Objetivo: Remover o maior elemento da area de armazenamento interna e decrementar NRArea
void RetiraMin(TipoArea *area, void* *R, int *NRArea);
//Argumentos: Area de armazenamento de memoria interna, registro a ser retirado e numero de registros  na area de armazenamento
//Objetivo: Remover o menor elemento da area de armazenamento interna e decrementar NRArea
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea area, int Esq, int Dir, int *i, int *j, int (*compara)(void*, void*));
//Argumentos: Arquivo de leitura inferior, Arquivo de Escrita inferior, Arquivo de leitura e escrita superior,
//            Area de armazenamento de memoria interna, posicao do primeiro elemento, posicao do ultimo elemento,
//            ponteiro que aponta para o ultimo elemento da parte dos menores,
//            ponteiro que aponta para o primeiro elemento da parte dos maiores, e a funcao de comparacao de dados genericos 
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, int (*compara)(void*, void*), int tamanhoDados);
//Argumentos: Arquivo de leitura inferior, Arquivo de Escrita inferior, Arquivo de leitura e escrita superior,
//            Area de armazenamento de memoria interna, posicao do primeiro elemento, posicao do ultimo elemento,
//            e a funcao de comparacao de dados genericos 
#endif