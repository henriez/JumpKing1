#include "LevelMenu.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"
#include "../../Jogo/Jogo.h"

LevelMenu::LevelMenu() {
	background = nullptr;
}

LevelMenu::~LevelMenu() {
	SDL_DestroyTexture(background);
}

void LevelMenu::init() {
	quit.set(100, 500, 324, 156);
	quit.setTex("Assets/Buttons/quit.png");

	start.set(500, 300, 324, 156);
	start.setTex("Assets/Buttons/start.png");

	background = GerenciadorDeTexturas::CarregaTextura("Assets/Buttons/menu.png");
}

void LevelMenu::reset() {
	start.reset();
	quit.reset();
}

int LevelMenu::update() {
	start.handleEvents();
	if (start.click()) return BUTTON_START;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void LevelMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,Jogo::getDimensoesJanela().x,Jogo::getDimensoesJanela().y };
	GerenciadorDeTexturas::Desenhe(background, fonte, destino);
	start.render();
	quit.render();
}