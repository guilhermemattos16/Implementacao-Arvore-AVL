/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define ORDEM 2 //árvore de ordem 2
#define FALSE 0
#define TRUE 1

typedef long TipoChave;
typedef struct Registro
{
    TipoChave Chave;
    // Outros Componentes
} Registro;


typedef struct Pagina* Apontador;
typedef struct Pagina
{
    char n;
    Registro r[2 * ORDEM];
    Apontador p[(2 * ORDEM) + 1];
} Pagina;

void Inicializa (Apontador *Dicionario) {
    *Dicionario = NULL;
}

void Pesquisa(Registro *x, Apontador Ap)
{
    int i = 1;
    if (Ap == NULL)
    {
        printf("Registro nao esta presente na arvore!\n");
        return ;
    }
    
    while ((i < Ap -> n) && (x -> Chave > Ap -> r[i-1].Chave))
    {
        i++;
    }

    if (x->Chave == Ap->r[i-1].Chave)
    {
        *x = Ap -> r[i-1];
        return;
    }
    
    if (x->Chave < Ap->r[i-1].Chave)
    {
        Pesquisa(x, Ap->p[i-1]);
    }

    else
    {
        Pesquisa(x, Ap -> p[i]);
    }
}

void Ins (Registro Reg, Apontador Ap, short *Cresceu, 
          Registro *RegRetorno, Apontador *ApRetorno) 
{
    int i = 1;
    int j;
    Apontador ApTemp;

    if (Ap == NULL)
    {
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while ((i < Ap -> n) && (Reg.Chave > Ap->r[i-1].Chave))
    {
        i++;
    }

    if (Reg.Chave == Ap -> r[i-1].Chave)
    {
        printf("Erro: Registro ja esta presente!\n");
        return;
    }
    
    if (Reg.Chave < Ap -> r[i-1].Chave)
    {
        Ins(Reg, Ap->p[i--], Cresceu, RegRetorno, ApRetorno);
    }
    
    if (!*Cresceu)
    {
        return;
    }
    
    if (Ap -> n < (2*ORDEM)) /* Pagina tem espaco */
    {
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = FALSE;
        return;
    }

    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (Apontador)malloc(sizeof(Pagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < (ORDEM+1))
    {
        InsereNaPagina(ApTemp, Ap->r[(2*ORDEM)-1], Ap->p[2*ORDEM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    else
    {
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    }
    for (j = ORDEM+2; j <= (2*ORDEM); j++)
    {
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    }
    Ap->n = ORDEM;
    ApTemp->p[0] = Ap->p[ORDEM+1];
    *RegRetorno = Ap->r[ORDEM];
    *ApRetorno = ApTemp;
}

void Insere(Registro Reg, Apontador *Ap)
{
    short Cresceu;
    Registro RegRetorno;
    Pagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    if (Cresceu) // Arvore Cresce na altura pela raiz
    {
        ApTemp = (Pagina *)malloc(sizeof(Pagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir)
{
    short NaoAchouPosicao;
    int k = Ap->n;
    NaoAchouPosicao = (k>0);
    while (NaoAchouPosicao)
    {
        if(Reg.Chave >= Ap->r[k-1].Chave)
        {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if (k<1)
        {
            NaoAchouPosicao = FALSE;
        }
    }
    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}