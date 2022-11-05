#pragma once

#include "../Entidade.h"

class Obstaculo : public Entidade
{
public:
	Obstaculo() {}
	virtual ~Obstaculo() {}

	virtual void render() = 0;
};

