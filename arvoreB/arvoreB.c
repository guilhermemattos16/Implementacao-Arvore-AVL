/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#include "arvoreB.h"

void Inicializa(Apontador *Pag)
{
    *Pag = NULL;
}

void InsereNaPagina(Apontador Ap, Artigo Art, Apontador ApDir)
{
    short NaoAchouPosicao;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (Art.id >= Ap->r[k - 1].id)
        {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = FALSE;
    }
    Ap->r[k] = Art;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(Artigo Art, Apontador Ap, short *Cresceu, Artigo *ArtRetorno, Apontador *ApRetorno)
{
    long i = 1;
    long j;
    Apontador ApTemp;
    if (Ap == NULL)
    {
        *Cresceu = TRUE;
        (*ArtRetorno) = Art;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->n && Art.id > Ap->r[i - 1].id)
        i++;
    if (Art.id == Ap->r[i - 1].id)
    {
        printf(" Erro: Artigo ja existe\n");
        *Cresceu = FALSE;
        return;
    }
    if (Art.id < Ap->r[i - 1].id)
        i--;
    Ins(Art, Ap->p[i], Cresceu, ArtRetorno, ApRetorno);
    if (!*Cresceu)
        return;
    if (Ap->n < ORDEM * 2)
    { /* Pagina tem espaco */
        InsereNaPagina(Ap, *ArtRetorno, *ApRetorno);
        *Cresceu = FALSE;
        return;
    }
    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (Apontador)malloc(sizeof(Pagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i < ORDEM + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[ORDEM * 2 - 1], Ap->p[ORDEM * 2]);
        Ap->n--;
        InsereNaPagina(Ap, *ArtRetorno, *ApRetorno);
    }
    else
        InsereNaPagina(ApTemp, *ArtRetorno, *ApRetorno);
    for (j = ORDEM + 2; j <= ORDEM * 2; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
    Ap->n = ORDEM;
    ApTemp->p[0] = Ap->p[ORDEM + 1];
    *ArtRetorno = Ap->r[ORDEM];
    *ApRetorno = ApTemp;
}

void Insere(Artigo Art, Apontador *Ap)
{
    short Cresceu;
    Artigo ArtRetorno;
    Pagina *ApRetorno, *ApTemp;
    Ins(Art, *Ap, &Cresceu, &ArtRetorno, &ApRetorno);
    if (Cresceu)
    { /* Arvore cresce na altura pela raiz */
        ApTemp = (Pagina *)malloc(sizeof(Pagina));
        ApTemp->n = 1;
        ApTemp->r[0] = ArtRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, short *Diminuiu)
{
    Pagina *Aux;
    long DispAux, j;
    if (PosPai < ApPai->n)
    { /* Aux = Pagina a direita de ApPag */
        Aux = ApPai->p[PosPai + 1];
        DispAux = (Aux->n - ORDEM + 1) / 2;
        ApPag->r[ApPag->n] = ApPai->r[PosPai];
        ApPag->p[ApPag->n + 1] = Aux->p[0];
        ApPag->n++;
        if (DispAux > 0)
        { /* Existe folga: transfere de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
            ApPai->r[PosPai] = Aux->r[DispAux - 1];
            Aux->n -= DispAux;
            for (j = 0; j < Aux->n; j++)
                Aux->r[j] = Aux->r[j + DispAux];
            for (j = 0; j <= Aux->n; j++)
                Aux->p[j] = Aux->p[j + DispAux];
            *Diminuiu = FALSE;
        }
        else
        { /* Fusao: intercala Aux em ApPag e libera Aux */
            for (j = 1; j <= ORDEM; j++)
                InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
            free(Aux);
            for (j = PosPai + 1; j < ApPai->n; j++)
            {
                ApPai->r[j - 1] = ApPai->r[j];
                ApPai->p[j] = ApPai->p[j + 1];
            }
            ApPai->n--;
            if (ApPai->n >= ORDEM)
                *Diminuiu = FALSE;
        }
    }
    else
    { /* Aux = Pagina a esquerda de ApPag */
        Aux = ApPai->p[PosPai - 1];
        DispAux = (Aux->n - ORDEM + 1) / 2;
        for (j = ApPag->n; j >= 1; j--)
            ApPag->r[j] = ApPag->r[j - 1];
        ApPag->r[0] = ApPai->r[PosPai - 1];
        for (j = ApPag->n; j >= 0; j--)
            ApPag->p[j + 1] = ApPag->p[j];
        ApPag->n++;
        if (DispAux > 0)
        { /* Existe folga: transf. de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[Aux->n - j],
                               Aux->p[Aux->n - j + 1]);
            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai - 1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = FALSE;
        }
        else
        { /* Fusao: intercala ApPag em Aux e libera ApPag */
            for (j = 1; j <= ORDEM; j++)
                InsereNaPagina(Aux, ApPag->r[j - 1], ApPag->p[j]);
            free(ApPag);
            ApPai->n--;
            if (ApPai->n >= ORDEM)
                *Diminuiu = FALSE;
        }
    }
}

void Antecessor(Apontador Ap, int Ind, Apontador ApPai, short *Diminuiu)
{
    if (ApPai->p[ApPai->n] != NULL)
    {
        Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
        if (*Diminuiu)
            Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
        return;
    }
    Ap->r[Ind - 1] = ApPai->r[ApPai->n - 1];
    ApPai->n--;
    *Diminuiu = (ApPai->n < ORDEM);
}

void Ret(int id, Apontador *Ap, short *Diminuiu)
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
    while (Ind < Pag->n && id > Pag->r[Ind - 1].id)
        Ind++;
    if (id == Pag->r[Ind - 1].id)
    {
        if (Pag->p[Ind - 1] == NULL)
        { /* Pagina folha */
            Pag->n--;
            *Diminuiu = (Pag->n < ORDEM);
            for (j = Ind; j <= Pag->n; j++)
            {
                Pag->r[j - 1] = Pag->r[j];
                Pag->p[j] = Pag->p[j + 1];
            }
            return;
        }
        /* Pagina nao e folha: trocar com antecessor */
        Antecessor(*Ap, Ind, Pag->p[Ind - 1], Diminuiu);
        if (*Diminuiu)
            Reconstitui(Pag->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
        return;
    }
    if (id > Pag->r[Ind - 1].id)
        Ind++;
    Ret(id, &Pag->p[Ind - 1], Diminuiu);
    if (*Diminuiu)
        Reconstitui(Pag->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
}

void Retira(int id, Apontador *Ap)
{
    short Diminuiu;
    Apontador Aux;
    Ret(id, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->n == 0)
    { /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
}

void ImprimeI(Apontador p, int nivel)
{
    long i;
    if (p == NULL)
        return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++)
        printf("ID: %ld ", (long)p->r[i].id);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

void Imprime(Apontador p)
{
    int n = 0;
    ImprimeI(p, n);
}

int Pesquisa(int id, Apontador Ap)
{
    long i = 1;
    Artigo aux;
    if (Ap == NULL)
    {
        printf("TipoRegistro nao esta presente na arvore\n");
        return FALSE;
    }
    while (i < Ap->n && id > Ap->r[i - 1].id)
        i++;
    if (id == Ap->r[i - 1].id)
    {
        aux = Ap->r[i - 1];
        printf("Id: %d\nAno: %d\nAutor: %sTitulo: %s", aux.id, aux.ano, aux.autor, aux.titulo);
        printf("Revista: %sDOI: %sPalavra Chave: %s", aux.revista, aux.DOI, aux.palavraChave);
        return TRUE;
    }
    if (id < Ap->r[i - 1].id)
        Pesquisa(id, Ap->p[i - 1]);
    else
        Pesquisa(id, Ap->p[i]);
    return FALSE;
}