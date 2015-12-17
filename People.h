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

void printPerson(People *p)
{
	printf(" Cedula: %s - ", p->ID);
	printf(" Nombre: %s ", p->name);
	printf("\n Direccion: %s - ", p->address);
	printf(" F. Nacimiento: %s \n\n", p->date);
}

void seePeople(People *p)
{
	while (p)
	{
		printPerson(p),
		p = p->next;
	}
}

void modifyPerson(People **p)
{
	int op = -1; char ID[10] = "", name[65] = "", address[100] = "", date[9] = "", codeC[8];
	while (op != 0) {
		system("cls");
		printf("\n\n Indica lo que deseas modificar.\n\n");
		printf("\n 1. Cedula De identidad.");
		printf("\n 2. Nombre.");
		printf("\n 3. Direccion. ");
		printf("\n 4. Fecha de Nacimiento.");
		printf(" 0. Salir. \n\n");
		printf("Indique opcion (0-4): ");
		op = 0;
		scanf("%i", &op);
		system("cls");
		printf("\n\n");
		switch (op)
		{
		case 1: printf(" Indique Cedula: ");
			scanf("%s", ID);
			strcpy((*p)->ID, ID);
			break;

		case 2:	printf(" Indique Nombre: ");
			scanf("%s", name);
			strcpy((*p)->name, name);
			break;

		case 3:	printf(" Indique Direccion: ");
			scanf("%s", address);
			strcpy((*p)->address, address);
			break;

		case 4:printf(" Indique Fecha de Nacimiento: ");
			scanf("%s", date);
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

int seachPerson(People *p, char ID[10], bool flag) 
{
	int x = 0;
	while (p)
	{
		if ((strcmp(ID, p->ID) == 0))
		{
			if (flag) modifyPerson(&p);
			x = 1;
			break;
		}
		p = p->next;
	}
	return x;
}

int countPerson(People *p)
{
	int sum = 0;
	while (p)
	{
		sum ++;
		p = p->next;
	}
	return sum;
}

int seachName(People *p, char name[65])
{
	int x = 0;
	while (p)
	{
		char * pch, comparation[65];
		pch = strpbrk(name, p->name);
		strcpy(comparation, pch);
		if ((strcmp(name, comparation) == 0))
		{
			printPerson(p);
			x ++;
		}
		p = p->next;
	}
	return x;
}

/* void returnDDMMAA(char DD[3], char MM[3], char AA[5], char carry[10])
{
	char *_p = carry;

	strncpy(DD, _p, 2);
	_p = &carry[2];
	strncpy(MM, _p, 2);
	_p = &carry[4];
	strncpy(AA, _p, 4);
}


void returnCarry(char date[10], char carry[10])
{
	char DD[3], MM[3], AA[5], DDP[3], MMP[3], AAP[5];
	returnDDMMAA(DD, MM, AA, carry);
	returnDDMMAA(DDP, MMP, AAP, date);
	if (strcmp(AA, AAP) > 0)
		strcpy(carry, date);
	else if ((strcmp(AA, AA) == 0) && (strcmp(MM, MMP) > 0))
		strcpy(carry, date);
	else if ((strcmp(AA, AA) == 0) && (strcmp(MM, MMP) == 0) && ((strcmp(DD, DDP) > 0) || (strcmp(DD, DDP) == 0)))
		strcpy(carry, date);
}
*/
