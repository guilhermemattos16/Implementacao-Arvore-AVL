/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#ifndef _ARVORE_B
#define _ARVORE_B


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define ORDEM 2 //árvore de ordem 2
#define FALSE 0
#define TRUE 1

typedef int TipoChave;
typedef struct Registro
{
    TipoChave Chave;
    // Outros Componentes
} Registro;


typedef struct Pagina* Apontador;
typedef struct Pagina
{
    char n;
    Registro r[2 * ORDEM]; //VETOR DE CHAVES
    Apontador p[(2 * ORDEM) + 1]; //VETOR DE PONTEIROS
} Pagina;

void Inicializa (Apontador *Dicionario);
void Pesquisa(Registro *x, Apontador Ap);
void Ins (Registro Reg, Apontador Ap, short *Cresceu, Registro *RegRetorno, Apontador *ApRetorno) ;
void Insere(Registro Reg, Apontador *Ap);
void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir);
void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, short *Diminuiu);
void Antecessor (Apontador Ap, int Ind, Apontador ApPai, short *Diminuiu);
void Ret(TipoChave Ch, Apontador *Ap, short *Diminuiu);
void Retira(TipoChave Ch, Apontador *Ap);

#endif