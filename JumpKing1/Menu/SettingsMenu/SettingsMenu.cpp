#include "SettingsMenu.h"
#include "../../Jogo/Jogo.h"

SettingsMenu::SettingsMenu() {
	background = nullptr;
}

SettingsMenu::~SettingsMenu() {
	SDL_DestroyTexture(background);
}

void SettingsMenu::init() {
	quit.set(100, 500, 324, 156);
	quit.setTex("Assets/Buttons/quit.png");;

	background = GerenciadorGrafico::CarregaTextura("Assets/Buttons/menu.png");
}

void SettingsMenu::reset() {
	quit.reset();
}

int SettingsMenu::update() {
	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void SettingsMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y };
	GerenciadorGrafico::Desenhe(background, fonte, destino);
	quit.render();
}