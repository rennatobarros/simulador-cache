#include "memoriaPrincipal.h"

memoriaPrincipal::memoriaPrincipal(){}

memoriaPrincipal::~memoriaPrincipal(){}

int memoriaPrincipal::getBloco(){ return bloco; }

void memoriaPrincipal::setBloco(int _bloco){ bloco = _bloco; }

vector<int> memoriaPrincipal::getEndereco(){ return endereco; }

void memoriaPrincipal::setEndereco(vector<int> _endereco){ endereco = _endereco; }

vector<int> memoriaPrincipal::getConteudo(){ return conteudo; }

void memoriaPrincipal::setConteudo(vector<int> _conteudo){ conteudo = _conteudo; }

void memoriaPrincipal::insereEndereco(int _endereco){ endereco.push_back(_endereco); }

void memoriaPrincipal::insereConteudo(int _conteudo){ conteudo.push_back(_conteudo); }
