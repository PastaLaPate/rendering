#pragma once

#include "shape.h"
#include <cmath>
#include <iostream>

// Concrete Triangle shape implementation
class TriangleShape : public Shape {
public:
    TriangleShape(Vector2 position = {0, 0}, Vector2 point2 = {50, 100}, Vector2 point3 = {100, 0}, Color color = WHITE)
        : Shape(position), p2(point2), p3(point3) {
        this->color = color;
    }
    
    void render() override {
        DrawTriangle(position, p2, p3, color);
    }
    
    Rectangle getBounds() const override {
        float minX = fmin(fmin(position.x, p2.x), p3.x);
        float maxX = fmax(fmax(position.x, p2.x), p3.x);
        float minY = fmin(fmin(position.y, p2.y), p3.y);
        float maxY = fmax(fmax(position.y, p2.y), p3.y);
        return {minX, minY, maxX - minX, maxY - minY};
    }
    
    bool contains(Vector2 point) const override {
        // Proper barycentric coordinate method for point-in-triangle test
        auto sign = [](Vector2 p1, Vector2 p2, Vector2 p3) {
            return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        };
        
        float d1 = sign(point, position, p2);
        float d2 = sign(point, p2, p3);
        float d3 = sign(point, p3, position);
        
        // All same sign (including zero) means the point is inside
        bool allNonNegative = (d1 >= 0) && (d2 >= 0) && (d3 >= 0);
        bool allNonPositive = (d1 <= 0) && (d2 <= 0) && (d3 <= 0);
        
        return allNonNegative || allNonPositive;
    }
    
    void setVertices(Vector2 p1, Vector2 p2, Vector2 p3) {
        position = p1;
        this->p2 = p2;
        this->p3 = p3;
    }
    
    void setPosition(Vector2 newPosition) override {
        // Calculate offset from current position
        Vector2 offset = {newPosition.x - position.x, newPosition.y - position.y};
        // Move all three vertices by the same offset
        position = newPosition;
        p2.x += offset.x;
        p2.y += offset.y;
        p3.x += offset.x;
        p3.y += offset.y;
    }
    
    Vector2 getVertex2() const { return p2; }
    Vector2 getVertex3() const { return p3; }
    
private:
    Vector2 p2;
    Vector2 p3;
};
