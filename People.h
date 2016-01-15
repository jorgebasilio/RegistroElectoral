struct People {
  char address[100];
  char name[70];
  char date[11]; 
  char ID[11];
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

    case 2: printf(" Indique Nombre: ");
      scanf("%s", name);
      strcpy((*p)->name, name);
      break;

    case 3: printf(" Indique Direccion: ");
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
      else printPerson(p);
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
  char * pch, comparation[65];
  int x = 0;
  while (p)
  {
    pch = strpbrk(name, p->name);
    if (pch != NULL)
    {
      strcpy(comparation, pch);
      if ((strcmp(name, comparation) == 0))
      {
        printPerson(p);
        x++;
      }
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


People *KeyToPeople( key *data ){
  if(!data){
    return NULL;
  }
  People *person = new People;
  int cont = 0;
  while(cont < 4 && data){
    if( strcmp(data->clave, "cedula") == 0)
    {
      strcpy(person->ID, data->valor);
      cont++;
    }
    else if( strcmp(data->clave, "nombre") == 0 )
    { 
      strcpy(person->name, data->valor);
      cont++;
    }
    else if( strcmp(data->clave, "direccion") == 0 )
    { 
      strcpy(person->address, data->valor);
      cont++;
    }
    else if( strcmp(data->clave, "fecha") == 0 )
    {
      strcpy(person->date, data->valor);
      cont++;
    }
    else
      return( NULL);
    data = data->next;
  }
  if(cont == 4) 
    return person;
  else
    return NULL;
}

People *RecorverPeopleDB(){
  People *aux = NULL,*person = new People;
  FILE *data_people = fopen("people.dat", "r");
  if(data_people != NULL){
    while(fread(person, sizeof(People), 1, data_people) != NULL){
      addPerson(&aux, person->ID, person->name, person->address, person->date);      
    }
    rewind(data_people);
    fclose(data_people);
  }
  else{
    system("cls");
    printf("La Base de datos de los electores no ha sido creada...\n");
    system("PAUSE");
  }
  return aux;
}

int calculateAge( char *date, char *timeS ){
  char sysyear[5];
  char sysmonth[3];
  char sysday[3];
  char peoyear[5];
  char peomonth[3];
  char peoday[3];
  int sys_year = 0;
  int sys_month = 0;
  int sys_day = 0;
  int peo_year = 0;
  int peo_month = 0;
  int peo_day = 0;
  int age = 0;
  int e = 0;
  if ( strlen(date) == strlen(timeS) )
  {
    for (int i = 0; i < 4; ++i)
    {
      if ( i == 0 || i == 1 || i == 2 || i == 3 )
      {
        sysyear[e] = timeS[6+i];
        peoyear[e] = date[6+i];  
      }
      if ( i == 0 || i == 1 )
      {
        sysmonth[e] = timeS[3+i];
        peomonth[e] = date[3+i];
      }
      if ( i == 0 || i == 1 )
      {
        sysday[e] = timeS[i];
        peoday[e] = date[i];
      }
      e++;
      if( e == 4 ){
        sysyear[e] = '\0';
        peoyear[e] = '\0';
        sysmonth[2] = '\0';
        peomonth[2] = '\0';
        sysday[2] = '\0';
        peoday[2] = '\0';
      }
    }
    sys_year = atoi(sysyear);
    sys_month = atoi(sysmonth);
    sys_day = atoi(sysday);
    peo_year = atoi(peoyear);
    peo_month = atoi(peomonth);
    peo_day = atoi(peoday);
    age = sys_year - peo_year;
    if (sys_month >= peo_month)
      if (sys_day >= peo_day)
        return age;
    return(age - 1);
  }
}
void peopleRangAge( People *people, int min, int max ){
  time_t t = time(0);
  struct tm *tlocal = localtime(&t);
  char timeSystem[64];
  strftime(timeSystem,64,"%d/%m/20%y",tlocal);
  int e = (-1);
  bool flag = false;
  while(people != NULL){
    int age_people = calculateAge( people->date, timeSystem );
    if ( e == (-1))
    {
      printf("\n%-10s \| %-25s \| %-25s\n", "Cedula", "Nombre", "Edad");
      e = 0;
    }
    if ( age_people >= min && age_people <= max)
    {

      printf("%-10s \| %-25s \| %-25i\n", people->ID, people->name, age_people);
      e++;
      flag = true;
    }
    people = people->next;
  }
  if(!flag)
    printf("No hay personas que coincidan en el rango de edad\n");
  else
    printf("Coinciden \" %i \" Personas en el rango de edad\n", e);
}