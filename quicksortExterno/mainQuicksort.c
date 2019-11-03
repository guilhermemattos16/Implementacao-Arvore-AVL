#include "QuicksortExterno.h"

typedef struct {
    int matricula;
    char nome[3];
}Aluno;

FILE *ArqLEs;   /* Gerencia o Ls e o Es */
FILE *ArqLi;    /* Gerencia o Li */
FILE *ArqEi;    /* Gerencia o Ei */


int comparaNome(void* a, void* b){
    Aluno *aluno1 = (Aluno*)a;
    Aluno *aluno2 = (Aluno*)b;
    return strcoll(aluno1->nome, aluno2->nome);
}
int comparaMatricula(void* a, void* b){
    Aluno *aluno1 = (Aluno*)a;
    Aluno *aluno2 = (Aluno*)b;
    return (aluno1->matricula) - (aluno2->matricula);
}


Aluno teste[7] = {1234552, "Luc",
                  1234752, "Arl",
                  1234442, "Mar",
                  1234731, "Luc",
                  1234123, "Jo",
                  1234111, "Raf",
                  1234004, "Jul"};

int menu(){
    int opcao;
    printf("\n\n1-Ordenar por ordem alfabetica\n2-Ordenar por matricula\n3-Sair\n\n");
    scanf("%d", &opcao);
    return opcao;
}

int main(int argc, char *argv[]){
    int opcao;
    do{
        opcao = menu();
        setbuf(stdin,NULL);
        ArqLi = fopen ("teste.dat", "wb");
        if(ArqLi == NULL) {printf("Arquivo nao pode ser aberto\n "); exit(1);}
        fwrite(&teste, sizeof(Aluno), 7, ArqLi);
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
        if(opcao == 1)
            QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, 7, comparaNome, sizeof(Aluno));
        
        else if(opcao == 2)
            QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, 7, comparaMatricula, sizeof(Aluno));
        fflush(ArqLi);
        fclose(ArqEi);
        fclose(ArqLEs);
        fseek(ArqLi,0, SEEK_SET);
        Aluno exibir;
        while(fread(&exibir, sizeof(Aluno), 1, ArqLi)){
            printf("Nome: %s\nMatricula: %d\n\n", exibir.nome, exibir.matricula);
        }
        fclose(ArqLi);
    }while(opcao > 0 && opcao < 3);

     return 0;
}
