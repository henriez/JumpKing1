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

	bool isOnScreen() const { return onScreen; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
private:
	bool onScreen;
	bool speed;
};

