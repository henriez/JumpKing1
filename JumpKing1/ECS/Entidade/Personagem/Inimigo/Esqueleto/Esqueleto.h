#pragma once

#include "../Inimigo.h"

class Esqueleto : public Inimigo {
public:
	Esqueleto();
	~Esqueleto();

	void setGround(const bool inGround);
	bool inGround() const;
	const int getSpeed() const { return speed; }
	void changeSide() { flip = (flip) ? false : true; }

	void atualizar();
	void render();
private:
	SDL_Rect sprite;
	bool flip;
	const int speed;
	const int maxSpeed;
	const int fSpeed;
	bool onGround;
};