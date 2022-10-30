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
	void atualizar() {}
	void render() {}
private:
	SDL_Rect colisor;
};