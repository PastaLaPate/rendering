#pragma once
#include "collidable.h"

class Hoverable : Collidable {
    public:
        virtual void onHoverStart() = 0;
        virtual void onHoverEnd() = 0;
};