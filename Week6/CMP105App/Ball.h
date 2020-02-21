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
	void chaseMouseCursor(float dt);
	void launch(float dt);

	bool m_flag;

	int m_mouseX;
	int m_mouseY;
	int newMouseX;
	int newMouseY;
	double m_dragDist;


	sf::Vector2f m_maxGravAccel;

	float m_acceleration;
	float m_gravityScalar;
	float m_jumpScalar;
	sf::Vector2f m_gravitationalAccel;
	sf::Vector2f m_direction;
	sf::Vector2f m_stepVelocity;

	sf::Vector2f mouseStartPoint;
	sf::Vector2f mouseEndPoint;
	sf::Vector2f deltaDir;
	float magnitude;
	bool fired = false;
};