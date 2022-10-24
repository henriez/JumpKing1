#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {}

void Menu::init() {
	start.set(100, 100, 324, 156, "StartButton test.\n");
	start.setTex("Assets/button.png");
	settings.set(100, 300, 324, 156, "StartButton test.\n");
	settings.setTex("Assets/button.png");
	quit.set(100, 500, 324, 156, "StartButton test.\n");
	quit.setTex("Assets/quit.png");

	resume.set(500, 300, 324, 156, "StartButton test.\n");
	resume.setTex("Assets/quit.png");

	//inicializar demais botoes
}

int Menu::click() {
	//teste dos botoes

	start.handleEvents();
	settings.handleEvents();
	quit.handleEvents();
	resume.handleEvents(); 
	if (resume.click()) return BUTTON_RESUME;
 	if (start.click()) return BUTTON_START;
	if (settings.click()) return BUTTON_SETTINGS;
	if (quit.click()) return BUTTON_QUIT;

	return 0; //nenhum botao foi clicado
}

void Menu::update() {
	
}

void Menu::render() {
	start.render();
	settings.render();
	quit.render();
	resume.render();
}

