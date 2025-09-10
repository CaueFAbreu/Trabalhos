#include "netflix.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n--- MENU DE GERENCIAMENTO NETFLIX ---\n");
    printf("1. Adicionar novo perfil\n");
    printf("2. Remover um perfil\n");
    printf("3. Adicionar serie a um perfil\n");
    printf("4. Listar series de um perfil\n");
    printf("5. Alterar status de 'Favorita' de uma serie\n");
    printf("6. Gerar relatorio geral de todos os perfis\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    NoPerfil* listaDePerfis = NULL;

    listaDePerfis = carregarDadosDoArquivo(listaDePerfis, "dados.txt");

    int opcao;
    char nome[100];
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: {
                printf("Digite o nome do novo perfil: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                if (buscarPerfil(listaDePerfis, nome) != NULL) {
                    printf("Erro: Ja existe um perfil com este nome.\n");
                } else {
                    listaDePerfis = inserirPerfil(listaDePerfis, nome);
                    printf("Perfil '%s' adicionado com sucesso!\n", nome);
                }
                break;
            }
            case 2: {
                printf("Digite o nome do perfil a ser removido: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                int sucesso = (buscarPerfil(listaDePerfis, nome) != NULL);
                listaDePerfis = removerPerfil(listaDePerfis, nome);

                if (sucesso) {
                    printf("Perfil '%s' removido com sucesso!\n", nome);
                } else {
                    printf("Erro: Perfil '%s' nao encontrado.\n", nome);
                }
                break;
            }
            case 3: {
                printf("Digite o nome do perfil para adicionar a serie: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                NoPerfil* perfilNode = buscarPerfil(listaDePerfis, nome);
                if (perfilNode == NULL) {
                    printf("Erro: Perfil '%s' nao encontrado.\n", nome);
                } else {
                    char titulo[100];
                    int temporadas;
                    
                    printf("Digite o titulo da serie: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = 0;

                    printf("Digite o numero de temporadas: ");
                    scanf("%d", &temporadas);
                    limparBuffer();

                    perfilNode->seriesAssistidas = inserirSerie(perfilNode->seriesAssistidas, titulo, temporadas, 0);
                    printf("Serie '%s' adicionada ao perfil '%s'.\n", titulo, nome);
                }
                break;
            }
            case 4: {
                printf("Digite o nome do perfil para listar as series: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                NoPerfil* perfilNode = buscarPerfil(listaDePerfis, nome);
                 if (perfilNode == NULL) {
                    printf("Erro: Perfil '%s' nao encontrado.\n", nome);
                } else {
                    printf("\n--- Series assistidas por @%s ---\n", nome);
                    imprimirSeries(perfilNode->seriesAssistidas);
                }
                break;
            }
            case 5: {
                printf("Digite o nome do perfil: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                NoPerfil* perfilNode = buscarPerfil(listaDePerfis, nome);
                if (perfilNode == NULL) {
                    printf("Erro: Perfil '%s' nao encontrado.\n", nome);
                } else {
                    char tituloSerie[100];
                    printf("Digite o titulo da serie para favoritar/desfavoritar: ");
                    fgets(tituloSerie, sizeof(tituloSerie), stdin);
                    tituloSerie[strcspn(tituloSerie, "\n")] = 0;

                    NoSerie* serieNode = buscarSerie(perfilNode->seriesAssistidas, tituloSerie);
                    if (serieNode == NULL) {
                        printf("Erro: Serie '%s' nao encontrada nesse perfil.\n", tituloSerie);
                    } else {
                        favoritarSerie(serieNode);
                    }
                }
                break;
            }
            case 6: {
                gerarRelatorioGeral(listaDePerfis);
                break;
            }
            case 0:
                printf("Saindo do programa. Liberando memoria...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    listaDePerfis = liberarListaPerfis(listaDePerfis);
    printf("Memoria liberada. Ate mais!\n");

    return 0;
}