#include "BaseDatos.h"
#include <iostream>
using namespace std;
BaseDatos::BaseDatos() {
}
void BaseDatos::abrirBaseDatos(sqlite3 **db)
{
	sqlite3_open("hotel.db", db);
}

void BaseDatos::cerrarBaseDatos(sqlite3 **db)
{
    sqlite3_close(*db);
}
void BaseDatos::crearTablas(sqlite3 **db)
{
    const char *sql_insert = "CREATE TABLE IF NOT EXISTS habitacion(numH INT, tipo VARCHAR(20), numP INT, precio DOUBLE, ocupada INT)";
    const char *sql_insert2 = "CREATE TABLE IF NOT EXISTS usuario(nombre VARCHAR(20), primerApellido VARCHAR(20), segundoApellido VARCHAR(20), dni VARCHAR(20), usuario VARCHAR(20), contrasenya VARCHAR(20), telefono INT, tipo CHAR(1))";
    const char *sql_insert3 = "CREATE TABLE IF NOT EXISTS reserva(usuario VARCHAR(20), numH INT, precio DOUBLE, añoE INT, mesE INT, diaE INT, añoS INT, mesS INT, diaS INT)";
    sqlite3_stmt *stmt1;
    sqlite3_stmt *stmt2;
    sqlite3_stmt *stmt3;
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
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    while (result == SQLITE_ROW) {
        h.numA = sqlite3_column_int(stmt, 0);
        sprintf(h.tipo, "%s", (char*)sqlite3_column_text(stmt, 1));
        h.numP = sqlite3_column_int(stmt, 2);
        h.precio = sqlite3_column_double(stmt, 3);
        h.ocupada = sqlite3_column_int(stmt, 4);
        result = sqlite3_step(stmt);
        lH.listaHabitacion[lH.numE] = h;
        lH.numE++;
    }
    sqlite3_finalize(stmt);
}
void BaseDatos::volcarBaseDatosListaUsuario(sqlite3 *db, ListaUsuario &lU)
{
    char sql[200];
    Usuario u;
    sprintf(sql, "SELECT * FROM usuario");
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    while (result == SQLITE_ROW) {
        sprintf(u.nombre, "%s", (char*)sqlite3_column_text(stmt, 0));
        sprintf(u.primerApellido, "%s", (char*)sqlite3_column_text(stmt, 1));
        sprintf(u.segundoApellido, "%s", (char*)sqlite3_column_text(stmt, 2));
        sprintf(u.dni, "%s", (char*)sqlite3_column_text(stmt, 3));
        sprintf(u.usuario, "%s", (char*)sqlite3_column_text(stmt, 4));
        sprintf(u.contrasenya, "%s", (char*)sqlite3_column_text(stmt, 5));
        u.telefono = sqlite3_column_int(stmt, 6);
        u.tipo = sqlite3_column_text(stmt, 7)[0];
        result = sqlite3_step(stmt);
        lU.anyadirUsuario(u);
    }
    sqlite3_finalize(stmt);
}
void BaseDatos::volcarBaseDatosListaReserva(sqlite3 *db, ListaReserva &lR)
{
	char sql[200];
	Reserva r;
	sprintf(sql, "SELECT * FROM reserva");
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	while (result == SQLITE_ROW) {
		sprintf(r.usuario, "%s", (char*)sqlite3_column_text(stmt, 0));
		r.habitacion.numA = sqlite3_column_int(stmt, 1);
		r.precio = sqlite3_column_double(stmt, 2);
		r.entrada.anyo = sqlite3_column_int(stmt, 3);
		r.entrada.mes = sqlite3_column_int(stmt, 4);
		r.entrada.dia = sqlite3_column_int(stmt, 5);
		r.salida.anyo = sqlite3_column_int(stmt, 6);
		r.salida.mes = sqlite3_column_int(stmt, 7);
		r.salida.dia = sqlite3_column_int(stmt, 8);
		result = sqlite3_step(stmt);
		lR.anyadirReserva(r);
	}
	sqlite3_finalize(stmt);
}
void BaseDatos::anyadirUsuarioBaseDatos(sqlite3 *db, Usuario u)
{
	char sql[100];
	sqlite3_stmt *stmt;
	sprintf(sql, "insert into usuario values('%s','%s','%s','%s','%s','%s',%d,'%c')", u.getNombre(), u.getprimerApellido(), u.getsegundoApellido(), u.getDni(), u.getUsuario(), u.getContrasenya(), u.getTelefono(), u.getTipo());
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}
void BaseDatos::anyadirReservaBaseDatos(sqlite3 *db, Reserva r)
{
	char sql[100];
	sqlite3_stmt *stmt;
	sprintf(sql, "insert into reserva values('%s',%d,%f,%d,%d,%d,%d,%d,%d)", r.usuario,r.habitacion.numA , r.precio,r.entrada.anyo, r.entrada.mes,r.entrada.dia,r.salida.anyo, r.salida.mes, r.salida.dia);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}
void BaseDatos::borrarReserva(sqlite3 *db, Reserva &r)
{
    char sql[300];
    sqlite3_stmt *stmt;
    sprintf(sql, "DELETE FROM Reserva WHERE usuario = '%s' AND numH = %d AND añoE = %d AND mesE = %d AND diaE = %d AND añoS = %d AND mesS = %d AND diaS = %d",
            r.usuario, r.habitacion.numA, r.entrada.anyo, r.entrada.mes, r.entrada.dia, r.salida.anyo, r.salida.mes, r.salida.dia);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
}
void BaseDatos::modificarReserva(sqlite3 *db, Reserva &nuevaReserva, Reserva &viejaReserva)
{
	char sql[300];
	sqlite3_stmt *stmt;
	sprintf(sql, "UPDATE Reserva SET añoE = %d, mesE = %d, diaE = %d, añoS = %d, mesS = %d, diaS = %d WHERE usuario = '%s' AND numH = %d AND añoE = %d AND mesE = %d AND diaE = %d AND añoS = %d AND mesS = %d AND diaS = %d",
			nuevaReserva.entrada.anyo, nuevaReserva.entrada.mes, nuevaReserva.entrada.dia, nuevaReserva.salida.anyo, nuevaReserva.salida.mes, nuevaReserva.salida.dia, viejaReserva.usuario,
			viejaReserva.habitacion.numA, viejaReserva.entrada.anyo, viejaReserva.entrada.mes, viejaReserva.entrada.dia, viejaReserva.salida.anyo, viejaReserva.salida.mes, viejaReserva.salida.dia);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}
void BaseDatos::borrarTablasUsuarioReserva(sqlite3 *db)
{
	char sql[200];
	char sql2[200];
	sprintf(sql, "DROP TABLE usuario");
	sprintf(sql2, "DROP TABLE reserva");
	sqlite3_stmt *stmt1;
	sqlite3_stmt *stmt2;
	sqlite3_prepare_v2(db, sql, -1, &stmt1, NULL);
	sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);
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
*/
