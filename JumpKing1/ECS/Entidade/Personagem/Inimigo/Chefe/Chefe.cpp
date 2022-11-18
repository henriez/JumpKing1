#include "Chefe.h"

Chefe::Chefe() {
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSaude>();
}

Chefe::~Chefe() {}

void Chefe::atualizar() {}

void Chefe::render() {}

int Chefe::attack() {
	return 0;
}