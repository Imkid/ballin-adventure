#ifndef MARIO_HPP_INCLUDED
#define MARIO_HPP_INCLUDED
#include "Collider.hpp"

//{ cMario
class cMario : public cCollider
{
    public:
        cMario();
        ~cMario();
        sf::Vector2f getMovement();

        void reset(sf::Sprite & rThisSprite);

    private:
        float xSpeed, xAccel, ySpeed, yAccel;
        //bool onGround, isDead, reset;

};

cMario::cMario()
{
    setWidth(64);
    setHeight(128);
    xSpeed = 3;
}

cMario::~cMario()
{
}

sf::Vector2f cMario::getMovement(void)
{
    sf::Vector2f movementVector;

    if (!getIsDead()) {
        if (isOnGround()) {
        ySpeed = -8;
        yAccel = 0;
        xAccel = rand() % 4;
        }
    }
    yAccel += .3;

    movementVector.x = xSpeed + xAccel;
    movementVector.y = ySpeed + yAccel;
    return movementVector;
}

void cMario::reset(sf::Sprite & rThisSprite)
{
    rThisSprite.SetX(200);
    rThisSprite.SetY(200);
    xSpeed = 0;
    xAccel = 0;
    ySpeed = 0;
    yAccel = 0;
    setIsDead(false);
}
//}

#endif // MARIO_HPP_INCLUDED
