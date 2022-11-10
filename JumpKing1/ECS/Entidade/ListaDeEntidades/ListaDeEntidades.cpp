#include "ListaDeEntidades.h"

ListaDeEntidades::ListaDeEntidades() {}

ListaDeEntidades::~ListaDeEntidades() {
	clear();
}

void ListaDeEntidades::atualizar() {
	for (auto& e : listaEntidades)
		if (e != nullptr)
			e->atualizar();
}

void ListaDeEntidades::addEntidade(Entidade* en) {
	listaEntidades.push_back(en);
}

void ListaDeEntidades::render() {
	for (auto& e : listaEntidades)
		if (e != nullptr)
			e->render();
}

void ListaDeEntidades::clear() {
	for (auto& e : listaEntidades)
		if (e != nullptr) {
			delete e;
			e = nullptr;
		}
	listaEntidades.clear();
}
