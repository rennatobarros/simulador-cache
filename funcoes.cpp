#include "funcoes.h"

void lerArquivo(int &t_bloco, int &linha, int &bloco, int &mapea, int &n_conj, int &sub, int &p_escrita){
	string ler_linha;
	int i = 0;

	ifstream arquivo("config.txt");

	if (arquivo.bad()){
		cout << "Erro!";
	}

	while(getline(arquivo, ler_linha)){
		i++;
	}

	/** Verificando se o arquivo de configuração está correto */
	if (i != 7){
		cout << "Arquivo de configuração incompleto!";
		exit(1);
	}

	arquivo.clear();
	arquivo.seekg(arquivo.beg);

	arquivo >> t_bloco;
	arquivo >> linha;
	arquivo >> bloco;
	arquivo >> mapea;
	arquivo >> n_conj;
	arquivo >> sub;
	arquivo >> p_escrita;
}

void init(){
	int t_bloco, linha, bloco, mapea, n_conj, sub, p_escrita, endereco, ciclo = 0;
	string comando = "", elemento, linha_comando;
	queue<int> fifo;
	map<int, int> lfu;

	lerArquivo(t_bloco, linha, bloco, mapea, n_conj, sub, p_escrita);

	int **v = new int*[linha];
	for (int i = 0; i < linha; ++i){
		v[i] = new int[2];
	}

	memoriaCache *c = new memoriaCache[linha];

	memoriaPrincipal *m = new memoriaPrincipal[bloco];

	initMemPrinc(m, t_bloco, bloco);
	initMemCache(c, t_bloco, linha);

	cout << "Digite os comandos: ('sair' para finalizar)\n" << endl;
	do{
		getline(cin, linha_comando);
		stringstream ss(linha_comando);

		ss >> comando >> elemento;

		/** Convertendo as letrar para minusculas */
		for (int i = 0; i < (int)comando.length(); ++i){
			comando[i] = tolower(comando[i]);
		}

		ss.clear();

		if (comando == "read"){
			endereco = stoi(elemento);
			if (endereco >= 0 && endereco <= ((t_bloco * bloco) - 1)){
				int bloco_cache = endereco / t_bloco;
				if (mapea == 1){
					mapea_direto(c, m, bloco_cache, linha);
				}else if(mapea == 2){
					mapea_totalmenteAssociativo(c, m, bloco_cache, linha, sub, fifo, lfu, ciclo);	
				}else if (mapea == 3){
					mapea_parcialmenteAssociativo(c, m, bloco_cache, linha, sub, n_conj, v, ciclo);
				}
			}
		}else if (comando == "show"){
			imprime(c, m, t_bloco, bloco, linha);
		}else if (comando != "sair"){
			cout << "Comando inválido!!" << endl;
		}
	}while(comando != "sair");

	for (int i = 0; i < 2; ++i){
		delete[] v[i];
	}

	delete[] v;
	delete[] c;
	delete[] m;
}

void imprime(memoriaCache *c, memoriaPrincipal *m, int t_bloco, int bloco, int linha){
	cout << endl << "CACHE L1" << endl;
	cout << "Linha - Bloco - Endereço - Conteudo" << endl;

	for (int i = 0; i < linha; ++i){
		for (int j = 0; j < t_bloco; ++j){
			vector<int> v = c[i].getEndereco();
			vector<int> v2 = c[i].getEndereco();

			cout << c[i].getLinha() << " - " << c[i].getBloco() << " - " << v[j] << " - " << v2[j];
			cout << endl;
		}
	}
}

void initMemPrinc(memoriaPrincipal *m, int t_bloco, int bloco){
	int aux = 0;
	for (int i = 0; i < bloco; ++i){
		m[i].setBloco(i);
		int j = 0;
		while(j < t_bloco){
			m[i].insereEndereco(aux++);
			m[i].insereConteudo(aux*5);
			j++;
		}
	}
}

void initMemCache(memoriaCache *c, int t_bloco, int linha){
	for (int i = 0; i < linha; ++i){
		c[i].setLinha(i);
		c[i].setBloco(-1);
		int j = 0;
		while(j < t_bloco){
			c[i].insereEndereco(-1);
			c[i].insereConteudo(-1);
			j++;	
		}
		
	}
}