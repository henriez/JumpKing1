#pragma once
#include "../Componentes/ListaDeComponentes/ListaDeComponentes.h"
#include "../../Ente.h"
#include <fstream>
using namespace std;

class Jogo;

class Entidade : public Ente{
protected:
	ListaDeComponentes componentes;
	bool active;
public:
	Entidade() {
		active = true;
	}
	virtual ~Entidade() {}

	virtual void render() = 0;
	virtual void atualizar() = 0;
	virtual void salvar(int faseID) = 0;
	template<typename T>
	void addComponente() {
		componentes.addComponente<T>();
	}
	template<typename T> T* getComponente() {
		return componentes.getComponente<T>();
	}

	bool isActive() const { return active; }

};