#pragma once
#include "collidable.h"

class Hoverable : public virtual Collidable {
    public:
        virtual void onHoverStart() = 0;
        virtual void onHoverEnd() = 0;
};