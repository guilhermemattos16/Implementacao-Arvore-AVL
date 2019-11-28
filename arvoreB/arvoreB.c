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
    Registro r[ORDEM];
    Apontador p[ORDEM + 1];
} Pagina;

typedef struct Tabela {
Registro Item[ORDEM + 1];
    int n;
} Tabela;









int cont = -1, count = 0;

typedef struct artigo {
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
} Artigo;

typedef struct Pagina_str *Apontador;
typedef struct Pagina_str
{
  int n;
  int pageNum;
  int num;
  Artigo r[2*ORDEM];
  Apontador p[2*ORDEM+1];
} Pagina;

typedef struct node{
    Artigo info;
    struct Node *prox;
} Node;

typedef struct pagina
{
    //armazena numero de chaves na pagina
    short int totalChaves;

    //vetor de chaves
    int chaves[ORDEM-1];

    //Ponteiros das paginas filhas, -1 aponta para NULL
    struct pagina filha[ORDEM];
} Pagina;








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


void Busca(k, ponteiroRaiz)
{
    if (ponteiroRaiz == -1)
    {
        return printf("Chave nao encontrada");
    }
    
    else
    {
        //carrega em memoria primaria pagina apontado por ponteiroRaiz
        //procura k na pagina carregada
        
        // if () //k foi encontrada
        {
            return printf("chave encontrada");
        }
        //else
        //{
            //ponteiro = ponteiro para a próxima página da possível ocorrência de k
            // return (Busca (k, ponteiro));
        //}
    }
}

// void emOrdem (tpaginaB raiz) {
//     if(raiz==NULL)
//         return;
 
//     for(int i=0; i < raiz.n, i++) {
//         emOrdem(raiz -> pont[i]);
//         printf("%i",raiz -> chv[i]);
//     }
//     emOrdem(raiz -> pont[raiz.n]);
// }

