#include "raylib.h"
#include "Arbol.hpp"
#include "Boton.hpp"
#include "InputBox.hpp"

const int screenWidth = 1280;
const int screenHeight = 720;

int main() {
    InitWindow(screenWidth, screenHeight, "Árbol AVL Visual - Raylib");
    SetTargetFPS(60);

    Arbol arbol;

    Boton botonInsertar({20, 20, 160, 40}, "Insertar");
    Boton botonEliminarMin({20, 70, 160, 40}, "Eliminar > Menores");
    Boton botonEliminarMax({20, 120, 160, 40}, "Eliminar < Mayores");
    Boton botonBuscarProf({20, 170, 160, 40}, "Buscar Profundidad");
    Boton botonBuscarAnch({20, 220, 160, 40}, "Buscar Anchura");
    Boton botonPre({20, 270, 160, 40}, "Preorden");
    Boton botonIn({20, 320, 160, 40}, "Inorden");
    Boton botonPost({20, 370, 160, 40}, "Postorden");

    InputBox inputValor({200, 20, 100, 40});
    InputBox inputEliminar({200, 70, 100, 40});
    InputBox inputEliminar2({200, 120, 100, 40});
    InputBox inputBuscar1({200, 170, 100, 40});
    InputBox inputBuscar2({200, 220, 100, 40});

    std::string mensaje = "";

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (botonInsertar.estaPresionado()) {
                arbol.resetearColores();
                arbol.insertarAnimado(inputValor.getValorNumerico());
                mensaje = "";
            } else if (botonEliminarMin.estaPresionado()) {
                arbol.resetearColores();
                int val = inputEliminar.getValorNumerico();
                if (arbol.existe(val)) {
                    arbol.eliminarMayorDeMenores(val);
                    mensaje = "Numero eliminado: " + std::to_string(val);
                } else {
                    mensaje = "Numero no encontrado";
                }
            } else if (botonEliminarMax.estaPresionado()) {
                arbol.resetearColores();
                int val = inputEliminar2.getValorNumerico();
                if (arbol.existe(val)) {
                    arbol.eliminarMenorDeMayores(val);
                    mensaje = "Numero eliminado: " + std::to_string(val);
                } else {
                    mensaje = "Numero no encontrado";
                }
            } else if (botonBuscarProf.estaPresionado()) {
                arbol.resetearColores();
                bool f = arbol.buscarProfundidadAnimada(inputBuscar1.getValorNumerico());
                mensaje = f ? (std::string("Numero Encontrado: ") + std::to_string(arbol.getUltimoEncontrado())) : "Numero no Encontrado: none";
            } else if (botonBuscarAnch.estaPresionado()) {
                arbol.resetearColores();
                bool f = arbol.buscarAnchuraAnimada(inputBuscar2.getValorNumerico());
                mensaje = f ? (std::string("Numero Encontrado: ") + std::to_string(arbol.getUltimoEncontrado())) : "Numero no Encontrado: none";
            } else if (botonPre.estaPresionado()) {
                arbol.resetearColores();
                mensaje = arbol.recorrerAnimado("preorden");
            } else if (botonIn.estaPresionado()) {
                arbol.resetearColores();
                mensaje = arbol.recorrerAnimado("inorden");
            } else if (botonPost.estaPresionado()) {
                arbol.resetearColores();
                mensaje = arbol.recorrerAnimado("postorden");
            }
        }

        inputValor.actualizar();
        inputEliminar.actualizar();
        inputEliminar2.actualizar();
        inputBuscar1.actualizar();
        inputBuscar2.actualizar();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, 300, screenHeight, LIGHTGRAY);
        botonInsertar.dibujar();
        botonEliminarMin.dibujar();
        botonEliminarMax.dibujar();
        botonBuscarProf.dibujar();
        botonBuscarAnch.dibujar();
        botonPre.dibujar();
        botonIn.dibujar();
        botonPost.dibujar();

        inputValor.dibujar();
        inputEliminar.dibujar();
        inputEliminar2.dibujar();
        inputBuscar1.dibujar();
        inputBuscar2.dibujar();

        arbol.dibujar();

        DrawText(mensaje.c_str(), 320, screenHeight - 30, 20, DARKBLUE);
        std::string info = "Grado: " + std::to_string(arbol.obtenerGrado()) +
                           " Altura: " + std::to_string(arbol.obtenerAltura());
        int w = MeasureText(info.c_str(), 20);
        DrawText(info.c_str(), screenWidth - w - 10, screenHeight - 30, 20, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
