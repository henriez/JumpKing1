#pragma once
#include "../Ente.h"

class MenuEnte : public Ente {
public:
	MenuEnte() : background(nullptr) {}
	virtual ~MenuEnte() {}

	virtual void reset() = 0;
	virtual int update() = 0;
	void atualizar() {}
	void render() {}
protected: 
	SDL_Texture* background;
};