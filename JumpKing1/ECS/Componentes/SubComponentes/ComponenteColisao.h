#pragma once

#include "../Componente.h"
#include <SDL.h>

class ComponenteColisao : public Componente {
public:
	ComponenteColisao() {
		colisor = { 0,0,0,0 };
	}
	~ComponenteColisao() {}

	
	void atualizar() {}
	void render() {}
private:
	SDL_Rect colisor;
};