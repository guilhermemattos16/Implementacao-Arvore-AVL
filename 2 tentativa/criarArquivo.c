#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#define TAMAREA 100
#define TRUE 1
#define FALSE 0

typedef int TipoApontador;
typedef int TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  /* Outros Componentes */
} TipoItem;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox, Ant;
} TipoCelula;
typedef struct TipoArea {
  TipoCelula Itens[TAMAREA];
  TipoApontador CelulasDisp, Primeiro, Ultimo;
  int NumCelOcupadas;
} TipoArea;
typedef TipoItem TipoRegistro;


FILE *ArqLi;
TipoItem R;

int main (){
    ArqLi = fopen ("teste.dat", "wb");
    if(ArqLi == NULL) {printf("Arquivo nao pode ser aberto\n "); exit(1);}
    R.Chave = 5;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 3;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 10; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 6;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 1;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 7;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 100;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 666;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 2;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 40;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 30;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 90;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 80;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 70;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 60;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 50;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 20;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 22;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 24;  fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    fclose(ArqLi);
}