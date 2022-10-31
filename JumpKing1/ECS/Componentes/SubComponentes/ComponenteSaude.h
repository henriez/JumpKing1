#pragma once

#include "../Componente.h"

class ComponenteSaude : public Componente {
public:
	ComponenteSaude() { saude = saudeMax = 0; }
	~ComponenteSaude() {}

private:
	float saude;
	float saudeMax;

};