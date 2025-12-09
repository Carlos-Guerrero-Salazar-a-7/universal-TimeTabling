#include "../include/horario_disponibilidad.h"

const char* horario_disponibilidad::NOMBRES_DIAS[horario_disponibilidad::DIAS] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
};

const horario_disponibilidad::FranjaHoraria horario_disponibilidad::FRANJAS_HORARIAS[horario_disponibilidad::FRANJAS] = {
    {"7:00", "7:55"}, {"7:55", "8:50"}, {"8:50", "9:45"}, {"9:45", "10:10"},
    {"10:10", "11:05"}, {"11:05", "12:00"}, {"12:00", "12:55"}, {"12:55", "13:50"},
    {"13:50", "13:55"}, {"14:00", "14:55"}, {"14:55", "15:50"}, {"15:50", "16:45"},
    {"16:45", "17:10"}, {"17:10", "18:05"}, {"18:05", "19:00"}
};
