
struct Center {
  char name[65];
  char address[100];
  char codeC[4]; // code hijo
  char codeR[4]; // code padre
  char code[8];
  Center *next;
  People *left;
};
bool vacio(Center *c)
{
  return (!(c));
}

void addCenter(Center **c, char name[65], char address[100], char codeC[4])
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
    else printf("Codigo Centro Electoral ya registrado!!");
  }
}

void seeCenter(Center *c)
{
  printf(" Codigo: %s - ", c->code);
  printf(" Nombre: %s ", c->name);
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
        printf("\n Cedula: \n");
        scanf("%s", &ID);
        printf("\n Nombre: \n");
        scanf("%s", &name);
        printf("\n Direccion: \n");
        scanf("%s", &address);
        printf("\n Fecha de Nacimiento: \n");
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
      printf("\n\n [%i] Centro Electoral : \n\n", cont);
      seeCenter(c);
      printf("\n\n");
      seachCenter(c, c->code, &flag);
      c = c->next;
      cont++;
    }
  }
}


void changeCenter(Center **c, People **p, char codeC[8]) // parametros: lista principal completa, sub-lita a enlazar, numero X que se va a eliminar de la principal 
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

void DeletePeople(People **p, Center **c)      //Elimina toda la sub-lista indicada.
{
  while (*p)
  {
    People *t = (*p);
    (*c)->left = (*p)->next;
    delete t;
  }
}

void seachChangeDeleteCenter(Center **c, char codeC[8], bool flag)
{
  Center *aux = (*c);
  while (aux->next)
  {
    printf("\n Entro while seachChangeDelete");
    if ((strcmp(codeC, aux->next->code) == 0)) // se evalua para buscar el numero a eliminar
    {
      Center *t = aux->next;
      aux->next = aux->next->next;
      if (flag && !vacio(t->left)) // depende de la opcion del usuario, de lo que desea hacer
        DeletePeople(&(t)->left, &t); // elimina toda la sub-lista
      else if (!flag && !vacio(t->left))
        changeCenter(c, &(t)->left, codeC); // busca otra caja principal para poner la sub-lista de la caja a eliminar
      delete t;
      break;
    }
    aux = aux->next;
  }
}

People *seachSonCenter(Center **c, char ID[10])
{
  Center *aux = (*c);
  People *ref = NULL;
  while (aux)
  {
    People *t = aux->left;
    bool flag = false;
    while (t)
    {
      if ((strcmp(ID, t->ID) == 0)) // caso cabeza
      {
        aux->left = t->next;
        ref = t;
        if (ref->next != NULL)
          ref->next = NULL;
        flag = true;
        break;
      }
      else if ((strcmp(ID, t->next->ID) == 0))
      {
        ref = t->next;
        t->next = t->next->next;
        if (ref->next != NULL)
      
          ref->next = NULL;
        flag = true;
        break;
      }
      t = t->next;
    }
    if (flag) break;
    aux = aux->next;
  }
  return ref;
}

void changeCodeCenter(Center ** c, char codeR[4])
{
  while (*c)
  {
    strcpy((*c)->code, codeR);
    strcat((*c)->code, (*c)->codeC);
    strcpy((*c)->codeR, codeR);
    (*c) = (*c)->next;
  }
}

void modifyCenter(Center **c)
{
  int op = -1; char name[65] = "", address[100] = "", codeC[8] = "";
  while (op != 0)
  {
    system("cls");
    printf("\n\n Indica lo que deseas modificar.\n\n");
    printf("\n 1. Codigo Centro Electoral.");
    printf("\n 2. Nombre.");
    printf("\n 3. Direccion. ");
    printf(" 0. Salir. \n\n");
    printf("Indique opcion (0-4): ");
    op = 0;
    scanf(" %i", &op);
    system("cls");
    printf("\n\n");
    switch (op)
    {
      case 1: printf(" Indique Codigo del Centro Electoral: ");
        scanf(" %s", codeC);
        strcpy((*c)->code, (*c)->codeR);
        strcat((*c)->code, codeC);
        strcpy((*c)->codeC, codeC);
        break;

      case 2: printf(" Indique Nombre: ");
        scanf(" %s", name);
        strcpy((*c)->name, name);
        break;

      case 3: printf(" Indique Direccion: ");
        scanf(" %s", address);
        strcpy((*c)->address, address);
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

int countStatesCenterPerson(Center *c, bool flag)
{
  int sumPeople = 0, sumCenter = 0;
  while (c)
  {
    if (!flag) printf("\n Centro Electoral: %s codigo %s", c->name, c->code);
    int x = countPerson(c->left);
    if (!flag) printf("\n Tiene %i votantes ", x);
    sumPeople += x;
    sumCenter++;
    c = c->next;
  }
  if (flag) return sumPeople;
  else return sumCenter;
}

void countCenterPerson(Center *c)
{
  printf("\n Centro Electoral: %s codigo %s", c->name, c->code);
  int x = countPerson(c->left);
  printf("\n Tiene %i votantes ", x);

}

int seachNameCenter(Center *c, char name[65])
{
  int re = 0;
  while (c)
  {
    int x = seachName(c->left, name);
    if (x != 0)
    {
      printf(" \n En :");
      seeCenter(c);
      printf(" Hay [%i] personas que coinciden con: %s", x, name);
      re++;
    }
    c = c->next;
  }
  return re;
}

int movePerson(Center **c, People *ref, char newFather[8])
{
  Center *aux = (*c); int flag = 0;
  while (aux)
  {
    if ((strcmp(newFather, aux->code) == 0))
    {
      ref->next = aux->left;
      aux->left = ref;
      flag = 1;
      break;
    }
    aux = aux->next;
  }
  return flag;
}
int changeSonFather(Center **c, char ID[10], char newFather[8]) //modificar
{
  Center *aux = (*c); bool flag = false; int x = 0;
  while (aux)
  {
    People *t = aux->left, *ref = NULL;
    char father[8];
    strcpy(aux->code, father);
    while (t)
    {
      if (t->next)
      {
        if (strcmp(ID, t->next->ID) == 0)
        {
          People *ref = t->next;
          t->next = t->next->next;
        }
        else if (strcmp(ID, t->ID) == 0) // Caso cabeza
        {
          aux->left = t->next;
          People *ref = t;
        }
        Center *auxo = (*c);
        while (auxo)
        {
          if (strcmp(newFather, auxo->code) == 0)
          {
            People *t = auxo->left;
            while (t->next)
              t = t->next;
            t->next = ref;
            x = 1;
            break;
          }
          auxo = auxo->next; //error en esta linea, o una cercana.
        }
        flag = true;
        break;
      }
      t = t->next;
    }
    if (flag) break;
    aux = aux->next;
  }
  return x;
} //modificar
Center *KeyToCenter( key *data ){
  if(!data){
    return NULL;
  }
  Center *center =  new Center;
  int cont = 0;
  while(cont < 3 && (data != NULL))
  {
    if (strcmp(data->clave,"nombre") == 0)
    {
      strcpy(center->name, data->valor);
      cont++;
    }
    if (strcmp(data->clave,"direccion") == 0)
    {
      strcpy(center->address, data->valor);
      cont++;
    }
    if (strcmp(data->clave,"codigo") == 0)
    {
      strcpy(center->code, data->valor);
      cont++;
    }

    data = data->next;
  }
  if (cont == 3) return(center);
  else return(NULL);
}

index *IndexCenter( key **data, Center *center ){
  if(*data != NULL){
    while(*data){
      if (strcmp((*data)->clave, "references") == 0){
        index *aux = (*data)->ind;
        while(aux){
          strcpy(aux->id, center->code);
          strcpy(aux->belongs_to, "people");
          aux = aux->next;
        }
        return((*data)->ind);
      }
      *data = (*data)->next;
    }
  } 
  else 
    return NULL;
}
bool centerExists( Center *data, char code[]){
  while(data != NULL){
    if (strcmp(data->code, code) == 0)
      return true;
    data = data->next;
  }
  return false;  
}