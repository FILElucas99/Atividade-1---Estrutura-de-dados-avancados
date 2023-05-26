#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define TAM 50
#define MAX 5

typedef struct cartao Cartao;

typedef struct {
    char nome[TAM];
    char cpf[15];
    char endereco[TAM];
    Cartao* cartoes[TAM];
    int numCartoes;
    int id;
} Usuario;

struct cartao {
    int num;
    Usuario* titular;
    char validade[TAM];
    char bandeira[TAM];
    int codigo;
    struct NoArv* dados;
};

typedef struct {
    char itens[TAM];
    float valor;
    int id_compra;
    Usuario user;
} Compra;

struct NoArv {
    Compra compra;
    int altura;
    struct NoArv* esq, * dir;
};

//Cabeçalho tabelas hash

struct tabNo_Usuario {
    Usuario dado;
    struct tabNo_Usuario *next;
};
typedef struct tabNo_Usuario* noUser;

typedef struct tabela_User {
    noUser* tab;
    int tamanho;
    int numUsuarios;
    float taxa;
} tab_User;

struct tabNo_Cartao {
    Cartao* dado;
    struct tabNo_Cartao *next;
};
typedef struct tabNo_Cartao* noCartao;

typedef struct tabela_Cartao {
    noCartao* tab;
    int tamanho;
    int numCartao;
    float taxa;
} tab_Cartao;

//Árvore de compras
struct NoArv* novoNo(Compra compra);
int maior(int a, int b);
int alturaDoNo(struct NoArv* no);
int fatorDeBalanceamento(struct NoArv* no);
struct NoArv* balancear(struct NoArv* raiz);
struct NoArv* rotacaoEsquerda(struct NoArv* no);
struct NoArv* rotacaoDireita(struct NoArv* no);
struct NoArv* rotacaoDireitaEsquerda(struct NoArv* no);
struct NoArv* rotacaoEsquerdaDireita(struct NoArv* no);
struct NoArv* inserir(struct NoArv* raiz, Compra compra);
void imprimir(struct NoArv* raiz);

//Tabela de Usuários
tab_User* criarTabelaUsuarios();
tab_Cartao* criarTabelaCartoes();
void inserir_User(tab_User* tabela, Usuario novo_usuario);
void exibirUsuarios(tab_User* tabela);
void double_size_User(tab_User* t);
int funcao_Hash_User(tab_User* t, int dado);

void inserir_Cartao(tab_Cartao* tabela, Cartao* novo_cartao);
void exibirCartao(tab_Cartao* tabela);
void double_size_Cartao(tab_Cartao* t);
void exibirCompra(struct NoArv* cartao, int id);
int funcao_Hash_Cartao(tab_Cartao* t, int dado);
noUser buscaId(tab_User* t, int aux);
noCartao buscaCartao(tab_Cartao* t, int num);
bool verificaID(tab_User* t, int id);
bool verificaNumero(tab_Cartao* t, int num);
bool verificaId_Compra(struct NoArv* raiz, int id);
void menu();

#endif // LIB_H_INCLUDED
