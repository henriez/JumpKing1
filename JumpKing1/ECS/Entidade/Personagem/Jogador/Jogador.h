#pragma once
#include "../Personagem.h"
#include "ControladorDeEventos.h"

class Jogador : public Personagem {
public:
	Jogador();
	~Jogador();

	void atualizar();
	void render();
private:
	void inicializar();
	ControladorDeEventos controladorEventos;
	friend class GerenciadorDeCamera;
};