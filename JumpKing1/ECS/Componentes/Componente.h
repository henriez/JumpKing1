#pragma once 
#include "../../Ente.h"

class Entidade;

class Componente : public Ente{
public:
	Componente() {}
	~Componente() {}

	virtual void atualizar() {}
	virtual void render() {}

};