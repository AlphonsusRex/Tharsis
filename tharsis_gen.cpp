// ============================================================
// tharsis_gen.cpp — Transpilador Tharsis → C (v0.2)
//
// Transpila un archivo .t (Tharsis) a .c (C) y lo compila con gcc.
// Uso: tharsis_gen <archivo.t> [--solo-c]
//   --solo-c : solo genera el .c, no compila (útil para tests)
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

// ============================================================
// Tipos
// ============================================================

struct ReglaTraduccion {
    std::string palabra_tharsis;
    std::string equivalente_c;
};

// Estado del lexer que persiste entre líneas (para comentarios /* */).
struct EstadoLexer {
    bool en_comentario_bloque = false;
};

// ============================================================
// Utilidades
// ============================================================

// Escapa una ruta como argumento de shell POSIX (comillas simples).
std::string escapar_shell(const std::string& s) {
    std::string r = "'";
    for (char c : s) {
        if (c == '\'') r += "'\\''";
        else r += c;
    }
    r += "'";
    return r;
}

// ¿La línea empieza (ignorando espacios) con una directiva de preprocesador?
bool es_directiva_preprocesador(const std::string& linea, size_t desde = 0) {
    size_t i = linea.find_first_not_of(" \t", desde);
    return i != std::string::npos && linea[i] == '#';
}

// ¿Hay un tipo (identificador alfanumérico) al final de 'resultado'?
// Sirve para saber si 'principal' lleva ya un tipo delante (int, void...).
bool hay_tipo_antes(const std::string& resultado) {
    for (size_t k = resultado.size(); k > 0; --k) {
        unsigned char c = static_cast<unsigned char>(resultado[k - 1]);
        if (std::isspace(c)) continue;
        return std::isalnum(c) || c == '_';
    }
    return false;
}

// ============================================================
// Procesamiento de una línea
// ============================================================
// Recorre la línea carácter a carácter distinguiendo:
//   - strings "..."     → copiados tal cual, respetando escapes
//   - char literals 'x' → idem
//   - // comentario     → copiado tal cual, sin traducir
//   - /* */ comentario  → copiado tal cual, con estado entre líneas
//   - código normal     → se intentan traducir las palabras clave
// ============================================================
std::string procesar_linea(const std::string& linea,
                           EstadoLexer& estado,
                           const std::vector<ReglaTraduccion>& dicc) {
    std::string resultado;
    size_t i = 0;

    // 1) Continuar comentario de bloque iniciado en una línea anterior.
    if (estado.en_comentario_bloque) {
        while (i < linea.size()) {
            if (linea[i] == '*' && i + 1 < linea.size() && linea[i + 1] == '/') {
                resultado += "*/";
                estado.en_comentario_bloque = false;
                i += 2;
                break;
            }
            resultado += linea[i];
            ++i;
        }
        if (estado.en_comentario_bloque) return resultado;  // sigue abierto
    }

    // 2) Directivas de preprocesador: copiar tal cual.
    if (es_directiva_preprocesador(linea, i)) {
        resultado += linea.substr(i);
        return resultado;
    }

    // 3) Recorrido principal.
    while (i < linea.size()) {
        char c = linea[i];

        // Comentario de línea: copiar el resto tal cual.
        if (c == '/' && i + 1 < linea.size() && linea[i + 1] == '/') {
            resultado += linea.substr(i);
            return resultado;
        }

        // Comentario de bloque: copiar hasta '*/' o fin de línea.
        if (c == '/' && i + 1 < linea.size() && linea[i + 1] == '*') {
            estado.en_comentario_bloque = true;
            resultado += "/*";
            i += 2;
            while (i < linea.size()) {
                if (linea[i] == '*' && i + 1 < linea.size() && linea[i + 1] == '/') {
                    resultado += "*/";
                    estado.en_comentario_bloque = false;
                    i += 2;
                    break;
                }
                resultado += linea[i];
                ++i;
            }
            continue;
        }

        // String "...": copiar respetando secuencias de escape.
        if (c == '"') {
            resultado += c;
            ++i;
            while (i < linea.size()) {
                char sc = linea[i];
                resultado += sc;
                if (sc == '\\' && i + 1 < linea.size()) {
                    resultado += linea[i + 1];
                    i += 2;
                    continue;
                }
                ++i;
                if (sc == '"') break;
            }
            continue;
        }

        // Char literal '...': copiar respetando secuencias de escape.
        if (c == '\'') {
            resultado += c;
            ++i;
            while (i < linea.size()) {
                char sc = linea[i];
                resultado += sc;
                if (sc == '\\' && i + 1 < linea.size()) {
                    resultado += linea[i + 1];
                    i += 2;
                    continue;
                }
                ++i;
                if (sc == '\'') break;
            }
            continue;
        }

        // Identificador o palabra: intentar traducir.
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            size_t inicio = i;
            while (i < linea.size() &&
                   (std::isalnum(static_cast<unsigned char>(linea[i])) || linea[i] == '_')) {
                ++i;
            }
            std::string palabra = linea.substr(inicio, i - inicio);

            bool traducida = false;
            for (const auto& regla : dicc) {
                if (regla.palabra_tharsis != palabra) continue;

                if (palabra == "principal") {
                    // ¿Le sigue '('? Entonces es definición/llamada.
                    size_t j = i;
                    while (j < linea.size() &&
                           std::isspace(static_cast<unsigned char>(linea[j]))) ++j;
                    bool seguido_de_paren = (j < linea.size() && linea[j] == '(');

                    if (seguido_de_paren && !hay_tipo_antes(resultado)) {
                        resultado += "int main";  // principal() → int main()
                    } else {
                        resultado += "main";      // int principal() → int main()
                    }
                } else {
                    resultado += regla.equivalente_c;
                }
                traducida = true;
                break;
            }
            if (!traducida) resultado += palabra;
            continue;
        }

        // Cualquier otro carácter (operadores, números, espacios...).
        resultado += c;
        ++i;
    }

    return resultado;
}

// Extrae el basename de un path (para el header del .c generado).
std::string basename(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}


// ============================================================
// main
// ============================================================
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: tharsis_gen <archivo.t> [--solo-c]\n";
        std::cout << "  Transpila un archivo Tharsis (.t) a C (.c).\n";
        std::cout << "  --solo-c : solo genera el .c, no compila con gcc.\n";
        return 1;
    }

    std::string nombre_archivo = argv[1];
    bool solo_c = (argc >= 3 && std::string(argv[2]) == "--solo-c");

    // Extensión .t / .T
    if (nombre_archivo.length() < 2) {
        std::cerr << "Error: nombre de archivo inválido: " << nombre_archivo << "\n";
        return 1;
    }
    std::string ext = nombre_archivo.substr(nombre_archivo.length() - 2);
    if (ext != ".t" && ext != ".T") {
        std::cerr << "Error: el archivo debe tener extensión .t: " << nombre_archivo << "\n";
        return 1;
    }

    std::ifstream entrada(nombre_archivo);
    if (!entrada.is_open()) {
        std::cerr << "Error: no se pudo abrir " << nombre_archivo << "\n";
        return 1;
    }

    std::string nombre_base = nombre_archivo.substr(0, nombre_archivo.length() - 2);
    std::string nombre_c    = nombre_base + ".c";

    std::ofstream salida(nombre_c);
    if (!salida.is_open()) {
        std::cerr << "Error: no se pudo crear " << nombre_c << "\n";
        return 1;
    }

    // --- Diccionario de traducción ---
    // El matching es por palabra completa (identificadores), así que
    // Y / O / NO no requieren espacios alrededor.
    std::vector<ReglaTraduccion> dicc = {
        // Tipos
        {"entero",       "int"},
        {"decimal",      "float"},
        {"doble",        "double"},
        {"caracter",     "char"},
        {"booleano",     "bool"},
        {"vacio",        "void"},
        {"largo",        "long"},
        {"corto",        "short"},

        // Entrada / salida / utilidades
        // NOTA: imprimir(x) → printf(x). Solo válido si 'x' es un literal
        //       de formato o un char*. Para enteros: imprimir("%d", x).
        //       La versión con formato automático llega en v0.3 (parser).
        {"imprimir",     "printf"},
        {"talla_de",     "sizeof"},
        {"nulo",         "NULL"},
        // 'leer' → 'scanf' NO se traduce: scanf necesita "%d", &x y el
        //        transpilador no conoce tipos. Pendiente para v0.3.
        // 'tomar_cadena' se resuelve con una macro en la cabecera generada.

        // Control de flujo
        {"si",           "if"},
        {"sino",         "else"},
        {"mientras",     "while"},
        {"para",         "for"},
        {"hacer",        "do"},
        {"segun",        "switch"},
        {"caso",         "case"},
        {"por_defecto",  "default"},

        // Salto
        {"retornar",     "return"},
        {"romper",       "break"},
        {"continuar",    "continue"},

        // Modificadores
        {"constante",    "const"},
        {"estatico",     "static"},
        {"sin_signo",    "unsigned"},
        {"con_signo",    "signed"},
        {"estructura",   "struct"},
        {"definir_tipo", "typedef"},
        {"enumeracion",  "enum"},

        // Booleanos
        {"verdadero",    "true"},
        {"falso",        "false"},

        // Operadores lógicos (mayúsculas para no colisionar con variables)
        {"NO",           "!"},
        {"Y",            "&&"},
        {"O",            "||"},

        // Función principal (lógica especial en procesar_linea)
        {"principal",    "main"},
    };

    // --- Cabecera del archivo C generado ---
    salida << "/* ============================================================ */\n";
    salida << "/* Generado por tharsis_gen desde: " << basename(nombre_archivo) << "\n";
    salida << "   NO EDITAR: modificar el .t y volver a transpilar            */\n";
    salida << "/* ============================================================ */\n\n";
    salida << "#include <stdio.h>\n";
    salida << "#include <stdlib.h>\n";
    salida << "#include <string.h>\n";
    salida << "#include <stdbool.h>\n\n";
    salida << "/* Macro de tomar_cadena(var, tam): lee una línea de stdin.      */\n";
    salida << "/* 'tam' es el tamaño total del buffer 'var'.                   */\n";
    salida << "#ifndef tomar_cadena\n";
    salida << "#define tomar_cadena(var, tam) fgets((var), (tam), stdin)\n";
    salida << "#endif\n\n";

    // --- Procesar archivo línea a línea ---
    EstadoLexer estado;
    std::string linea;
    while (std::getline(entrada, linea)) {
        salida << procesar_linea(linea, estado, dicc) << "\n";
    }
    if (estado.en_comentario_bloque) {
        std::cerr << "Advertencia: comentario /* sin cerrar al final del archivo\n";
    }

    entrada.close();
    salida.close();

    std::cout << "[1/2] Transpilado a C -> " << nombre_c << "\n";

    if (solo_c) return 0;

    // --- Compilación con gcc ---
    std::string comando = "gcc -std=c17 -Wall -Wextra -o "
                        + escapar_shell(nombre_base) + " "
                        + escapar_shell(nombre_c);
    std::cout << "[2/2] Compilando: " << comando << "\n";
    std::cout.flush();

    int rc = std::system(comando.c_str());
    if (rc == 0) {
        std::cout << "[OK] Ejecutable creado -> ./" << nombre_base << "\n";
        return 0;
    }
    std::cerr << "[ERROR] gcc falló. Revisa " << nombre_c << "\n";
    return 1;
}
