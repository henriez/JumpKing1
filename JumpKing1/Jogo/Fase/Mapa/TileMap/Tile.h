#pragma once
#include "../../../../ECS/Componentes/ListaDeComponentes/ListaDeComponentes.h"

class Tile {
public:
	Tile();
	~Tile();
	void inicializa();
	void render();
private:
	bool colide;
	int id;
	ListaDeComponentes componentes;
};