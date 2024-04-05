#pragma once

#include "surface.h" // include the surface header file
#include "template.h" // include the template header file

namespace Tmpl8 { // use the template namespace
    class MouseHandler { // define the MouseHandler class
    public: // public access specifier
        MouseHandler(Surface* screen); // constructor that takes a pointer to a surface as argument
        void DrawCursor(int mousex, int mousey); // function that draws the cursor at the specified position
        void ToggleCursorVisibility(); // function that toggles the visibility of the cursor

    private: // private access specifier
        Surface* screen; // pointer to a surface
        Sprite MouseCursor; // sprite object for the cursor
        bool isCursorVisible; // flag to indicate if the cursor is visible
    };
}
