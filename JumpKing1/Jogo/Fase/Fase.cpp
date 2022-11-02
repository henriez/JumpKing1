#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera.h"

Fase::Fase() {
	mapa = nullptr;
}

Fase::~Fase() {
	clear();
	if (mapa != nullptr) {
		delete mapa;
	}
}

void Fase::inicializar(const int id) {
	mapa = new Mapa;
	Jogador* jogador = new Jogador;
	switch (id) {
	case 1:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 100;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 6240;
		break;
	case 2:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 300;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 7648;
		break;
	default:
		break;
	}
	GerenciadorDeCamera::setJogador(jogador);

	// Escolher lugares aleatorios e criar mais inimigos. Ex:
	/*
	for (qtd = 0; qtd < qtdMax; qtd++) {
		InimigoTipo1* tmp = new InimigoTipo1;
		tmp->getComponente<ComponenteTransform>()->posicao.x = lugarX;
		tmp->getComponente<ComponenteTransform>()->posicao.y = lugarY;
		listaEntidades.addEntidade(static_cast<Entidade*>(tmp));
	}
	*/
	InimigoTipo1* en1 = new InimigoTipo1;
	en1->getComponente<ComponenteTransform>()->posicao.x = 164;
	en1->getComponente<ComponenteTransform>()->posicao.y = 6200;

	InimigoTipo2* en2 = new InimigoTipo2;
	InimigoTipo3* en3 = new InimigoTipo3;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(en1));
	listaEntidades.addEntidade(static_cast<Entidade*>(en2));
	listaEntidades.addEntidade(static_cast<Entidade*>(en3));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar(id);
}

void Fase::init_BossRoom() {

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