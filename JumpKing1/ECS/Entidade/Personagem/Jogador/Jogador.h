#pragma once
#include "../Personagem.h"

class Jogador : public Personagem {
public:

	Jogador();
	~Jogador();

	void setGround(const bool inGround);
	bool inGround() const;
	void atualizar();
	void atacar();
	void render();
	void shoot();

	const int getSpeed() const { return speed; }
	bool isAttacking() const { return attacking; }
private:
	void inicializar();
	friend class GerenciadorDeCamera;

	const int speed;
	const int maxSpeed;
	bool onGround;
	bool flip;
	bool attacking;
	Uint32 timer;
};
