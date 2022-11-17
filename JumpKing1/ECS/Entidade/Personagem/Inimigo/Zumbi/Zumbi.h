#pragma once

#include "../Inimigo.h"

class Zumbi : public Inimigo {
public:
	Zumbi(float x = 0, float y = 0);
	~Zumbi();

	const int getSpeed() const { return speed; }
	const float getDistance() const { return distance; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val) { state = val; }
	void setTarget(bool val) { haveTarget = val; }
	void setDistance(float val) { distance = val; }

	void atualizar();
	void render();
private:
	SDL_Rect sprite;
	unsigned char state;
	bool flip;
	bool haveTarget;
	int speed;
	float distance;
};