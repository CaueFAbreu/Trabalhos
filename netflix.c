#include "netflix.h"

// --- Implementação das Funções da Lista de Séries ---

NoSerie* inserirSerie(NoSerie* lista, const char* titulo, int temporadas, int favorita) {
    NoSerie* novoNo = (NoSerie*)malloc(sizeof(NoSerie));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    strcpy(novoNo->titulo, titulo);
    novoNo->temporadas = temporadas;
    novoNo->favorita = favorita;

    if (lista == NULL) {
        novoNo->proximo = novoNo;
        novoNo->anterior = novoNo;
        return novoNo;
    }

    NoSerie* ultimo = lista->anterior;
    novoNo->proximo = lista;
    novoNo->anterior = ultimo;
    lista->anterior = novoNo;
    ultimo->proximo = novoNo;

    return lista;
}

NoSerie* buscarSerie(NoSerie* lista, const char* titulo) {
    if (lista == NULL) {
        return NULL;
    }
    NoSerie* atual = lista;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != lista);
    return NULL;
}

void favoritarSerie(NoSerie* serie) {
    if (serie != NULL) {
        serie->favorita = !serie->favorita; // Inverte
        printf("Status de favorito da serie '%s' alterado com sucesso!\n", serie->titulo);
    }
}

void imprimirSeries(NoSerie* lista) {
    if (lista == NULL) {
        printf("  -> Nenhuma serie assistida.\n");
        return;
    }
    NoSerie* atual = lista;
    do {
        printf("  -> Titulo: %s | Temporadas: %d | Favorita: %s\n",
               atual->titulo,
               atual->temporadas,
               atual->favorita ? "Sim" : "Nao");
        atual = atual->proximo;
    } while (atual != lista);
}

NoSerie* liberarListaSeries(NoSerie* lista) {
    if (lista == NULL) {
        return NULL;
    }
    NoSerie* atual = lista;
    NoSerie* proximo;
    do {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    } while (atual != lista);
    return NULL;
}

// --- Implementação das Funções da Lista de Perfis ---

NoPerfil* inserirPerfil(NoPerfil* lista, const char* nomeUsuario) {
    NoPerfil* novoNo = (NoPerfil*)malloc(sizeof(NoPerfil));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    strcpy(novoNo->nomeUsuario, nomeUsuario);
    novoNo->seriesAssistidas = NULL;

    if (lista == NULL) {
        novoNo->proximo = novoNo;
        novoNo->anterior = novoNo;
        return novoNo;
    }

    NoPerfil* ultimo = lista->anterior;
    novoNo->proximo = lista;
    novoNo->anterior = ultimo;
    lista->anterior = novoNo;
    ultimo->proximo = novoNo;
    
    return novoNo;
}

NoPerfil* removerPerfil(NoPerfil* lista, const char* nomeUsuario) {
    NoPerfil* noParaRemover = buscarPerfil(lista, nomeUsuario);
    if (noParaRemover == NULL) {
        return lista; // Retorna a lista original se não encontrou
    }

    // Libera a lista de séries antes de remover o perfil
    noParaRemover->seriesAssistidas = liberarListaSeries(noParaRemover->seriesAssistidas);

    if (noParaRemover->proximo == noParaRemover) {
        free(noParaRemover);
        return NULL;
    }

    noParaRemover->anterior->proximo = noParaRemover->proximo;
    noParaRemover->proximo->anterior = noParaRemover->anterior;

    NoPerfil* novaLista = lista;
    if (noParaRemover == lista) {
        novaLista = lista->proximo;
    }
    
    free(noParaRemover);
    return novaLista;
}

NoPerfil* buscarPerfil(NoPerfil* lista, const char* nomeUsuario) {
    if (lista == NULL) {
        return NULL;
    }
    NoPerfil* atual = lista;
    do {
        if (strcmp(atual->nomeUsuario, nomeUsuario) == 0) {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != lista);

    return NULL;
}

void gerarRelatorioGeral(NoPerfil* lista) {
    printf("\n=========================================\n");
    printf("        RELATORIO GERAL - NETFLIX\n");
    printf("=========================================\n");
    if (lista == NULL) {
        printf("Nenhum perfil cadastrado no sistema.\n");
        printf("=========================================\n");
        return;
    }
    
    NoPerfil* atual = lista;
    do {
        printf("\nPERFIL: @%s\n", atual->nomeUsuario);
        printf("-----------------------------------------\n");
        imprimirSeries(atual->seriesAssistidas);
        atual = atual->proximo;
    } while (atual != lista);
    printf("\n=========================================\n");
}


NoPerfil* liberarListaPerfis(NoPerfil* lista) {
    if (lista == NULL) {
        return NULL;
    }
    NoPerfil* atual = lista;
    NoPerfil* proximo;
    do {
        proximo = atual->proximo;
        // Libera a lista interna de series de cada perfil
        atual->seriesAssistidas = liberarListaSeries(atual->seriesAssistidas);
        free(atual);
        atual = proximo;
    } while (atual != lista);

    return NULL;
}


// --- Implementação da Leitura de Arquivo ---

NoPerfil* carregarDadosDoArquivo(NoPerfil* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }

    char linha[256];
    NoPerfil* perfilAtual = NULL;
    int lendoSeries = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\r\n")] = 0; //Remove quebra de linha

        if (strcmp(linha, "[PERFIL]") == 0) {
            lendoSeries = 0;
            if (fgets(linha, sizeof(linha), arquivo)) {
                linha[strcspn(linha, "\r\n")] = 0;
                lista = inserirPerfil(lista, linha);
                perfilAtual = lista; // O novo perfil é o novo início
            }
        } else if (strcmp(linha, "[SERIES]") == 0) {
            lendoSeries = 1;
        } else if (strcmp(linha, "[FIM_PERFIL]") == 0) {
            lendoSeries = 0;
            perfilAtual = NULL;
        } else if (lendoSeries && perfilAtual != NULL) {
            char titulo[100];
            int temporadas, favorita;
            
            char* token = strtok(linha, ";"); //Quebra a string no ';'
            if (token) strcpy(titulo, token);
            token = strtok(NULL, ";"); 
            if (token) temporadas = atoi(token); //Converte uma string de numero para seu valor inteiro
            token = strtok(NULL, ";");
            if (token) favorita = atoi(token);
            
            perfilAtual->seriesAssistidas = inserirSerie(perfilAtual->seriesAssistidas, titulo, temporadas, favorita);
        }
    }
    fclose(arquivo);
    printf("Dados carregados com sucesso do arquivo '%s'.\n", nomeArquivo);
    return lista;
}