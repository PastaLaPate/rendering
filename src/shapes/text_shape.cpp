#include "shapes/text_shape.h"
#include "raylib.h"
#include "rendering/mat3.h"

TextShape::TextShape(Vector2 position, const std::string &text, int fontSize, Color color)
    : Shape(position), text(text), fontSize(fontSize)
{
    this->color = color;
}

void TextShape::render(const Mat3 &cameraMatrix)
{
    Vector2 transformedPosition = cameraMatrix.multiply(position);
    DrawText(text.c_str(), transformedPosition.x, transformedPosition.y, fontSize, color);
}

Rectangle TextShape::getBounds() const
{
    float width = text.length() * (fontSize * 0.6f);
    float height = fontSize;
    return {position.x, position.y, width, height};
}

bool TextShape::contains(Vector2 point) const
{
    auto bounds = getBounds();
    return point.x >= bounds.x && point.x <= bounds.x + bounds.width &&
           point.y >= bounds.y && point.y <= bounds.y + bounds.height;
}

void TextShape::setText(const std::string &newText)
{
    text = newText;
}

void TextShape::setFontSize(int size)
{
    fontSize = size;
}

std::string TextShape::getText() const { return text; }
int TextShape::getFontSize() const { return fontSize; }

// Clickable interface
void TextShape::onMouseDown() {}
void TextShape::onMouseUp() {}
void TextShape::onClick() {}

// Draggable interface
void TextShape::onDrag(float x, float y) { setPosition({x, y}); }
