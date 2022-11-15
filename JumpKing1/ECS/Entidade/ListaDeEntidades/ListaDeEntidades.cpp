#include "ListaDeEntidades.h"

ListaDeEntidades::ListaDeEntidades() {}

ListaDeEntidades::~ListaDeEntidades() {
	clear();
}

void ListaDeEntidades::addEntidade(Entidade* en) {
	listaEntidades.add(en);
}

void ListaDeEntidades::clear() {
	listaEntidades.clear();
}

void ListaDeEntidades::atualizar() {
	Entidade* aux = listaEntidades.begin();
	while (aux) {
		aux->atualizar();
		aux = listaEntidades.next();
	}
}

void ListaDeEntidades::render() {
	Entidade* aux = listaEntidades.begin();
	while (aux) {
		aux->render();
		aux = listaEntidades.next();
	}
}