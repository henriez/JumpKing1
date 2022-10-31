#include "ControladorDeEventos.h"
#include "Jogador.h"
#include "../../Jogo/Jogo.h"
#include "../../../Gerenciador/GerenciadorDeCamera.h"
#include "../../../Gerenciador/GerenciadorDeColisao.h"

ControladorDeEventos::ControladorDeEventos() {
	jogador = nullptr;
}

ControladorDeEventos::~ControladorDeEventos() {

}

void ControladorDeEventos::setTransform(Jogador* jg) {
	jogador = jg;
}

void ControladorDeEventos::atualizar() {	
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
		case SDLK_SPACE:
			//if (jogador->inGround())
				transform->velocidade.y = -2;
			break;
		default:
			break;
		}
	}

	GerenciadorDeColisao::colisao_jogador1();

	GerenciadorDeCamera::AtualizaJogador();
}