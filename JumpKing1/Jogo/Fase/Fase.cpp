#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../ECS/Gerenciador/GerenciadorDeEventos/GerenciadorDeEventos.h"
#include "../../ECS/Gerenciador/GerenciadorDeSave/GerenciadorDeSave.h"
#include <fstream>
#include <string>
#include "../TextBox/Textbox.h"
using namespace std;


Fase::Fase() {
	mapa = nullptr;
	player_is_alive = true;
	jogo = nullptr;
	id = 0;
	event_manager = GerenciadorDeEventos::getInstance();
	//collision_manager = GerenciadorDeColisao
}

Fase::~Fase() {
	if (mapa != nullptr) {
		delete mapa;
	}
	GerenciadorDeEventos::deleteInstance();
}

void Fase::setJogo(Jogo* jg) {
	jogo = jg;
}

/*
void Fase::criaGoblins() {
	Goblin* gbl = nullptr;
	std::vector<SDL_Point> posicoes;
	std::fstream file;
	SDL_Point pos = {0,0};
	char c;
	int a1, a2, a3, a4, i, nPosicoes;

	if (id == 1) file.open("Assets/TileMap/Mapa1/mapa1_posicoes_goblins.csv");
	else if (id == 2) file.open("Assets/TileMap/Mapa2/mapa2_posicoes_goblins.csv");


		file.get(c);
		a1 = atoi(&c);
		file.get(c);
		a2 = atoi(&c);
		file.get(c);
		a3 = atoi(&c);
		file.ignore();
		//quantidade de posicoes

		nPosicoes = a1 * 100 + a2 * 10 + a3;

		for (int i = 0; i < nPosicoes; i++) {

			file.get(c);
			a1 = atoi(&c);
			file.get(c);
			a2 = atoi(&c);
			file.get(c);
			a3 = atoi(&c);
			file.get(c);
			a4 = atoi(&c);
			pos.x = a1 * 1000 + a2 * 100 + a3 * 10 + a4;

			file.ignore();

			file.get(c);
			a1 = atoi(&c);
			file.get(c);
			a2 = atoi(&c);
			file.get(c);
			a3 = atoi(&c);
			file.get(c);
			a4 = atoi(&c);
			file.ignore();
			pos.y = a1 * 1000 + a2 * 100 + a3 * 10 + a4;

			posicoes.push_back(pos);
		}

		file.close();
	

	std::vector<SDL_Point>::iterator it;

	int nZumbis = rand() % (posicoes.size() - 3) + 3;

	for (i = 0; i < nZumbis; i++) {
		pos = posicoes[rand() % posicoes.size()];
		gbl = new Goblin(pos.x, pos.y);
		listaEntidades.addEntidade(static_cast<Entidade*>(gbl));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(gbl));
	}
}*/

void Fase::render() {
	mapa->render();
	GerenciadorDeColisao::renderObstaculos();
	GerenciadorDeColisao::renderProjeteis();
	listaEntidades.render();

	if (player_is_alive) {
		int saude = GerenciadorDeColisao::getJogador1()->getComponente<ComponenteSaude>()->getHealth();
		SDL_Rect fonte = { 0,0,40,40 };
		SDL_Rect posRect;

		for (int i = 0; i < saude; i++) {
			posRect.x = (0.03 * i + 0.02) * GerenciadorDeCamera::camera.w;
			posRect.y = (0.03) * GerenciadorDeCamera::camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		saude = GerenciadorDeColisao::getJogador2()->getComponente<ComponenteSaude>()->getHealth();
		for (int i = 0; i < saude; i++) {
			posRect.x = (-0.03 * i + 0.97) * GerenciadorDeCamera::camera.w - 40;
			posRect.y = (0.03) * GerenciadorDeCamera::camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		int pontuacao = GerenciadorDeColisao::getJogador1()->getPontuacao() + GerenciadorDeColisao::getJogador2()->getPontuacao();
		//int pontuacao = 34500;
		graphics->renderPontuacao(pontuacao);
	}
}

void Fase::clear() {

	mapa->clear();
	listaEntidades.clear();
}

void Fase::gameOver() {
	player_is_alive = false;
}

