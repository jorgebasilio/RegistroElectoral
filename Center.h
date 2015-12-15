# RegistroElectoral

struct Center {
	char name[65];
	char address[100];
	char code[8];
	Center *next;
	People *left;
};

bool vacio(Center *c)
{
	return (!(c));
}

void addCenter(Center **c, char name[65], char address[100], char codeC[8])
{
	bool flag = false;
	if (vacio(*c))
	{
		Center *aux = new Center;
		strcpy(aux->code, codeC);
		strcpy(aux->name, name);
		strcpy(aux->address, address);
		aux->next = (*c);
		aux->left = NULL;
		(*c) = aux;
		flag = true;
	}
	else
	{
		Center *t = (*c);
		while (t)
		{
			if ((strcmp(codeC, t->code) == 0))
			{
				flag = true;
				break;
			}
			t = t->next;
		}

		if (!flag)
		{
			Center *aux = new Center;
			strcpy(aux->code, codeC);
			strcpy(aux->name, name);
			strcpy(aux->address, address);
			aux->next = NULL;
			aux->left = NULL;
			t = (*c);
			while (t->next)
				t = t->next;
			t->next = aux;
		}
		else printf("Persona ya registrada!!");
	}
}

void seeCenter(Center *c)
{
		printf("Codigo: %s - ", c->code);
		printf("Nombre: %s ", c->name);
		printf("\n Direccion: %s - ", c->address);
}	

void addPersonCenter(Center *c, char codeC[8])
{
	char ID[10], name[65], address[100], date[9];
	if (!(vacio(c)))
	{
		while (c)
		{
			if ((strcmp(codeC, c->code) == 0)) 
			{
				printf("\n Ingrese sus datos: \n");
				scanf("%s", &ID);
				scanf("%s", &name);
				scanf("%s", &address);
				scanf("%s", &date);
				addPerson(&(c)->left, ID, name, address, date);
				break;
			}
			c = c->next;
		}
	}
}

void seach(Center *c, char codeC[8]) //Busca el valor indicado (x) para mandar puntero a mostrar22 y mostrar su sub-lista.        Optimizar
{
	if (!(vacio(c)))
	{
		while (c)
		{
			if ((strcmp(codeC, c->code) == 0)) 
			{
				seePeople(c->left);
				break;
			}
			c = c->next;
		}
	}
}

void seeAll(Center *c) //Muestra cada caja de lista principal con su debida sub-lista.       Optimizar
{
	int cont = 1;
	if (!vacio(c))
	{
		while (c)
		{
			printf("\n\n Caja [%i] principal con su sublista : \n\n", cont);
			seeCenter(c);
			printf("\n\n");
			seach(c, c->code);
			c = c->next;
			cont++;
		}
	}
}
