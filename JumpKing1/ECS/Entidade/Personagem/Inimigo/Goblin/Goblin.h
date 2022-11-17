#pragma once

#include "../Inimigo.h"

class Goblin : public Inimigo {
public:
	Goblin(float x, float y);
	~Goblin();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val) { state = val; }

	void atualizar();
	void render();
private:
	SDL_Rect sprite;
	unsigned char state;
	bool flip;
	int speed;
};