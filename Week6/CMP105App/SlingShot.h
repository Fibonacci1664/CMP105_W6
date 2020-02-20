#pragma once
#include "Framework/Animation.h"
#include "Framework\GameObject.h"

class SlingShot : public GameObject
{
public:
	SlingShot();
	~SlingShot();

	virtual void handleInput(float dt) override;
	virtual void update(float dt) override;

private:
	Animation m_slingShot;

	void addFrames();
	void calulateDragDistance();
	void fireMario(float dt);

	int m_mouseX;
	int m_mouseY;
	int newMouseX;
	int newMouseY;

	int m_dragDist;
	bool m_flag;
	bool m_fireMario;

};

