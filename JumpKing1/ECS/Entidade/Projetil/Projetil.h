#pragma once
#include <SDL.h>
#include "../Entidade.h"
#include "../../Componentes/Vector2D/Vector2D.h"

class Projetil : public Entidade
{
public:
	Projetil();
	Projetil(float x, float y, float vx, float vy);
	~Projetil();

	void init();
	void atualizar();
	void render();
	int getSpeed() const { return speed; }

	bool isOnScreen() const { return onScreen; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
	void collide() { maxColisoes--; }

	void salvar(int faseID) {
		if (isActive()) {
			ofstream file;
			if (faseID == 1) file.open("Saves/Fase1/projeteis.dat", ios::app);
			else if (faseID == 2) file.open("Saves/Fase2/projeteis.dat", ios::app);
			ComponenteTransform* transform = getComponente<ComponenteTransform>();
			std::string str = std::to_string(transform->velocidade.x) + " " + std::to_string(transform->velocidade.y) +
				" " + std::to_string(transform->posicao.x) + " " + std::to_string(transform->posicao.y) + "\n";

			file << str;

			file.close();
		}
	}
private:
	bool onScreen;
	
	int speed;
	SDL_Rect sprite;
	bool flip;
	int maxColisoes;
};

