#include "QuicksortExterno.h"

void FAVazia(TipoArea *area){ 
    int i;
    area->numCelOcupadas = 0;
    area->primeiro = -1;
    area->ultimo = -1;
    area->celulasDisp = 0;
    for (i = 0; i < TAMAREA; i++) {
        area->itens[i].ant = -1;
        area->itens[i].prox = i + 1;
    }
}

int ObterNumCelOcupadas(TipoArea *area){
    return (area->numCelOcupadas);
}

void InsereItem(void* info, TipoArea *area, int (*compara)(void*, void*)){ 
    int pos, disp, indiceInsercao;
    if (area->numCelOcupadas == TAMAREA){
        printf("Tentativa de insercao em lista cheia.\n");
        return;
    }
    disp = area->celulasDisp;
    area->celulasDisp = area->itens[area->celulasDisp].prox;
    area->itens[disp].info = info;
    area->numCelOcupadas++;
    if (area->numCelOcupadas == 1){ /* Insercao do primeiro info */
        area->primeiro = disp;
        area->ultimo = area->primeiro;
        area->itens[area->primeiro].prox = -1;
        area->itens[area->primeiro].ant = -1;
        return;
    }
    pos = area->primeiro;
    if (compara(info, area->itens[pos].info) < 0){ /* Insercao realizada na primeira posicao */
        area->itens[disp].ant = -1;
        area->itens[disp].prox = pos;
        area->itens[pos].ant = disp;
        area->primeiro = disp;
        return;
    }
    indiceInsercao = area->itens[pos].prox;
    while (indiceInsercao != -1 && compara(area->itens[indiceInsercao].info, info) < 0){
        pos = indiceInsercao;
        indiceInsercao = area->itens[pos].prox;
    }
    if (indiceInsercao == -1){ /*Insercao realizada na ultima posicao*/
        area->itens[disp].ant = pos;
        area->itens[disp].prox = -1;
        area->itens[pos].prox = disp;
        area->ultimo = disp;
        return;
    }
    area->itens[disp].ant = pos;
    area->itens[disp].prox = area->itens[pos].prox;
    area->itens[pos].prox = disp;
    pos = area->itens[disp].prox;
    area->itens[pos].ant = disp;
    /* Insercao realizada no meio de Area */
}

void RetiraPrimeiro(TipoArea *area, void* *info){ 
    int proxTmp;
    if (area->numCelOcupadas == 0){ /* Area vazia */
        printf("Erro - Lista vazia\n");
        return;
    }
    *info = area->itens[area->primeiro].info;
    proxTmp = area->itens[area->primeiro].prox;
    area->itens[area->primeiro].prox = area->celulasDisp;
    area->celulasDisp = area->primeiro;
    area->primeiro = proxTmp;
    if ((unsigned int)area->primeiro < TAMAREA)
    area->itens[area->primeiro].ant = -1;
    area->numCelOcupadas--;
}

void RetiraUltimo(TipoArea *area, void* *info){ 
    int antTmp;
    if (area->numCelOcupadas == 0){ /* area vazia */
        printf("Erro - Lista vazia\n");
        return;
    }
    *info = area->itens[area->ultimo].info;
    antTmp = area->itens[area->ultimo].ant;
    area->itens[area->ultimo].prox = area->celulasDisp;
    area->celulasDisp = area->ultimo;
    area->ultimo = antTmp;
    if ((unsigned int)area->ultimo < TAMAREA)
    area->itens[area->ultimo].prox = -1;
    area->numCelOcupadas--;
}

/*Procedimentos utilizados pelo Particao do quicksort externo*/
void LeSup(FILE **ArqLEs, void* *UltLido, int *Ls, short *OndeLer){ 
    fseek(*ArqLEs, (*Ls - 1) * tamanhoDado,SEEK_SET );
    fread(UltLido, tamanhoDado, 1, *ArqLEs);
    (*Ls)--;  
    *OndeLer = FALSE;
}

void LeInf(FILE **ArqLi,  void* *UltLido, int *Li, short *OndeLer){ 
    fread(UltLido, tamanhoDado, 1, *ArqLi);
    (*Li)++; 
    *OndeLer = TRUE;
}

void InserirArea(TipoArea *area, void* *UltLido, int *NRArea, int (*compara)(void*, void*)){ /*Insere UltLido de forma ordenada na Area*/
  InsereItem(*UltLido, area, compara);  
  *NRArea = ObterNumCelOcupadas(area);
}

void EscreveMax(FILE **ArqLEs, void* R, int *Es){
    fseek(*ArqLEs, (*Es - 1) * tamanhoDado,SEEK_SET );
    fwrite(&R, tamanhoDado, 1, *ArqLEs);  
    (*Es)--;
}

void EscreveMin(FILE **ArqEi,  void* R, int *Ei){
    fwrite(&R, tamanhoDado, 1, *ArqEi);  
    (*Ei)++; 
}

void RetiraMax(TipoArea *area,  void* *R, int *NRArea){ 
    RetiraUltimo(area, R);  
    *NRArea = ObterNumCelOcupadas(area); 
}

void RetiraMin(TipoArea *area, void* *R, int *NRArea){ 
    RetiraPrimeiro(area, R);  
    *NRArea = ObterNumCelOcupadas(area); 
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea area, int Esq, int Dir, int *i, int *j, int (*compara)(void*, void*)){ 
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    short OndeLer = TRUE;  
    void* UltLido;
    void* Linf = (void*)INT_MIN;
    void* Lsup = (void*)INT_MAX;
    void* R2;
    fseek (*ArqLi, (Li - 1)* tamanhoDado, SEEK_SET );
    fseek (*ArqEi, (Ei - 1)* tamanhoDado, SEEK_SET );
    *i = Esq - 1;  
    *j = Dir + 1;
    while (Ls >= Li){ 
        if (NRArea < TAMAREA - 1){ 
            if (OndeLer) 
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else 
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&area, &UltLido, &NRArea, compara);
            continue;
        }
        if (Ls == Es) 
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei) 
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer) 
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else 
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        if (compara(UltLido, Lsup) > 0){ 
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if (compara(UltLido, Linf) < 0){ 
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        InserirArea(&area, &UltLido, &NRArea, compara);
        if (Ei - Esq < Dir - Es){ 
            RetiraMin(&area, &R2, &NRArea);
            EscreveMin(ArqEi, R2, &Ei);
            Linf = R2;
        } 
        else{ 
            RetiraMax(&area, &R2, &NRArea);
            EscreveMax(ArqLEs, R2, &Es);
            Lsup = R2;
        }
    }
    while (Ei <= Es){ 
        RetiraMin(&area, &R2, &NRArea);
        EscreveMin(ArqEi, R2, &Ei);
    }
}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, int (*compara)(void*, void*), int tamanhoDados){
    int i, j;
    TipoArea area;   /* Area de armazenamento interna*/
    tamanhoDado = tamanhoDados;
    if (Dir - Esq < 1){
        return;
    } 
    FAVazia(&area);
    Particao(ArqLi, ArqEi, ArqLEs, area, Esq, Dir, &i, &j, compara);
    if (i - Esq < Dir - j){ /* ordene primeiro o subarquivo menor */
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, compara, tamanhoDados);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, compara, tamanhoDados);
    }
    else{
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, compara, tamanhoDados);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, compara, tamanhoDados);
    }
}