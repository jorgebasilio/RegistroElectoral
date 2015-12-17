#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "People.h"
#include "Center.h"
#include "Register.h"
using namespace std;

void main()
{
	int op = -1; char ID[10] = "", name[65] = "", address[100] = "", date[9] = "", codeC[4] = "", codeR[4] = "", number[12] = "", code[8] = "";
	Register *r = NULL;
	Center *c = NULL;
	People *p = NULL;
	while (op != 0) {
		system("cls");
		printf("\n\n                                Menu principal. \n\n\n");
		printf("\n 1. Insertar Registro Estatal."); //funciona
		printf("\n 2. Insertar Centro Electoral en Registrol Estatal."); //funciona
		printf("\n 3. Ingresar Persona en Centro Electoral. "); //funciona
		printf("\n 4. Mostrar todo."); //funciona
		printf("\n 5. Elimina Centro Electoral (Elimina votantes)."); //funciona.
		printf("\n 6. Elimina Centro Electoral (Cambia votantes de Centro Electoral). "); //funciona
		printf("\n 7. Elimina Registro Estatal (Cambia votantes y Centros Electorales)."); //Por probar
		printf("\n 8. Modificar Registro Estatal."); //Por probar
		printf("\n 9. Modificar Centro Electoral. "); //Por probar
		printf("\n 10. Modificar Persona."); //por probar 
		printf("\n 11. Reporte General."); //funciona
		printf("\n 12. Reporte por Registro Estata."); //funciona
		printf("\n 13. Buscar persona por cedula. "); //funciona
		printf("\n 14. Prueba comparar sinonimos."); //funciona, pero no se ha provado completamente.
		printf("\n 15. Cambiar de Centro Electoral a una persona(Mismo Registro Estatal)."); // Por probar
		printf("\n 16. .");
		printf(" 0. Salir. \n\n");
		printf("Indique opcion (1-5): ");
		op = 0;
		scanf("%i", &op);
		system("cls");
		printf("\n\n");
		bool flag = true;
		switch (op)
		{
		case 1: printf(" Indique datos: \n");
			printf(" Introduce codigo: \n");
			scanf("%s", codeR);
			printf(" Indique nombre: \n");
			scanf("%s", name);
			printf(" Indique numero: \n");
			scanf("%s", number);
			printf(" Indique direccion: \n");
			scanf("%s", address);
			addRegister(&r, name, address, number, codeR);
			break;

		case 2:	printf(" Indique codigo Registro Estatal: ");
			scanf("%s", codeR);
			addCenterRegister(r, codeR);
			break;

		case 3:	printf(" Indique codigo centro electoral: ");
			scanf("%s", codeC);
			seachCenterRegister(r, codeC);
			break;

		case 4:
			printf(" Centros electorales con personas: \n");
			seeAll(r);
			break;

		case 5: printf(" Codigo Centro electoral para eliminar de una Region Estatal \n (Elimina todos su votantes, sin guardar.):");
			scanf("%s", codeC);
			seachDeleteCenter(&r, codeC, flag);
			break;

		case 6:
			printf(" Codigo Centro electoral para eliminar de una Region Estatal \n (Guarda votantes en otro Centro Electoral.):");
			scanf("%s", code);
			flag = false;
			seachDeleteCenter(&r, code, flag);
			break;

		case 7:
			printf(" Codigo Region Estatal para eliminar \n (Guarda votantes y Centros Electorales en otra Region Estatal.):");
			scanf("%s", codeR);
			flag = false;
			seachChangeDeleteRegister(&r, codeR, flag);
			break;

		case 8: printf(" Codigo Region Estatal para modificar :");
			scanf("%s", codeR);
			seachChangeDeleteRegister(&r, codeR, flag);
			break;

		case 9: printf(" Codigo Centro Electoral para modificar :");
			scanf("%s", code);
			seachCenterModify(r, code);
			break;

		case 10: printf(" Cedula de la persona a modificar :");
			scanf("%s", ID);
			seachIDModify(r, ID);
			break;

		case 11: printf(" Reporte general \n");
			printf(" Hay %i Estados en total \n", countStates(r));
			break;

		case 12: printf(" Reporte por Registro Estatal. \n");
			printf(" Codigo Region Estatal para reporte: \n");
			scanf("%s", codeR);
			seachR(r, codeR);
			break;

		case 13: printf("\n Cedula a ubicar el centro electoral. :");
			scanf("%s", ID);
			seachID(r, ID);
			break;

		case 14: printf("\n Inserte nombre o apellido a buscar. :"); 
			scanf("%s", name);
			seachNameRegister(r, name);
			break;

		case 15:  printf("\n Inserte cedula de la persona a redirigir:");
			scanf("%s", ID);
			printf("\n Inserte codigo del Centro Electoral de redireccionamiento:");
			scanf("%s", code);
			seachSonFather(r, ID, code);
			break;

		case 16:
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
