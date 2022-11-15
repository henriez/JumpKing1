#include "SettingsMenu.h"
#include "../../Jogo/Jogo.h"

SettingsMenu::SettingsMenu() {
	background = nullptr;
}

SettingsMenu::~SettingsMenu() {
	SDL_DestroyTexture(background);
}

void SettingsMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	quit.set(0.1 * dm.w, 0.8*dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Back Button.png");;

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void SettingsMenu::reset() {
	quit.reset();
}

int SettingsMenu::update() {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();
	graphics->present();

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void SettingsMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);
	quit.render();
}