#pragma once
#include "../Componentes/ListaDeComponentes/ListaDeComponentes.h"

class Jogo;

class Entidade {
protected:
	ListaDeComponentes componentes;
public:
	Entidade() {}
	virtual ~Entidade() {}

	virtual void render() = 0;
	virtual void atualizar() = 0;
	template<typename T>
	void addComponente() {
		componentes.addComponente<T>();
	}
	template<typename T> T* getComponente() {
		return componentes.getComponente<T>();
	}

};