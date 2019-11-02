#include "QuicksortExterno.h"

int comp(void* a, void* b){
    int *p = (int*)a;
    int *p2 = (int*)b;
    return p - p2;
}
int main(int argc, char *argv[]){ 
    FILE *ArqLEs;   /* Gerencia o Ls e o Es */
    FILE *ArqLi;    /* Gerencia o Li */
    FILE *ArqEi;    /* Gerencia o Ei */
    ArqLi = fopen ("teste.dat", "wb");
    if(ArqLi == NULL) {printf("Arquivo nao pode ser aberto\n "); exit(1);}
    int R;
    R = 5;  fwrite(&R, sizeof(int), 1, ArqLi);
    R = 3;  fwrite(&R, sizeof(int), 1, ArqLi);
    R = 10; fwrite(&R, sizeof(int), 1, ArqLi);
    R = 6;  fwrite(&R, sizeof(int), 1, ArqLi);
    R = 1;  fwrite(&R, sizeof(int), 1, ArqLi);
    R = 7;  fwrite(&R, sizeof(int), 1, ArqLi);
    R = 4;  fwrite(&R, sizeof(int), 1, ArqLi);
    fclose(ArqLi);
    ArqLi = fopen ("teste.dat", "r+b");
    if (ArqLi == NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    } 
    ArqEi = fopen ("teste.dat", "r+b");
    if (ArqEi == NULL){
        printf("Arquivo nao pode ser aberto\n"); 
        exit(1);
    }
    ArqLEs = fopen ("teste.dat", "r+b");
    if (ArqLEs == NULL){ 
        printf ("Arquivo nao pode ser aberto\n");  
        exit(1);
    }
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, 7, comp, sizeof(int));
    fflush(ArqLi); 
    fclose(ArqEi); 
    fclose(ArqLEs);
    fseek(ArqLi,0, SEEK_SET);
    while(fread(&R, sizeof(int), 1, ArqLi)){ 
        printf("Registro=%d\n", R);
    }
    fclose(ArqLi);
    return 0;
}