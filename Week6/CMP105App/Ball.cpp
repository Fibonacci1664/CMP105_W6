#include "Ball.h"
#include "Player.h"
#include "Framework/Vector.h"


Ball::Ball()
{
	//setVelocity(sf::Vector2f(0.0f, 400.0f));
	m_acceleration = 100.0f;			// Is this the equivalent of our 'm_scale' below and simply acts as a scalar?
	m_direction = sf::Vector2f(5.0f, 0.0f);
	
	m_jumpScalar = 600;

	// Gravitational Accelleration.
	m_gravityScalar = 100;		// What is the purpose of this, is this so we can still keep the nice 9.8 figure as gravity but then just multiply it by a scalar?
	m_gravitationalAccel = sf::Vector2f(0, 9.8) * m_gravityScalar;

	m_mouseX = 0;
	m_mouseY = 0;
}

Ball::~Ball()
{

}

void Ball::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		m_stepVelocity = sf::Vector2f(0, -1.0f) * m_jumpScalar;
	}

	if (input->isMouseLDown())
	{
		m_stepVelocity = sf::Vector2f(0, 0);
		m_mouseX = input->getMouseX();
		m_mouseY = input->getMouseY();
		//input->setMouseLDown(false);		// Uncomment this line if you dont wish to drag the ball around.
		teleportBall(dt);
	}
}

void Ball::update(float dt)
{
	//move(dt);
	moveAtoB(dt);
	//gravityFall(dt);
}

void Ball::move(float dt)
{
	/*
	 * What are the main differences between the two different ways to create accelleration?
	 * When is it approraite to use which method?
	 * Is one method better than the other for different tasks?
	 */

	m_direction = Vector::normalise(m_direction);		/*
														 * Normalized, thus reducing the y-value of m_direction to 1.0f
														 * so it is no longer 5.0f. This will now need multiplied by some scalar
														 * value e.g. m_acceleration, to be of any use.
														 */

	velocity += (m_direction * m_acceleration) * dt;

	setPosition(getPosition() + (velocity * dt));

	if ((getPosition().y + getSize().y / 2.0f) > window->getSize().y)
	{
		/*
		 * Need to review when it is appropraite to use a Vector2?
		 * My understanding is that we pass in and create a NEW vector2 object when the thing were
		 * passing in does not already exist as an vector2 object, hence we are creating a NEW one.
		 * SEE BELOW!
		 */

		// Shouldn't need to create a new vector2 object here as getPosition() is already a vector2 object, is this correct?
		//setPosition(sf::Vector2f(getPosition().x, window->getSize().y - getSize().y / 2.0f));

		// The above setPosition() function should be more like this.
		setPosition(getPosition().x, window->getSize().y - getSize().y / 2.0f);
		velocity = sf::Vector2f(0, 0);
	}
}

void Ball::gravityFall(float dt)
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

void Ball::teleportBall(float dt)
{
	setPosition(m_mouseX, m_mouseY);
}

void Ball::moveAtoB(float dt)
{
	// My attempt at a chase player solution.
	/*sf::Vector2f playerPos = Player::getPlayerPos();

	sf::Vector2f delta = playerPos - getPosition();
	Vector::normalise(delta);
	velocity = (delta * m_acceleration) * dt;*/

	sf::Vector2f startPoint = sf::Vector2f(getPosition().x, getPosition().y);
	sf::Vector2f endPoint = sf::Vector2f(window->getSize().x, window->getSize().y);
	sf::Vector2f delta = endPoint - startPoint;
	Vector::normalise(delta);
	velocity = (delta * m_acceleration) * dt;
	setPosition(getPosition() + (velocity * dt));
}