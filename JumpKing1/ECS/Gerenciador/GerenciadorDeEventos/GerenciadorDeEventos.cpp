#include "GerenciadorDeEventos.h"
#include "../../Jogo/Jogo.h"

GerenciadorDeEventos* GerenciadorDeEventos::manager = nullptr;

GerenciadorDeEventos::GerenciadorDeEventos() {
	jogador = nullptr;
	jogador2 = nullptr;
}

GerenciadorDeEventos::~GerenciadorDeEventos(){}

GerenciadorDeEventos* GerenciadorDeEventos::getInstance() {
	if (manager == nullptr) {
		manager = new GerenciadorDeEventos;
	}
	return manager;
}

void GerenciadorDeEventos::deleteInstance() {
	if (manager != nullptr) {
		delete manager;
		manager = nullptr;
	}
}

void GerenciadorDeEventos::setJogador1(Jogador* pl) {
	jogador = pl;
}

void GerenciadorDeEventos::setJogador2(Jogador* pl) {
	jogador2 = pl;
}

void GerenciadorDeEventos::atualizar() {	
	ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
	if (Jogo::evento.type == SDL_KEYUP) {
		switch (Jogo::evento.key.keysym.sym) {
		case SDLK_a:
			transform->velocidade.x = 0;
			break;
		case SDLK_d:
			transform->velocidade.x = 0;
			break;
		default:
			break;
		}
	}

	if (Jogo::evento.type == SDL_KEYDOWN) {
		switch (Jogo::evento.key.keysym.sym) {
		case SDLK_a:
			transform->velocidade.x = -1;
			break;
		case SDLK_d:
			transform->velocidade.x = 1;
			break;
		case SDLK_w:
			//if (jogador->inGround())
				transform->velocidade.y = -2;
				jogador->setGround(false);
			break;
		case SDLK_LSHIFT:
			jogador->atacar();
			jogador->shoot();
			break;
		default:
			break;
		}
	}

	transform = jogador2->getComponente<ComponenteTransform>();
	if (Jogo::evento.type == SDL_KEYUP) {
		switch (Jogo::evento.key.keysym.sym) {
		case SDLK_j:
			transform->velocidade.x = 0;
			break;
		case SDLK_l:
			transform->velocidade.x = 0;
			break;
		default:
			break;
		}
	}

	if (Jogo::evento.type == SDL_KEYDOWN) {
		switch (Jogo::evento.key.keysym.sym) {
		case SDLK_j:
			transform->velocidade.x = -1;
			break;
		case SDLK_l:
			transform->velocidade.x = 1;
			break;
		case SDLK_i:
			//if (jogador2->inGround())
			transform->velocidade.y = -2;
			jogador2->setGround(false);
			break;
		case SDLK_SPACE:
			jogador2->atacar();
			break;
		default:
			break;
		}
	}

}