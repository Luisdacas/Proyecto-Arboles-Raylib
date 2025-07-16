#include "Arbol.hpp"

Arbol::Arbol() {
    raiz = nullptr;
    recorridoTexto = "";
    recorridoTam = 0;
    ultimoNodoEncontrado = nullptr;
}

int Arbol::altura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int Arbol::balance(Nodo* nodo) {
    return nodo ? altura(nodo->izq) - altura(nodo->der) : 0;
}

Nodo* Arbol::rotarIzq(Nodo* y) {
    Nodo* x = y->der;
    Nodo* T2 = x->izq;

    x->izq = y;
    y->der = T2;

    y->altura = std::max(altura(y->izq), altura(y->der)) + 1;
    x->altura = std::max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

Nodo* Arbol::rotarDer(Nodo* x) {
    Nodo* y = x->izq;
    Nodo* T2 = y->der;

    y->der = x;
    x->izq = T2;

    x->altura = std::max(altura(x->izq), altura(x->der)) + 1;
    y->altura = std::max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

Nodo* Arbol::insertarAVL(Nodo* nodo, int valor) {
    if (!nodo) return new Nodo(valor);

    if (valor < nodo->dato)
        nodo->izq = insertarAVL(nodo->izq, valor);
    else if (valor > nodo->dato)
        nodo->der = insertarAVL(nodo->der, valor);
    else
        return nodo;

    nodo->altura = 1 + std::max(altura(nodo->izq), altura(nodo->der));

    int balanceFactor = balance(nodo);


    if (balanceFactor > 1 && valor < nodo->izq->dato)
        return rotarDer(nodo);
    if (balanceFactor < -1 && valor > nodo->der->dato)
        return rotarIzq(nodo);
    if (balanceFactor > 1 && valor > nodo->izq->dato) {
        nodo->izq = rotarIzq(nodo->izq);
        return rotarDer(nodo);
    }
    if (balanceFactor < -1 && valor < nodo->der->dato) {
        nodo->der = rotarDer(nodo->der);
        return rotarIzq(nodo);
    }

    return nodo;
}

Nodo* Arbol::buscarMinimo(Nodo* nodo) {
    while (nodo->izq) nodo = nodo->izq;
    return nodo;
}

Nodo* Arbol::buscarMaximo(Nodo* nodo) {
    while (nodo->der) nodo = nodo->der;
    return nodo;
}

Nodo* Arbol::eliminarAVL(Nodo* nodo, int valor, bool usarMenor) {
    if (!nodo) return nodo;

    if (valor < nodo->dato)
        nodo->izq = eliminarAVL(nodo->izq, valor, usarMenor);
    else if (valor > nodo->dato)
        nodo->der = eliminarAVL(nodo->der, valor, usarMenor);
    else {
        if (!nodo->izq || !nodo->der) {
            Nodo* temp = nodo->izq ? nodo->izq : nodo->der;
            delete nodo;
            return temp;
        }

        Nodo* reemplazo = usarMenor ? buscarMaximo(nodo->izq) : buscarMinimo(nodo->der);
        nodo->dato = reemplazo->dato;
        if (usarMenor)
            nodo->izq = eliminarAVL(nodo->izq, reemplazo->dato, usarMenor);
        else
            nodo->der = eliminarAVL(nodo->der, reemplazo->dato, usarMenor);
    }

    nodo->altura = 1 + std::max(altura(nodo->izq), altura(nodo->der));
    int balanceFactor = balance(nodo);

    if (balanceFactor > 1 && balance(nodo->izq) >= 0)
        return rotarDer(nodo);
    if (balanceFactor > 1 && balance(nodo->izq) < 0) {
        nodo->izq = rotarIzq(nodo->izq);
        return rotarDer(nodo);
    }
    if (balanceFactor < -1 && balance(nodo->der) <= 0)
        return rotarIzq(nodo);
    if (balanceFactor < -1 && balance(nodo->der) > 0) {
        nodo->der = rotarDer(nodo->der);
        return rotarIzq(nodo);
    }

    return nodo;
}

void Arbol::insertarAnimado(int valor) {
    raiz = insertarAVL(raiz, valor);
    actualizarPosiciones(raiz, 850, 60, 200);
    dormir(1000);  // 4 segundos
}

void Arbol::eliminarMayorDeMenores(int valor) {
    raiz = eliminarAVL(raiz, valor, true);
    actualizarPosiciones(raiz, 850, 60, 200);
    dormir(1000);
}

void Arbol::eliminarMenorDeMayores(int valor) {
    raiz = eliminarAVL(raiz, valor, false);
    actualizarPosiciones(raiz, 850, 60, 200);
    dormir(1000);
}

bool Arbol::buscarPasoAPasoProf(Nodo* nodo, int valor) {
    recorridoTam = 0;
    while (nodo) {
        if (recorridoTam < MAX_RECORRIDO) recorridoActual[recorridoTam++] = nodo;
        if (valor == nodo->dato) { ultimoNodoEncontrado = nodo; return true; }
        nodo = (valor < nodo->dato) ? nodo->izq : nodo->der;
    }
    ultimoNodoEncontrado = nullptr;
    return false;
}

bool Arbol::buscarPasoAPasoAnch(int valor) {
    recorridoTam = 0;
    if (!raiz) { ultimoNodoEncontrado = nullptr; return false; }
    Nodo* cola[MAX_RECORRIDO];
    int ini = 0, fin = 0;
    cola[fin++] = raiz;
    while (ini < fin) {
        Nodo* actual = cola[ini++];
        if (recorridoTam < MAX_RECORRIDO) recorridoActual[recorridoTam++] = actual;
        if (actual->dato == valor) { ultimoNodoEncontrado = actual; return true; }
        if (actual->izq && fin < MAX_RECORRIDO) cola[fin++] = actual->izq;
        if (actual->der && fin < MAX_RECORRIDO) cola[fin++] = actual->der;
    }
    ultimoNodoEncontrado = nullptr;
    return false;
}

bool Arbol::buscarProfundidadAnimada(int valor) {
    bool encontrado = buscarPasoAPasoProf(raiz, valor);
    recorridoTexto = "";
    for (int i = 0; i < recorridoTam; ++i) {
        Nodo* nodo = recorridoActual[i];
        actualizarPosiciones(raiz, 850, 60, 200);
        dibujar();
        dibujarAnillo(nodo);
        DrawText("Buscando...", 320, 680, 20, RED);
        EndDrawing();
        dormir(1000);
        recorridoTexto += std::to_string(nodo->dato) + " ";
    }
    if (encontrado && ultimoNodoEncontrado)
        ultimoNodoEncontrado->color = GREEN;
    return encontrado;
}

bool Arbol::buscarAnchuraAnimada(int valor) {
    bool encontrado = buscarPasoAPasoAnch(valor);
    recorridoTexto = "";
    for (int i = 0; i < recorridoTam; ++i) {
        Nodo* nodo = recorridoActual[i];
        actualizarPosiciones(raiz, 850, 60, 200);
        dibujar();
        dibujarAnillo(nodo);
        DrawText("Buscando...", 320, 680, 20, RED);
        EndDrawing();
        dormir(1000);
        recorridoTexto += std::to_string(nodo->dato) + " ";
    }
    if (encontrado && ultimoNodoEncontrado)
        ultimoNodoEncontrado->color = GREEN;
    return encontrado;
}

std::string Arbol::recorrerAnimado(const std::string& tipo) {
    recorridoTam = 0;
    recorrerPasoAPaso(raiz, tipo);
    recorridoTexto = "";
    for (int i = 0; i < recorridoTam; ++i) {
        Nodo* nodo = recorridoActual[i];
        actualizarPosiciones(raiz, 850, 60, 200);
        dibujar();
        dibujarAnillo(nodo);
        DrawText("Recorriendo...", 320, 680, 20, BLUE);
        EndDrawing();
        dormir(1000);
        recorridoTexto += std::to_string(nodo->dato) + " ";
    }
    return "Recorrido: " + recorridoTexto;
}

void Arbol::recorrerPasoAPaso(Nodo* nodo, const std::string& tipo) {
    if (!nodo || recorridoTam >= MAX_RECORRIDO) return;
    if (tipo == "preorden" && recorridoTam < MAX_RECORRIDO)
        recorridoActual[recorridoTam++] = nodo;
    recorrerPasoAPaso(nodo->izq, tipo);
    if (tipo == "inorden" && recorridoTam < MAX_RECORRIDO)
        recorridoActual[recorridoTam++] = nodo;
    recorrerPasoAPaso(nodo->der, tipo);
    if (tipo == "postorden" && recorridoTam < MAX_RECORRIDO)
        recorridoActual[recorridoTam++] = nodo;
}

void Arbol::actualizarPosiciones(Nodo* nodo, float x, float y, float offset) {
    if (!nodo) return;
    nodo->x = x;
    nodo->y = y;
    actualizarPosiciones(nodo->izq, x - offset, y + 80, offset * 0.5f);
    actualizarPosiciones(nodo->der, x + offset, y + 80, offset * 0.5f);
}

void Arbol::dibujarRecursivo(Nodo* nodo) {
    if (!nodo) return;

    if (nodo->izq)
        DrawLine(nodo->x, nodo->y, nodo->izq->x, nodo->izq->y, Util::COLOR_LINEA);
    if (nodo->der)
        DrawLine(nodo->x, nodo->y, nodo->der->x, nodo->der->y, Util::COLOR_LINEA);

    dibujarRecursivo(nodo->izq);
    dibujarRecursivo(nodo->der);

    DrawCircle(nodo->x, nodo->y, 20, nodo->color);
    DrawText(std::to_string(nodo->dato).c_str(), nodo->x - 10, nodo->y - 10, 20, Util::COLOR_TEXTO);
    int fe = altura(nodo->izq) - altura(nodo->der);
    DrawText(("FE: " + std::to_string(fe)).c_str(), nodo->x - 60, nodo->y + 8, 14, DARKGRAY);
}

void Arbol::dibujarAnillo(Nodo* nodo) {
    Vector2 centro = { nodo->x, nodo->y };
    float grosor = 5;
    DrawRing(centro, 26, 26 + grosor, 0, 360, 60, Util::COLOR_ANILLO);
}

void Arbol::dibujar() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    dibujarRecursivo(raiz);
}

void Arbol::dormir(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Arbol::reiniciarColoresRec(Nodo* nodo) {
    if (!nodo) return;
    nodo->color = Util::COLOR_NODO;
    reiniciarColoresRec(nodo->izq);
    reiniciarColoresRec(nodo->der);
}

void Arbol::resetearColores() {
    reiniciarColoresRec(raiz);
    ultimoNodoEncontrado = nullptr;
}

int Arbol::getUltimoEncontrado() const {
    return ultimoNodoEncontrado ? ultimoNodoEncontrado->dato : 0;
}

int Arbol::calcularGrado(Nodo* nodo) {
    if (!nodo) return 0;
    int hijos = 0;
    if (nodo->izq) hijos++;
    if (nodo->der) hijos++;
    int gradoIzq = calcularGrado(nodo->izq);
    int gradoDer = calcularGrado(nodo->der);
    int maxSub = gradoIzq > gradoDer ? gradoIzq : gradoDer;
    return hijos > maxSub ? hijos : maxSub;
}

int Arbol::obtenerAltura() {
    return altura(raiz)- 1;
}

int Arbol::obtenerGrado() {
    return calcularGrado(raiz);
}

bool Arbol::existe(int valor) const {
    Nodo* nodo = raiz;
    while (nodo) {
        if (valor == nodo->dato) return true;
        nodo = valor < nodo->dato ? nodo->izq : nodo->der;
    }
    return false;
}
