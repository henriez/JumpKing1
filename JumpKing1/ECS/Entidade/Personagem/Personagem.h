#pragma once
#include "../Entidade.h"

class Personagem : public Entidade {
public:
	Personagem() {
		addComponente<ComponenteSaude>();
		vulnerable = true;
	}
	virtual ~Personagem() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
	void damage() {
		if (vulnerable) {
			vulnerable_timer = SDL_GetTicks();
			getComponente<ComponenteSaude>()->damage();
			vulnerable = false;
		}
	}
	bool isAlive() {
		if (getComponente<ComponenteSaude>()->atualiza() == DEAD)
			return false;
		return true;
	}

protected:
	bool vulnerable;
	Uint32 vulnerable_timer;
};