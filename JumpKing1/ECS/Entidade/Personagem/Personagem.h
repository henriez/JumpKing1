#pragma once
#include "../Entidade.h"

class Jogo;

class Personagem : public Entidade {
public:
	Personagem() {
		jogo = nullptr;
	}
	~Personagem() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
};