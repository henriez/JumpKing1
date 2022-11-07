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
	void shoot();
	void damage();
	bool isAlive();

	const int getSpeed() const { return speed; }
private:
	void inicializar();
	ControladorDeEventos controladorEventos;
	friend class GerenciadorDeCamera;

	const int speed;
	const int maxSpeed;
	bool onGround;
	bool flip;
};
