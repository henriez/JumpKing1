#pragma once

#include "../Entidade.h"

class Obstaculo : public Entidade
{
public:
	Obstaculo() { 
		onScreen = false; 
		addComponente<ComponenteColisao>();
	}
	virtual ~Obstaculo() {}

	virtual void render() = 0;
	virtual void salvar(int faseID) = 0;

	bool isOnScreen() const { return onScreen; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
protected:
	bool onScreen;
};

