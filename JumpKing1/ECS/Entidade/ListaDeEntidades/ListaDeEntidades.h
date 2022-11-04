#pragma once

#include <vector>

#include "../Personagem/Jogador/Jogador.h"
#include "../Personagem/Inimigo/Esqueleto/Esqueleto.h"
#include "../Personagem/Inimigo/Zumbi/Zumbi.h"
#include "../Personagem/Inimigo/Chefe/Chefe.h"

class ListaDeEntidades {
public:
	ListaDeEntidades();
	~ListaDeEntidades();
	void atualizar();
	void addEntidade(Entidade* en);
	void render();
	void clear();
private:
	std::vector<Entidade*> listaEntidades;


};