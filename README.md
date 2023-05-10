# Atividade 1 - Estrutura de Dados Avançado
*Equipe :*

1- Francisco Lucas Farias da Silva - 538691

2- Lucas Eduardo Mota - 535488

3- Maria Clara Pereira de Sousa - 536940


# Apresentação
Uma Loja Virtual deseja implantar um sistema de gerenciamento das compras pagas por seus
clientes (usuários), através do uso de cartões de crédito. Desta forma, o sistema deverá ser
capaz de cadastrar uma transação eletrônica de uma compra e das informações do pagador
(nome completo, número do cartão, bandeira e código de segurança). 

# Observações
A proposta é desenvolver uma estratégia para criptografar os dados do cartão de crédito do
pagador e otimizar (futuramente) a busca por um histórico de pagamentos realizado por um
determinado cartão de crédito. Sabendo que o um cartão de crédito pode ser utilizado por
diversas compras, estas deverão ser arranjadas em um conjunto em que agrupem o usuário
que utilizou este cartão e os dados da compra.

# Elementos Necessários
*• Cartão de crédito* = Número único, Nome do titular e Data de validade, bandeira e código de segurança.

*• Sobre a compra* = Itens da compra (descrição), Valor da compra e usuário.

*• Usuário* = CPF, Nome Completo, Endereço e Cartões de crédito cadastrados.

# Lógica de organização
• Os cartões são indexados por numeração única, objetivando o acesso à informação,
sendo estes indexados em uma estrutura de tabela hash.

• Os usuários também são indexados por numeração única (CPF), objetivando o acesso à
informação, sendo estes indexados em uma estrutura de tabela hash.

• Cada cartão possui um conjunto de compras, com identificação única, e que, também,
objetivando o acesso rápido as informações, podem ser organizadas em uma estrutura
de dados. Dessa forma, para o momento, a estrutura hierarquia arbórea balanceada
atenderá a indexação destas informações.

# Métodos obrigatórios
• Cadastrar compra, para cada compra realizada deverá existir um cartão e um usurário
vinculado a ela.

• Cadastrar cartões de crédito, ao realizar o cadastro de um cartão, este poderá não ter
compras vinculadas a ele.

• Cadastrar usuários, sabendo que para seu cadastro será necessário a indicação de pelo
menos um cartão de crédito.

• Listar os dados de um usuário, de uma compra ou de um cartão.

# Representação visual da tabela de dispersão dos usuários, tabela de dispersão dos cartões de crédito, juntamente com a árvore de compras
![WhatsApp Image 2023-05-10 at 2 47 57 PM](https://github.com/FILElucas99/Atividade-1---Estrutura-de-dados-avancados/assets/109489204/782517b3-653f-45a9-836b-e25c5d575883)
![WhatsApp Image 2023-05-10 at 2 47 58 PM](https://github.com/FILElucas99/Atividade-1---Estrutura-de-dados-avancados/assets/109489204/f2a10f9e-e345-4c6c-b75d-d2c71425bc40)

Os usuários e os cartões de créditos são representados por diferentes estruturas do tipo tabela
hash. Os usuários guardam em si, para além do seus dados, o número dos cartões de créditos
que são cadastrados na sua conta de usuários e os cartões de créditos armazenam, para além
das suas informações, os dados das compras realizadas organizadas em uma estrutura arbórea
auto ajustável, em que A, C, E, P e B representam estas informações.

# Pontos essenciais
*Objetivo:* Esta atividade possui como objetivo estimular a análise de problemas e a criatividade
da aplicação dos recursos abordados na disciplina de Estrutura de Dados Avançada.

*Estruturas de uso:* Deverão ser aplicados, para a resolução dessa atividade as estruturas: Tabelas
Hash e árvores: AVL ou Vermelho e Preto. Todas as estruturas utilizadas na implementação
deverão ser construídas, ou seja, não devem ser utilizados APIs, bibliotecas ou módulos
construídos por terceiros. No qual fica optativa a escolha da linguagem de programação utilizada para plataforma desktop.
