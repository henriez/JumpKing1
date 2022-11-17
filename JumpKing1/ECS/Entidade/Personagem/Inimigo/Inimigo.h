#pragma once
#include "../Personagem.h"

class Inimigo : public Personagem {
public:
	Inimigo() : target(false), distance(0) { platform = { 0, 0, 0, 0 }; }
	virtual ~Inimigo() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;

	void setPlatform(SDL_Rect plat) { platform = plat; }
	SDL_Rect getPlatform() { return platform; }
	void setDistance(float val) { distance = val; }
	const float getDistance() const { return distance; }
	void setTarget(bool val) { target = val; }
	bool haveTarget() { return target; }

private:
	SDL_Rect platform;
	float distance;
	bool target;
};