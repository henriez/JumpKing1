#pragma once

#include "../Componente.h"
#include <SDL.h>

class ComponenteColisao : public Componente {
public:
	ComponenteColisao() {
		colisor = { 0,0,0,0 };
	}
	~ComponenteColisao() {}

	void set(int xpos, int ypos, int w, int h) {
		colisor.x = xpos;
		colisor.y = ypos;
		colisor.w = w;
		colisor.h = h;
	}
	void setPos(int x, int y) {
		colisor.x = x;
		colisor.y = y;
	}
	void atualizar() {}
	void render() {}

	SDL_Rect getColisor() const{
		return colisor;
	}
private:
	SDL_Rect colisor;
};