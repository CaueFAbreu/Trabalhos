#ifndef LIVRO_H
#define LIVRO_H

typedef struct {
    char titulo[30], autor[30];
    int ano;
    float preco; 
} Livro;

typedef struct {
    Livro *livro;
    int tamanho;
    int capacidade;
} Lista;

Lista* ini_lista(int capacidadeI);
void inserir_livro(Lista *lista, char *titulo, char *autor, int ano, float preco);
int excluir_livro(Lista *lista, char *titulo);
void catalogo(Lista *lista);

void Liberar_lista(Lista *lista);

#endif