#pragma once
#include "raylib.h"

struct Collidable
{
    virtual bool Collides(Vector2 p) const = 0;
};