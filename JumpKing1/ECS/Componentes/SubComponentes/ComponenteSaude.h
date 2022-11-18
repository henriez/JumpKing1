#pragma once

#include "../Componente.h"

#define ALIVE 1
#define DEAD 0

class ComponenteSaude : public Componente {
public:
	ComponenteSaude() { saude = saudeMax = 0; }
	~ComponenteSaude() {}

	void init(unsigned int initialHealth) {
		saude = saudeMax = initialHealth;
	}

	int atualiza() {
		if (saude <= 0)
			return DEAD;
		return ALIVE;
	}
	
	void damage(int dmg) {
		if (saude > 0) {
			saude -= dmg;
		}

	}

	int getHealth() const {
		return saude;
	}

	int getMaxHealth() const {
		return saudeMax;
	}

private:
	float saude;
	float saudeMax;

};