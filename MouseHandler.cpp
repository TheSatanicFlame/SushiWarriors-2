#include "MouseHandler.h" // include the header file that contains the class declaration

namespace Tmpl8 {
    MouseHandler::MouseHandler(Surface* screen) // constructor that takes a pointer to a surface as argument
        : screen(screen), MouseCursor(new Surface("assets/pointer.png"), 1), isCursorVisible(true) {} // initialize the screen pointer and the MouseCursor object

    void MouseHandler::DrawCursor(int mousex, int mousey) { // function that draws the cursor at the specified position
        if (isCursorVisible) { // check if the cursor is visible
            MouseCursor.DrawScaled(mousex, mousey, 32, 32, screen); // draw the cursor at the specified position
        }
    }

    void MouseHandler::ToggleCursorVisibility() { // function that toggles the visibility of the cursor
        isCursorVisible = !isCursorVisible; // toggle the visibility of the cursor
    }
}
