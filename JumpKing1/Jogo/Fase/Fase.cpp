#include "Fase.h"

Fase::Fase() {
	arquivoSave = nullptr;
	mapa = new Mapa;
	jogo = nullptr;
}

Fase::~Fase() {
	delete mapa;
}

void Fase::inicializar(Jogo* jg) {
	jogo = jg;
	Jogador* jogador = new Jogador;
	jogador->setJogo(jogo);
	InimigoTipo1* en1 = new InimigoTipo1;
	en1->setJogo(jogo);
	InimigoTipo2* en2 = new InimigoTipo2;
	en2->setJogo(jogo);
	InimigoTipo3* en3 = new InimigoTipo3;
	en3->setJogo(jogo);
	Chefe* boss = new Chefe;
	boss->setJogo(jogo);

	listaEntidades.addEntidade(jogador);
	listaEntidades.addEntidade(en1);
	listaEntidades.addEntidade(en2);
	listaEntidades.addEntidade(en3);
	listaEntidades.addEntidade(boss);

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