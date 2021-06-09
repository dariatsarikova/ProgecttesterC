#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "Timer.h"

class Calculator
{
public:
	Calculator();
	~Calculator();
	void exec();
private:
	const char* grid[4] = {
		"789|",
		"456*",
		"123-",
		"0.=+",
	};
	
	const uint16_t WIDTH = 1920;
	const uint16_t HEIGHT = 1080;

	const uint16_t SCREEN_WIDTH = WIDTH * 3 / 10;
	const uint16_t SCREEN_HEIGHT = HEIGHT * 3 / 5;

	//The window renderer
	SDL_Renderer* renderer;

	//The window we'll be rendering to
	SDL_Window* window;

	typedef std::vector<float> Line;
	std::vector<Line> letters[255];

	std::string number_screen;
	long long left_side = 0;
	long long answer;
	char tmp_operation;

	Timer t;
	std::string time;
	bool is_update_time = false;

	int init();
	int close();
	void draw();
	void drawButton(char ch, int x, int y, int w, int h);
	void drawSymbol(char ch, int x, int y, int w, int h);
	void drawScreen();
};
