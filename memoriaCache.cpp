#include "memoriaCache.h"

memoriaCache::memoriaCache(){}

memoriaCache::~memoriaCache(){}

int memoriaCache::getLinha(){ return linha; }

void memoriaCache::setLinha(int _linha){ linha = _linha; }

ostream& operator<<(ostream &os, Cache &c) {

	return os;
}

istream& operator>>(istream &is, Cache &c) {

	return is;
}
