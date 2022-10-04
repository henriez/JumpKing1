#pragma once

#include "../Componente.h"
#include "../Vector2D/Vector2D.h"

class ComponenteTransform : public Componente {
public:
	ComponenteTransform() {}
	~ComponenteTransform() {}

	void atualizar() {}
	void render() {}

	Vector2D posicao;
	Vector2D velocidade;
private:
};