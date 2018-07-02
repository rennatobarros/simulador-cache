#include "mapeamento.h"

void mapea_direto(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha){
	int linha_cache = bloco_cache % linha;

	if (c[linha_cache].getBloco() == bloco_cache){
		cout << "HIT" << endl;
	}else{
		c[linha_cache].setBloco(m[bloco_cache].getBloco());
		c[linha_cache].setEndereco(m[bloco_cache].getEndereco());
		c[linha_cache].setConteudo(m[bloco_cache].getConteudo());
		cout << "MISS => Alocado na linha " << linha_cache << endl;
	}
}

void mapea_totalmenteAssociativo(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha, int sub, queue<int> &fifo, map<int, int> &lfu, int &ciclo){
	if (sub == 1){
		total_aleatorio(c, m, linha, bloco_cache);
	}else if(sub == 2){
		total_fifo(c, m, linha, bloco_cache, fifo);
	}else if(sub == 3){
		total_lfu(c, m, linha, bloco_cache, lfu);
	}else if(sub == 4){
		total_lru(c, m, linha, bloco_cache, lfu, ciclo);
	}
}

void mapea_parcialmenteAssociativo(memoriaCache *c, memoriaPrincipal *m, int bloco_cache, int linha, int sub, int n_conj, int **v, int &cont){
	if (sub == 1){
		parcial_aleatorio(c, m, linha, bloco_cache, n_conj);
	}else if(sub == 2){
		parcial_fifo(c, m, linha, bloco_cache, n_conj, v, cont);
	}else if(sub == 3){
		parcial_lfu(c, m, linha, bloco_cache, n_conj, v);
	}else if(sub == 4){
		parcial_lru(c, m, linha, bloco_cache, n_conj, v, cont);
	}
}