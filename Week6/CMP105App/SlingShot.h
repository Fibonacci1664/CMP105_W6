#pragma once
#include "Framework/Animation.h"
#include "Framework/GameObject.h"
#include "Ball.h"

class SlingShot : public GameObject
{
public:
	SlingShot();
	~SlingShot();

	virtual void handleInput(float dt) override;
	virtual void update(float dt) override;

private:

	void addFrames();
	void calulateDragDistance();
	void fireBall(float dt);
	void loadTextures();
	void initBall();

	int m_mouseX;
	int m_mouseY;
	int newMouseX;
	int newMouseY;

	double m_dragDist;
	bool m_flag;
	bool m_fireMario;

};

