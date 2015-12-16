#pragma once

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

void seachCenter(Center *c, char codeC[8], bool *flag)
{
	if (!(vacio(c)))
	{
		while (c)
		{
			if ((strcmp(codeC, c->code) == 0))
			{
				if (*flag)
					seePeople(c->left);
				else
				{
					addPersonCenter(c, codeC);
					*flag = true;
				}

				break;
			}
			c = c->next;
		}
	}
}

void seePersonCenter(Center *c)
{
	int cont = 1; bool flag = true;
	if (!vacio(c))
	{
		while (c)
		{
			printf("\n\n Caja [%i] principal con su sublista : \n\n", cont);
			seeCenter(c);
			printf("\n\n");
			seachCenter(c, c->code, &flag);
			c = c->next;
			cont++;
		}
	}
}
void change(Center **c, People **p, char codeC[8]) // parametros: lista principal completa, sub-lita a enlazar, numero X que se va a eliminar de la principal 
{
	char codeCNew[8];
	printf("\n Codigo Centro Electoral donde iran los electores :");
	scanf("%s", &codeCNew);
	Center *aux = (*c);
	while (aux)
	{
		if ((strcmp(codeCNew, aux->code) == 0) && (strcmp(codeCNew, codeC) != 0)) // se busca la caja principal a enlazar con sublista de X, mientras sea distinto de X
		{
			People *t = aux->left; // se asigna un auxiliar hacia la sublista que ya tiene la caja principal que se le desea enlazar la otra sublista
			while (t->next) // busca el final de la sublista de la caja principal
				t = t->next;
			t->next = (*p); //enlaza la ultima caja de la sublista, con el puntero de la sublita de la caja a eliminar
			break;
		}
		aux = aux->next;
	}
}

void seachChangeDelete(Center **c, char codeC[8], bool flag)
{
	Center *aux = (*c);
	while (aux)
	{
		printf("\n Entro while seachChangeDelete");
		if ((strcmp(codeC, aux->next->code) == 0)) // se evalua para buscar el numero a eliminar
		{
			Center *t = aux->next;
			aux->next = aux->next->next;
			if (flag && !vacio(t->left)) // depende de la opcion del usuario, de lo que desea hacer
				DeletePeople(&(t)->left); // elimina toda la sub-lista
			else if (!flag && !vacio(t->left))
				change(c, &(t)->left, codeC); // busca otra caja principal para poner la sub-lista de la caja a eliminar
			delete t;
			break;
		}
		aux = aux->next;
	}
}

