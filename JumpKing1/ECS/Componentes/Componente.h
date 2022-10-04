#pragma once 

class Entidade;

class Componente {
public:
	Componente() {}
	~Componente() {}

	virtual void atualizar() = 0;
protected:
};