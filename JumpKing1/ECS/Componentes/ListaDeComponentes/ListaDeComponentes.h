#pragma once

#include <vector>
#include "../Componente.h"
#include <map>
#include <iostream>

#include "../SubComponentes/ComponenteSprite.h"
#include "../SubComponentes/ComponenteColisao.h"
#include "../SubComponentes/ComponenteTransform.h"
#include "../SubComponentes/ComponenteSaude.h"

class ListaDeComponentes {
public:
	ListaDeComponentes() {}
	~ListaDeComponentes() {}

	template<typename T> void addComponente() {
		T* componente = new (T);
		lista[typeid(componente).name()] = componente;
	}

	template<typename T> T* getComponente() {
		T* c = nullptr;
		return (T*)lista[typeid(c).name()];
	}
private:
	std::map<std::string, Componente*> lista;
	
};	