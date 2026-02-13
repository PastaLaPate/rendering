#pragma once
#include "collidable.h"

class Clickable : Collidable  {
    public:
        virtual void onMouseDown(){};
        virtual void onMouseUp(){};
        virtual void onClick(){};
};