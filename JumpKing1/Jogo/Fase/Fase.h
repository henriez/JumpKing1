#pragma once

#include "../../Ente.h"
#include "Mapa/Mapa.h"
#include "../../ECS/Entidade/ListaDeEntidades/ListaDeEntidades.h"
#include "../Jogo.h"

class Fase : public Ente{
public:
	Fase();
	~Fase();

	void inicializar(const int id);
	void setJogo(Jogo* jg);
	void atualizar();
	void render();
	void clear();
	void gameOver();
private:
	ListaDeEntidades listaEntidades;
	Mapa* mapa;
	bool player_is_alive;
	Jogo* jogo;
};
