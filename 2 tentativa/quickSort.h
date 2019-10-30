#define TamArea 100

typedef int Apontador;
typedef int TipoChave;
typedef struct TipoItem{
    TipoChave Chave;
}TipoItem;

typedef struct Celula {
    TipoItem Item;
    Apontador Prox, Ant;
} Celula;
