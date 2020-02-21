#include<iostream>
#include "Ball.h"
#include "Player.h"
#include "Framework/Vector.h"


Ball::Ball()
{
	//setVelocity(sf::Vector2f(0.0f, 400.0f));

	// USE THIS TYPE OF ACCELERATION FOR WHEN ANY OTHER TYPE OF ACCEL IS REQ OTHER THAN GRAVITY I.E CARS ETC.
	m_acceleration = 10.0f;			// Is this the equivalent of our 'm_scale' below and simply acts as a scalar value?
	m_direction = sf::Vector2f(5.0f, 0.0f);
	
	m_jumpScalar = 600;

	// Gravitational Accelleration. USE THIS FOR WHEN GRAVITY IS NEEDED.
	m_gravityScalar = 100;		// What is the purpose of this, is this so we can still keep the nice 9.8 figure as gravity but then just multiply it by a scalar?
	m_gravitationalAccel = sf::Vector2f(0, 9.8) * m_gravityScalar;

	m_mouseX = 0;
	m_mouseY = 0;
	m_flag = false;
	m_mouseX = 0;
	m_mouseY = 0;
	newMouseX = 0;
	newMouseY = 0;
	m_dragDist = 0;

	m_maxGravAccel = sf::Vector2f(0.0f, 750.0f);
}

Ball::~Ball()
{
	std::cout << "Ball object destoryed!\n";
}

void Ball::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		m_stepVelocity = sf::Vector2f(0, -1.0f) * m_jumpScalar;
	}

	launch(dt);

	//if (input->isMouseLDown())
	//{
	//	//input->setMouseLDown(false);		// Uncomment this line if you dont wish to drag the ball around.	//	m_stepVelocity = sf::Vector2f(0, 0);
	//	
	//	//teleportBall(dt);
	//}
}

void Ball::update(float dt)
{
	//move(dt);
	//moveAtoB(dt);
	//chaseMouseCursor(dt);
	gravityFall(dt);
}

void Ball::move(float dt)
{
	/*
	 * What are the main differences between the two different ways to create accelleration?
	 * When is it approraite to use which method?
	 * Is one method better than the other for different tasks?
	 */

	m_direction = Vector::normalise(m_direction);		/*
														 * Normalized, thus reducing the y-value of m_direction to a unit vector (NOT NECESSARILY 1)
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

	/*
	 * Check to make sure that if we keep spamming the beach ball that its accel doesnt keep increasing forever
	 * As without this check the only time velocity will be controlled is if the ball strikes the 'ground'.
	 */
	if (Vector::magnitude(m_stepVelocity) > Vector::magnitude(m_maxGravAccel))
	{
		m_stepVelocity = m_maxGravAccel;
	}

	// If the ball hits the 'ground', bounce.
	if ((getPosition().y + getSize().y / 2.0f) > window->getSize().y)
	{
		setPosition(getPosition().x, window->getSize().y - getSize().y / 2.0f);
		m_stepVelocity = (-m_stepVelocity) / 1.2f;
	}
}

void Ball::teleportBall(float dt)
{
	setPosition(m_mouseX, m_mouseY);
}

void Ball::moveAtoB(float dt)
{
	sf::Vector2f startPoint = sf::Vector2f(getPosition().x, getPosition().y);
	sf::Vector2f endPoint = sf::Vector2f(window->getSize().x, window->getSize().y);
	sf::Vector2f delta = endPoint - startPoint;
	delta = Vector::normalise(delta);

	// Here we are NOT using += as we are NOT accelerating we are simply moving A to B at a constant velocity.
	velocity = (delta * m_acceleration) * dt;
	setPosition(getPosition() + velocity);
}

void Ball::chaseMouseCursor(float dt)
{
	m_mouseX = input->getMouseX();
	m_mouseY = input->getMouseY();

	sf::Vector2f startPoint = sf::Vector2f(getPosition().x, getPosition().y);		// Balls position.
	sf::Vector2f endPoint = sf::Vector2f(m_mouseX, m_mouseY);						// Mouse cursor position.
	sf::Vector2f deltaDir = endPoint - startPoint;									// The distance between.

	deltaDir = Vector::normalise(deltaDir);

	velocity += (deltaDir * m_acceleration) * dt;

	setPosition(getPosition() + (velocity * dt));

	sf::Vector2f ballPos = getPosition();
	sf::Vector2f distanceBetween = endPoint - ballPos;
	float mag = Vector::magnitude(distanceBetween);

	if (mag < getSize().x / 2.0f || mag < getSize().y / 2.0f)
	{
		velocity = sf::Vector2f(0, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// NEED HELP FIGURING THIS OUT! THIS IS NOT WORKING AS INTENDED.
void Ball::launch(float dt)
{
	// If we've clicked the left mouse button, set where that happened.
	if (input->isMouseLDown() && !m_flag)
	{
		m_flag = true;
		mouseStartPoint = sf::Vector2f(input->getMouseX(), input->getMouseY());				// Where we first click.
	}

	// If we release the left mouse button.
	if (!input->isMouseLDown() && m_flag)
	{
		m_flag = false;
		mouseEndPoint = sf::Vector2f(input->getMouseX(), input->getMouseY());				// Where we release the left mouse button.

		// We are doing this the opposite way than normal i.e. (end - start) otherwise we end up with neg vel.
		deltaDir = mouseStartPoint - mouseEndPoint;											// The distance between click and release.

		// PRINT MAG.
		magnitude = Vector::magnitude(deltaDir);
		std::cout << "Mag : " << magnitude << '\n';

		//deltaDir = Vector::normalise(deltaDir);								// No point in normalising and then multiplying by mag as this just resluts in the original deltaDir vector.
		//velocity = (deltaDir * m_acceleration) * dt;

		fired = true;
	}

	std::cout << "Norm deltaDir X : " << deltaDir.x << " Norm deltaDir Y : " << deltaDir.y << '\n';

	setPosition(getPosition() + (deltaDir * m_acceleration * dt));

	/*
	 * If we have 'fired' the ball we need to reduce incrementally the delta that is being added to the set position each
	 * each frame by a fixed amount until such time as the delta becomes less than a threshold amount at which point we
	 * set the delta to zero and fired to false, meaning that the delta reduction will stop happening until such time as another
	 * ball is 'fired'.
	 */
	if (fired)
	{
		deltaDir = deltaDir / 1.1f;						// Reduce delta incrementally.

		if (Vector::magnitude(deltaDir) < 5)			// If delta drops below threshold.
		{
			deltaDir = sf::Vector2f(0, 0);				// Set to zero
			fired = false;
		}
	}

	if (getPosition().x + getSize().x / 2.0f > window->getSize().x)
	{
		// This is wrong! fix it.
		//setPosition(getPosition());
	}
}