#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

#include <iostream>
using namespace std;

#include <queue>
#include <map>

#include "memoriaPrincipal.h"
#include "memoriaCache.h"
#include "tipo_sub.h"

void mapea_direto(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha);

void mapea_totalmenteAssociativo(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha, int sub, queue<int> &fifo, map<int, int> &lfu, int &ciclo);

void mapea_parcialmenteAssociativo(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha, int sub, int n_conj, int **v, int &cont);


#endif