#pragma once
#include "../Personagem.h"

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
	friend class GerenciadorDeCamera;

	const int speed;
	const int maxSpeed;
	bool onGround;
	bool flip;
};
