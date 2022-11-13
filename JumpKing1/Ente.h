#pragma once
#include "ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"

class Ente {
public:
	Ente() {
		graphics = GerenciadorGrafico::getInstance();
	}
	virtual ~Ente() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
protected:
	GerenciadorGrafico* graphics;
};