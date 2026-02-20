#pragma once

class Scene;
class Mat3;

class Renderable
{
public:
    virtual void render(const Scene &scene) = 0;
};