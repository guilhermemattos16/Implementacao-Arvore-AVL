#include "redBlackTree.h"




void imprimir(struct node *x){

	if(x != NILL){
        printf("%d - %d\t", x->chave, x->cor);
		imprimir(x->esq);		
		imprimir(x->dir);
	}
}

struct node *busca(void *chave, int (*comp)(void*, void*)){
	struct node *x;

	x = ROOT;
	while(x != NILL && (comp(x->chave, chave) != 0)){
		if(comp(chave, x->chave) < 0){
			x = x->esq;
		}
		else{
			x = x->dir;
		}
	}

	return x;
}

struct node *sucessor(struct node *x){
	while(x->esq != NILL){
		x = x->esq;
	}
	return x;
}

/*
 * Inserção é feita da mesma forma que uma ABS. Com exeção que o novo nó é colorido como vermelho.
 * Como o nó é colorido como vermelho isso pode violar a propriedade 2 ou 4. Por essa razão
 * um procedimento auxiliar é chamada. insercao_fixup é chamada para consertar as violações.
 */

void insercao(void *chave, int (*comp)(void*, void*)){
	struct node *z, *x, *y;
	z = malloc(sizeof(struct node));

	z->chave = chave;
	z->cor= RED;
	z->esq = NILL;
	z->dir = NILL;

	x = ROOT;
	y = NILL;

	/* 
	 * Passa pela arvore até uma que folha(NILL) é encontrada. y é usado para guardar
     * o ultimo não-NILL nó que seráo pai de z.
	 */
	while(x != NILL){
		y = x;
		if(comp(z->chave, x->chave) <= 0){
			x = x->esq;
		}
		else{
			x = x->dir;
		}
	}

	if(y == NILL){
		ROOT = z;
	}
	else if(comp(z->chave, y->chave) <= 0){
		y->esq = z;
	}
	else{
		y->dir = z;
	}

	z->pai = y;

	insercao_fixup(z);
}

/*
 *  Aqio é o pseudo codigo para consertar as violações.
 *  Here is the psudocode for fixing violations.
 * 
 * while (pai de z é RED)
 *		if(pai de z é filho a esquerda do avo de z) entao
 *			if(tio direito de Z ou avo filho direito é RED ) entao
 *			    torna pai e tio de z BLACK
 *			    torna avo de z RED
 *				tornar o pai de z novo z, pois pode violar as propriedades 2 e 4
 *				(o loop while continuara)
 *			
 *			else(tio dir de z não é RED)
 *				if(z é filho direita do pai de z) entao
 *					torna z como pai de z
 *					rotacao esquerda em z
 *				torna cor do de z BLACK
 *				torna avo de z RED
 *				rotacao direita em avo de z
 *				( O loop nao passa na proxima interacao pois nao há violação)
 *
 *		else(pai de z é filho direita do avo de z)
 *		    faça a mesma coisa que foi feita acima troque direita para esquerda e vice-versa
 *
 * Neste ponto propriedade 2 pode ser violada, então faca a raiz ser BLACK
 */

void insercao_fixup(struct node *z){
	while(z->pai->cor == RED){

		/* pai de z é filho esquerda do avo de z*/
		if(z->pai == z->pai->pai->esq){

			/* o filho direito do avo de z é RED f*/
			if(z->pai->pai->dir->cor == RED){
				z->pai->cor = BLACK;
				z->pai->pai->dir->cor = BLACK;
				z->pai->pai->cor = RED;
				z = z->pai->pai;
			}

			/* o filho direito do avo de z não é RED */
			else{
				
				/* z é o filho direito do pai */
				if(z == z->pai->dir){
					z = z->pai;
					rotacaoEsquerda(z);
				}

				z->pai->cor = BLACK;
				z->pai->pai->cor = RED;
				rotacaoDireita(z->pai->pai);
			}
		}

		/* o pai de z é o filho direito do avo de z */
		else{
			
			/* tio esquerdo de z ou filho esquerdo do avô de z também é vermelho */
			if(z->pai->pai->esq->cor == RED){
				z->pai->cor = BLACK;
				z->pai->pai->esq->cor = BLACK;
				z->pai->pai->cor = RED;
				z = z->pai->pai;
			}

			/* tio esquerdo de z não é vermelho */
			else{
				/* z é filho esqueda de seus pais */
				if(z == z->pai->esq){
					z = z->pai;
					rotacaoDireita(z);
				}

				z->pai->cor = BLACK;
				z->pai->pai->cor = RED;
				rotacaoEsquerda(z->pai->pai);
			}
		}
	}

	ROOT->cor = BLACK;
}

/*
 * vamos dizer que y é filho direito de x. Rotacao a esquerda em x fazendo y pai de x, e y filho esqueda de x
 * e filho esquedo de y torna ser filho a direita de x.
 * 
 * 		x									y
 *	   / \                                 / \
 *  STA   y			----------->		  x   STC
 *		 / \							 / \
 *	  STB   STC						  STA   STB
 */

void rotacaoEsquerda(struct node *x){
	struct node *y;
	
	/* Faça o filho esquerdo de y filho direto de x */
	y = x->dir;
	x->dir = y->esq;
	if(y->esq != NILL){
		y->esq->pai = x;
	}

	/* Faça pai de x ser pai de y e y ser filho de pai de x */
	y->pai = x->pai;
	if(y->pai == NILL){
		ROOT = y;
	}
	else if(x == x->pai->esq){
		x->pai->esq = y;
	}
	else{
		x->pai->dir = y;
	}
	
	/* Tornar filho esquerdo de x, y e pai de y, x */
	y->esq = x;
	x->pai = y;
}

/*
 * Vamos dizer que y é filho esquerdo de x. Rotacione x a direita fazendo x filho direito de y
 * e y pai de x. Filho direito de y passa a ser filho esquerdo de x.
 *
 *			|											|
 *			x											y
 *		   / \										   / \
 *		  y   STA		---------------->			STB	  x
 *		 / \											 / \
 *	  STB   STC										  STC   STA
 */

void rotacaoDireita(struct node *x){
	struct node *y;

	/* faça filho direito de y ser filho esquerdo de x */
	/*  */
	y = x->esq;
	x->esq = y->dir;
	if(y->dir != NILL){
		y->dir->pai = x;
	}

	/* faça pai de x ser pai de y e y ser filho do pai do x */
	y->pai = x->pai;
	if(y->pai == NILL){
		ROOT = y;
	}
	else if(x == x->pai->esq){
		x->pai->esq = y;	
	}
	else{
		x->pai->dir = y;
	}

	/* tornar y pai de x, x filho de y */
	y->dir = x;
	x->pai = y;
}

/*
 * Remoção é feita no mesmo mecanisco de ABP. Se z não tem filho, z é removido. Se z
 * tem um unico filho, z é substituido pelo seu filho. Se não z é substituido pelo seu
 * sucessor. Se o sucessor não for filho de z, o sucessor será substituído por seu próprio
 *  filho primeiro. então z é substituído pelo sucessor.
 * 
 * Um ponteiro y é usado para acompanhamento. Nos primeiros 2 casos y é z. 3 caso y é sucessor de z.
 * Então nos primeiros dois casos y é removido. No 3 caso y é movido.
 * 
 * Outro ponteiro x é usado para acompanha o nó que substitui y.
 *
 * Como remover ou mover y pode afetar tres propriedades da RBT uma variavel yOriginalColor
 * é usada para guardar a cor original. Se for BLACK então removendo ou movendo y afeta 3 propriedades
 * da RBT. Nesse caso um procedimento auxiliar remocao_fixup(x) é chamado para corrigir.
 * 
 */

void remocao(struct node *z){
	struct node *y, *x;
	int yOriginalColor;

	y = z;
	yOriginalColor = y->cor;

	if(z->esq == NILL){
		x = z->dir;
		troca(z, z->dir);
	}
	else if(z->dir == NILL){
		x = z->esq;
		troca(z, z->esq);
	}
	else{
		y = sucessor(z->dir);
		yOriginalColor = y->cor;

		x = y->dir;

		if(y->pai == z){
			x->pai = y;
		}
		else{
			troca(y, y->dir);
			y->dir = z->dir;
			y->dir->pai = y;
		}

		troca(z, y);
		y->esq = z->esq;
		y->esq->pai = y;
		y->cor= z->cor;
	}

	if(yOriginalColor == BLACK){
		remocao_fixup(x);
	}
}

/*
 * Como y era BLACK e removido x ganha y um nó negro extra.
 * 
 * Mova o nó negro extra de x até
 * 		1. x se tornar raiz. Nesse caso apenas remova o nó negro
 * 		2. x se torna RED and BLACK nó. nesse caso just make x BLACK
 * 
 * Primeiro verifica se x é filho direito ou esquedo do seu pai. Dizendo que x é filho esquedo
 * 
 * Temos 4 casos.
 * 
 * Caso 1: irmao w de x é RED. Transforma caso 1 para o caso 2 recolorindo w e pai de x.
 * Então rotacione a esqueda o pai de x.
 *
 * Caso 2: irmao w de x é BLACK, os dois filhos de w é BLACK. Mova x e a cor Negra de W
 * para pai de x colorindo w para RED e pai de x para BLACK.
 * Faça pai de x novo x. Nota se caso dois passa para caso 1 pai de x se torna RED and BLACK como isso
 * se torna RED no caso 1. Então lopp vai parar até a proxima interação.
 *
 * Caso 3: w é preto, filho esquerdo de w é RED e o direito é BLACK. Transforme caso 3 em caso 4
 * colorindo w e seu filho a esquerda, entao rotacione w a direita.
 *
 * Caso 4: w é BLACK, w filho direito é RED. Recolore w com a cor do pai de x.
 * faca pai de x BLACK, w filho a direita BLACK. Agora rotacione pai de x a esquerda.
 * Faca x apontar para raiz. Então o loop irá parar até a proxima interação
 *
 * Se x é filho direita do seu pai faça a mesma coisa trocando esq<->dir
 */

void remocao_fixup(struct node *x){
	struct node *w;	

	while(x != ROOT && x->cor== BLACK){
		
		if(x == x->pai->esq){
			w = x->pai->dir;

			if(w->cor== RED){
				w->cor= BLACK;
				x->pai->cor= RED;
				rotacaoEsquerda(x->pai);
				w = x->pai->dir;
			}

			if(w->esq->cor== BLACK && w->dir->cor== BLACK){
				w->cor= RED;
				x->pai->cor= BLACK;
				x = x->pai;
			}
			else{

				if(w->dir->cor== BLACK){
					w->cor= RED;
					w->esq->cor= BLACK;
					rotacaoDireita(w);
					w = x->pai->dir;
				}

				w->cor= x->pai->cor;
				x->pai->cor= BLACK;
				x->dir->cor= BLACK;
				rotacaoEsquerda(x->pai);
				x = ROOT;		

			}

		}
		else{
			w = x->pai->esq;

			if(w->cor== RED){
				w->cor= BLACK;
				x->pai->cor= BLACK;
				rotacaoDireita(x->pai);
				w = x->pai->esq;
			}

			if(w->esq->cor== BLACK && w->dir->cor == BLACK){
				w->cor = RED;
				x->pai->cor = BLACK;
				x = x->pai;
			}
			else{

				if(w->esq->cor == BLACK){
					w->cor = RED;
					w->dir->cor = BLACK;
					rotacaoEsquerda(w);
					w = x->pai->esq;
				}

				w->cor = x->pai->cor;
				x->pai->cor = BLACK;
				w->esq->cor = BLACK;
				rotacaoDireita(x->pai);
				x = ROOT;

			}
		}

	}

	x->cor = BLACK;
}

/* troca no u com no v */
void troca(struct node *u, struct node *v){
	if(u->pai == NILL){
		ROOT = v;
	}
	else if(u == u->pai->esq){
		u->pai->esq = v;
	}
	else{
		u->pai->dir = v;
	}

	v->pai = u->pai;
}