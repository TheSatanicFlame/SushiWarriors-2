#pragma once

#include "surface.h"
#include "template.h"

namespace Tmpl8 {
    class MouseHandler {
    public:
        MouseHandler(Surface* screen);
        void DrawCursor(int mousex, int mousey);
        void ToggleCursorVisibility();

    private:
        Surface* screen;
        Sprite MouseCursor;
        bool isCursorVisible;
    };
}
