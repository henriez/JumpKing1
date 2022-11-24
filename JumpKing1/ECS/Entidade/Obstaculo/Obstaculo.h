#pragma once

#include "../Entidade.h"
#include "../Personagem/Jogador/Jogador.h"
#include "../../Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"

class Obstaculo : public Entidade
{
public:
	Obstaculo() { 
		onScreen = false; 
		addComponente<ComponenteColisao>();
	}
	virtual ~Obstaculo() {}

	virtual void render() = 0;
	virtual void salvar(int faseID) = 0;
	virtual void impedir(Jogador* jogador) = 0;

	bool isOnScreen() const { return onScreen; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
protected:
	bool onScreen;
};

