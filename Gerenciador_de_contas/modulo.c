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
    int hash = funcao_Hash_User(tabela, novo_usuario.id);

    noUser novo = malloc(sizeof(*novo));
    novo->dado = novo_usuario;
    novo->next = NULL;

    if (tabela->tab[hash] == NULL) {
        tabela->tab[hash] = novo;
    } else {
        noUser atual = tabela->tab[hash];
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }

    tabela->numUsuarios++;
    tabela->taxa = (float)tabela->numUsuarios / tabela->tamanho;

    if (tabela->taxa >= 0.5) {
        double_size_User(tabela);
    }
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
                printf("Cartão %d\n", j + 1);
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
    printf("Tamanho da tabela hash de usuarios: %d", tabela->tamanho);
}

void double_size_User(tab_User* t) {
    int oldSize = t->tamanho;
    int newSize = t->tamanho * 2;

    noUser* newTab = malloc(newSize * sizeof(noUser));

    for (int i = 0; i < newSize; i++) {
        newTab[i] = NULL;
    }

    for (int i = 0; i < oldSize; i++) {
        noUser current = t->tab[i];
        while (current != NULL) {
            noUser next = current->next;
            int newHash = funcao_Hash_User(t,current->dado.id) % newSize;

            if (newTab[newHash] == NULL) {
                newTab[newHash] = current;
                current->next = NULL;
            } else {
                noUser atual = newTab[newHash];
                while (atual->next != NULL) {
                    atual = atual->next;
                }
                atual->next = current;
                current->next = NULL;
            }
            current = next;
        }
    }
    free(t->tab);

    t->tamanho = newSize;
    t->tab = newTab;
}

tab_Cartao* criarTabelaCartoes() {
    tab_Cartao* tabela = malloc(sizeof(tab_Cartao));
    tabela->tab = malloc(MAX * sizeof(noCartao));
    tabela->tamanho = MAX;
    tabela->taxa = 0.0;

    // Inicialize todos os elementos da tabela com NULL
    for (int i = 0; i < MAX; i++) {
        tabela->tab[i] = NULL;
    }

    return tabela;
}

void inserir_Cartao(tab_Cartao* tabela, Cartao* novo_cartao) {
    int hash = funcao_Hash_Cartao(tabela, novo_cartao->num);

    noCartao novo = malloc(sizeof(*novo));
    novo->dado = novo_cartao;
    novo->next = NULL;

    if (tabela->tab[hash] == NULL) {
        tabela->tab[hash] = novo;
    } else {
        noCartao atual = tabela->tab[hash];
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }

    tabela->numCartao++;
    tabela->taxa = (float)tabela->numCartao / tabela->tamanho;

    if (tabela->taxa >= 0.5) {
        double_size_Cartao(tabela);
    }
}

void double_size_Cartao(tab_Cartao* t) {
    int oldSize = t->tamanho;
    int newSize = t->tamanho * 2;

    noCartao* newTab = malloc(newSize * sizeof(noCartao));

    for (int i = 0; i < newSize; i++) {
        newTab[i] = NULL;
    }

    for (int i = 0; i < oldSize; i++) {
        noCartao current = t->tab[i];
        while (current != NULL) {
            noCartao next = current->next;
            int newHash = funcao_Hash_Cartao(t,current->dado->num) % newSize;

            if (newTab[newHash] == NULL) {
                newTab[newHash] = current;
                current->next = NULL;
            } else {
                noCartao atual = newTab[newHash];
                while (atual->next != NULL) {
                    atual = atual->next;
                }
                atual->next = current;
                current->next = NULL;
            }
            current = next;
        }
    }
    free(t->tab);

    t->tamanho = newSize;
    t->tab = newTab;
}

void exibirCartao(tab_Cartao* tabela) {
    if (tabela == NULL) {
        printf("Tabela de cartoes nao inicializada.\n");
        return;
    }

    for (int i = 0; i < tabela->tamanho; i++) {
        noCartao atual = tabela->tab[i];
        int posicao = 0;  // Variável para armazenar a posição na lista encadeada
        while (atual != NULL) {
            printf("indice: %d\n", i);
            printf("Posicao: %d\n", posicao);
            printf("Numero: %d\n", atual->dado->num);
            printf("Titular: %s\n", atual->dado->titular->nome);
            printf("Data de validade: %s\n", atual->dado->validade);
            printf("Bandeira: %s\n", atual->dado->bandeira);
            printf("Codigo: %d\n\n", atual->dado->codigo);
            printf("Compras do cartao do usuario %s:\n", atual->dado->titular->nome);
            imprimir(atual->dado->dados);
            printf("----------------\n");
            atual = atual->next;
            posicao++;
        }
    }
    printf("Tamanho da tabela hash de cartoes: %d",tabela->tamanho);
}

int funcao_Hash_User(tab_User* t,int dado) {
    return dado % t->tamanho;
}
int funcao_Hash_Cartao(tab_Cartao* t,int dado) {
    return dado % t->tamanho;
}

noUser buscaId(tab_User* t, int aux) {
    int hash = funcao_Hash_User(t, aux);
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
    int hash = funcao_Hash_Cartao(t, num);
    noCartao current = t->tab[hash];

    while (current != NULL) {
        if (current->dado->num == num) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool verificaID(tab_User* t, int id) {
    for (int i = 0; i < t->tamanho; i++) {
        noUser current = t->tab[i];
        while (current != NULL) {
            if (current->dado.id == id)
                return false;

            current = current->next;
        }
    }
    return true;
}

bool verificaNumero(tab_Cartao* t, int num){
    for (int i = 0; i < t->tamanho; i++) {
        noCartao current = t->tab[i];
        while (current != NULL) {
            if (current->dado->num == num)
                return false;

            current = current->next;
        }
    }
    return true;
}

bool verificaId_Compra(struct NoArv* raiz, int id) {
    if (raiz == NULL) {
        return false;
    }

    if (raiz->compra.id_compra == id) {
        return true;
    }

    if (verificaId_Compra(raiz->esq, id)) {
        return true;
    }

    if (verificaId_Compra(raiz->dir, id)) {
        return true;
    }

    return false;
}

void exibirCompra(struct NoArv* cartao, int id){
    if(cartao){
        if(cartao->compra.id_compra == id){
            printf("\nId encontrado, aqui esta as informacoes da sua compra\n");
            printf("Nome: %s\n", cartao->compra.user.nome);
            printf("Valor: %.2f\n", cartao->compra.valor);
            printf("Itens: %s\n", cartao->compra.itens);
            printf("----------------\n");
        } else {
            exibirCompra(cartao->esq, id);
            exibirCompra(cartao->dir, id);
        }
    }
}

void menu(){
    tab_User* tabelaUsuarios = criarTabelaUsuarios();
    tab_Cartao* tabelaCartao = criarTabelaCartoes();

    noUser user;
    noCartao cartao;
    Compra compra;

    int opcao, aux, num, id_compra;
    float preco;
    char itens[TAM];

    do {
        printf("Escolha uma opcao:\n");
        printf("1. Inserir novo usuario\n");
        printf("2. Exibir usuarios cadastrados\n");
        printf("3. Exibir cartoes cadastrados\n");
        printf("4. Cadastrar compra\n");
        printf("5. Exibir compra\n");
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
                printf("Digite o endereco do usuario: ");
                scanf(" %[^\n]", usuario->endereco);
                do{
                    printf("Digite o id do usuario: ");
                    scanf("%d", &usuario->id);
                    if(!verificaID(tabelaUsuarios, usuario->id))
                        printf("Id ja exisente, informe um diferente\n");
                } while (!verificaID(tabelaUsuarios, usuario->id));

                printf("\nQuantos cartoes o usuario possui? ");
                scanf("%d", &usuario->numCartoes);

                for (int i = 0; i < usuario->numCartoes; i++) {
                    usuario->cartoes[i] = NULL;
                }

                for (int j = 0; j < usuario->numCartoes; j++) {
                    usuario->cartoes[j] = malloc(sizeof(Cartao));
                    usuario->cartoes[j]->titular = usuario;

                    do{
                        printf("Digite o numero do cartao %d: ", j + 1);
                        scanf("%d", &usuario->cartoes[j]->num);
                        if(!verificaNumero(tabelaCartao, usuario->cartoes[j]->num))
                            printf("Numero ja exisente, informe um diferente\n");

                    } while (!verificaNumero(tabelaCartao, usuario->cartoes[j]->num));

                    printf("Digite a data de validade do cartao %d: ", j + 1);
                    scanf(" %[^\n]", usuario->cartoes[j]->validade);

                    printf("Digite a bandeira do cartao %d: ", j + 1);
                    scanf(" %[^\n]", usuario->cartoes[j]->bandeira);

                    printf("Digite o codigo do cartao %d: ", j + 1);
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
                printf("\nInforme o seu id de usuario: ");
                scanf("%d",&aux);
                user = buscaId(tabelaUsuarios, aux);
                if(user){
                    printf("ID encontrado\n");
                    printf("Com que cartao sera realizada a compra: ");
                    scanf("%d",&num);
                    cartao = buscaCartao(tabelaCartao, num);
                    if(cartao && cartao->dado->titular->id == user->dado.id){
                        printf("Cartao encontrado\n");
                        do{
                        printf("Informe o id da compra: ");
                        scanf("%d", &compra.id_compra);
                        if(verificaId_Compra(cartao->dado->dados, compra.id_compra)){
                            printf("\nJa existe compra com esse id\n\n");
                        }

                    } while (verificaId_Compra(cartao->dado->dados, compra.id_compra));
                        printf("Informe os itens da compra: ");
                        scanf(" %[^\n]", itens);
                        strcpy(compra.itens, itens);
                        printf("Informe o preco: ");
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
                printf("\nInforme o num do cartao vinculado as compra(s): ");
                scanf("%d", &num);
                printf("\n");
                cartao = buscaCartao(tabelaCartao, num);
                if(cartao){

                        printf("Cartao encontrado\n");
                        printf("Informe o id da compra: ");
                        scanf("%d",&id_compra);
                        exibirCompra(cartao->dado->dados, id_compra);

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
