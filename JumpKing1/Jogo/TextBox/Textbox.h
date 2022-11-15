/* ============================================================================ */
//
// Author: Henrique A. p. Mendes 
// github: https://github.com/HenriqueAPMendes
// linkedin: https://www.linkedin.com/in/henrique-mendes-508156215/
//
// A simple SDL2 textBox for dealing with user text input 
//
/* ============================================================================ */


// TextBox header

#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<string>
#include<iostream>

class TextBox {
public:
	TextBox();
	~TextBox();
	
	void setBackground(const char* path);
	void setBoxBackgroundColor(SDL_Color background);
	void setBoxOutlineColor(SDL_Color outline);
	void setTextColor(SDL_Color text);
	void setPosition(int x, int y, int w, int h);
	bool setFontToHeight(std::string fontPath); //set font according to the height of Rect
	bool setFont(std::string fontPath, int fontSize); //set font manually

	void run(std::string message, int windowW = 640, int windowH = 480);

	std::string getInput();

private:

	void eraseOneChar(); //erase last char
	void appendText(std::string tmp_Text);

	void closeFont();
	void update();
	void clearBox(); //clear the textbox

	TTF_Font* font;
	std::string text = "";
	std::string message = "";

	SDL_Rect position;
	const char* background;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Color backgroundColor;
	SDL_Color outlineColor;
	SDL_Color textColor;
};

