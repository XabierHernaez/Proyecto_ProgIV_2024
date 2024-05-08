#include "BaseDatos.h"
#include <iostream>
using namespace std;
BaseDatos::BaseDatos() {
}
void BaseDatos::abrirBaseDatos(sqlite3 **db)
{
    int result;
    result = sqlite3_open("hotel.db", db);
    if (result != SQLITE_OK) {
        cout << "Error al abrir la BBDD" << endl;
    }
    else {
        cout << "Base de datos abierta correctamente" << endl;
    }
}

void BaseDatos::cerrarBaseDatos(sqlite3 **db)
{
    int result = sqlite3_close(*db);
    if (result != SQLITE_OK) {
        cout << "Error al cerrar la base de datos" << endl;
    }
    else {
        cout << "Base de datos cerrada correctamente" << endl;
    }
}
void BaseDatos::crearTablas(sqlite3 **db)
{
    const char *sql_insert = "CREATE TABLE IF NOT EXISTS habitacion(numH INT, tipo VARCHAR(20), numP INT, precio DOUBLE, ocupada INT)";
    const char *sql_insert2 = "CREATE TABLE IF NOT EXISTS usuario(nombre VARCHAR(15), primerApellido VARCHAR(15), segundoApellido VARCHAR(15), dni VARCHAR(15), usuario VARCHAR(15), contrasenya VARCHAR(15), telefono INT, tipo VARCHAR(1))";
    sqlite3_stmt *stmt1; // Puntero para la primera sentencia SQL
    sqlite3_stmt *stmt2; // Puntero para la segunda sentencia SQL
    sqlite3_prepare_v2(*db, sql_insert, -1, &stmt1, NULL);
    sqlite3_prepare_v2(*db, sql_insert2, -1, &stmt2, NULL);
    sqlite3_step(stmt1);
    sqlite3_step(stmt2);
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
}
BaseDatos::~BaseDatos() {
}
/*
 void BaseDatos::cargarFicheroABaseHabitacion(sqlite3 *db)
{
    Habitacion h;
    char sql[100];
    sqlite3_stmt *stmt;
    FILE *pf;
    pf = fopen("habitaciones.txt", "r");
    if(pf != nullptr){
        while(fscanf(pf, "%d %s %d %f %d", &h.numA, h.tipo, &h.numP, &h.precio, &h.ocupada) == 5){
            sprintf(sql, "insert into habitacion values(%d,'%s',%d,%f,%d)", h.numA, h.tipo, h.numP, h.precio, h.ocupada);
            sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
            sqlite3_step(stmt); //Ejecutar la sentencia
            sqlite3_reset(stmt); // Resetear la sentencia para reutilizarla en la siguiente iteración
        }
        // Finalizar la sentencia después del bucle
        sqlite3_finalize(stmt);

        fclose(pf);
    }
}
void BaseDatos::cargarFicheroABaseUsuario(sqlite3 *db)
{
	FILE *pf;
	Usuario u;
	char tipo;
	char sql[100];
	sqlite3_stmt *stmt;
	pf = fopen("usuarios.txt", "r");
	if(pf != (FILE*)NULL){
		while(fscanf(pf, "%s %s %s %s %s %s %d %c", u.nombre, u.primerApellido, u.segundoApellido, u.dni, u.usuario, u.contrasenya, &u.telefono, &tipo) != EOF){
			cout<<"a"<<endl;
			u.setTipo(tipo);
			sprintf(sql, "insert into usuario values('%s','%s','%s','%s','%s','%s',%d,'%c')", u.nombre, u.primerApellido, u.segundoApellido, u.dni, u.usuario, u.contrasenya, u.telefono, u.tipo);
			sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
			sqlite3_step(stmt); //Ejecutar la sentencia
			sqlite3_reset(stmt); // Resetear la sentencia para reutilizarla en la siguiente iteración
		}
		sqlite3_finalize(stmt);
		fclose(pf);
	}
}
 * */
