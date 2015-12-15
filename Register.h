# RegistroElectoral

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

void addRegister(Register **r, char name[65], char address[100],char number[12], char codeR[4])
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
