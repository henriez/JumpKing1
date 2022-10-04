#include "Jogo/Jogo.h"

int main() {
	Jogo jogo;

	while (jogo.executando())
		jogo.atualizar();
	
	return 0;
}