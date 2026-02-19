#pragma once
#include "collidable.h"

class Clickable : public virtual Collidable  {
    public:
        virtual void onMouseDown(){};
        virtual void onMouseUp(){};
        virtual void onClick(){};
};