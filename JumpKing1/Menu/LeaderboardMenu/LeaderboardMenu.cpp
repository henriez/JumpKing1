#include "LeaderboardMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

LeaderboardMenu::LeaderboardMenu() {
	background = nullptr;
}

LeaderboardMenu::~LeaderboardMenu() {
	SDL_DestroyTexture(background);
}

void LeaderboardMenu::init() {
	quit.set(100, 500, 324, 156);
	quit.setTex("Assets/Buttons/quit.png");
	background = GerenciadorGrafico::CarregaTextura("Assets/Buttons/menu.png");
}

void LeaderboardMenu::reset() {
	quit.reset();
}

int LeaderboardMenu::update() {
	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void LeaderboardMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y}; //receber dados da janela
	GerenciadorGrafico::Desenhe(background, fonte, destino);
	quit.render();
}