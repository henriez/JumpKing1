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

	SDL_Texture* texture;

	bool isHovering;
	bool isClicked;
public:
	SDL_Rect pos;

	Button();
	~Button();

	void set(int xpos, int ypos, int width, int height, std::string text);
	void setTex(const char* path);

	virtual void handleEvents();
	void render();
	intVector2D getMousePos();
	void onClick();
	bool click() { return isClicked; }
};

