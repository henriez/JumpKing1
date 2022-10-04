#pragma once

#include "../Inimigo.h"

class Chefe : public Inimigo {
public:
	Chefe();
	~Chefe();

	void atualizar();
	void render();
};