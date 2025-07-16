
#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <string>
#include <list>
#include <sstream>

namespace Util {

// Convierte vector de enteros a string con flechas (ej: 10 → 15 → 20)
inline std::string vectorARecorrido(const std::list<int>& valores) {
    if (valores.empty()) return "";
    std::ostringstream os;
    auto it = valores.begin();
    while (it != valores.end()) {
        os << *it;
        ++it;
        if (it != valores.end()) os << " → ";
    }
    return os.str();
}

// Convierte una string numérica a entero (con validación básica)
inline int stringAEntero(const std::string& texto) {
    try {
        return std::stoi(texto);
    } catch (...) {
        return 0;
    }
}

// Colores personalizados
const Color COLOR_NODO = DARKGREEN;
const Color COLOR_TEXTO = RAYWHITE;
const Color COLOR_LINEA = GRAY;
const Color COLOR_ANILLO = RED;

} // namespace Util

#endif
