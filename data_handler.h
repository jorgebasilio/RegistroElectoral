bool referencesIsPresent( char *root_file, char *id  ){
  index *ind = new index;
  FILE *data_index = fopen(root_file, "r");
  if(data_index != NULL){
    while((fread(ind, sizeof(index), 1, data_index)) != NULL){
      if( strcmp(ind->has_one, id) == 0 ){
        rewind(data_index);
        fclose(data_index);
        return true;        
      }
    }
    return false;
  }
  else
    return false;
}

//----------------PEOPLE
People *findPeople( char *id ){
  People *person = new People;
  FILE *data_people = fopen("people.dat", "r");
  if(data_people != NULL){
    while(fread(person, sizeof(People), 1, data_people) != NULL){
      if( strcmp(person->ID, id) == 0 ){
        rewind(data_people);
        fclose(data_people);      
      }
    }
    return person;
  }
  else{
    rewind(data_people);
    fclose(data_people);
    return person;
  }
}
bool peopleIsPresent( char *id ){
  People *person = new People;
  FILE *data_people = fopen("people.dat", "r");
  if(data_people != NULL){
    while(fread(person, sizeof(People), 1, data_people) != NULL){
      if( strcmp(person->ID, id) == 0 ){
        rewind(data_people);
        fclose(data_people);
        return true;        
      }
    }
    return false;
  }
  else{
    rewind(data_people);
    fclose(data_people);
    return false;
  }
}
void createPeopleDB(){
  FILE *fp = NULL;
  fp=fopen("People.dat", "rb");
  if(fp == NULL)
    fp=fopen("People.dat", "wb");
  fclose(fp);
}
void SavePeopleDB( key *data ){
  People *person = KeyToPeople(data);
  if (person != NULL)
  {
    createPeopleDB();
    FILE *data_people = fopen("people.dat", "a+b");
    if((data_people != NULL) && (!peopleIsPresent( person->ID ))){
      fwrite(person, sizeof(People), 1, data_people);
    }
    rewind(data_people);
    fclose(data_people);
  }
}
void ViewPeopleDB(){
  People *person = new People;
  FILE *data_people = fopen("people.dat", "r");
  if(data_people != NULL){
    printf("\n%-10s \| %-25s \| %-25s \| %-10s\n\n", "Cedula", "Nombre", "Direccion", "Fecha Nac." );
    while(fread(person, sizeof(People), 1, data_people) != NULL){
      printf("%-10s \| %-25s \| %-25s \| %-10s\n", person->ID, person->name, person->address, person->date);
    }
    rewind(data_people);
    fclose(data_people);
  }
  else
    printf("La Base de datos de los electores no ha sido creada...\n");
}
//------------------Center
void indexrPeople( People **person, People **aux ){
  (*aux)->next = (*person);
  *person = (*aux);
}
People *findPeopleCenter( char *code ){
  index *ind = new index;
  FILE *index_center = fopen("center.index", "r");
  People *aux = NULL;
  if(index_center != NULL){
    while(fread(ind, sizeof(index), 1, index_center) != NULL){
      if( strcmp(ind->id, code) == 0 ){
        People *tmp = findPeople( ind->has_one );
        indexrPeople(&aux, &tmp);
      }
    }
    rewind(index_center);
    fclose(index_center);
    return aux;
  }
  else
    return NULL;
}
Center *RecorverCenterDB(){
  Center *aux = new Center, *rtn = NULL, *ctr = new Center;
  FILE *data_center = fopen("center.dat", "r");
  if(data_center != NULL){
    bool flag = false;
    while(fread(ctr, sizeof(Center), 1, data_center) != NULL){
      if (flag)
      {
        aux->next = new Center;
        aux = aux->next;
      }
      strcpy(aux->code, ctr->code);
      strcpy(aux->name, ctr->name);
      strcpy(aux->address, ctr->address);
      aux->next = NULL;
      aux->left = findPeopleCenter(aux->code);
      if (rtn == NULL){
        rtn = aux;
        flag = true;
      }
    }
    aux->next = NULL;
    rewind(data_center);
    fclose(data_center);
  }
  else
    printf("La Base de datos de los electores no ha sido creada...\n");
  return rtn;
}
Center *findCenter( char *code ){
  Center *ctr = new Center;
  FILE *data_center = fopen("center.dat", "r");
  if(data_center != NULL){
    while(fread(ctr, sizeof(Center), 1, data_center) != NULL){
      if( strcmp(ctr->code, code) == 0 ){
        ctr->left = findPeopleCenter(ctr->code);
        rewind(data_center);
        fclose(data_center);
        return ctr;        
      }
    }
    rewind(data_center);
    fclose(data_center);
    return NULL;
  }
  else
    return NULL;
}
bool centerIsPresent( char *code ){
  Center *ctr = new Center;
  FILE *data_center = fopen("center.dat", "r");
  if(data_center != NULL){
    while(fread(ctr, sizeof(Center), 1, data_center) != NULL){
      if( strcmp(ctr->code, code) == 0 ){
        rewind(data_center);
        fclose(data_center);
        return true;        
      } 
    }
    rewind(data_center);
    fclose(data_center);
    return false;
  }
  else
    return false;
}
void createCenterDB(){
  FILE *fp1 = NULL;
  FILE *fp2 = NULL;
  fp1=fopen("center.dat", "rb");
  fp2=fopen("center.index", "rb");
  if((fp1 == NULL) && (fp1 == NULL)){
    fp1=fopen("center.dat", "wb");
    fp2=fopen("center.index", "wb");
    fclose(fp1);
    fclose(fp2);
  }
}
void SaveCenterDB( key *data ){
  Center *polling_station = KeyToCenter(data);
  if (polling_station != NULL)
  {
    createCenterDB();
    FILE *data_center = fopen("center.dat", "a+b");
    if(data_center != NULL){ 
      if(!centerIsPresent(polling_station->code))
        fwrite(polling_station, sizeof(Center), 1, data_center);
      rewind(data_center);
      fclose(data_center);
    }
    index *r_center = IndexCenter(&data, polling_station);
    if (r_center != NULL)
    {
      FILE *index_center = fopen("center.index", "a+b");
      if(index_center != NULL){
        while(r_center != NULL){
          if( peopleIsPresent(r_center->has_one) && (!referencesIsPresent("center.index", r_center->has_one)))
            fwrite(r_center, sizeof(index), 1, index_center);
          r_center = r_center->next;
        }
        rewind(index_center);
        fclose(index_center);
      }
    }
    
  }
}
//----------------Register  
void indexrCenter( Center **ctr, Center **aux ){
  (*aux)->next = (*ctr);
  *ctr = (*aux);
}
Center *findCenterRegister( char *id ){
  index *ind = new index;
  FILE *index_register = fopen("register.index", "r");
  Center *aux = NULL;
  if(index_register != NULL){
    while(fread(ind, sizeof(index), 1, index_register) != NULL){
      if( strcmp(ind->id, id) == 0 ){
        Center *tmp = findCenter( ind->has_one );
        if(tmp != NULL){
          tmp->next = aux;
          aux = tmp;          
        }
      }
    }
    rewind(index_register);
    fclose(index_register);
    return aux;
  }
  else
    return NULL;
}
Register *RecorverRegisterDB(){
  Register *aux = new Register,*rtn = NULL,*reg = new Register;
  FILE *data_register = fopen("register.dat", "r");
  if(data_register != NULL){
    bool flag = false;
    while(fread(reg, sizeof(Register), 1, data_register) != NULL){
      if (flag)
      {
        aux->next = new Register;
        aux = aux->next;
      }
      strcpy(aux->code, reg->code);
      strcpy(aux->name, reg->name);
      strcpy(aux->address, reg->address);
      strcpy(aux->number, reg->number);
      aux->next = NULL;
      aux->down = findCenterRegister(aux->code);
      if (rtn == NULL){
        rtn = aux;
        flag = true;
      }
    }
    rewind(data_register);
    fclose(data_register);
  }
  else
    printf("La Base de datos de los electores no ha sido creada...\n");
  return rtn;
}

Register *findRegister( char *code ){
  Register *ctr = new Register;
  FILE *data_register = fopen("register.dat", "r");
  if(data_register != NULL){
    while(fread(ctr, sizeof(Register), 1, data_register) != NULL){
      if( strcmp(ctr->code, code) == 0 ){
        rewind(data_register);
        fclose(data_register);
        return ctr;        
      }
    }
    rewind(data_register);
    fclose(data_register);
    return NULL;
  }
  else
    return NULL;
}

bool registerIsPresent( char *code ){
  Register *ctr = new Register;
  FILE *data_register = fopen("register.dat", "r");
  if(data_register != NULL){
    while(fread(ctr, sizeof(Register), 1, data_register) != NULL){
      if( strcmp(ctr->code, code) == 0 ){
        rewind(data_register);
        fclose(data_register);
        return true;        
      }
    }
    rewind(data_register);
    fclose(data_register);
    return false;
  }
  else
    return false;
} 
void createRegisterDB(){
  FILE *fp1 = NULL;
  FILE *fp2 = NULL;
  fp1=fopen("register.dat", "rb");
  fp2=fopen("register.index", "rb");
  if((fp1 == NULL) && (fp1 == NULL)){
    fp1=fopen("register.dat", "wb");
    fp2=fopen("register.index", "wb");
  }
  fclose(fp1);
  fclose(fp2);
}
void SaveRegisterDB( key *data ){
  Register *electoral_registers = KeyToRegister(data);
  if (electoral_registers != NULL)
  {
    createRegisterDB();
    FILE *data_register = fopen("register.dat", "a+b");
    if(data_register != NULL){
      if (!registerIsPresent(electoral_registers->code))
        fwrite(electoral_registers, sizeof(Register), 1, data_register);
      rewind(data_register);
      fclose(data_register);
    }
    index *r_register = IndexRegister(&data, electoral_registers);
    if (r_register != NULL)
    {
      FILE *index_register = fopen("register.index", "a+b");
      if(index_register != NULL){
        while(r_register){
          if (centerIsPresent(r_register->has_one) && (!referencesIsPresent("register.index", r_register->has_one)))
            fwrite(r_register, sizeof(index), 1, index_register);          
          r_register = r_register->next;
        }
        rewind(index_register);
        fclose(index_register);
      }
    }
  }
}

void seed( key **data, char root_file[], void (* function_struct)(key*) ) {
  FILE *fichero;
  char line[500];
  fichero = fopen(root_file, "r");
  while(!feof(fichero)){ 
    fgets(line, 500, fichero);
    key *aux = (*data);
    while(aux){
      if (strcmp(aux->clave,"references") == 0)
      {
        index *keys = references(line);
        aux->ind = keys;
      }
      else
      {
        char *key = ReturnValue(line, aux->clave);
        AddValue(&aux, key);
      }
      aux = aux->next;
    }
    delete(aux);
    (* function_struct)(*data);
  }
  rewind(fichero);
  fclose(fichero);
}
void savePeopleMemoryDB( People *data ){
  //Guarda todos los cambios realizados con people en BD
  while((data) != NULL)
  {
    FILE *data_people = fopen("people.dat", "a+b");
    if((data_people != NULL) && (!peopleIsPresent( (data)->ID ))){
      fwrite(data, sizeof(People), 1, data_people);
    }
    rewind(data_people);
    fclose(data_people);
    data = (data)->next;
  }
}
void saveIndexCenterDB( char code[], People *data ){
  while(data != NULL)
  {
    index *aux = new index;
    strcpy(aux->id, code);
    strcpy(aux->belongs_to, "people");
    strcpy(aux->has_one, data->ID);
    FILE *indexcenters = fopen("center.index", "a+b");
    fwrite(aux, sizeof(index), 1, indexcenters);
    rewind(indexcenters);
    fclose(indexcenters);
    data = data->next;
  }
}
void saveCenterMemoryDB( Center *data ){
  //Guarda todos los cambios realizados con center's en DB
  while((data) != NULL)
  {
    FILE *data_center = fopen("center.dat", "a+b");
    if(data_center != NULL){
      if (!centerIsPresent( (data)->code ))
      {
        fwrite(data, sizeof(Center), 1, data_center);
        savePeopleMemoryDB((data)->left);
        saveIndexCenterDB( (data)->code, (data)->left );
      }
    }
    rewind(data_center);
    fclose(data_center);
    data = (data)->next;
  }
}

void saveIndexRegisterDB( char code[], Center *data ){
  while(data != NULL)
  {
    index *aux = new index;
    strcpy(aux->id, code);
    strcpy(aux->belongs_to, "center");
    strcpy(aux->has_one, data->code);
    FILE *indexregisters = fopen("register.index", "a+b");
    fwrite(aux, sizeof(index), 1, indexregisters);
    rewind(indexregisters);
    fclose(indexregisters);
    data = data->next;
  }
}
void saveRegisterMemoryDB( Register *data ){
  while((data) != NULL)
  {
    FILE *data_register = fopen("register.dat", "a+b");
    if(data_register != NULL){
      if (!registerIsPresent( (data)->code ))
      {
        fwrite(data, sizeof(Register), 1, data_register);
        saveCenterMemoryDB((data)->down);
        saveIndexRegisterDB( (data)->code, (data)->down );
      }
    }
    rewind(data_register);
    fclose(data_register);
    data = (data)->next;
  }
}

void saveChange( Register *data ){
  FILE *datapeople = fopen("people.dat", "wb");
  fclose(datapeople);
  FILE *datacenters = fopen("center.dat", "wb");
  FILE *indexcenters = fopen("center.index", "wb");
  fclose(datacenters);
  fclose(indexcenters);
  FILE *dataregisters = fopen("register.dat", "wb");
  FILE *indexregisters = fopen("register.index", "wb");
  fclose(dataregisters);
  fclose(indexregisters);
  saveRegisterMemoryDB(data);
}