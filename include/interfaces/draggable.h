#pragma once
#include "hoverable.h"
#include "clickable.h"

class Draggable : public virtual Hoverable, public virtual Clickable {
    public:
        void onHoverStart() override {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        };
        void onHoverEnd() override {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        };
        void onMouseDown() override {
            onStartDrag();
        };
        void onMouseUp() override {
            onEndDrag();
        };
        void onStartDrag() {
            SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
        };
        virtual void onDrag(float x, float y) = 0;
        void onEndDrag() {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        };

        bool isDraggable() const { return draggingEnabled; }
    protected:
        bool draggingEnabled = true;
        void setDraggingEnabled(bool enabled) { draggingEnabled = enabled; }
};