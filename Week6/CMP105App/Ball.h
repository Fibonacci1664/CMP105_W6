#pragma once
#include "Framework/GameObject.h"

class Ball : public GameObject
{
public:
	Ball();
	~Ball();

	void handleInput(float dt) override;
	void update(float dt) override;

protected:


private:

	void gravityFall(float dt);
	void move(float dt);
	void teleportBall(float dt);
	void moveAtoB(float dt);

	int m_mouseX;
	int m_mouseY;

	float m_acceleration;
	float m_gravityScalar;
	float m_jumpScalar;
	sf::Vector2f m_gravitationalAccel;
	sf::Vector2f m_direction;
	sf::Vector2f m_stepVelocity;
};