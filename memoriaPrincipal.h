#ifndef MEMORIAPRINCIPAL_H
#define MEMORIAPRINCIPAL_H

#include <iostream>
using namespace std;

#include <vector>

/** Classe para a representação da classe cache */
class memoriaPrincipal{
	private:
		int bloco; //Bloco da memória principal
		vector<int> endereco; //Endereço da memória principal
		vector<int> conteudo; //Conteúdo da memória principal

	public:
		memoriaPrincipal();
		~memoriaPrincipal();

		int getBloco();
		void setBloco(int);

		vector<int> getEndereco();
		void setEndereco(vector<int>);

		vector<int> getConteudo();
		void setConteudo(vector<int>);

		void insereEndereco(int); // Insere o endereço na memória
		void insereConteudo(int); // Insere o conteudo na memória

};

#endif