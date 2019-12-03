/*
Universidade Federal do Espirito Santo
Alunos: Arlon Felipe Scheidegger de Aguiar,
        Guilherme Souza Mattos,
        Luciano Alves
Ciencia da Computacao - Estrutura de Dados II
*/

#include "arvoreB.h"

int main(){
    Artigo art;
    Pagina *Pag;
    Inicializa(&Pag);
	int opcao, id, bool;

    do{
        system("clear || cls");
        printf("\n 1 - Inserir\n 2 - Busca\n 3 - Remover\n 4 - Imprimir\n 5 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Informe id: ");
            scanf("%d", &art.id);
            setbuf(stdin, NULL);
            printf("Informe ano: ");
            scanf("%d", &art.ano);
            setbuf(stdin, NULL);
            printf("Autor: ");
            fgets(art.autor, 200, stdin);
            printf("Titulo: ");
            fgets(art.titulo, 200, stdin);
            printf("Revista: ");
            fgets(art.revista, 200, stdin);
            printf("DOI: ");
            fgets(art.DOI, 20, stdin);
            printf("Palavra Chave: ");
            fgets(art.palavraChave, 200, stdin);
            Insere(art, &Pag);
            printf("Pressione enter para continuar");
            getchar();
            break;
        case 2:
            printf("Digite o id do artigo procurado: ");
            scanf("%d", &id);
            Pesquisa(id, Pag);
            if(bool == FALSE){
                printf("Artigo nao encontrado");
            }
            printf("Pressione enter para continuar");
            getchar();
            getchar();
            break;
        case 3:
            printf("Digite o id do artigo a ser removido: ");
            scanf("%d", &id);
            Retira(id, &Pag);
            printf("Pressione enter para continuar");
            getchar();
            getchar();
            break;
        case 4:
            Imprime(Pag);
            printf("Pressione enter para continuar");
            getchar();
            getchar();
            break;
        
        default:
            break;
        }
    }while (opcao != 5);
    

	return 0;
}