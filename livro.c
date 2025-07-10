#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

Lista* ini_lista(int capacidadeI){
    Lista *lista = (Lista*) malloc (sizeof(Lista));
    if (lista == NULL){
        printf("Não foi possivel alocar memória para a lista.\n");
        exit(1);
    }
    
    lista->livro = (Livro*) malloc(capacidadeI * sizeof(Livro));
    if (lista->livro == NULL){
        printf("Não foi possivel alocar memória para os livros.\n");
        free(lista);
        exit(1);
    }
    
    lista->tamanho = 0;
    lista->capacidade = capacidadeI;
    
    return lista;
}

void inserir_livro(Lista *lista, char *titulo, char *autor, int ano, float preco){
    if (lista->tamanho >= lista->capacidade){
        int capacidade_att = lista->capacidade * 2;
        Livro *novo_v = (Livro*) realloc (lista->livro, capacidade_att * sizeof(Livro));
        if (novo_v == NULL) {
            printf("Não foi possivel realocar a memória.\n");
            return;
        }
        lista->livro = novo_v;
        lista->capacidade = capacidade_att;
    }


   Livro novo_livro;
    strncpy(novo_livro.titulo, titulo, sizeof(novo_livro.titulo) - 1);
    strncpy(novo_livro.autor, autor, sizeof(novo_livro.autor) - 1);
    novo_livro.titulo[sizeof(novo_livro.titulo) - 1] = '\0';
    novo_livro.autor[sizeof(novo_livro.autor) - 1] = '\0';
    novo_livro.ano = ano;
    novo_livro.preco = preco;

    lista->livro[lista->tamanho] = novo_livro;
    lista->tamanho++;
}

int excluir_livro(Lista *lista, char *titulo){
    if (lista == NULL || lista->tamanho == 0) {
        return 0;  
    }
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->livro[i].titulo, titulo) == 0) {
            for (int j = i; j < lista->tamanho - 1; j++) {
                lista->livro[j] = lista->livro[j + 1];
            }

            lista->tamanho--;
            printf("Livro removido com sucesso: %s\n", titulo);
            return 1;
        }
    }
    return 0;
}

void catalogo(Lista *lista){
    if (lista == NULL || lista->tamanho == 0) {
        printf("Nenhum livro cadastrado no catalogo.\n");
        return;
    }
    printf("\nLista de Livros:\n");
    
    for (int i = 0; i < lista->tamanho; i++){
        Livro l = lista->livro[i];
        printf("Título : %s\n", l.titulo);
        printf("Autor  : %s\n", l.autor);
        printf("Ano    : %d\n", l.ano);
        printf("Preço  : R$ %.2f\n", l.preco);
    }
}

void Liberar_lista(Lista *lista){
    if (lista != NULL){
        free(lista->livro);
        free(lista);
    }
}