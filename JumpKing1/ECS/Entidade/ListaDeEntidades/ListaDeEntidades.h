#pragma once

#include <vector>

#include "../Personagem/Jogador/Jogador.h"
#include "../Personagem/Inimigo/Esqueleto/Esqueleto.h"
#include "../Personagem/Inimigo/Goblin/Goblin.h"
#include "../Personagem/Inimigo/Mago/Mago.h"
#include "../Projetil/Projetil.h"
#include "../../Lista/Lista.h"

class ListaDeEntidades {
public:
	ListaDeEntidades();
	~ListaDeEntidades();

	void addEntidade(Entidade* en);
	void clear();

	void atualizar();
	void render();
private:
	Lista<Entidade*> listaEntidades;

};