#include "ControladorDeEventos.h"
#include "Jogador.h"
#include "../../Jogo/Jogo.h"
#include "../../../Gerenciador/GerenciadorDeCamera.h"

ControladorDeEventos::ControladorDeEventos() {
	transform = nullptr;
}

ControladorDeEventos::~ControladorDeEventos() {

}

void ControladorDeEventos::setTransform(Jogador* jg) {
	transform = jg->getComponente<ComponenteTransform>();
}

void ControladorDeEventos::atualizar() {	

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
		case SDLK_SPACE:
			transform->velocidade.y = -2;
			break;
		default:
			break;
		}
	}

	GerenciadorDeCamera::AtualizaJogador();
}