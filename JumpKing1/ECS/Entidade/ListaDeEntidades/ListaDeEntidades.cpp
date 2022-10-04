#include "ListaDeEntidades.h"

ListaDeEntidades::ListaDeEntidades() {}

ListaDeEntidades::~ListaDeEntidades() {
	for (auto& e : listaEntidades)
		if (e != NULL)
			delete e;
}

void ListaDeEntidades::atualizar() {
	for (auto& e : listaEntidades)
		e->atualizar();
}

void ListaDeEntidades::addEntidade(Entidade* en) {
	listaEntidades.push_back(en);
}

void ListaDeEntidades::render() {
	for (auto& e : listaEntidades) 
		e->render();
}

