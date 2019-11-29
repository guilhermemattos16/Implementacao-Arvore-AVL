/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#include "arvoreB.h"
void ImprimeI(Apontador p, int nivel)
{ 
    long i;
    if (p == NULL) return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++) {
        printf("%d ", p->r[i].Chave);
    }
    
    putchar('\n');
    nivel++;
    
    for (i = 0; i <= p->n; i++) {
        ImprimeI(p->p[i], nivel);
    }
} 

void Imprime(Apontador p)
{   int  n = 0; 
    ImprimeI(p, n); 
} 

// void imprimir(Apontador p){

// 	if(x != NILL){
//         printf("%d - %d\t", x->chave, x->cor);
// 		imprimir(x->esq);		
// 		imprimir(x->dir);
// 	}
// }

void percorreB (Apontador r)
// recebe um apontador para uma B-árvore e imprime a chave de todas as suas células
{
  int i;
  if (r != NULL)
  {
    for (i = 0; i < (2*ORDEM); i++)
    {
      percorreB (r->p[i]);
      printf ("%d ", r->r[i]);
    }
    percorreB (r->p[2*ORDEM]);
  }
}

void TestaI(Apontador p, int pai, short direita)
{   int i;
    int antecessor = 0;
    
    if (p == NULL) return;
    
    if (p->r[0].Chave > pai && direita == FALSE) 
    {   
        printf("Erro: filho %12ld maior que pai %d\n", p->r[0].Chave, pai);
        return;
    }
    for (i = 0; i < p->n; i++) 
    {   if (p->r[i].Chave <= antecessor) 
        { 
            printf("Erro: irmao %ld maior que irmao a esquerda %d\n", (long)p->r[i].Chave, antecessor);
            return;
        }
        antecessor = p->r[i].Chave;
    }
    for (i = 0; i < p->n; i++) 
        TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

void Testa(Apontador p)
{   int i;
    if (p == NULL) return;
    for (i = 0; i < p->n; i++) 
        TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

// int main(int argc, char *argv[])
// {   
//     Registro x;
//     Pagina *D;
//     Inicializa(&D);


//     printf("Chave: ");
//     scanf("%ld%*[^\n]", &x.Chave);
//     getchar();
//     while (x.Chave != 0) 
//     {   Insere(x, &D);
//         Imprime(D); 
//         printf("Chave: ");
//         scanf("%ld%*[^\n]", &x.Chave);
//         getchar();
//     }
//     Testa(D);
//     printf("Chave: ");
//     scanf("%ld%*[^\n]", &x.Chave);
//     getchar();
//     while (x.Chave != 0) 
//     {   Retira(x.Chave, &D);
//         Imprime(D);
//         printf("Chave: ");
//         scanf("%ld%*[^\n]", &x.Chave);
//         getchar();
//     }
//     Testa(D);
//     return 0;
// }


int main(){
    Registro x;
    Pagina *Dicionario;
	int opcao;

    Inicializa(&Dicionario);
    do{
        printf("\n 1 - Inserir\n 2 - Busca\n 3 - Remover\n 4 - Imprimir\n 5 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor da chave para inserção: ");
            scanf("%d", &x.Chave);
            Insere(x, &Dicionario);
            break;
        case 2:
            printf("Digite o valor da chave para buscar: ");
            scanf("%d", &x.Chave);
            // printf((Pesquisa(x.Chave, Dicionario) == NULL) ? "Valor não encontrado\n" : "%d\n", Pesquisa(x.Chave, Dicionario)->chave);
            break;
        case 3:
            printf("Digite o valor da chave para remover: ");
            scanf("%d", &x.Chave);
            Retira(x.Chave, &Dicionario);
            break;
        case 4:
            // Imprime(Dicionario);
            percorreB(Dicionario);
            break;
        
        default:
            break;
        }
    }while (opcao != 5);
    

	return 0;
}
