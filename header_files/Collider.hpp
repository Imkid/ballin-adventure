#ifndef COLLIDER_HPP_INCLUDED
#define COLLIDER_HPP_INCLUDED

//{ cCollider
class cCollider
{
    private:
        float minX, maxX, minY, maxY, width, height;
        bool onGround, isDead;

    public:
        cCollider();
        ~cCollider();

        // accessor methods (using minX and maxY because the center is the bottom left corner of collider)
        void setMinX(float x);
        void setMaxY(float y);
        void setWidth(float w);
        void setHeight(float h);
        void setOnGround(bool t);
        void setIsDead(bool t);
        bool getIsDead();
        bool isOnGround();
        float getMinX();    // might not need getters because of sprite.getposition
        float getMaxY();
        void getCoordinates(sf::Sprite& thisSprite);
        bool checkCollisions(cCollider otherObject);

        void reset();

        // making sprite and spritePtr public
        sf::Sprite colliderSprite;
        sf::Sprite * colliderSpritePtr;


};

//{ getters, setters, constructor/destructor for cCollider
cCollider::cCollider()
{
//    *colliderSpritePtr = &colliderSprite;
    isDead = false;
}

cCollider::~cCollider()
{
}

void cCollider::setMaxY(float y)
{
    maxY = y;
}

float cCollider::getMaxY(void)
{
    return maxY;
}

void cCollider::setMinX(float x)
{
    minX = x;
}

float cCollider::getMinX(void)
{
    return minX;
}

void cCollider::setWidth(float w)
{
    width = w;
}

void cCollider::setHeight(float h)
{
    height = h;
}

void cCollider::setOnGround(bool t)
{
    onGround = t;
}

bool cCollider::isOnGround(void)
{
    return onGround;
}

void cCollider::setIsDead(bool t)
{
    isDead = t;
}

bool cCollider::getIsDead(void)
{
    return isDead;
}
//}

bool cCollider::checkCollisions(cCollider otherObject)
{
    if (maxX > otherObject.minX && minX < otherObject.maxX && maxY > otherObject.minY && minY < otherObject.maxY)
        return true;
    return false;
}

void cCollider::getCoordinates(sf::Sprite& thisSprite)
{
    setMinX(thisSprite.GetPosition().x);
    setMaxY(thisSprite.GetPosition().y);
    if (maxY > 763) {
        setOnGround(true);
        //rThisSprite.SetY(763);
    }
    else {
        setOnGround(false);
    }
    maxX = minX + width;
    minY = maxY - height;
}
//}

#endif // COLLIDER_HPP_INCLUDED
