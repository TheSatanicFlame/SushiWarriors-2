#include "MouseHandler.h"

namespace Tmpl8 {
    MouseHandler::MouseHandler(Surface* screen)
        : screen(screen), MouseCursor(new Surface("assets/pointer.png"), 1), isCursorVisible(true) {}

    void MouseHandler::DrawCursor(int mousex, int mousey) {
        if (isCursorVisible) {
            MouseCursor.DrawScaled(mousex, mousey, 32, 32, screen);
        }
    }

    void MouseHandler::ToggleCursorVisibility() {
        isCursorVisible = !isCursorVisible;
    }
}
