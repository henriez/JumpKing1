#pragma once

#include "../Inimigo.h"

class Esqueleto : public Inimigo {
public:
	Esqueleto(float x, float y);
	~Esqueleto();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val) { state = val; }

	void atualizar();
	void render();
	int attack();
private:
	int agressividade;
};