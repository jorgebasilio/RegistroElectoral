#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clave_valor.h"
#include "data_handler.h"

//Estructura del key :
//
//   "clave": "valor";
//
//Para mas de uno (separar con comas ','):
//
//   "clave": "valor", "clave2": "valor2";
//
// LOS DATOS CARGADOS SON DE PRUEBA
//

void main(){
	key *caja = NULL; //estructura creada para almacenar clave-valor que se buscaran en el string
					  				//con un puntero next para colocar los key necesarios que necesitemos migrar
	                  //de algun registro ya establecido

	char algo1[] = "nombre"; //Creo la clave que se buscara en el string

	char algo[] = "\"nombre\": \"jorge Leonardo de freitas\","; //String donde se buscara la clave

	AddKey(&caja, algo1);
	ViewKey(caja);

	char *hola = ReturnValue(algo, caja->clave); // Dada una clave, busca el valor que le corresponde a la misma

	AddValue(&caja, hola);
	ViewValue(caja);

	int x = 0;
	scanf("%i", &x);
}

