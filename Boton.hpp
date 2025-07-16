#ifndef BOTON_HPP
#define BOTON_HPP

#include "raylib.h"
#include <string>

class Boton {
private:
    Rectangle rect;
    std::string texto;
    Color colorFondo;
    Color colorTexto;

public:
    Boton(Rectangle r, const std::string& t);
    void dibujar();
    bool estaPresionado();
};

#endif
