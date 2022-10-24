#pragma once
#include "../Entidade.h"

class Personagem : public Entidade {
public:
	Personagem() {}
	~Personagem() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
};