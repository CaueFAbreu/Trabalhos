#ifndef NETFLIX_H
#define NETFLIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoSerie {
    char titulo[100];
    int temporadas;
    int favorita;
    struct NoSerie* proximo;
    struct NoSerie* anterior;
} NoSerie;

typedef struct NoPerfil {
    char nomeUsuario[50];
    NoSerie* seriesAssistidas;
    struct NoPerfil* proximo;
    struct NoPerfil* anterior;
} NoPerfil;


// Protótipos de Funções de Séries

NoSerie* inserirSerie(NoSerie* lista, const char* titulo, int temporadas, int favorita);
NoSerie* removerSerie(NoSerie* lista, const char* titulo);
NoSerie* buscarSerie(NoSerie* lista, const char* titulo);
void favoritarSerie(NoSerie* serie);
void imprimirSeries(NoSerie* lista);
NoSerie* liberarListaSeries(NoSerie* lista);


// Protótipos de Funções de Perfis

NoPerfil* inserirPerfil(NoPerfil* lista, const char* nomeUsuario);
NoPerfil* removerPerfil(NoPerfil* lista, const char* nomeUsuario);
NoPerfil* buscarPerfil(NoPerfil* lista, const char* nomeUsuario);
void gerarRelatorioGeral(NoPerfil* lista);
NoPerfil* liberarListaPerfis(NoPerfil* lista);

// Protótipos de Funções de Arquivo
NoPerfil* carregarDadosDoArquivo(NoPerfil* lista, const char* nomeArquivo);

#endif