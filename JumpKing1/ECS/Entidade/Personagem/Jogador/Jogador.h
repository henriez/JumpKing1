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
	void damage(int dmg = 1) override;

	const int getSpeed() const { return speed; }
	bool facingLeft() { return flip; }
	bool isAttacking() const { return attacking; }
	void setPontuacao(int pontuacao) { points = pontuacao; }
	int getPontuacao() const { return points; }
	void hit(int increase) { points += increase; }
private:
	void inicializar();
	friend class GerenciadorDeCamera;

	int points;

	const int speed;
	const int maxSpeed;
	bool onGround;
	bool flip;
	bool attacking;
	Uint32 timer;
};
