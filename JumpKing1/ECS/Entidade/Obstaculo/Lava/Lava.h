#pragma once

#include "../Obstaculo.h"

class Lava : public Obstaculo
{
public:
	Lava();
	Lava(int x, int y, int w, int h, int temp);
	~Lava();
	void render();
	void renderHitbox();

	void atualizar();
	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/lavas.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/lavas.dat", ios::app);

		SDL_Rect pos = getComponente<ComponenteColisao>()->getColisor();

		std::string str = std::to_string(pos.x) + " " + std::to_string(pos.y) + " "
			+ std::to_string(pos.w) + " " + std::to_string(pos.h) + " "
			+ std::to_string(temperatura) + "\n";

		file << str;

		file.close();
	}

	SDL_Rect getPos() const;

private:
	SDL_Rect fonte;
	SDL_Rect destino;
	int temperatura;
};

