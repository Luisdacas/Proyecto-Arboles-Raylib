#include "Boton.hpp"

Boton::Boton(Rectangle r, const std::string& t) {
    rect = r;
    texto = t;
    colorFondo = DARKGRAY;
    colorTexto = RAYWHITE;
}

void Boton::dibujar() {
    DrawRectangleRec(rect, colorFondo);
    DrawText(texto.c_str(), rect.x + 10, rect.y + 10, 16, colorTexto);
}

bool Boton::estaPresionado() {
    Vector2 mouse = GetMousePosition();
    return CheckCollisionPointRec(mouse, rect);
}
