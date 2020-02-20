#include "Player.h"
#include <iostream>


Player::Player()
{
	movingLeft = false;
	movingRight = false;
	ducking = false;
	setVelocity(sf::Vector2f(150, 150));
	addFrames();
	setTextureRect(run.getCurrentFrame());
	duck.setPlaying(false);




	m_jumpScalar = 300;

	// Gravitational Accelleration.
	m_gravityScalar = 100;		// What is the purpose of this, is this so we can still keep the nice 9.8 figure as gravity but then just multiply it by a scalar?
	m_gravitationalAccel = sf::Vector2f(0, 9.8) * m_gravityScalar;

	//m_playersPos = sf::Vector2f(getPosition().x, getPosition().y);
}

Player::~Player()
{
	std::cout << "Player object destroyed!\n";
}

void Player::update(float dt)
{
	gravityFall(dt);

	if (!run.getPlaying())
	{
		run.reset();
	}
	else
	{
		setTextureRect(run.getCurrentFrame());
	}

	if (!swim.getPlaying())
	{
		swim.reset();
	}
	else
	{
		setTextureRect(swim.getCurrentFrame());
	}

	if (!duck.getPlaying())
	{
		duck.reset();
	}
	else
	{
		setTextureRect(duck.getCurrentFrame());
	}
}

void Player::handleInput(float dt)
{
	run.setPlaying(false);
	swim.setPlaying(false);

	// Move right.
	if (input->isKeyDown(sf::Keyboard::L) && !ducking)
	{
		movingRight = true;
		movingLeft = false;
		run.setPlaying(true);
		run.setFlipped(false);
		run.animate(dt);
		setTextureRect(run.getCurrentFrame());

		setPosition(sf::Vector2f(getPosition().x + getVelocity().x * dt, getPosition().y));
	}

	// Move left.
	if (input->isKeyDown(sf::Keyboard::J) && !ducking)
	{
		movingLeft = true;
		movingRight = false;
		run.setPlaying(true);
		run.setFlipped(true);
		run.animate(dt);
		setTextureRect(run.getCurrentFrame());

		setPosition(sf::Vector2f(getPosition().x - getVelocity().x * dt, getPosition().y));
	}

	// Swim right.
	if (input->isKeyDown(sf::Keyboard::P) && (input->isKeyDown(sf::Keyboard::L) && !ducking))
	{
		run.setPlaying(false);
		swim.setPlaying(true);
		swim.setFlipped(false);
		swim.animate(dt);
		setTextureRect(swim.getCurrentFrame());

		setPosition(sf::Vector2f(getPosition().x + (getVelocity().x / 3) * dt, getPosition().y));
	}

	// Swim left.
	if (input->isKeyDown(sf::Keyboard::P) && (input->isKeyDown(sf::Keyboard::J) && !ducking))
	{
		run.setPlaying(false);
		swim.setPlaying(true);
		swim.setFlipped(true);
		swim.animate(dt);
		setTextureRect(swim.getCurrentFrame());

		setPosition(sf::Vector2f(getPosition().x - (getVelocity().x / 3) * dt, getPosition().y));
	}

	// Duck.
	if (input->isKeyDown(sf::Keyboard::K))
	{
		ducking = true;
		run.setPlaying(false);
		duck.setPlaying(true);

		if (movingRight)
		{
			duck.setFlipped(false);
		}
		else if (movingLeft)
		{
			duck.setFlipped(true);
		}

		//duck.animate(dt);
		setTextureRect(duck.getCurrentFrame());

		setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	}
	else if (!input->isKeyDown(sf::Keyboard::K))
	{
		ducking = false;

		if (duck.getPlaying())
		{
			duck.setPlaying(false);
			setTextureRect(run.getCurrentFrame());
		}
	}


	// JUMP.
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		run.setPlaying(false);
		setTextureRect(run.getCurrentFrame());
		m_stepVelocity = sf::Vector2f(0, -1.0f) * m_jumpScalar;
	}
}

void Player::gravityFall(float dt)
{
	// s = ut + 1/2 at^2.
	//				  s		  =			u		  t   +  1/2			a				 t^2
	sf::Vector2f displacement = (m_stepVelocity * dt) + (0.5f * m_gravitationalAccel * dt * dt);

	// v = u + at.
	m_stepVelocity += m_gravitationalAccel * dt;

	setPosition(getPosition() + displacement);

	if ((getPosition().y + getSize().y / 2.0f) > window->getSize().y)
	{
		setPosition(getPosition().x, window->getSize().y - getSize().y / 2.0f);
		m_stepVelocity = sf::Vector2f(0, 0);
	}
}

void Player::addFrames()
{
	for (int i = 0; i < (runFrames * FRAME_WIDTH); i += FRAME_WIDTH)
	{
		run.addFrame(sf::IntRect(i, 0, FRAME_WIDTH, FRAME_HEIGHT));
	}

	for (int i = 0; i < (swimFrames * FRAME_WIDTH); i += FRAME_WIDTH)
	{
		swim.addFrame(sf::IntRect(i, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
	}

	for (int i = 0; i < (duckFrames * FRAME_WIDTH); i += FRAME_WIDTH)
	{
		duck.addFrame(sf::IntRect(i, (FRAME_HEIGHT * 2), FRAME_WIDTH, FRAME_HEIGHT));
	}

	run.setFrameSpeed(1.0f / 10.f);
	swim.setFrameSpeed(1.5f / 10.f);
	duck.setFrameSpeed(1.0f / 10.f);
}