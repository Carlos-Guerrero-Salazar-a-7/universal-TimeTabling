#ifndef MODIFICACIONES_OBJETOS_H
#define MODIFICACIONES_OBJETOS_H

class Modificador {
public:
    static bool obtenerValor(const char* instruccion, const char* clave, char* valor, int max_len);
    static void parsearCadenas(const char* input, char** output, int& cantidad, int max_items, int max_len);
};

#endif // MODIFICACIONES_OBJETOS_H
