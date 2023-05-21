#include "lib.h"

int main(){
    struct NoArv* raiz = NULL;

    Usuario user1;
    user1.cpf = 2;
    strcpy(user1.nome, "Tadeu++");

    Compra compra1;
    strcpy(compra1.itens, "Sabao e arroz");
    compra1.valor = 100.50;
    compra1.user = user1;

    Usuario user2;
    user2.cpf = 1;
    strcpy(user2.nome, "PauloCobol");

    Compra compra2;
    strcpy(compra2.itens, "Linguica e macarrao");
    compra2.valor = 30.50;
    compra2.user = user2;

    Usuario user3;
    user3.cpf = 3;
    strcpy(user3.nome, "WesleyScript");

    Compra compra3;
    strcpy(compra3.itens, "oleo e wasabi");
    compra3.valor = 34.00;
    compra3.user = user3;

    // Inserir nós na árvore
    raiz = inserir(raiz, compra1);
    raiz = inserir(raiz, compra2);
    raiz = inserir(raiz, compra3);

    // Imprimir a árvore
    imprimir(raiz, 1);

    return 0;
}
