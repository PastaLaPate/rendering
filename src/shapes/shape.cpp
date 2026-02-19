#include "shapes/shape.h"

Shape::Shape(Vector2 position) : position(position) {}



bool Shape::Collides(Vector2 p) const {
    return contains(p);
}