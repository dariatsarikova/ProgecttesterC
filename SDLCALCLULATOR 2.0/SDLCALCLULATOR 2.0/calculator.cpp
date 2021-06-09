#include "calculator.h"

using namespace std;


Calculator::Calculator()
{
	init();
}

Calculator::~Calculator()
{
	close();
}

int Calculator::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Problem with init: " << SDL_GetError() << endl;
		return 1;
	}
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0)
	{
		cout << "Problem with creating window and renderer: " << SDL_GetError() << endl;
		return 1;
	}
	SDL_SetWindowPosition(window, WIDTH / 2 - SCREEN_WIDTH / 2, HEIGHT / 2 - SCREEN_HEIGHT / 2 );

	letters['0'] = {
		Line{.7, .1, .2, .1},
		Line{.2, .1, .2, .5},
		Line{.7, .5, .7, .9},
		Line{.7, .9, .2, .9},
		Line{.2, .9, .2, .3},
		Line{.7, .1, .7, .5},
	};
	letters['1'] = {
		Line{.7, .9, .7, .1},
		Line{.7, .1, .3, .5},
	};
	letters['2'] = {
		Line{.2, .1, .8, .1},
		Line{.8, .1, .2, .9},
		Line{.2, .9, .8, .9},
	};
	letters['3'] = {
		Line{.2, .1, .8, .1},
		Line{.8, .1, .4, .5},
		Line{.4, .5, .8, .9},
		Line{.8, .9, .2, .9},
	};
	letters['4'] = {
		Line{.1, .7, .8, .1},
		Line{.9, .7, .1, .7},
		Line{.8, .9, .8, .1},
	};
	letters['5'] = {
		Line{.3, .1, .8, .1},
		Line{.3, .1, .3, .4},
		Line{.3, .4, .8, .4},
		Line{.8, .4, .8, .9},
		Line{.8, .9, .3, .9},

	};
	letters['6'] = {
		Line{.7, .1, .2, .1},
		Line{.2, .1, .2, .5},
		Line{.2, .5, .7, .5},
		Line{.7, .5, .7, .9},
		Line{.7, .9, .2, .9},
		Line{.2, .9, .2, .3},

	};
	letters['7'] = {
		Line{.2, .1, .8, .1},
		Line{.8, .1, .4, .9},
		

	};
	letters['8'] = {
		Line{.7, .1, .2, .1},
		Line{.2, .1, .2, .5},
		Line{.2, .5, .7, .5},
		Line{.7, .5, .7, .9},
		Line{.7, .9, .2, .9},
		Line{.2, .9, .2, .3},
		Line{.7, .1, .7, .5},
	};
	letters['9'] = {
		Line{.7, .1, .2, .1},
		Line{.2, .1, .2, .5},
		Line{.2, .5, .7, .5},
		Line{.7, .1, .7, .5},
		Line{.7, .5, .7, .9},
		Line{.7, .9, .2, .9},
		
		
	};
	letters['-'] = {
		Line{.1, .5, .9, .5},

	};
	letters['+'] = {
		Line{.1, .5, .9, .5},
		Line{.5, .9, .5, .1},

	};
	letters['='] = {
		Line{.1, .7, .9, .7},
		Line{.1, .3, .9, .3},

	};
	letters['*'] = {
		Line{.2, .2, .8, .8},
		Line{.2, .8, .8, .2},

	};
	letters['.'] = {
		Line{.2, .8, .3, .8},

	};
	letters['|'] = {
		Line{.2, .5, .8, .8},
		Line{.2, .5, .8, .2},

	};


	return 0;
}

int Calculator::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
	return 0;
}

void Calculator::exec()
{
	int selected_x, selected_y;
	bool quit = false;
	//int number_screen = 0;
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			//selected_x = (event.button.x ? event.button.x * 4 / SCREEN_WIDTH : -1);
			selected_x = event.button.x * 4 / SCREEN_WIDTH;
			selected_y = event.button.y * 5 / SCREEN_HEIGHT - 1;
			//cout << selected_x << " " << selected_y << endl;
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:

				if (selected_y == -1) break;
				char ch = grid[selected_y][selected_x];
				if ('0' <= ch && ch <= '9')
				{
					number_screen += ch;
					break;
				}
				switch (ch)
				{
				case '|':
					if (number_screen.size() > 0)
						number_screen.pop_back();
					break;
				case '+':
					tmp_operation = '+';
					left_side = atoi(number_screen.c_str());
					number_screen = "";
					break;
				case '-':
					tmp_operation = '-';
					left_side = atoi(number_screen.c_str());
					number_screen = "";
					break;
				case '*':
					tmp_operation = '*';
					left_side = atoi(number_screen.c_str());
					number_screen = "";
					break;

				case '=':
					is_update_time = true;
					t.reset();
					switch (tmp_operation)
					{
					case '+':
						answer = left_side + atoi(number_screen.c_str());
						break;
					case '-':
						answer = left_side - atoi(number_screen.c_str());
						break;
					case '*':
						answer = left_side * atoi(number_screen.c_str());
						break;
					}
					number_screen = std::to_string(answer);
					break;
				}
				break;
			}
		}
		draw();
		if (is_update_time)
		{
			time = std::to_string(t.elapsed());
			is_update_time = false;
		}
	}
}

void Calculator::draw() {
	SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			drawButton(
				grid[i][j],
				SCREEN_WIDTH / 4 * j,
				SCREEN_HEIGHT / 5 * (i + 1),
				SCREEN_WIDTH / 4,
				SCREEN_HEIGHT / 5);

	drawScreen();

	int width_symbol = SCREEN_HEIGHT / 20;
	for (int i = 0; i < time.size(); i++)
	{
		drawSymbol(
			time[i],
			width_symbol * i,
			0,
			width_symbol,
			width_symbol
		);
	}
	SDL_RenderPresent(renderer);
}

void Calculator::drawButton(char ch, int x, int y, int w, int h) {
	int border = 2;
	SDL_Rect outlineRect = { x + border, y + border, w - 2 * border, h - 2 * border };
	SDL_SetRenderDrawColor(renderer, 176, 176, 176, 255);
	SDL_RenderFillRect(renderer, &outlineRect);

	//symbol
	drawSymbol(ch, x, y, w, h);
}

void Calculator::drawSymbol(char ch, int x, int y, int w, int h) {

	SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
	for (Line line : letters[ch])
		SDL_RenderDrawLine(renderer, line[0] * w + x, line[1] * h + y, line[2] * w + x, line[3] * h + y);
}

void Calculator::drawScreen() {
	int width_symbol = SCREEN_HEIGHT / 10;
	for (int i = 0; i < number_screen.size(); i++)
		drawSymbol(
			number_screen[i],
			SCREEN_WIDTH - width_symbol * (number_screen.size() - i),
			SCREEN_HEIGHT / 5 - width_symbol,
			width_symbol,
			width_symbol
		);

	if (left_side == 0)
		return;

	string tmp_left_side = std::to_string(left_side);
	for (int i = 0; i < tmp_left_side.size(); i++)
		drawSymbol(
			tmp_left_side[i],
			SCREEN_WIDTH - width_symbol / 2 * (tmp_left_side.size()- i),
			0,
			width_symbol / 2,
			width_symbol / 2
		);

	drawSymbol(
		tmp_operation,
		SCREEN_WIDTH - width_symbol / 2,
		width_symbol / 2,
		width_symbol / 2,
		width_symbol / 2
	);
}