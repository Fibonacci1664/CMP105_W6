#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>
#include "Ball.h"
#include "Player.h"


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	void loadTextures();
	void initBalls();
	void initPlayer();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// More level variables
	sf::Texture m_ballTexture;
	sf::Texture m_marioTexture;
	Ball m_ball_1;
	Ball m_ball_2;
	Player m_player_1;
};