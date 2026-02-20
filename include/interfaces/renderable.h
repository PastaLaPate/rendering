#pragma once

class Mat3;

class Renderable
{
public:
    virtual void render(const Mat3 &cameraMatrix) = 0;
};