#ifndef MEMORIACACHE_H
#define MEMORIACACHE_H

#include "memoriaPrincipal.h"

/** Classe para a representação da classe cache */
class memoriaCache : public memoriaPrincipal{
	private:
		int linha;

	public:
		memoriaCache();
		~memoriaCache();

		int getLinha();
		void setLinha(int);

		friend ostream& operator<<(ostream &o, memoriaCache &c); // Sobrecarga operador de extracao
		friend istream& operator>>(istream &i, memoriaCache &c);

};

#endif