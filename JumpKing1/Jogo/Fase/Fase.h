#pragma once

#include "../../Ente.h"
#include "Mapa/Mapa.h"
#include "../../ECS/Entidade/ListaDeEntidades/ListaDeEntidades.h"
#include "../Jogo.h"

class GerenciadorDeEventos;

class Fase : public Ente{
public:
	Fase();
	virtual ~Fase();

	void setJogo(Jogo* jg);
	void render();
	void clear();
	void gameOver();

	virtual void inicializar() = 0;
	virtual void atualizar() = 0;
	virtual void save() = 0;
	virtual void saveRank() = 0;
	virtual void load() = 0;
protected:
	ListaDeEntidades listaEntidades;
	GerenciadorDeEventos* event_manager;
	//GerenciadorDeColisao* collision_manager;
	//GerenciadorDeCamera* camera_manager;
	Mapa* mapa;
	bool player_is_alive;
	Jogo* jogo;
	int id;
};
