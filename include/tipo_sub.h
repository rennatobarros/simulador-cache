#ifndef TIPO_SUB_H
#define TIPO_SUB_H

#include <iostream>
using namespace std;

#include <queue>
#include <map>

#include <ctime>
#include <cstdlib>

#include <utility>

#include "memoriaPrincipal.h"
#include "memoriaCache.h"

void total_aleatorio(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache);

void total_fifo(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, queue<int> &fifo);

void total_lfu(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, map<int, int> &lfu);

void total_lru(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, map<int, int> &lru, int &ciclo);

void parcial_aleatorio(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj);

void parcial_fifo(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v, int &cont);

void parcial_lfu(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v);

void parcial_lru(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v, int &cont);

#endif