#pragma once
#include "raylib.h"
#include "rendering/mat3.h"

class Camera2 {
public:
    Camera2() : pos({0, 0}), scale({1, 1}), rotation(0) {}

    void setPosition(const Vector2 &position)
    {
        matrixDirty = true;
        pos = position;
    }

    void setScale(const Vector2 &s)
    {
        matrixDirty = true;
        scale = s;
    }

    void setRotation(float r)
    {
        matrixDirty = true;
        rotation = r;
    }

    Vector2 getPosition() const
    {
        return pos;
    }

    Vector2 getScale() const
    {
        return scale;
    }

    float getRotation() const
    {
        return rotation;
    }

    Mat3 getCameraMatrix() const
    {
        if (matrixDirty) {
            Mat3 translation = Mat3::translation(-pos.x, -pos.y);
            Mat3 rotationMat = Mat3::rotation(rotation);
            Mat3 scaleMat = Mat3::scale(scale.x, scale.y);
            cameraMatrix = scaleMat * rotationMat * translation;
            matrixDirty = false;
        }
        return cameraMatrix;
    }

    Vector2 toWorldPosition(Vector2 screenPos) const
    {
        // Invert the camera transformations to convert screen position to world position
        Mat3 invCameraMatrix = Mat3::translation(pos.x, pos.y) *
                               Mat3::rotation(-rotation) *
                               Mat3::scale(1.0f / scale.x, 1.0f / scale.y);
        return invCameraMatrix.multiply(screenPos);
    }
protected:
    mutable bool matrixDirty = true;
    mutable Mat3 cameraMatrix;
    Vector2 pos;
    Vector2 scale;
    float rotation;
};