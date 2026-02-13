#include "raylib.h"
#include "interfaces/renderable.h"
#include "interfaces/draggable.h"

class Point : public Renderable, Draggable {
    public:
        Point(float x, float y) : position{x, y} {}
        Vector2 position;
        void render() override {
            DrawCircle(position.x, position.y, 5, RED);
        }
        bool Collides(Vector2 p) const override {
            return p.x * p.x + p.y * p.y <= 5 * 5; // Check if the point is within a radius of 5
        }
        void onDrag(float x, float y) override {
            position.x = x;
            position.y = y;
        }
};