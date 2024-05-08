
#ifndef BASEDATOS_H_
#define BASEDATOS_H_
#include "Habitacion.h"
#include "Usuario.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "sqlite3.h"

#ifdef __cplusplus
}
#endif

class BaseDatos {
public:
    BaseDatos();
    void abrirBaseDatos(sqlite3 **db);
    void cerrarBaseDatos(sqlite3 **db);
    void crearTablas(sqlite3 **db);
    //void cargarFicheroABaseHabitacion(sqlite3 *db);
    //void cargarFicheroABaseUsuario(sqlite3 *db);
    virtual ~BaseDatos();
};

#endif
