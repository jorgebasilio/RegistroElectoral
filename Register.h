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
		else printf("Registro Estatal ya registrado!!");
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
				scanf("%s", &codeC);
				scanf("%s", &name);
				scanf("%s", &address);
				addCenter(&(r)->down, name, address, codeC);
				break;
			}
			r = r->next;
		}
	}
}

void seachCenterRegister(Register *r, char codeC[8])
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
			printf("\n\n Caja [%i] Registro : \n\n", cont);
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

void seachDeleteCenter(Register **r, char codeC[8], bool flag) // busca el la caja principal a eliminar
{
	Register *aux = (*r);
	if (!(vacio(aux)))
	{
		while (aux)
		{
			printf("\n Entro while seachDeleteCenter");
			seachChangeDelete(&(aux)->down, codeC, flag);
			aux = aux->next;
		}
	}
} // falta el caso de si es el cabeza de a lista. 

