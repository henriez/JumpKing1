#pragma once
#include "../Personagem.h"
#include "ControladorDeEventos.h"

class Jogador : public Personagem {
public:
	Jogador();
	~Jogador();

	void setGround(const bool inGround);
	bool inGround() const;
	void atualizar();
	void render();

	int getSpeed() const { return speed; }
private:
	void inicializar();
	ControladorDeEventos controladorEventos;
	friend class GerenciadorDeCamera;

	int speed;
	bool onGround;
};
