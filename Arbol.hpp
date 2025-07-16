#ifndef ARBOL_HPP
#define ARBOL_HPP

#include "raylib.h"
#include <string>
#include "Utilidades.hpp"
#include <cmath>
#include <thread>
#include <chrono>

struct Nodo {
    int dato;
    int altura;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;
    float x, y;
    Color color;

    Nodo(int v) : dato(v), altura(1), izq(nullptr), der(nullptr), padre(nullptr), x(0), y(0), color(Util::COLOR_NODO) {}
};

class Arbol {
private:
    Nodo* raiz;
    static const int MAX_RECORRIDO = 128;
    Nodo* recorridoActual[MAX_RECORRIDO];
    int recorridoTam;
    Nodo* ultimoNodoEncontrado;
    std::string recorridoTexto;

    Nodo* insertarAVL(Nodo* nodo, int valor);
    Nodo* eliminarAVL(Nodo* nodo, int valor, bool usarMenor);
    Nodo* rotarIzq(Nodo* y);
    Nodo* rotarDer(Nodo* x);
    int altura(Nodo* nodo);
    int balance(Nodo* nodo);
    void actualizarPosiciones(Nodo* nodo, float x, float y, float offset);
    void dibujarRecursivo(Nodo* nodo);
    void dibujarAnillo(Nodo* nodo);
    void dormir(int ms);

    int calcularGrado(Nodo* nodo);

    void recorrer(Nodo* nodo, const std::string& tipo);
    void recorrerPasoAPaso(Nodo* nodo, const std::string& tipo);

    bool buscarPasoAPasoProf(Nodo* nodo, int valor);
    bool buscarPasoAPasoAnch(int valor);

    Nodo* buscarMinimo(Nodo* nodo);
    Nodo* buscarMaximo(Nodo* nodo);
    void reiniciarColoresRec(Nodo* nodo);

public:
    Arbol();
    void insertarAnimado(int valor);
    void eliminarMayorDeMenores(int valor);
    void eliminarMenorDeMayores(int valor);
    bool buscarProfundidadAnimada(int valor);
    bool buscarAnchuraAnimada(int valor);
    std::string recorrerAnimado(const std::string& tipo);
    void dibujar();
    void resetearColores();
    int getUltimoEncontrado() const;
    int obtenerAltura();
    int obtenerGrado();
    bool existe(int valor) const;
};

#endif
