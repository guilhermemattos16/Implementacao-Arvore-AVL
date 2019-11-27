#include "redBlackTree.h"

int main(){
	NILL = malloc(sizeof(struct node));
	NILL->cor = BLACK;   

	ROOT = NILL;
	
	int opcao;
    void *chave;

    do{
        printf("1 - Inserir\n 2 - Busca\n 3 - Remover\n 4 - Imprimir\n 5 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor da  para inserção: ");
            scanf("%d", &chave);
            insercao(chave, compara);
            break;
        case 2:
            printf("Digite o valor da chave para buscar: ");
            scanf("%d", &chave);
            printf((busca(chave, compara) == NILL) ? "Valor não encontrado\n" : "%d\n", busca(chave, compara)->chave);
            break;
        case 3:
            printf("Digite o valor da chave para remover: ");
            scanf("%d", &chave);
            remocao(busca(chave, compara));
            break;
        case 4:
            imprimir(ROOT);
            break;
        
        default:
            break;
        }
    }while (opcao != 5);
    

	return 0;
}
