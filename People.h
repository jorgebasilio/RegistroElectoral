# RegistroElectoral

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
		else printf("Persona ya registrada!!");
	}
}

void seePeople(People *p)
{
	while (aux)
	{
		printf("Cedula: %s - ", p->ID);
		printf("Nombre: %s ", p->name);
		printf("\n Direccion: %s - ", p->address);
		printf("F. Nacimiento: %s \n\n", p->date);
		p = p->next;
	}	
}
