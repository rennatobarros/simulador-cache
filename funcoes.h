#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
using namespace std;

/** Estrutura pilha para ser utlizado método FIFO*/
#include <queue>

#include <map>

#include <fstream>
#include <sstream>
#include <string>

#include "memoriaCache.h"
#include "memoriaPrincipal.h"
#include "mapeamento.h"

void lerArquivo(int &t_bloco, int &linha, int &bloco, int &mapea, int &n_conj, int &sub, int &p_escrita);

void init();

void imprime(memoriaCache *c, memoriaPrincipal *m, int t_bloco, int bloco, int linha);

void initMemPrinc(memoriaPrincipal *m, int t_bloco, int bloco);

void initMemCache(memoriaCache *c, int t_bloco, int linha);

#endif