#include "Zumbi.h"

Zumbi::Zumbi() {
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSaude>();
}

Zumbi::~Zumbi() {}

void Zumbi::atualizar() {}

void Zumbi::render() {}
