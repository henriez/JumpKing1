#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <string>

#include "../../ECS/Componentes/Vector2D/intVector2D.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"

class Button {
private:
protected:
	SDL_Color idleColor;
	SDL_Color hoverColor;
	SDL_Color clickColor;

	SDL_Texture* texture;

	std::string buttonText;

	bool isHovering;
	bool isClicked;
public:
	SDL_Rect pos;

	Button();
	~Button();

	void set(int xpos, int ypos, int width, int height, SDL_Color idle, SDL_Color hover, SDL_Color click, std::string text);
	void setTex(const char* path);

	virtual void handleEvents();
	void render();
	intVector2D getMousePos();
	void setButtonText(std::string text);
	virtual void onClick();
	bool click() { return isClicked; }
};

//classes derivadas de botao

class StartButton : public Button{
public:
	StartButton() :
		Button() {
	}

	// overrie de button
	void handleEvents();
	void onClick();
};

class SettingsButton : public Button {
public:
	SettingsButton() :	Button() {}

	// overrie de button
	void handleEvents();
	void onClick();
};

class QuitButton : public Button {
public:
	QuitButton() :	Button() {}

	// overrie de button
	void handleEvents();
	void onClick();
};