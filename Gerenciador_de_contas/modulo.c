#include "lib.h"

int fatorDeBalanceamento(struct NoArv* no){
    if(no){
        return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
    } else {
        return 0;
    }
}

struct NoArv* balancear(struct NoArv* raiz) {
    int fb = fatorDeBalanceamento(raiz);

    if (fb < -1 && fatorDeBalanceamento(raiz->dir) <= 0) {
        raiz = rotacaoEsquerda(raiz);
    } else if (fb < -1 && fatorDeBalanceamento(raiz->dir) > 0) {
        raiz = rotacaoDireitaEsquerda(raiz);
    } else if (fb > 1 && fatorDeBalanceamento(raiz->esq) >= 0) {
        raiz = rotacaoDireita(raiz);
    } else if (fb > 1 && fatorDeBalanceamento(raiz->esq) < 0) {
        raiz = rotacaoEsquerdaDireita(raiz);
    }

    raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

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

struct NoArv* rotacaoEsquerda(struct NoArv* no) {
    struct NoArv* y = no->dir;
    struct NoArv* f = y->esq;

    y->esq = no;
    no->dir = f;

    no->altura = maior(alturaDoNo(no->esq), alturaDoNo(no->dir)) + 1;
    y->altura = maior(alturaDoNo(y->esq), alturaDoNo(y->dir)) + 1;

    return y;
}

struct NoArv* rotacaoDireita(struct NoArv* no) {
    struct NoArv* y = no->esq;
    struct NoArv* f = y->dir;

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

struct NoArv* inserir(struct NoArv* raiz, Compra compra) {
    if (raiz == NULL) {
        return novoNo(compra);
    } else {
        int valorCompra = compra.valor;
        int valorRaiz = raiz->compra.valor;

        if (valorCompra < valorRaiz) {
            raiz->esq = inserir(raiz->esq, compra);
        } else {
            raiz->dir = inserir(raiz->dir, compra);
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

    return balancear(raiz);
}


void imprimir(struct NoArv* raiz) {
    if (raiz) {
        imprimir(raiz->esq);
        printf("Itens: %s\n", raiz->compra.itens);
        printf("Nome: %s\n", raiz->compra.user.nome);
        printf("Valor: R$%.2f\n\n", raiz->compra.valor);
        imprimir(raiz->dir);
    }
}

//Funções da tabela hash
tab_User* criarTabelaUsuarios() {
    tab_User* tabela = malloc(sizeof(tab_User));
    tabela->tab = malloc(MAX * sizeof(noUser));
    tabela->tamanho = MAX;
    tabela->numUsuarios = 0;
    tabela->taxa = 0.0;

    // Inicialize todos os elementos da tabela com NULL
    for (int i = 0; i < MAX; i++) {
        tabela->tab[i] = NULL;
    }

    return tabela;
}

void inserir_User(tab_User* tabela, Usuario novo_usuario) {
    int hash = funcao_Hash(novo_usuario.id);

    noUser novo = malloc(sizeof(*novo));
    novo->dado = novo_usuario;
    novo->next = NULL;

    if (tabela->tab[hash] == NULL) {
        tabela->tab[hash] = novo;
    } else {
        // Tratamento de colisão: insere o novo usuário no final da lista encadeada
        noUser atual = tabela->tab[hash];
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }

    tabela->numUsuarios++; // Incrementa o número de usuários

    // Verifica se a tabela atingiu ou excedeu 50% de ocupação antes de incrementar a taxa
    if (tabela->taxa >= (float)tabela->tamanho * 0.5) {
        double_size_User(tabela); // Chama a função double_size para aumentar o tamanho da tabela
    }

    tabela->taxa = (float)tabela->numUsuarios / tabela->tamanho; // Atualiza a taxa de ocupação
}

void exibirUsuarios(tab_User* tabela) {
    if (tabela == NULL) {
        printf("Tabela de usuários não inicializada.\n");
        return;
    }

    for (int i = 0; i < tabela->tamanho; i++) {
        noUser atual = tabela->tab[i];
        int posicao = 1;

        while (atual != NULL) {
            Usuario usuario = atual->dado;
            printf("Indice: %d\n", i);
            printf("Posicao: %d\n", posicao);
            printf("Nome: %s\n", usuario.nome);
            printf("CPF: %s\n", usuario.cpf);
            printf("Endereco: %s\n", usuario.endereco);
            printf("ID: %d\n\n", usuario.id);

            printf("Cartoes do usuario %s:\n\n", usuario.nome);
            for (int j = 0; j < usuario.numCartoes; j++) {
                printf("Cartao %d\n", j + 1);
                printf("Numero do cartao: %d\n", usuario.cartoes[j]->num);
                printf("Validade do cartao: %s\n", usuario.cartoes[j]->validade);
                printf("Bandeira do cartao: %s\n", usuario.cartoes[j]->bandeira);
                printf("Codigo do cartao: %d\n\n", usuario.cartoes[j]->codigo);
            }

            printf("----------------\n");
            atual = atual->next;
            posicao++;
        }
    }
}


tab_Cartao* criarTabelaCartoes() {
    tab_Cartao* tabela = malloc(sizeof(tab_Cartao));
    tabela->tab = malloc(TAM * sizeof(noCartao));
    tabela->tamanho = TAM;
    tabela->taxa = 0.0;

    // Inicialize todos os elementos da tabela com NULL
    for (int i = 0; i < TAM; i++) {
        tabela->tab[i] = NULL;
    }

    return tabela;
}

void double_size_User(tab_User* t) {
    int newSize = t->tamanho * 2;

    // Cria um novo vetor de ponteiros para nós
    noUser* newTab = malloc(newSize * sizeof(noUser));

    // Inicializa o novo vetor com ponteiros nulos
    for (int i = 0; i < newSize; i++) {
        newTab[i] = NULL;
    }

    // Reespalha os elementos da tabela original para o novo vetor
    for (int i = 0; i < t->tamanho; i++) {
        noUser current = t->tab[i];
        while (current != NULL) {
            noUser next = current->next;
            int h = funcao_Hash(current->dado.id) % newSize;
            current->next = newTab[h];
            newTab[h] = current;
            current = next;
        }
    }

    // Libera a memória da tabela original
    free(t->tab);

    // Atualiza o tamanho e o vetor da tabela com os novos valores
    t->tamanho = newSize;
    t->tab = newTab;
}

void inserir_Cartao(tab_Cartao* tabela, Cartao* novo_cartao) {
    int hash = funcao_Hash(novo_cartao->num);

    noCartao novo = malloc(sizeof(*novo));
    novo->dado = novo_cartao;
    novo->next = NULL;

    if (tabela->tab[hash] == NULL) {
        tabela->tab[hash] = novo;
    } else {
        // Tratamento de colisão: insere o novo cartão no final da lista encadeada
        noCartao atual = tabela->tab[hash];
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }

    // Verifica se a tabela atingiu ou excedeu 50% de ocupação antes de incrementar a taxa
    if (tabela->taxa >= (float)tabela->tamanho * 0.5) {
        double_size_Cartao(tabela); // Chama a função double_size para aumentar o tamanho da tabela
    }

    tabela->taxa++; // Incrementa a taxa de ocupação
}

void double_size_Cartao(tab_Cartao* t) {
    int newSize = t->tamanho * 2;

    // Cria um novo vetor de ponteiros para nós
    noCartao* newTab = malloc(newSize * sizeof(noCartao));

    // Inicializa o novo vetor com ponteiros nulos
    for (int i = 0; i < newSize; i++) {
        newTab[i] = NULL;
    }

    // Reespalha os elementos da tabela original para o novo vetor
    for (int i = 0; i < t->tamanho; i++) {
        noCartao current = t->tab[i];
        while (current != NULL) {
            noCartao next = current->next;
            int h = funcao_Hash(current->dado->num) % newSize;
            current->next = newTab[h];
            newTab[h] = current;
            current = next;
        }
    }

    // Libera a memória da tabela original
    free(t->tab);

    // Atualiza o tamanho e o vetor da tabela com os novos valores
    t->tamanho = newSize;
    t->tab = newTab;
}


void exibirCartao(tab_Cartao* tabela) {
    if (tabela == NULL) {
        printf("Tabela de cartoes nao inicializada.\n");
        return;
    }

    for (int i = 0; i < TAM; i++) {
        noCartao atual = tabela->tab[i];
        int posicao = 0;  // Variável para armazenar a posição na lista encadeada
        while (atual != NULL) {
            printf("indice: %d\n", i);
            printf("Posicao: %d\n", posicao);
            printf("Numero: %d\n", atual->dado->num);
            printf("Titular: %s\n", atual->dado->titular->nome);
            printf("Data de validade: %s\n", atual->dado->validade);
            printf("Bandeira: %s\n", atual->dado->bandeira);
            printf("Codigo: %d\n", atual->dado->codigo);
            printf("----------------\n");
            atual = atual->next;
            posicao++;
        }
    }
}

int funcao_Hash(int dado) {
    return dado % MAX;
}

noUser buscaId(tab_User* t, int aux) {
    int hash = funcao_Hash(aux);
    noUser current = t->tab[hash];

    while (current != NULL) {
        if (current->dado.id == aux) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}


noCartao buscaCartao(tab_Cartao* t, int num) {
    int hash = funcao_Hash(num);
    noCartao current = t->tab[hash];

    while (current != NULL) {
        if (current->dado->num == num) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void menu(){
    tab_User* tabelaUsuarios = criarTabelaUsuarios();
    tab_Cartao* tabelaCartao = criarTabelaCartoes();

    noUser user;
    noCartao cartao;
    Compra compra;

    int opcao, aux, num;
    float preco;
    char itens[TAM];

    do {
        printf("Escolha uma opcao:\n");
        printf("1. Inserir novo usuario\n");
        printf("2. Exibir usuarios cadastrados\n");
        printf("3. Exibir cartoes cadastrados\n");
        printf("4. Cadastrar compra\n");
        printf("5. Exibir compras\n");
        printf("6. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInsercao de Usuario:\n");

                Usuario* usuario = malloc(sizeof(Usuario)); // Aloca memória para o usuário

                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", usuario->nome);
                printf("Digite o CPF do usuario: ");
                scanf(" %[^\n]", usuario->cpf);
                printf("Digite o endereço do usuario: ");
                scanf(" %[^\n]", usuario->endereco);
                printf("Digite o id do usuario: ");
                scanf("%d", &usuario->id);

                printf("\nQuantos cartoes o usuario possui? ");
                scanf("%d", &usuario->numCartoes);

                for (int i = 0; i < usuario->numCartoes; i++) {
                    usuario->cartoes[i] = NULL;
                }

                for (int j = 0; j < usuario->numCartoes; j++) {
                    usuario->cartoes[j] = malloc(sizeof(Cartao));
                    usuario->cartoes[j]->titular = usuario;

                    printf("Digite o numero do cartao %d: ", j + 1);
                    scanf("%d", &usuario->cartoes[j]->num);

                    printf("Digite a data de validade do cartao %d: ", j + 1);
                    scanf(" %[^\n]", usuario->cartoes[j]->validade);

                    printf("Digite a bandeira do cartao %d: ", j + 1);
                    scanf(" %[^\n]", usuario->cartoes[j]->bandeira);

                    printf("Digite o código do cartão %d: ", j + 1);
                    scanf("%d", &usuario->cartoes[j]->codigo);

                    // Inicialize os dados do cartão como NULL
                    usuario->cartoes[j]->dados = NULL;

                    inserir_Cartao(tabelaCartao, usuario->cartoes[j]);
                    printf("\n");
                }

                inserir_User(tabelaUsuarios, *usuario);
                printf("Usuario inserido com sucesso!\n\n");

                break;

            case 2:
                printf("\nUsuarios cadastrados:\n");
                printf("----------------\n");
                exibirUsuarios(tabelaUsuarios);
                printf("\n");
                break;

            case 3:
                printf("\nCartoes cadastrados:\n");
                exibirCartao(tabelaCartao);
                printf("\n");
                break;

            case 4:
                printf("\nInforme seu id: ");
                scanf("%d",&aux);
                user = buscaId(tabelaUsuarios, aux);
                if(user){
                    printf("ID encontrado\n");
                    printf("Com que cartao sera realizada a compra: ");
                    scanf("%d",&num);
                    cartao = buscaCartao(tabelaCartao, num);
                    if(cartao && cartao->dado->titular->id == user->dado.id){
                        printf("Cartao encontrado\n");
                        printf("Informe os itens da compra: ");
                        scanf(" %[^\n]", itens);
                        strcpy(compra.itens, itens);
                        printf("Informe o preço: ");
                        scanf("%f", &preco);
                        printf("\n");
                        compra.valor = preco;
                        compra.user = user->dado;
                        if(cartao->dado->dados == NULL){
                            cartao->dado->dados = novoNo(compra);
                        } else {
                            inserir(cartao->dado->dados, compra);
                        }
                        printf("Compra cadastrada\n");

                    } else {
                        printf("Esse cartao nao esta vinculado a: %s\n\n", user->dado.nome);
                    }
                } else {
                    printf("Usuario nao cadastrado\n");
                }
                break;
            case 5:
                printf("\nInforme o num do cartão vinculado as compra(s): ");
                scanf("%d", &num);
                printf("\n");
                cartao = buscaCartao(tabelaCartao, num);
                if(cartao){
                        printf("Cartao encontrado, aqui está as compras:\n");
                        imprimir(cartao->dado->dados);

                } else {
                    printf("Cartao nao cadastrado\n");
                }
                break;

            case 6:
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
                break;
        }

    } while (opcao != 6);
}
