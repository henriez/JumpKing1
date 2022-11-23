#pragma once
#include "..//Obstaculo.h"

class Tile : public Obstaculo{
public:
	Tile();
	~Tile();
	void render();
	void renderHitbox();

	void atualizar();
	void salvar(int faseID) { // são estáticos, não é necessário salvar
	}

	void setPosition(int x, int y, int srcX, int srcY);
	SDL_Rect getPos() const;
private:
	SDL_Rect fonte;
	SDL_Rect destino;
};