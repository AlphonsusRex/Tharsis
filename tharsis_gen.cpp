// ============================================================
// tharsis_gen.cpp — Transpilador Tharsis → C (v0.3)
//
// SOLO traduce el lenguaje C a español.
// Toda la traducción de ESP-IDF está en include/tharsis_esp_idf.h
// Toda la traducción de host está en include/tharsis_host.h
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

struct ReglaTraduccion {
    std::string palabra_tharsis;
    std::string equivalente_c;
};

struct EstadoLexer {
    bool en_comentario_bloque = false;
};

std::string escapar_shell(const std::string& s) {
    std::string r = "'";
    for (char c : s) {
        if (c == '\'') r += "'\\''";
        else r += c;
    }
    r += "'";
    return r;
}

bool es_directiva_preprocesador(const std::string& linea, size_t desde = 0) {
    size_t i = linea.find_first_not_of(" \t", desde);
    return i != std::string::npos && linea[i] == '#';
}

std::string basename(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}

// ¿Hay un tipo (identificador alfanumérico) al final de 'resultado'?
bool hay_tipo_antes(const std::string& resultado) {
    for (size_t k = resultado.size(); k > 0; --k) {
        unsigned char c = static_cast<unsigned char>(resultado[k - 1]);
        if (std::isspace(c)) continue;
        return std::isalnum(c) || c == '_';
    }
    return false;
}

std::string procesar_linea(const std::string& linea,
                           EstadoLexer& estado,
                           const std::vector<ReglaTraduccion>& dicc) {
    std::string resultado;
    size_t i = 0;

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
        if (estado.en_comentario_bloque) return resultado;
    }

    if (es_directiva_preprocesador(linea, i)) {
        resultado += linea.substr(i);
        return resultado;
    }

    while (i < linea.size()) {
        char c = linea[i];

        if (c == '/' && i + 1 < linea.size() && linea[i + 1] == '/') {
            resultado += linea.substr(i);
            return resultado;
        }

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

        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            size_t inicio = i;
            while (i < linea.size() &&
                   (std::isalnum(static_cast<unsigned char>(linea[i])) || linea[i] == '_')) {
                ++i;
            }
            std::string palabra = linea.substr(inicio, i - inicio);
            
            // Lógica especial para 'principal': añadir 'int' si no hay tipo
            if (palabra == "principal") {
                size_t j = i;
                while (j < linea.size() &&
                       std::isspace(static_cast<unsigned char>(linea[j]))) ++j;
                bool seguido_de_paren = (j < linea.size() && linea[j] == '(');

                if (seguido_de_paren && !hay_tipo_antes(resultado)) {
                    resultado += "int "; 
                }
                resultado += palabra; 
                continue;
            }
            
            bool traducida = false;
            for (const auto& regla : dicc) {
                if (regla.palabra_tharsis == palabra) {
                    resultado += regla.equivalente_c;
                    traducida = true;
                    break;
                }
            }
            if (!traducida) resultado += palabra;
            continue;
        }

        resultado += c;
        ++i;
    }

    return resultado;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: tharsis_gen <archivo.t> [--solo-c] [--modo idf]\n";
        return 1;
    }

    std::string nombre_archivo = argv[1];
    bool solo_c = false;
    bool modo_idf = false;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--solo-c") solo_c = true;
        else if (arg == "--modo" && i + 1 < argc) {
            modo_idf = (std::string(argv[i + 1]) == "idf");
            ++i;
        }
    }

    if (nombre_archivo.length() < 2) {
        std::cerr << "Error: nombre de archivo inválido\n";
        return 1;
    }
    std::string ext = nombre_archivo.substr(nombre_archivo.length() - 2);
    if (ext != ".t" && ext != ".T") {
        std::cerr << "Error: el archivo debe tener extensión .t\n";
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

    std::vector<ReglaTraduccion> dicc = {
        {"entero",       "int"},
        {"decimal",      "float"},
        {"doble",        "double"},
        {"caracter",     "char"},
        {"booleano",     "bool"},
        {"vacio",        "void"},
        {"largo",        "long"},
        {"corto",        "short"},

        {"talla_de",     "sizeof"},
        {"nulo",         "NULL"},

        {"si",           "if"},
        {"sino",         "else"},
        {"mientras",     "while"},
        {"para",         "for"},
        {"hacer",        "do"},
        {"segun",        "switch"},
        {"caso",         "case"},
        {"por_defecto",  "default"},

        {"retornar",     "return"},
        {"romper",       "break"},
        {"continuar",    "continue"},

        {"constante",    "const"},
        {"estatico",     "static"},
        {"volatil",      "volatile"},
        {"sin_signo",    "unsigned"},
        {"con_signo",    "signed"},
        {"estructura",   "struct"},
        {"definir_tipo", "typedef"},
        {"enumeracion",  "enum"},

        {"verdadero",    "true"},
        {"falso",        "false"},

        {"NO",           "!"},
        {"Y",            "&&"},
        {"O",            "||"},
    };

    salida << "/* ============================================================ */\n";
    salida << "/* Generado por tharsis_gen desde: " << basename(nombre_archivo) << "\n";
    salida << "   NO EDITAR: modificar el .t y volver a transpilar            */\n";
    salida << "/* ============================================================ */\n\n";

    if (modo_idf) {
        salida << "#include \"tharsis_esp_idf.h\"\n\n";
    } else {
        salida << "#include \"tharsis_host.h\"\n\n";
    }

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

    std::string comando = "gcc -std=c17 -Wall -Wextra -Iinclude -o "
                        + escapar_shell(nombre_base) + " "
                        + escapar_shell(nombre_c);
    std::cout << "[2/2] Compilando: " << comando << "\n";

    int rc = std::system(comando.c_str());
    if (rc == 0) {
        std::cout << "[OK] Ejecutable creado -> ./" << nombre_base << "\n";
        return 0;
    }
    std::cerr << "[ERROR] gcc falló. Revisa " << nombre_c << "\n";
    return 1;
}
