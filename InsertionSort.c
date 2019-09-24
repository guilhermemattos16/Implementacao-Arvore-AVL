// Exemplo dado em sala para implementação de insertion sort para tipo generico de dados.
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int compara(void *a, void *b){
    int* locala = (int*) a;
    int* localb = (int*) b;

    return (*locala) - (*localb);
}

struct str_aluno
{
    int matricula;
} typedef aluno;


int compMat(void *a, void *b){
    aluno *localA = (aluno *)a;
    aluno *localB = (aluno *)b;

    if (localA->matricula == localB->matricula)
    {
        return 0;
    }
    else
    {
        if (localA->matricula > localB->matricula)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}

void insertionSort(void *V, int tam, (int)(*comp)(void *, void *), int tamElem) {
    int i, j;
    void *aux = malloc(tamElem);
    for (i = 0; i < tam; i++)
    {
        memcpy(aux, &(V[i]), tamElem);
        for (j = i-1; j >= 0; j--)
        {
            if (comp(&(V[j]), aux) > 0)
            {
                memcpy(&(V[j+1]), &(V[j]), tamElem);
            }
            else
            {
                break;
            }
        }
        memcpy(&(V[j+1]), aux, tamElem);
    }
}