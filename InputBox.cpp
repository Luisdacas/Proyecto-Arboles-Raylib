#include "InputBox.hpp"

InputBox::InputBox(Rectangle r) {
    box = r;
    texto = "";
    activa = false;
}

void InputBox::actualizar() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        activa = CheckCollisionPointRec(mouse, box);
    }

    if (activa) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= '0' && key <= '9') {
                texto += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !texto.empty()) {
            texto.pop_back();
        }
    }
}

void InputBox::dibujar() {
    DrawRectangleLinesEx(box, 2, activa ? RED : BLACK);
    DrawText(texto.c_str(), box.x + 5, box.y + 10, 20, BLACK);
}

int InputBox::getValorNumerico() {
    return texto.empty() ? 0 : std::stoi(texto);
}
