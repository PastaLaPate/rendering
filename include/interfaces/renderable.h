#pragma once
#include "camera.h"

class Mat3;

class Renderable
{
public:
    virtual void render(const Camera2 &camera) = 0;
};