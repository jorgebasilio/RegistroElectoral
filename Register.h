#pragma once

struct Register {
	char name[65];
	char address[100];
	char number[12];
	char code[4];
	Register *next;
	Center *down;
};

bool vacio(Register *r)
{
	return (!(r));
}

void addRegister(Register **r, char name[65], char address[100], char number[12], char codeR[4])
{
	bool flag = false;
	if (vacio(*r))
	{
		Register *aux = new Register;
		strcpy(aux->code, codeR);
		strcpy(aux->name, name);
		strcpy(aux->address, address);
		strcpy(aux->number, number);
		aux->next = (*r);
		aux->down = NULL;
		(*r) = aux;
		flag = true;
	}
	else
	{
		Register *t = (*r);
		while (t)
		{
			if ((strcmp(codeR, t->code) == 0))
			{
				flag = true;
				break;
			}
			t = t->next;
		}

		if (!flag)
		{
			Register *aux = new Register;
			strcpy(aux->code, codeR);
			strcpy(aux->name, name);
			strcpy(aux->address, address);
			strcpy(aux->number, number);
			aux->next = NULL;
			aux->down = NULL;
			t = (*r);
			while (t->next)
				t = t->next;
			t->next = aux;
		}
		else printf("Codigo Registro Estatal ya registrado!!");
	}
}

void addCenterRegister(Register *r, char codeR[4])
{
	char name[65], address[100], codeC[8];
	if (!(vacio(r)))
	{
		while (r)
		{
			if ((strcmp(codeR, r->code) == 0))
			{
				printf("\n Ingrese sus datos: \n");
				scanf("%s", codeC);
				scanf("%s", name);
				scanf("%s", address);
				addCenter(&(r)->down, name, address, codeC, codeR);
				break;
			}
			r = r->next;
		}
	}
}

void seachCenterRegister(Register *r, char codeC[4])
{
	bool flag = false;
	if (!vacio(r))
	{
		while (r)
		{
			seachCenter(r->down, codeC, &flag);
			if (!(flag))
				r = r->next;
			else
				break;
		}
	}
}

void seeRegister(Register *r)
{
	printf("Codigo: %s - ", r->code);
	printf("Nombre: %s ", r->name);
	printf("Numero: %s ", r->number);
	printf("\n Direccion: %s - ", r->address);
}

void seeAll(Register *r)
{
	int cont = 1;
	if (!vacio(r))
	{
		while (r)
		{
			printf("\n\n Caja [%i] Registro Estatal: \n\n", cont);
			seeRegister(r);
			printf("\n\n");
			seePersonCenter(r->down);
			cont++;
			r = r->next;
			system("pause");
			system("cls");
		}
	}
}

void seachDeleteCenter(Register **r, char code[8], bool flag) // busca el la caja principal a eliminar
{
	Register *t = (*r);
	if (!(vacio(t)))
	{
		while (t)
		{
			printf("\n Entro while seachDeleteCenter");
			Center *aux = (*r)->down;
			if ((strcmp(code, aux->code) == 0)) //caso cabeza
			{
				(*r)->down = (aux)->next;
				if (flag)
					DeletePeople(&(aux)->left, &aux);
				else // else if (!flag && !vacio(t->down))
					changeCenter(&aux, &(aux)->left, code);
				delete aux;
				break;
			}
			else
				seachChangeDeleteCenter(&(t)->down, code, flag);
			t = t->next;
		}
	}
} // falta el caso de si es el cabeza de a lista. 

void changeRegister(Register **r, Center **c, char codeR[4]) // parametros: lista principal completa, sub-lita a enlazar, numero X que se va a eliminar de la principal 
{
	char codeRNew[4];
	printf("\n Codigo Region Estatal donde desea mover los centros :");
	scanf("%s", &codeRNew);
	Register *aux = (*r);
	while (aux)
	{
		printf("\n Entro while changeRegister :");
		if ((strcmp(codeRNew, aux->code) == 0) && (strcmp(codeRNew, codeR) != 0)) // se busca la caja principal a enlazar con sublista de X, mientras sea distinto de X
		{
			Center *t = aux->down; // se asigna un auxiliar hacia la sublista que ya tiene la caja principal que se le desea enlazar la otra sublista
			while (t->next) // busca el final de la sublista de la caja principal
				t = t->next;
			t->next = (*c); //enlaza la ultima caja de la sublista, con el puntero de la sublita de la caja a eliminar
			changeCodeCenter(&(t)->next, codeRNew);
			break;
		}
		aux = aux->next;
	}
} // Solucionar, se interrumpe la corrida.

void modifyRegister(Register **r)
{
	int op = -1; char name[65] = "", address[100] = "", codeR[4] = "", number[12] = "";
	while (op != 0) {
		system("cls");
		printf("\n\n Indica lo que deseas modificar.\n\n");
		printf("\n 1. Codigo de Region Estatal(Modifica Codigo Centros Electorales).");
		printf("\n 2. Nombre.");
		printf("\n 3. Direccion. ");
		printf("\n 4. Numero.");
		printf(" 0. Salir. \n\n");
		printf("Indique opcion (0-4): ");
		op = 0;
		scanf("%i", &op);
		system("cls");
		printf("\n\n");
		switch (op)
		{
		case 1: printf(" Indique Codigo Estatal: ");
			scanf("%s", codeR);
			//printf(" %s: " ,(*r)->code);
			strcpy((*r)->code, codeR);
			//printf(" %s: ", (*r)->code);
			changeCodeCenter(&(*r)->down, codeR);
			break;

		case 2:	printf(" Indique Nombre: ");
			scanf("%s", name);
			strcpy((*r)->name, name);
			break;

		case 3:	printf(" Indique Direccion: ");
			scanf("%s", address);
			strcpy((*r)->address, address);
			break;

		case 4:printf(" Indique Numero Telefonico: ");
			scanf("%s", number);
			strcpy((*r)->number, number);
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

void seachChangeDeleteRegister(Register **r, char codeR[4], bool flag) 
{
	Register *aux = (*r);
	if (!(vacio(aux)))
	{
		if ((strcmp(codeR, aux->code) == 0)) //caso cabeza
		{
			(*r) = (*r)->next;
			if (flag)
				modifyRegister(&(*r));
			else // else if (!flag && !vacio(t->down))
			{
				changeRegister(r, &(*r)->down, codeR);
				delete aux;
			}
		}
		else
		{
			while (aux->next)
			{
				if ((strcmp(codeR, aux->next->code) == 0))
				{
					Register *t = aux->next;
					aux->next = aux->next->next;
					if (flag)
						modifyRegister(&t);
					else // else if (!flag && !vacio(t->down))
					{
						changeRegister(r, &(t)->down, codeR);
						delete t;
					}
					break;
				}
				aux = aux->next;
			}
		}
	}
}

int countStates(Register *r)
{
	int sumStates = 0, sumAllPeople = 0; bool flag = true;
	while (r)
	{
		printf("\n Region Estatal: %s codigo %s", r->name, r->code);
		int x = countStatesCenterPerson(r->down, flag);
		printf("\n En total tiene %i votantes ", x);
		sumAllPeople += x;
		sumStates++;
		r = r->next;
	}
	return sumStates;
}

void seachR(Register *r, char codeR[4])
{
	while (r)
	{
		if ((strcmp(codeR, r->code) == 0))
		{
			printf("\n En la Region Estatal %s codigo %s", r->name, r->code);
			bool flag = false;
			int x = countStatesCenterPerson(r->down, flag);
			printf("\n Hay %i Centro electorales.", x);
			break;
			r = r->next;
		}
	}
}

void seachRC(Register *r, char code[8])
{
	while (r)
	{
		Center *aux = r->down;
		while (aux)
		{
			if ((strcmp(code, aux->code) == 0))
			{
				countCenterPerson(aux);
				break;
			}
			aux = aux->next;
		}
		r = r->next;
	}
} // reporte centro electoral

void seachID(Register *r, char ID[10])
{
	while (r)
	{
		Center *aux = r->down; bool flag = false;
		while (aux)
		{
			if (seachPerson(aux->left, ID, flag) == 1)
			{
				seeCenter(aux);
				printPerson(aux->left);
			}
		}
		r = r->next;
	}
}

void seachNameRegister(Register *r, char name[65])
{
	int re = 0;
	while (r)
	{
		int x = seachNameCenter(r->down, name);
		if (x != 0)
		{
			printf(" \n En :");
			seeRegister(r);
			printf(" Hay [%i] Centro(s) Electorale(s) que coinciden con : %s", x, name);
			re++;
		}
		r = r->next;
		printf("\n\n");
		system("pause");
		system("cls");
	}
	printf(" Hay [%i] Registro(s) Regionale(s) que coinciden con : %s", re, name);
}

void seachIDModify(Register *r, char ID[10])
{
	int x = 0;
	while (r)
	{
		Center *aux = r->down; bool flag = true;
		while (aux)
		{
			x = seachPerson(aux->left, ID, flag);
			if (x == 1)
				break;
			aux = aux->next;
		}
		r = r->next;
	}
}

void seachCenterModify(Register *r, char codeC[8])
{
	while (r)
	{
		Center *aux = r->down;
		while (aux)
		{
			if ((strcmp(codeC, aux->code) == 0))
			{
				modifyCenter(&aux);
				break;
			}
			aux = aux->next;
		}
	}
}

void seachSonFather(Register *r, char ID[10], char newFather[8])
{
	while (r) 
	{
		if (changeSonFather(&(r)->down, ID, newFather) == 1)
			break;
		r = r->next;
	}
}
