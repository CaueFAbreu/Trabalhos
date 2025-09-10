Relatório do Trabalho Final: Gerenciador de Perfis Estilo Netflix
Alunos: [Nome do Aluno 1], [Nome do Aluno 2], [Nome do Aluno 3]
Tema Escolhido: Netflix (Gerenciamento de perfis e listas de séries assistidas)
Data: 8 de setembro de 2025

Introdução
O objetivo deste trabalho foi desenvolver um sistema de gerenciamento de perfis e séries assistidas, inspirado na plataforma Netflix, utilizando a linguagem C. O requisito fundamental era a aplicação de listas duplamente encadeadas como estrutura de dados principal para armazenar e manipular as informações.

A solução foi projetada com base em uma estrutura de listas aninhadas:

Uma lista principal duplamente encadeada e circular para armazenar os perfis dos usuários. Cada nó (NoPerfil) contém o nome do usuário e um ponteiro para sua própria lista de séries.

Dentro de cada nó de perfil, uma segunda lista duplamente encadeada e circular armazena as séries (NoSerie) que aquele usuário assistiu, incluindo título, número de temporadas e um status de "favorita".

Optou-se por uma abordagem modular, separando a lógica de manipulação da estrutura de dados (netflix.c e netflix.h) da camada de interação com o usuário (main.c). O sistema também implementa a persistência de dados através da leitura de um arquivo dados.txt na inicialização, permitindo que o estado da aplicação seja salvo entre execuções. O estilo de programação adotado não utiliza structs descritoras para as listas; em vez disso, as funções que modificam a lista (como inserção e remoção) recebem um ponteiro para o nó inicial e retornam o novo ponteiro inicial, garantindo a integridade da lista.

Documentação do Código
As funções foram implementadas para prover as operações básicas de uma lista (inclusão, busca, remoção), além de funcionalidades específicas ao tema Netflix.

Funções Básicas de Inclusão
NoPerfil* inserirPerfil(NoPerfil* lista, const char* nomeUsuario): Aloca um novo nó de perfil e o insere no início da lista circular de perfis. A função recebe o ponteiro do início atual da lista e retorna o ponteiro para o novo nó, que se torna o novo início.

NoSerie* inserirSerie(NoSerie* lista, ...): De forma análoga, aloca um novo nó de série e o insere na lista circular de séries de um determinado perfil. A inserção é feita no final, mantendo o início da lista original.

Funções Básicas de Busca
NoPerfil* buscarPerfil(NoPerfil* lista, const char* nomeUsuario): Percorre a lista circular de perfis a partir do nó inicial usando um laço do-while. Compara o nome de usuário de cada nó com o valor buscado. Retorna um ponteiro para o nó encontrado ou NULL se não houver correspondência.

NoSerie* buscarSerie(NoSerie* lista, const char* titulo): Opera de maneira idêntica à busca de perfil, mas percorre a lista de séries de um usuário específico em busca de um título.

Funções Básicas de Remoção
NoPerfil* removerPerfil(NoPerfil* lista, const char* nomeUsuario): Localiza o perfil a ser removido usando buscarPerfil. Um passo crucial desta função é invocar liberarListaSeries sobre a lista de séries do perfil, garantindo que toda a memória aninhada seja liberada antes de remover o nó do perfil em si. A função então reajusta os ponteiros proximo e anterior dos nós vizinhos e libera a memória do nó removido. Retorna o novo ponteiro de início da lista, que pode mudar caso o nó removido fosse o antigo início.

Funções Adicionais
void favoritarSerie(NoSerie* serie): Esta função demonstra a manipulação de dados dentro de um nó existente. Ela recebe um ponteiro direto para um nó de série e inverte seu campo favorita (de 1 para 0 ou vice-versa), simulando a ação de favoritar ou desfavoritar um título.

void gerarRelatorioGeral(NoPerfil* lista): Atravessa a lista principal de perfis. Para cada perfil encontrado, invoca a função imprimirSeries para exibir a lista de séries aninhada correspondente. Essa funcionalidade gera uma visão completa de todos os dados cadastrados no sistema.

NoPerfil* carregarDadosDoArquivo(NoPerfil* lista, ...): Responsável pela persistência. Lê o arquivo dados.txt, interpretando uma formatação simples com tags ([PERFIL], [SERIES]) para popular a estrutura de listas na memória no momento em que o programa é iniciado.

Exemplos de Uso
A seguir, demonstrações de operações realizadas pelo programa, com base no arquivo dados.txt fornecido.

1. Inicialização e Relatório Geral
Ao iniciar, o programa lê o arquivo dados.txt e carrega os perfis "Leo" e "Caue". Se o usuário escolher a opção 6 (Gerar relatório geral), a saída será:

Dados carregados com sucesso do arquivo 'dados.txt'.

--- MENU DE GERENCIAMENTO NETFLIX ---
[...]
Escolha uma opcao: 6

=========================================
        RELATORIO GERAL - NETFLIX
=========================================

PERFIL: @Caue
-----------------------------------------
  -> Titulo: Peaky Blinders | Temporadas: 5 | Favorita: Sim
  -> Titulo: Breaking Bad | Temporadas: 2 | Favorita: Nao

PERFIL: @Leo
-----------------------------------------
  -> Titulo: Stranger Things | Temporadas: 4 | Favorita: Sim
  -> Titulo: The Witcher | Temporadas: 3 | Favorita: Nao
  -> Titulo: Dark | Temporadas: 3 | Favorita: Sim

=========================================
2. Adicionando uma Nova Série a um Perfil
O usuário decide adicionar a série "Better Call Saul" ao perfil de "Caue" usando a opção 3.

Entrada de dados:

Escolha uma opcao: 3

Digite o nome do perfil para adicionar a serie: Caue

Digite o titulo da serie: Better Call Saul

Digite o numero de temporadas: 6

Saída obtida:

Serie 'Better Call Saul' adicionada ao perfil 'Caue'.
Ao listar as séries de Caue (opção 4), o novo item aparece na lista.

3. Removendo um Perfil
O usuário remove o perfil "Leo" do sistema utilizando a opção 2.

Entrada de dados:

Escolha uma opcao: 2

Digite o nome do perfil a ser removido: Leo

Saída obtida:

Perfil 'Leo' removido com sucesso!
Se um novo relatório geral for gerado (opção 6), o perfil "Leo" e todas as suas séries não serão mais exibidos, demonstrando que a remoção e a liberação de memória em cascata funcionaram corretamente.

Conclusão
A implementação deste projeto foi uma experiência prática enriquecedora para solidificar os conceitos de estruturas de dados, especialmente a manipulação de listas duplamente encadeadas circulares e aninhadas.

Desafios Enfrentados:
O principal desafio foi o correto gerenciamento de ponteiros e de memória. A lógica de remoção de um nó em uma lista circular, que exige o tratamento cuidadoso dos ponteiros anterior e proximo dos nós vizinhos, demandou atenção especial. O maior ponto de complexidade, no entanto, foi a operação de removerPerfil, que necessitava primeiramente liberar toda a memória da lista de séries interna antes de liberar o nó do perfil em si, um processo crucial para evitar vazamentos de memória (memory leaks).

Principais Lições Aprendidas:

A importância da Modularização: Separar a lógica de dados (netflix.c) da lógica de interface (main.c) provou ser uma estratégia fundamental para manter o código organizado, legível e fácil de depurar.

Gerenciamento de Memória em C: O projeto reforçou a disciplina de alocar (malloc) e liberar (free) memória de forma consciente. A complexidade das listas aninhadas tornou evidente como um pequeno descuido na ordem de liberação pode levar a erros graves.

Aplicação Prática de Estruturas de Dados: Foi possível observar como uma estrutura de dados teórica pode modelar de forma eficaz um problema do mundo real. A capacidade de aninhar listas duplamente encadeadas se mostrou uma ferramenta poderosa para representar relações hierárquicas (um perfil possui uma lista de séries).

Em suma, o trabalho não apenas cumpriu os requisitos técnicos, mas também proporcionou um aprendizado valioso sobre boas práticas de programação, design de software e a resolução de problemas complexos com estruturas de dados dinâmicas.
