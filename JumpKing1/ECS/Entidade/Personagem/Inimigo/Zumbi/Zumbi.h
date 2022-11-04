#pragma once

#include "../Inimigo.h"

class Zumbi : public Inimigo {
public:
	Zumbi();
	~Zumbi();

	void atualizar();
	void render();
};