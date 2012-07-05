#ifndef FIREBALL_HPP_INCLUDED
#define FIREBALL_HPP_INCLUDED
#include "Collider.hpp"

//{ cFireball
class cFireball : public cCollider
{
    public:
        cFireball();
        ~cFireball();
        sf::Vector2f getMovement();

    private:
        float xSpeed, xAccel, ySpeed, yAccel;
        //bool onGround, isDead, reset;
};

cFireball::cFireball()
{
    setWidth(32);
    setHeight(32);
    xSpeed = 6;
}

cFireball::~cFireball()
{
}

sf::Vector2f cFireball::getMovement() // TODO improve fireball motion
{
    sf::Vector2f movementVector;

    if (isOnGround()) {
        ySpeed = -8;
        yAccel = 0;
    }
    yAccel += .3;

    movementVector.x = xSpeed;
    movementVector.y = ySpeed + yAccel;
    return movementVector;
}
//}

#endif // FIREBALL_HPP_INCLUDED
