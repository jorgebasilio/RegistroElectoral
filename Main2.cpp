# RegistroElectoral

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "People.h"
#include "Center.h"
#include "Register.h"

void main()
{
	int op = -1; char ID[10], name[65], address[100], date[9], codeC[8], codeR[4], number[12];
	Register *r = NULL;
	Center *c = NULL;
	People *p = NULL;
	while (op != 0) {
		system("cls");
		printf("\n\n                                Menu principal. \n\n\n");
		printf("\n 1. Insertar Registro Estatal.");
		printf("\n 2. Insertar Centro Electoral en Registrol Estatal.");
		printf("\n 3. Ingresar Persona en Centro Electoral. ");
		printf("\n 4. Mostrar todo. \n\n");

		printf(" 0. Salir. \n\n");
		printf("Indique opcion (1-5): ");
		op = 0;
		scanf("%i", &op);
		system("cls");
		printf("\n\n");
		bool flag = true;
		switch (op)
		{
			case 1: printf(" Indique datos: ");
				scanf("%s", &codeR);
				scanf("%s", &name);
				scanf("%s", &number);
				scanf("%s", &address);
				addRegister(&r, name, address, number, codeR);
				break;

			case 2:	printf(" Indique codigo Registro Estatal: ");
					scanf("%s", &codeR);
					addCenterRegister(r, codeR);
				break;

			case 3:	printf(" Indique codigo centro electoral: "); 
					scanf("%s", &codeC);
					// Buscar en que registro estatal esta ese centro electoral, para agragar la persona
					addPersonCenter(c, codeC);
				/* printf(" Indique sus cedula: ");
				scanf("%s", &ID);
				scanf("%s", &name);
				scanf("%s", &address);
				scanf("%s", &date);
				addPerson(&p, ID, name, address, date); */
				break;

			case 4:
				printf(" Centros electorales con personas: \n");
				seeAll(r);
				break;

			 
		}
		if (op)
		{
			printf("\n\n");
			system("pause");
			system("cls");
		}
	}
}

