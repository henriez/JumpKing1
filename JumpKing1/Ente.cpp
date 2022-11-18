#include "Ente.h"

GerenciadorGrafico* Ente::graphics = nullptr;

Ente::Ente() {
	graphics = GerenciadorGrafico::getInstance();
}