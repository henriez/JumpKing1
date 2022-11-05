#pragma once

#include "../Entidade.h"

class Obstaculo : public Entidade
{
public:
	Obstaculo() { onScreen = false; }
	virtual ~Obstaculo() {}

	virtual void render() = 0;

	bool isOnScreen() const { return onScreen; }
	void setScreen(const bool inScreen) { onScreen = inScreen; }
protected:
	bool onScreen;
};

