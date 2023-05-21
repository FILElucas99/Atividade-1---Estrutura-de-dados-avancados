#include "lib.h"

int fatorDeBalanceamento(struct NoArv* no){
    if(no){
        return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
    } else {
        return 0;
    }
}

struct NoArv* balancear(struct NoArv* raiz){
    int fb = fatorDeBalanceamento(raiz);

    if(fb < -1 && fatorDeBalanceamento(raiz->dir) <= 0){
        raiz = rotacaoEsquerda(raiz);
    }
    else if(fb < -1 && fatorDeBalanceamento(raiz->dir) > 0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }
    else if(fb > 1 && fatorDeBalanceamento(raiz->esq) >= 0){
        raiz = rotacaoDireita(raiz);
    }
    else if(fb > 1 && fatorDeBalanceamento(raiz->esq) < 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }

    return raiz;
}

//Função que cria um nó compra e retorna seu endereço
struct NoArv* novoNo(Compra compra){
    struct NoArv* novo = (struct NoArv*) malloc(sizeof(struct NoArv));
    if(novo){
        novo->compra = compra;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->altura = 0;
    } else {
        printf("\nERRO ao alocar nó...");
    }
    return novo;
}

int maior(int a, int b){
    return (a>b)? a:b;
}

int alturaDoNo(struct NoArv* no){
    if(no == NULL){
        return -1;
    } else {
        return no->altura;
    }
}

struct NoArv* rotacaoEsquerda(struct NoArv* no){
    struct NoArv *y, *f;

    y = no->dir;
    f = no->esq;

    y->esq = no;
    no->dir = f;

    no->altura = maior(alturaDoNo(no->esq), alturaDoNo(no->dir));
    y->altura = maior(alturaDoNo(y->esq), alturaDoNo(y->dir));

    return y;

}

struct NoArv* rotacaoDireita(struct NoArv* no){
     struct NoArv *f, *y;

     y = no->esq;
     f = y->dir;

     y->dir = no;
     no->esq = f;

     no->altura = maior(alturaDoNo(no->esq), alturaDoNo(no->dir)) + 1;
     y->altura = maior(alturaDoNo(y->esq), alturaDoNo(y->dir)) + 1;

     return y;

}

struct NoArv* rotacaoDireitaEsquerda(struct NoArv* no){
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
}

struct NoArv* rotacaoEsquerdaDireita(struct NoArv* no){
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
}

struct NoArv* inserir(struct NoArv* raiz, Compra compra){
    if(raiz == NULL){
        return novoNo(compra);
    } else {
        int cpfCompra = compra.user.cpf;
        int cpfRaiz = raiz->compra.user.cpf;

        if(cpfCompra < cpfRaiz){
            raiz->esq = inserir(raiz->esq, compra);
        }
        else if(cpfCompra > cpfRaiz){
            raiz->dir = inserir(raiz->dir, compra);
        } else {
            printf("Compra já cadastrada...");
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

    return balancear(raiz);
}

void imprimir(struct NoArv* raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->dir, nivel + 1);
        printf("\n\n");
        for(i = 0; i < nivel; i++){
            printf("\t");
        }
        printf("Itens: %s,Valor: %.2f,Nome: %s", raiz->compra.itens,
               raiz->compra.valor,
               raiz->compra.user.nome);

        imprimir(raiz->esq, nivel + 1);
    }
}


