#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	loadTextures();
	initBalls();
	initPlayer();
	initSling();
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	m_ball_1.handleInput(dt);
	//m_player_1.handleInput(dt);
	
	m_sling.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	m_ball_1.update(dt);
	m_sling.update(dt);
	//m_ball_2.update(dt);
	//m_player_1.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(m_ball_1);
	//window->draw(m_ball_2);
	//window->draw(m_player_1);
	window->draw(m_sling);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

void Level::loadTextures()
{
	m_ballTexture.loadFromFile("gfx/Beach_Ball.png");
	m_marioTexture.loadFromFile("gfx/MarioSheetT.png");
	m_slingShotTexture.loadFromFile("gfx/slingshot.png");
}

void Level::initBalls()
{
	m_ball_1.setInput(input);
	m_ball_1.setWindow(window);
	m_ball_1.setTexture(&m_ballTexture);
	m_ball_1.setSize(sf::Vector2f(25, 25));
	m_ball_1.setOrigin(sf::Vector2f(m_ball_1.getSize().x / 2.0f, m_ball_1.getSize().y / 2.0f));
	m_ball_1.setPosition(0 + 30, window->getSize().y - 200);

	m_ball_2.setInput(input);
	m_ball_2.setWindow(window);
	m_ball_2.setTexture(&m_ballTexture);
	m_ball_2.setSize(sf::Vector2f(80, 80));
	m_ball_2.setOrigin(sf::Vector2f(m_ball_1.getSize().x / 2.0f, m_ball_1.getSize().y / 2.0f));
	m_ball_2.setPosition(sf::Vector2f(0 + m_ball_2.getSize().x / 2.0f, window->getSize().y - (window->getSize().y / 2.0f)));
}

void Level::initPlayer()
{
	m_player_1.setInput(input);
	m_player_1.setWindow(window);
	m_player_1.setSize(sf::Vector2f(16, 21));				// Max size to accomodate ALL sprites.
	m_player_1.setOrigin(sf::Vector2f(m_player_1.getSize().x / 2, m_player_1.getSize().y / 2));
	m_player_1.setPosition(100, 100);
	m_player_1.setTexture(&m_marioTexture);
}

void Level::initSling()
{
	m_sling.setInput(input);
	m_sling.setWindow(window);
	m_sling.setSize(sf::Vector2f(50, 50));				// Max size to accomodate ALL sprites.
	m_sling.setOrigin(sf::Vector2f(m_player_1.getSize().x / 2, m_player_1.getSize().y / 2));
	m_sling.setPosition(0 + 50, window->getSize().y - 30);	
	m_sling.setTexture(&m_slingShotTexture);
}