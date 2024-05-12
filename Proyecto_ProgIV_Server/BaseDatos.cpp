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
    const char *sql_insert2 = "CREATE TABLE IF NOT EXISTS usuario(nombre VARCHAR(20), primerApellido VARCHAR(20), segundoApellido VARCHAR(20), dni VARCHAR(20), usuario VARCHAR(20), contrasenya VARCHAR(20), telefono INT, tipo CHAR(1))";
    const char *sql_insert3 = "CREATE TABLE IF NOT EXISTS reserva(usuario VARCHAR(20), numH INT, precio DOUBLE)";
    sqlite3_stmt *stmt1; // Puntero para la primera sentencia SQL
    sqlite3_stmt *stmt2; // Puntero para la segunda sentencia SQL
    sqlite3_stmt *stmt3; // Puntero para la segunda sentencia SQL
    sqlite3_prepare_v2(*db, sql_insert, -1, &stmt1, NULL);
    sqlite3_prepare_v2(*db, sql_insert2, -1, &stmt2, NULL);
    sqlite3_prepare_v2(*db, sql_insert3, -1, &stmt3, NULL);
    sqlite3_step(stmt1);
    sqlite3_step(stmt2);
    sqlite3_step(stmt3);
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_finalize(stmt3);
}
void BaseDatos::volcarBaseDatosListaHabitacion(sqlite3 *db, ListaHabitacion &lH)
{
    char sql[200];
    Habitacion h;
    sprintf(sql, "SELECT * FROM habitacion");
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // Preparar la sentencia
    int result = sqlite3_step(stmt); // Ejecutar la sentencia
    while (result == SQLITE_ROW) { // Mientras haya tuplas/filas que mirar
        h.numA = sqlite3_column_int(stmt, 0);
        sprintf(h.tipo, "%s", (char*)sqlite3_column_text(stmt, 1));
        h.numP = sqlite3_column_int(stmt, 2);
        h.precio = sqlite3_column_double(stmt, 3); // Utilizar sqlite3_column_double para campos DOUBLE
        h.ocupada = sqlite3_column_int(stmt, 4);
        result = sqlite3_step(stmt); // Ejecutar la sentencia
        lH.listaHabitacion[lH.numE] = h;
        lH.numE++; // Incrementar el contador de habitaciones en la lista
    }
    sqlite3_finalize(stmt); // Cerrar la sentencia
}
void BaseDatos::volcarBaseDatosListaUsuario(sqlite3 *db, ListaUsuario &lU)
{
    char sql[200];
    Usuario u;
    sprintf(sql, "SELECT * FROM usuario");
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // Preparar la sentencia
    int result = sqlite3_step(stmt); // Ejecutar la sentencia
    while (result == SQLITE_ROW) { // Mientras haya tuplas/filas que mirar
        sprintf(u.nombre, "%s", (char*)sqlite3_column_text(stmt, 0));
        sprintf(u.primerApellido, "%s", (char*)sqlite3_column_text(stmt, 1));
        sprintf(u.segundoApellido, "%s", (char*)sqlite3_column_text(stmt, 2));
        sprintf(u.dni, "%s", (char*)sqlite3_column_text(stmt, 3));
        sprintf(u.usuario, "%s", (char*)sqlite3_column_text(stmt, 4));
        sprintf(u.contrasenya, "%s", (char*)sqlite3_column_text(stmt, 5));
        u.telefono = sqlite3_column_int(stmt, 6); // Correcta posición de la columna del teléfono
        u.tipo = sqlite3_column_text(stmt, 7)[0]; // Correcta posición de la columna del tipo
        result = sqlite3_step(stmt); // Ejecutar la sentencia
        lU.anyadirUsuario(u);
    }
    sqlite3_finalize(stmt); // Cerrar la sentencia
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
*/
void BaseDatos::cargarFicheroABaseUsuario(sqlite3 *db)
{
	FILE* pf;
	Usuario u;
	char sql[100];
	char nombre[20];
	char p1[20];
	char p2[20];
	char dni[20];
	char usu[20];
	char contra[20];
	int tel;
	char tipo;
	sqlite3_stmt *stmt;
	pf = fopen("usuarios.txt", "r");
	if(pf != (FILE*)NULL){
		while(fscanf(pf, "%s %s %s %s %s %s %d %c", nombre, p1, p2, dni, usu, contra, &tel, &tipo) != EOF){
			u.setNombre(nombre);
			u.setprimerApellido(p1);
			u.setsegundoApellido(p2);
			u.setDni(dni);
			u.setUsuario(usu);
			u.setContrasenya(contra);
			u.setTelefono(tel);
			u.setTipo(tipo);
			sprintf(sql, "insert into usuario values('%s','%s','%s','%s','%s','%s',%d,'%c')", u.getNombre(), u.getprimerApellido(), u.getsegundoApellido(), u.getDni(), u.getUsuario(), u.getContrasenya(), u.getTelefono(), u.getTipo());
			sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
			sqlite3_step(stmt); //Ejecutar la sentencia
			sqlite3_reset(stmt); // Resetear la sentencia para reutilizarla en la siguiente iteración
			sqlite3_finalize(stmt);
		}
		fclose(pf);
	}
}
//* */
