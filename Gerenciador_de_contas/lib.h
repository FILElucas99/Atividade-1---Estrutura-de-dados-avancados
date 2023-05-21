#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define tam 50

typedef struct cartao Cartao;

typedef struct {
    char nome[tam];
    int cpf;
    char endereco[tam];
    Cartao *cartoes[tam];
} Usuario;

typedef struct {
    char itens[tam];
    float valor;
    Usuario user;
} Compra;

struct NoArv{
    Compra compra;
    int altura;
    struct NoArv *esq, *dir;
};

struct cartao {
    int num;
    Usuario titular;
    char validade[10];
    char bandeira[10];
    int codigo;
    struct NoArv* dados;
};

//Árvore de compras
struct NoArv* novoNo(Compra compra);
int maior(int a, int b);
int alturaDoNo(struct NoArv* no);
struct NoArv* rotacaoEsquerda(struct NoArv* no);
struct NoArv* rotacaoDireita(struct NoArv* no);
struct NoArv* rotacaoDireitaEsquerda(struct NoArv* no);
struct NoArv* rotacaoEsquerdaDireita(struct NoArv* no);
struct NoArv* inserir(struct NoArv* raiz, Compra compra);
void imprimir(struct NoArv* arv, int nivel);


#endif // LIB_H_INCLUDED
