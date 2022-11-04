#include "LeaderboardMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

LeaderboardMenu::LeaderboardMenu() {
	background = nullptr;
}

LeaderboardMenu::~LeaderboardMenu() {
	SDL_DestroyTexture(background);
}

void LeaderboardMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	quit.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Back Button.png");
	background = GerenciadorGrafico::LoadTexture("Assets/Buttons/menu.png");
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
	GerenciadorGrafico::render(background, fonte, destino);
	quit.render();
}