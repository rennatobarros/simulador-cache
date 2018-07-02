#include "tipo_sub.h"

void total_aleatorio(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache){
	bool hit = false, vazio = false;
	int prox;

	/** Verifica se o bloco atual é o bloco a ser preenchido*/
	for(int i = 0; i < linha ; i++) {
		if(c[i].getBloco() == bloco_cache) {
			hit = true;
		}
	}

	/** Caso hit não seja verdadeiro, salva o valor da posição disponivel */
	if(!hit){
		for(int i = 0; i < linha; i++) {
			if(c[i].getBloco() == -1) {
				vazio = true;
				prox = i;
				break;
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;

		} else {
			/** Aloca numa posição aleatória */
			srand(time(NULL));
			
			int r = rand() % linha;
			c[r].setBloco(m[bloco_cache].getBloco());
			c[r].setEndereco(m[bloco_cache].getEndereco());
			c[r].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << r << endl;
		}

	} else {
		cout << "HIT" << endl;
	}
}

void total_fifo(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, queue<int> &fifo){
	bool hit = false, vazio = false;
	int prox;

	for(int i = 0; i < linha ; i++) {
		if(c[i].getBloco() == bloco_cache) {
			hit = true;
		}
	}

	if(!hit){
		for(int i = 0; i < linha; i++) {
			if(c[i].getBloco() == -1) {
				vazio = true;
				prox = i;
				break;
			}
		}


		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;
			fifo.push(bloco_cache);

		} else {
			int r = fifo.front();

			for(int i = 0; i < linha; i++) {
				if(c[i].getBloco() == r) {
					c[i].setBloco(m[bloco_cache].getBloco());
					c[i].setEndereco(m[bloco_cache].getEndereco());
					c[i].setConteudo(m[bloco_cache].getConteudo());
					cout << "MISS => bloco alocado na linha " << i << endl;
					fifo.pop();
					fifo.push(bloco_cache);
				}
			}
		}

	} else {
		cout << "HIT" << endl;
	}
}

void total_lfu(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, map<int, int> &lfu){
	bool hit = false, vazio = false;
	int prox;

	for(int i = 0; i < linha ; i++) {
			if(c[i].getBloco() == bloco_cache) {
				hit = true;
				lfu[bloco_cache] += 1;

			}
		}

		if(!hit){
			for(int i = 0; i < linha; i++) {
				if(c[i].getBloco() == -1) {
					vazio = true;
					prox = i;
					break;
				}
			}


			if(vazio){
				c[prox].setBloco(m[bloco_cache].getBloco());
				c[prox].setEndereco(m[bloco_cache].getEndereco());
				c[prox].setConteudo(m[bloco_cache].getConteudo());
				cout << "MISS => bloco alocado na linha " << prox << endl;

				lfu.insert(pair<int, int>(bloco_cache, 1));

			} else {
				map<int, int>::iterator it = lfu.begin();
				int b = it->first;
				int menor = it->second;

				for(it = lfu.begin(); it != lfu.end(); ++it) {
					if(menor > it->second) {
						menor = it->second;
						b = it->first;
					}
				}

				int r = b;

				for(int i = 0; i < linha; i++) {
					if(c[i].getBloco() == r) {
						c[i].setBloco(m[bloco_cache].getBloco());
						c[i].setEndereco(m[bloco_cache].getEndereco());
						c[i].setConteudo(m[bloco_cache].getConteudo());
						cout << "MISS => bloco alocado na linha " << i << endl;
						lfu.erase(r);
						lfu.insert(pair<int, int>(bloco_cache, 1));
					}
				}
			}

		} else {
			cout << "HIT" << endl;
		}
}


void total_lru(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, map<int, int> &lru, int &ciclo){
	bool hit = false, vazio = false;
	int prox;

	for(int i = 0; i < linha ; i++) {
		if(c[i].getBloco() == bloco_cache) {
			hit = true;
			lru[bloco_cache] = ciclo++;
		}
	}

	if(!hit){
		for(int i = 0; i < linha; i++) {
			if(c[i].getBloco() == -1) {
				vazio = true;
				prox = i;
				break;
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;
			lru.insert(pair<int, int>(bloco_cache, ciclo++));

		} else {
			map<int, int>::iterator it = lru.begin();
			int b = it->first;
			int menor = it->second;
			cout << menor << endl;
			for(it = lru.begin(); it != lru.end(); ++it) {
				if(menor > it->second) {
					menor = it->second;
					b = it->first;
				}
			}

			int r = b;
			for(int i = 0; i < linha; i++) {
				if(c[i].getBloco() == r) {
					c[i].setBloco(m[bloco_cache].getBloco());
					c[i].setEndereco(m[bloco_cache].getEndereco());
					c[i].setConteudo(m[bloco_cache].getConteudo());
					cout << "MISS => bloco alocado na linha " << i << endl;
					lru.erase(r);
					lru.insert(pair<int, int>(bloco_cache, ciclo));
					ciclo++;
				}
			}
		}
	} else {
		cout << "HIT" << endl;
	}
}

void parcial_aleatorio(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj){
	bool hit = false, vazio = false;
	int prox;

	int divisoes = linha / n_conj;

	int way = bloco_cache % n_conj;

	cout << "\nConjunto: " << way << endl;

	for(int i = 0; i < n_conj ; i++) {
		if(i == way) {
			for(int j = i; j < divisoes + i; j++) {
				if(c[j + i ].getBloco() == bloco_cache) {
					hit = true;
				}
			}
		}
	}

	if(!hit){
		for(int i = 0; i < n_conj ; i++) {
			if(i == way) {
				for(int j = i; j < divisoes + i; j++) {
					if(c[ j + i ].getBloco() == -1) {
						vazio = true;
						prox = i + j;
						break;
					}
				}
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;

		} else {
			int r;
			
			srand(time(NULL));

			for(int i = 0; i < n_conj; i++) {
				if(i == way) {
					r = rand() % n_conj + ( i + way ) ;
				}
			}

			c[r].setBloco(m[bloco_cache].getBloco());
			c[r].setEndereco(m[bloco_cache].getEndereco());
			c[r].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << r << endl;
		}

	} else {
		cout << "HIT" << endl;
	}
}

void parcial_fifo(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v, int &cont){
	bool hit = false, vazio = false;
	int prox;

	int divisoes = linha / n_conj;

	int way = bloco_cache % n_conj;

	cout << "\nConjunto: " << way << endl;

	for(int i = 0; i < n_conj ; i++) {
		if(i == way) {
			for(int j = i; j < divisoes + i; j++) {
				if(c[j + i ].getBloco() == bloco_cache) {
					hit = true;
				}
			}
		}
	}

	if(!hit){
		for(int i = 0; i < n_conj ; i++) {
			if(i == way) {
				for(int j = i; j < divisoes + i; j++) {
					if(c[ j + i ].getBloco() == -1) {
						vazio = true;
						prox = i + j;
						break;
					}
				}
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;
			v[prox][0] = bloco_cache;
			v[prox][1] = cont++;

		} else {
			int b;
			int menor;

			for(int i = 0; i < n_conj ; i++) {
				if(i == way) {
					menor = v[i+way][1];
					b = v[i+way][0];
					for(int j = i + way; j < n_conj + way + i; j++){
						if(v[j][1] < menor) {
							menor = v[j][1];
							b = v[j][0];
						}
					}
				}
			}

			int r = b;

			for(int i = 0; i < n_conj; i++){
				if(i == way) {
					for(int j = (i + way); j < n_conj + (i + way); j++) {
						if(c[j].getBloco() == r) {
							c[j].setBloco(m[bloco_cache].getBloco());
							c[j].setEndereco(m[bloco_cache].getEndereco());
							c[j].setConteudo(m[bloco_cache].getConteudo());
							cout << "MISS => bloco alocado na linha " << j << endl;
					
							v[j][0] = bloco_cache;
							v[j][1] = cont++;
					
						}
					}
				}
			}
		}
	} else {
		cout << "HIT" << endl;
	}
}

void parcial_lfu(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v){
	bool hit = false, vazio = false;
	int prox;

	int divisoes = linha / n_conj;

	int way = bloco_cache % n_conj;

	cout << "\nConjunto: " << way << endl;

	for(int i = 0; i < n_conj ; i++) {
		if(i == way) {
			for(int j = i; j < divisoes + i; j++) {
				if(c[j + i ].getBloco() == bloco_cache) {
					hit = true;
					v[j + i][1] += 1;
				}
			}
		}
	}

	if(!hit){
		for(int i = 0; i < n_conj ; i++) {
			if(i == way) {
				for(int j = i; j < divisoes + i; j++) {
					if(c[ j + i ].getBloco() == -1) {
						vazio = true;
						prox = i + j;
						break;
					}
				}
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;

			v[prox][0] = bloco_cache;
			v[prox][1] = 1;

		} else {
			int b;
			int menor;

			for(int i = 0; i < n_conj ; i++) {
				if(i == way) {
					menor = v[i+way][1];
					b = v[i+way][0];
					for(int j = i + way; j < n_conj + way + i; j++){
						if(v[j][1] < menor) {
							menor = v[j][1];
							b = v[j][0];
						}
					}
				}
			}

			int r = b;

			for(int i = 0; i < n_conj; i++){
				if(i == way) {
					for(int j = (i + way); j < n_conj + (i + way); j++) {
						if(c[j].getBloco() == r) {
							c[j].setBloco(m[bloco_cache].getBloco());
							c[j].setEndereco(m[bloco_cache].getEndereco());
							c[j].setConteudo(m[bloco_cache].getConteudo());
							cout << "MISS => bloco alocado na linha " << j << endl;
					
							v[j][0] = bloco_cache;
							v[j][1] = 1;
					
						}
					}
				}
			}
		}
	} else {
		cout << "HIT" << endl;
	}
}

void parcial_lru(memoriaCache *c, memoriaPrincipal *m, int linha, int bloco_cache, int n_conj, int **v, int &cont){
	bool hit = false, vazio = false;
	int prox;

	int divisoes = linha / n_conj;

	int way = bloco_cache % n_conj;

	cout << "\nConjunto: " << way << endl;

	for(int i = 0; i < n_conj ; i++) {
		if(i == way) {
			for(int j = i; j < divisoes + i; j++) {
				if(c[j + i ].getBloco() == bloco_cache) {
					hit = true;
					v[j + i][1] = cont++;
				}
			}
		}
	}

	if(!hit){
		for(int i = 0; i < n_conj ; i++) {
			if(i == way) {
				for(int j = i; j < divisoes + i; j++) {
					if(c[ j + i ].getBloco() == -1) {
						vazio = true;
						prox = i + j;
						break;
					}
				}
			}
		}

		if(vazio){
			c[prox].setBloco(m[bloco_cache].getBloco());
			c[prox].setEndereco(m[bloco_cache].getEndereco());
			c[prox].setConteudo(m[bloco_cache].getConteudo());
			cout << "MISS => bloco alocado na linha " << prox << endl;
			v[prox][0] = bloco_cache;
			v[prox][1] = cont++;

		} else {
			int b;
			int menor;

			for(int i = 0; i < n_conj ; i++) {
				if(i == way) {
					menor = v[i+way][1];
					b = v[i+way][0];
					for(int j = i + way; j < n_conj + way + i; j++){
						if(v[j][1] < menor) {
							menor = v[j][1];
							b = v[j][0];
						}
					}
				}
			}

			int r = b;

			for(int i = 0; i < n_conj; i++){
				if(i == way) {
					for(int j = (i + way); j < n_conj + (i + way); j++) {
						if(c[j].getBloco() == r) {
							c[j].setBloco(m[bloco_cache].getBloco());
							c[j].setEndereco(m[bloco_cache].getEndereco());
							c[j].setConteudo(m[bloco_cache].getConteudo());
							cout << "MISS => bloco alocado na linha " << j << endl;
					
							v[j][0] = bloco_cache;
							v[j][1] = cont++;
					
						}
					}
				}
			}
		}
	} else {
		cout << "HIT" << endl;
	}
}