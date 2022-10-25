#include "Fase.h"

Fase::Fase() {
	arquivoSave = nullptr;
	jogo = nullptr;
}

Fase::~Fase() {
	clear();
}

void Fase::inicializar(Jogo* jg) {
	mapa = new Mapa;
	jogo = jg;
	Jogador* jogador = new Jogador;
	InimigoTipo1* en1 = new InimigoTipo1;
	InimigoTipo2* en2 = new InimigoTipo2;
	InimigoTipo3* en3 = new InimigoTipo3;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(en1));
	listaEntidades.addEntidade(static_cast<Entidade*>(en2));
	listaEntidades.addEntidade(static_cast<Entidade*>(en3));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar(jogo);
}

void Fase::atualizar() {
	listaEntidades.atualizar();
	mapa->atualizar();
}

void Fase::render() {
	mapa->render();
	listaEntidades.render();
}

void Fase::clear() {

	listaEntidades.clear();
	mapa->clear();
	delete mapa;
}