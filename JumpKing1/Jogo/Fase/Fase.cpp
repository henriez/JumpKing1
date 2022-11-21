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
	won = false;
}

Fase::~Fase() {
	if (mapa != nullptr) {
		delete mapa;
		mapa = nullptr;
	}
	GerenciadorDeEventos::deleteInstance();
}

void Fase::setJogo(Jogo* jg) {
	jogo = jg;
}

void Fase::render() {
	if (mapa) mapa->render();
	GerenciadorDeColisao::getInstance()->renderObstaculos();
	GerenciadorDeColisao::getInstance()->renderProjeteis();
	listaEntidades.render();

	if (player_is_alive) {
		int saude = GerenciadorDeColisao::getInstance()->getJogador1()->getComponente<ComponenteSaude>()->getHealth();
		SDL_Rect fonte = { 0,0,40,40 };
		SDL_Rect posRect;

		for (int i = 0; i < saude; i++) {
			posRect.x = (0.03 * i + 0.02) * GerenciadorDeCamera::getInstance()->camera.w;
			posRect.y = (0.03) * GerenciadorDeCamera::getInstance()->camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		saude = GerenciadorDeColisao::getInstance()->getJogador2()->getComponente<ComponenteSaude>()->getHealth();
		for (int i = 0; i < saude; i++) {
			posRect.x = (-0.03 * i + 0.97) * GerenciadorDeCamera::getInstance()->camera.w - 40;
			posRect.y = (0.03) * GerenciadorDeCamera::getInstance()->camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		int pontuacao = GerenciadorDeColisao::getInstance()->getJogador1()->getPontuacao() + GerenciadorDeColisao::getInstance()->getJogador2()->getPontuacao();
		//int pontuacao = 34500;
		graphics->renderPontuacao(pontuacao);
	}
}

void Fase::clear() {

	mapa->clear();
	listaEntidades.clear();
	if (mapa != nullptr) {
		delete mapa;
		mapa = nullptr;
	}
}

void Fase::gameOver() {
	player_is_alive = false;
}

