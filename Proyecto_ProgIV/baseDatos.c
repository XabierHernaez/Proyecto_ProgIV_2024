#include <stdio.h>
#include "sqlite3.h"
#include "baseDatos/baseDatos.h"


int crearBDD()
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

		char * mensaje_error = 0;
		int rc = sqlite3_open("Hotel.db", &db);
		if(rc != SQLITE_OK){
			fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Pais

		char *sql= "CREATE TABLE pais ("
				   "Cod_Pais INTEGER PRIMARY KEY NOT NULL,"
				   "Nom_Pais TEXT NOT NULL);";

		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'pais': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Parking"

		sql = "CREATE TABLE parking ("
			  "Cod_P INTEGER PRIMARY KEY NOT NULL,"
			  "Tipo_P TEXT NOT NULL,"
			  "Precio REAL);";

		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'parking': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Habitacion"

		sql = "CREATE TABLE habitacion ("
		      "Num_H INTEGER PRIMARY KEY NOT NULL,"
			  "Precio REAL NOT NULL,"
			  "Tipo TEXT,"
			  "Camas TEXT);";
		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'habitacion': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Ciudad"

		sql = "CREATE TABLE ciudad ("
			  "Cod_C INTEGER PRIMARY KEY NOT NULL,"
			  "Nom_C TEXT NOT NULL,"
			  "Cod_P INTEGER NOT NULL,"
			  "FOREIGN KEY (Cod_P) REFERENCES parking(Cod_P));";
		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'ciudad': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Cliente"
		sql = "CREATE TABLE cliente("
					"DNI INTEGER PRIMARY KEY NOT NULL,"
					"Nombre_C TEXT NOT NULL,"
					"Apellido_C TEXT NOT NULL,"
					"Usuario VARCHAR,"
					"Contraseña INTEGER,"
					"Num INTEGER,"
					"COD_C INTEGER NOT NULL,"
					"FOREIGN KEY (Cod_C) REFERENCES ciudad(Cod_C));";
		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'cliente': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

		// Crear tabla "Reserva"
		sql = "CREATE TABLE reserva ("
			  "Cod_R INTEGER PRIMARY KEY NOT NULL,"
			  "Fecha_R TEXT NOT NULL,"
			  "Inicio INTEGER,"
			  "Fin INTEGER,"
			  "DNI INTEGER NOT NULL,"
			  "Cod_P INTEGER NOT NULL."
			  "Num_H INTEGER NOT NULL,"
			  "FOREIGN KEY (DNI) REFERENCES cliente(DNI),"
			  "FOREIGN KEY (Cod_P) REFERENCES parking(Cod_P),"
			  "FOREIGN KEY (Num_H) REFERENCES habitacion(Num_H));";
		rc = sqlite3_exec(db, sql, 0, 0, &mensaje_error);
		if (rc != SQLITE_OK){
			fprintf(stderr, "Error al crear la tabla 'reserva': %s\n", mensaje_error);
			sqlite3_free(mensaje_error);
			sqlite3_close(db);
			return 1;
		}

int cerrarBD()
{
	sqlite3 *db;
	sqlite3_close(db);
	return 1;
}



}
