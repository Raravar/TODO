/* Archivo Main de proyecto CRUD con conexión a SQLITE.
Proposito del proyecto, recordar tareas por hacer (TODO)

Author: Raravar     //      Date: 20-04-2021 */

#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
using namespace std;

//Creación de la función de devolución de llamada
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    // Retorno exitoso
    return 0;
}

static int callback3(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main()
{
    // Puntero a la conexión SQLITE
    sqlite3* db;

    //Guarda cualquier mensaje de error

    char *zErrMsg = 0;

    // Guarda el resultado al abrir el archivo
    int rc;

    //Guarda cualquier SQL
    string sql;

    // Guarda el resultado al abrir el archivo
    rc = sqlite3_open("TODO.db", &db);

    if (rc){

            cout << "Error al abrir la Base de datos !: " << sqlite3_errmsg(db) << endl;

    } else {

        cout << "Base de datos abierta !" << endl;
    }

    //Creación de la tabla TODO con columna autoIncrementable
    sql = "CREATE TABLE TODO("
      "todo_id      INTEGER NOT NULL       UNIQUE,"
      "todo_title   TEXT,"
      "todo_desc           TEXT     NOT NULL,"
      "todo_date            TEXT     NOT NULL,"
      "PRIMARY KEY('todo_id' AUTOINCREMENT));";

	// Run the SQL (convert the string to a C-String with c_str() )
	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    // Truncado de tablas y secuencias autoincrementables

    std:string truncar;
	std::cout<<"Desea TRUNCAR LA TABLA?"<< endl;
	std::cin >> truncar;

	if (truncar == "si"){

        sql="DELETE FROM TODO;";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
        sql="DELETE FROM sqlite_sequence;";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

}

    //Ejemplo insert NUMERICO
    sql="INSERT INTO TODO ('todo_title', 'todo_desc', 'todo_date') VALUES ('Titulo ejemplo', 'Terminar el programa', '20-04-09');";
    rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);

        //Select con todos los TODO ARREGLADO

    sql = "SELECT * FROM TODO;";
    sqlite3_exec(db, sql.c_str(), callback3, 0, &zErrMsg);

    // Cierre de la conexión
    sqlite3_close(db);

    return (0);

    //
}
