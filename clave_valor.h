struct key{
	char clave[50];
	char valor[100];
  index *ind;
	key *next;
};
void AddKey(key **data, char *value){
	key *key_new = new key;
	memcpy( key_new->clave, value, strlen(value)+1 );
	key_new->next = (*data);
	*data = key_new;
}
void AddValue(key **data, char *value){
	memcpy( (*data)->valor, value, strlen(value)+1 );
}
void ViewKey(key *data){
	if(!data) printf("The key is empty");
	while(data){
		printf("\n\"%s\": ", data->clave);
		data = data->next;
	};
}
void ViewValue(key *data){
	if(!data) printf("The key is empty");
	while(data){
		printf("\"%s\"\n", data->valor);
		data = data->next;
	};
}
char *ReturnValue( char *data, char *clave ){
	int data_long = strlen(data);
	int clave_long = strlen(clave);
	int i = 0;
	int e;
	bool flag = false;
	char *valor = new char;
	while( i < data_long && (!flag) )
	{
		e = 0;
		while(data[i] == clave[e]){
			i++;
			e++;
			if((data[i] == '\"') && (data[(i+1)] == '\:') && (e == (clave_long))){
				flag = true;
				e = 0;
				i = i + 4;
			}
			while((data[i] != '\"') && (data[(i+1)] != '\,') && flag){
			  valor[e] = data[i];
				e++;
				i++;
			}
		}
		i++;
	}
	valor[e] = '\0';
	return valor;
}


/*
bool references_present( char *data ){
  if(strstr(data, "\"references\"") != NULL)
    return true;
  return false;
}
char *references_type( char *data ){
  return ReturnValue( data, "references" );
}*/
index *references( char *data ){
  index *aux = NULL;
  int data_long = strlen(data);
  char *value = new char;
  bool flag = false;
  int e= 0, a = 0;
  for (int i = 0; i < data_long; i++)
  {
    if((data[i] == '\"') && (data[(i+1)] == '\[')){
      flag = true;
      e = i+2;
    }
    while((data[e+1] != '\"') && (data[e] != ']') && (flag) && (e < data_long))
    {
      if((data[e] != ',') && (data[e] != ']'))
      {
        value[a] = data[e];
        a++;
      }
      else
      {
        value[a] = '\0';
        a = 0;
        AddIndex( &aux, value );
      }
      e++;
    }
  }
  return aux;
}