#pragma once

#include <string>
#include "shapes/shape.h"
#include "interfaces/draggable.h"

// Concrete Text shape implementation
class TextShape : public Shape, public Draggable {
public:
    TextShape(Vector2 position = {0, 0}, const std::string& text = "Text", int fontSize = 20, Color color = WHITE);
    void render() override;
    Rectangle getBounds() const override;
    bool contains(Vector2 point) const override;
    void setText(const std::string& newText);
    void setFontSize(int size);
    std::string getText() const;
    int getFontSize() const;

    // Clickable interface
    void onMouseDown() override;
    void onMouseUp() override;
    void onClick() override;

    // Draggable interface
    void onDrag(float x, float y) override;

private:
    std::string text;
    int fontSize;
};
