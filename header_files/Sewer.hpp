#ifndef SEWER_HPP_INCLUDED
#define SEWER_HPP_INCLUDED
#include "Collider.hpp"

//{ cSewer
class cSewer : public cCollider
{
    public:
        cSewer();
        ~cSewer();
};

cSewer::cSewer()
{
    setWidth(128);
    setHeight(188);
}

cSewer::~cSewer()
{
}
//}

#endif // SEWER_HPP_INCLUDED
