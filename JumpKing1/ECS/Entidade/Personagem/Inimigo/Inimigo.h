#pragma once
#include "../Personagem.h"

class Inimigo : public Personagem {
public:
	Inimigo() { platform = { 0, 0, 0, 0 }; }
	virtual ~Inimigo() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;

	void setPlatform(SDL_Rect plat) { platform = plat; }
	SDL_Rect getPlatform() { return platform; }
private:
	SDL_Rect platform;
};