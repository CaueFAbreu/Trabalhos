#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

void limpeza() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int opcao;
    Lista *lista = ini_lista(2);

    do {
        printf("\n===== MENU DO USUÁRIO =====\n");
        printf("1. Inserir livro\n");
        printf("2. Excluir livro do catalogo\n");
        printf("3. Acessar catalogo de livros\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpeza();

        switch (opcao) {
            case 1: {
                char titulo[30], autor[30];
                int ano;
                float preco;

                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Digite o autor do livro: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0';

                printf("Digite o ano: ");
                scanf("%d", &ano);
                limpeza();

                printf("Digite o preço: ");
                scanf("%f", &preco);
                limpeza();

                inserir_livro(lista, titulo, autor, ano, preco);
                printf("Livro inserido com sucesso!\n");
                break;
            }

            case 2: {
                char titulo[30];
                printf("Digite o título do livro a ser removido: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                if (!excluir_livro(lista, titulo)) {
                    printf("Livro não encontrado.\n");
                }
                break;
            }

            case 3:
                catalogo(lista);
                break;

            case 4:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 4);

    Liberar_lista(lista);
    return 0;
}
