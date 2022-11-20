#pragma once
#include <SDL.h>
#include "../Entidade.h"
#include "../../Componentes/Vector2D/Vector2D.h"

class Projetil : public Entidade
{
public:
	Projetil();
	~Projetil();

	void init();
	void atualizar();
	void render();
	int getSpeed() const { return speed; }

	bool isOnScreen() const { return onScreen; }
	bool isActive() const { return active; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
	void collide() { maxColisoes--; }
private:
	bool onScreen;
	bool active;
	int speed;
	SDL_Rect sprite;
	bool flip;
	int maxColisoes;
};

