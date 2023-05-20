#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define tam 50

typedef struct cartao Cartao;

typedef struct usuario {
    char nome[100];
    int cpf;
    char endereco[50];
    Cartao *cartoes[tam];
} Usuario;

typedef struct compra {
    char itens[50];
    float valor;
    Usuario user;
} Compra;

typedef struct arvcompras {
    Compra compras;
    int fator;
    struct arvcompras *esq, *dir;
} ArvCompras;

struct cartao {
    int num;
    Usuario titular;
    char validade[10];
    char bandeira[10];
    int codigo;
    ArvCompras *dados;
};




#endif // LIB_H_INCLUDED
