#pragma once

#include "../Inimigo.h"

class Mago : public Inimigo {
public:
	Mago(float x = 0, float y = 0);
	~Mago();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val);

	void shoot();
	void atualizar();
	void render();
	int attack();
private:
	int sabedoria;
};