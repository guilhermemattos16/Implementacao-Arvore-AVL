/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#include "arvoreB.h"


void Inicializa (Apontador *Dicionario) 
{
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

void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, short *Diminuiu)
{
    Pagina *Aux;
    long DispAux, j;

    if (PosPai < ApPai->n) // Aux = Pagina a direita de ApPag
    {
        Aux = ApPai->p[PosPai+1];
        DispAux = (Aux->n - ORDEM+1)/2;
        ApPag->r[ApPag->n] = ApPai->r[PosPai];
        ApPag->p[ApPag->n+1] = Aux->p[0];
        ApPag->n++;

        if (DispAux > 0) //Existe folga: tranfere de Aux para ApPag
        {
            for (j = 1; j < DispAux; j++)
            {
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            }
            ApPai->r[PosPai] = Aux->r[DispAux-1];
            Aux->n-=DispAux;
            
            for ( j = 0; j < Aux->n; j++)
            {
                Aux->r[j] = Aux->r[j+DispAux];
            }

            for ( j = 0; j <= Aux->n; j++)
            {
                Aux->p[j] = Aux->p[j+DispAux];
            }

            *Diminuiu = FALSE;
        }
        else //Fusao: intercala Aux em ApPag e libera Aux
        {
            for ( j = 1; j <= ORDEM; j++)
            {
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            }
            
            free(Aux);

            for (j = PosPai+1; j < ApPai->n; j++)
            {
                ApPai->r[j-1] = ApPai->r[j];
                ApPai->p[j] = ApPai->p[j+1];
            }
            
            ApPai->n--;
            if (ApPai->n >= ORDEM)
            {
                *Diminuiu = FALSE;
            }   
        }
    }
    else // Aux = Pagina a esquerda de ApPag
    {
        Aux = ApPai->p[PosPai-1];
        DispAux = (Aux->n - ORDEM+1)/2;

        for (j = ApPag->n; j >= 1; j--)
        {
            ApPag->r[j] = ApPag->r[j-1];
            ApPag->r[0] = ApPai->r[PosPai-1];
        }
        
        for (j = ApPag->n; j >= 0; j--)
        {
            ApPag->p[j+1] = ApPag->p[j];
            ApPag->n++;
        }
        
        if (DispAux > 0) //Existe folga: tranfere de Aux para ApPag
        {
            for (j = 1; j < DispAux; j++)
            {
                InsereNaPagina(ApPag, Aux->r[Aux->n-j], Aux->p[Aux->n-j+1]);
            }
            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
            Aux->n-=DispAux;
            *Diminuiu = FALSE;
        }
        else //Fusao: intercala ApPag em Aux e libera ApPag
        {
            for ( j = 1; j <= ORDEM; j++)
            {
                InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
            }
            
            free(ApPag);
            ApPai->n--;

            if (ApPai->n >= ORDEM)
            {
                *Diminuiu = FALSE;
            }   
        }
    }
}

void Antecessor (Apontador Ap, int Ind, Apontador ApPai, short *Diminuiu)
{
    if (ApPai->p[ApPai->n] != NULL)
    {
        Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
        if (*Diminuiu)
        {
            Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
            return;
        }
        Ap->r[Ind-1] = ApPai->r[ApPai->n-1];
        ApPai->n--;
        *Diminuiu = (ApPai->n < ORDEM);
    }
}

void Ret(TipoChave Ch, Apontador *Ap, short *Diminuiu)
{
    long j, Ind = 1;
    Apontador Pag;
    if (*Ap == NULL)
    {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }
    Pag = *Ap;
    while ((Ind < Pag->n) && (Ch > Pag->r[Ind-1].Chave))
    {
        Ind++;
    }
    
    if (Ch == Pag->r[Ind-1].Chave)
    {
        if (Pag->p[Ind-1] == NULL) // Pagina folha
        {
            Pag->n--;
            *Diminuiu = (Pag->n < ORDEM);
            for (j = Ind; j <= Pag->n; j++)
            {
                Pag->r[j-1] = Pag->r[j];
                Pag->p[j] = Pag->p[j+1];
            }
            return;
        }
        /* Pagina nao e folha: trocar com antecessor */
        Antecessor(*Ap, Ind, Pag->p[Ind-1], Diminuiu);
        if (*Diminuiu)
        {
            Reconstitui(Pag->p[Ind-1], *Ap, Ind-1, Diminuiu);
        }
        return;
    }
    
    if (Ch > Pag->r[Ind-1].Chave)
    {
        Ind++;
    }
    
    Ret(Ch, &Pag->p[Ind-1], Diminuiu);
    
    if (*Diminuiu)
    {
        Reconstitui(Pag->p[Ind-1], *Ap, Ind-1, Diminuiu);
    }
}

void Retira(TipoChave Ch, Apontador *Ap)
{
    short Diminuiu;
    Apontador Aux;
    Ret(Ch, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->n == 0) // Arvore diminui na altura
    {
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
}








// int cont = -1, count = 0;

// typedef struct artigo {
//     int id;
//     int ano;
//     char autor[200];
//     char titulo[200];
//     char revista[200];
//     char DOI[20];
//     char palavraChave[200];
// } Artigo;

// typedef struct Pagina_str *Apontador;
// typedef struct Pagina_str
// {
//   int n;
//   int pageNum;
//   int num;
//   Artigo r[2*ORDEM];
//   Apontador p[2*ORDEM+1];
// } Pagina;

// typedef struct node{
//     Artigo info;
//     struct Node *prox;
// } Node;

// typedef struct pagina
// {
//     //armazena numero de chaves na pagina
//     short int totalChaves;

//     //vetor de chaves
//     int chaves[ORDEM-1];

//     //Ponteiros das paginas filhas, -1 aponta para NULL
//     struct pagina filha[ORDEM];
// } Pagina;








// void buscaB (Pagina* pt, // Página a ser analisada 
//             int x,      // Chave procurada
//             int f,      // 
//             int g) {
//     Pagina *p;
//     int m;
    
//     p = pt; 
//     pt = pt; 
//     f = 0;
//     while (p != NULL)
//     {
//         int i = g = 1; 
//         pt = p; 
//         m = p -> m;
    
//         while (i <= m) {
//             if(x > p -> s[i]) { 
//                 i = g = i + 1;
//             }
//             else
//             {
//                 if(x = p -> s [i]) {
//                     p = NULL; 
//                     f = 1 ;
//                 }
//                 else { 
//                     p = p -> pont[i-1] ;
//                 }
//                 i = m + 2 ;
//             }
//         }
//         if (i= m + 1)
//         {
//             p = p -> pont[m];
//         }
//     }
// }


// void Busca(k, ponteiroRaiz)
// {
//     if (ponteiroRaiz == -1)
//     {
//         return printf("Chave nao encontrada");
//     }
    
//     else
//     {
//         //carrega em memoria primaria pagina apontado por ponteiroRaiz
//         //procura k na pagina carregada
        
//         // if () //k foi encontrada
//         {
//             return printf("chave encontrada");
//         }
//         //else
//         //{
//             //ponteiro = ponteiro para a próxima página da possível ocorrência de k
//             // return (Busca (k, ponteiro));
//         //}
//     }
// }

// void emOrdem (tpaginaB raiz) {
//     if(raiz==NULL)
//         return;
 
//     for(int i=0; i < raiz.n, i++) {
//         emOrdem(raiz -> pont[i]);
//         printf("%i",raiz -> chv[i]);
//     }
//     emOrdem(raiz -> pont[raiz.n]);
// }

