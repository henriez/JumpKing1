#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera.h"

Fase::Fase() {
	arquivoSave = nullptr;
	mapa = nullptr;
}

Fase::~Fase() {
	clear();
	if (mapa != nullptr) {
		delete mapa;
	}
}

void Fase::inicializar() {
	mapa = new Mapa;
	Jogador* jogador = new Jogador;
	GerenciadorDeCamera::setJogador(jogador);
	InimigoTipo1* en1 = new InimigoTipo1;
	InimigoTipo2* en2 = new InimigoTipo2;
	InimigoTipo3* en3 = new InimigoTipo3;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(en1));
	listaEntidades.addEntidade(static_cast<Entidade*>(en2));
	listaEntidades.addEntidade(static_cast<Entidade*>(en3));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar();
}

void Fase::atualizar() {
	listaEntidades.atualizar();
	if (mapa != nullptr)
		mapa->atualizar();
}

void Fase::render() {
	mapa->render();
	listaEntidades.render();
}

void Fase::clear() {

	listaEntidades.clear();
}