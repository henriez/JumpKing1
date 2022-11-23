#pragma once

#include "../Obstaculo.h"

class Espinhos : public Obstaculo
{
public:
	Espinhos();
	Espinhos(int x, int y, int w, int h,  int tam);
	~Espinhos();
	void render();
	void renderHitbox();

	void atualizar();
	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/espinhos.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/espinhos.dat", ios::app); \

		SDL_Rect pos = getComponente<ComponenteColisao>()->getColisor();

		std::string str = std::to_string(pos.x) + " " + std::to_string(pos.y) + " "
			+ std::to_string(pos.w) + " " + std::to_string(pos.h) + " "
			+ std::to_string(tamanho) + "\n";

		file << str;

		file.close();
	}

	SDL_Rect getPos() const;

	void setPosition(int x, int y, int srcX, int srcY);
private:
	SDL_Rect fonte;
	SDL_Rect destino;
	int tamanho;
};

