#include "SlingShot.h"
#include "Player.h"


SlingShot::SlingShot()
{
	m_mouseX = 0;
	m_mouseY = 0;
	newMouseX = 0;
	newMouseY = 0;
	m_dragDist = 0;

	input->setMouseLDown(false);
	m_flag = false;
	m_fireMario = false;
}

SlingShot::~SlingShot()
{

}

void SlingShot::handleInput(float dt)
{

}

void SlingShot::update(float dt)
{
	fireMario(dt);
}

void SlingShot::fireMario(float dt)
{
	Player mario;
}

void SlingShot::addFrames()
{

}

void SlingShot::calulateDragDistance()
{
	// If we've clicked the left mouse button, set where that happened.
	if (input->isMouseLDown() && !m_flag)
	{
		m_flag = true;
		m_mouseX = input->getMouseX();
		m_mouseY = input->getMouseY();
	}

	// While we continue to hold down the left mouse button, keep updating the end position.
	if (input->isMouseLDown())
	{
		newMouseX = input->getMouseX();
		newMouseY = input->getMouseY();
	}

	// If we release the left mouse button.
	if (!input->isMouseLDown())
	{
		m_flag = false;

		int deltaX = newMouseX - m_mouseX;
		int deltaY = newMouseY - m_mouseY;

		m_dragDist = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		m_fireMario = true;
	}
}
