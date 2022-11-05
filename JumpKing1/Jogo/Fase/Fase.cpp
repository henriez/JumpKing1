#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"

Fase::Fase() {
	mapa = nullptr;
	player_is_alive = true;
	jogo = nullptr;
}

Fase::~Fase() {
	if (mapa != nullptr) {
		delete mapa;
	}
}

void Fase::inicializar(const int id) {
	GerenciadorGrafico::setListaDeEntidades(&listaEntidades);
	GerenciadorDeColisao::setFase(this);
	mapa = new Mapa;
	Jogador* jogador = new Jogador;
	player_is_alive = true;
	GerenciadorDeCamera::setJogador(jogador);
	GerenciadorDeColisao::setJogador(jogador);
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
		Esqueleto* tmp = new Esqueleto;
		tmp->getComponente<ComponenteTransform>()->posicao.x = lugarX;
		tmp->getComponente<ComponenteTransform>()->posicao.y = lugarY;
		listaEntidades.addEntidade(static_cast<Entidade*>(tmp));
	}
	*/
	
	if (id == 1) {
		Esqueleto* en1T1 = new Esqueleto;
		en1T1->getComponente<ComponenteTransform>()->posicao.x = 456;
		en1T1->getComponente<ComponenteTransform>()->posicao.y = 6240;
		listaEntidades.addEntidade(static_cast<Entidade*>(en1T1));

		Esqueleto* en2T1 = new Esqueleto;
		en2T1->getComponente<ComponenteTransform>()->posicao.x = 160;
		en2T1->getComponente<ComponenteTransform>()->posicao.y = 5632.8;
		listaEntidades.addEntidade(static_cast<Entidade*>(en2T1));

		Esqueleto* en3T1 = new Esqueleto;
		en3T1->getComponente<ComponenteTransform>()->posicao.x = 1064;
		en3T1->getComponente<ComponenteTransform>()->posicao.y = 5358;
		listaEntidades.addEntidade(static_cast<Entidade*>(en3T1));

		Esqueleto* en4T1 = new Esqueleto;
		en4T1->getComponente<ComponenteTransform>()->posicao.x = 1500;
		en4T1->getComponente<ComponenteTransform>()->posicao.y = 5984;
		listaEntidades.addEntidade(static_cast<Entidade*>(en4T1));
	}

	Zumbi* zumbi = new Zumbi;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(zumbi));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar(id);
}

void Fase::setJogo(Jogo* jg) {
	jogo = jg;
}

void Fase::atualizar() {
	if (player_is_alive) {
		listaEntidades.atualizar();
		if (mapa != nullptr) {
			mapa->atualizar();
		}
		GerenciadorDeColisao::colisao_jogador1();
		GerenciadorDeCamera::Atualiza();
		
	}
	else {
		clear();
		jogo->gameOverMenu();
	}
	//else Jogo::evento.key.keysym.sym = SDLK_ESCAPE; //simula menu de pause

}

void Fase::render() {
	mapa->render();
	GerenciadorDeColisao::renderObstaculos();
	listaEntidades.render();
}

void Fase::clear() {

	mapa->clear();
	listaEntidades.clear();
}

void Fase::gameOver() {
	//clear();
	player_is_alive = false;
}