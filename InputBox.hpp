#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "raylib.h"
#include <string>

class InputBox {
private:
    Rectangle box;
    std::string texto;
    bool activa;

public:
    InputBox(Rectangle r);
    void actualizar();
    void dibujar();
    int getValorNumerico();
};

#endif

