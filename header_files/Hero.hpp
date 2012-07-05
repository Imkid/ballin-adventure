#ifndef HERO_HPP_INCLUDED
#define HERO_HPP_INCLUDED
#include "Collider.hpp"

//{ cHero
class cHero : public cCollider
{
    public:
        cHero(sf::Sprite & rHeroSprite);
        ~cHero();
        sf::Vector2f getMovement(const sf::Input & theInput, sf::Clock & jumpClock);
        void stopMotion();

    private:
        float xSpeed, xAccel, ySpeed, yAccel;
};

cHero::cHero(sf::Sprite & rHeroSprite)
{
    rHeroSprite.SetSubRect(sf::IntRect(4, 4, 67, 67));
    rHeroSprite.SetCenter(0, 64);
    rHeroSprite.SetX(600);
    rHeroSprite.SetY(762);
    setWidth(64);
    setHeight(64);
}

cHero::~cHero()
{
}

void cHero::stopMotion(void)
{
    xSpeed = 0;
    xAccel = 0;
    ySpeed = 0;
    yAccel = 0;
}

sf::Vector2f cHero::getMovement(const sf::Input & theInput, sf::Clock & jumpClock)
{
    sf::Vector2f movementVector;
    xSpeed = 0;
    ySpeed = 0;

    // horizontal movement
    if (theInput.IsKeyDown(sf::Key::Left)) {
        xSpeed += -5;
        xAccel += -.2;
    }
    else if (theInput.IsKeyDown(sf::Key::Right)) {
        xSpeed += 5;
        xAccel += .2;
    }


    // vertical movement
    if (theInput.IsKeyDown(sf::Key::Up)) {
        if (isOnGround()) {
            jumpClock.Reset();
            //ySpeed = -8;
        }
        if (jumpClock.GetElapsedTime() < .3) {
            yAccel -= .12 / (jumpClock.GetElapsedTime());
            ySpeed = 30 * (jumpClock.GetElapsedTime() - .3);
        }
    }
    if (isOnGround()) {
        yAccel = 0;
        if (xAccel > .2)
            xAccel -= .05;
        else if (xAccel < -.2)
            xAccel += .05;
    }
    else {
        yAccel += 1 + (jumpClock.GetElapsedTime() / 20);
    }

    movementVector.x = xSpeed + xAccel;
    movementVector.y = ySpeed + yAccel;

    return movementVector;
}
//}

#endif // HERO_HPP_INCLUDED
