#pragma once

#include "../Componente.h"

class ComponenteSaude : public Componente {
public:
	ComponenteSaude() { saude = saudeMax = 0; }
	~ComponenteSaude() {}

	void atualizar() {}
	void render() {}

private:
	float saude;
	float saudeMax;

};