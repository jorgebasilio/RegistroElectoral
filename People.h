#pragma once
struct People {
	char ID[10];
	char name[65];
	char address[100];
	char date[9];
	People *next;
};

bool vacio(People *p)
{
	return (!(p));
}

void addPerson(People **p, char ID[10], char name[65], char address[100], char date[9])
{
	bool flag = false;
	if (vacio(*p))
	{
		People *aux = new People;
		strcpy(aux->ID, ID);
		strcpy(aux->name, name);
		strcpy(aux->address, address);
		strcpy(aux->date, date);
		aux->next = (*p);
		(*p) = aux;
		flag = true;
	}
	else
	{
		People *t = (*p);
		while (t)
		{
			if ((strcmp(ID, t->ID) == 0))
			{
				flag = true;
				break;
			}
			t = t->next;
		}

		if (!flag)
		{
			People *aux = new People;
			strcpy(aux->ID, ID);
			strcpy(aux->name, name);
			strcpy(aux->address, address);
			strcpy(aux->date, date);
			aux->next = NULL;
			t = (*p);
			while (t->next)
				t = t->next;
			t->next = aux;
		}
		else printf(" Cedula ya registrada!!");
	}
}

void seePeople(People *p)
{
	while (p)
	{
		printf(" Cedula: %s - ", p->ID);
		printf(" Nombre: %s ", p->name);
		printf("\n Direccion: %s - ", p->address);
		printf(" F. Nacimiento: %s \n\n", p->date);
		p = p->next;
	}
}



void modifyPerson(People **p)
{
	int op = -1; char ID[10] = "", name[65] = "", address[100] = "", date[9] = "";
	while (op != 0) {
		system("cls");
		printf("\n\n Indica lo que deseas modificar.\n\n");
		printf("\n 1. Cedula De identidad.");
		printf("\n 2. Nombre.");
		printf("\n 3. Direccion. ");
		printf("\n 4. Fechar de Nacimiento.");
		printf(" 0. Salir. \n\n");
		printf("Indique opcion (0-4): ");
		op = 0;
		scanf("%i", &op);
		system("cls");
		printf("\n\n");
		switch (op)
		{
		case 1: printf(" Indique Cedula: ");
			scanf("%s", &ID);
			strcpy((*p)->ID, ID);
			break;

		case 2:	printf(" Indique Nombre: ");
			scanf("%s", &name);
			strcpy((*p)->name, name);
			break;

		case 3:	printf(" Indique Direccion: ");
			scanf("%s", &address);
			strcpy((*p)->address, address);
			break;

		case 4:printf(" Indique Fecha de Nacimiento: ");
			scanf("%s", &date);
			strcpy((*p)->date, date);
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

void seachPerson(People *p, char ID[10])
{
	while (p)
	{
		if ((strcmp(ID, p->ID) == 0))
		{
			modifyPerson(&p);
			break;
		}
		p = p->next;
	}
}
