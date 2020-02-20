#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt) override;
	void handleInput(float dt) override;


protected:
	Animation run;
	Animation swim;
	Animation duck;

private:
	const int runFrames = 4;
	const int swimFrames = 3;
	const int duckFrames = 2;

	const int FRAME_WIDTH = 15;
	const int FRAME_HEIGHT = 21;

	bool movingLeft;
	bool movingRight;
	bool ducking;

	void addFrames();




	void gravityFall(float dt);

	float m_gravityScalar;
	float m_jumpScalar;
	sf::Vector2f m_gravitationalAccel;
	sf::Vector2f m_stepVelocity;

};

