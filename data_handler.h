
// 1-  recorrer el archivo linea a linea
// 2-  obtener la linea en una variable y obtener los datos que pide el key
// 3-  luego de tener todos los datos cargarlos en otro archivo para salvarlos
// 4-  estructura del archivo debe ser como ya se planteo
//***********************************//
//* Falta hacer refactor del codigo *//
//***********************************//

int seed( char arch[]) {
  key *caja = NULL; 
  AddKey(&caja, "direccion");
  AddKey(&caja, "cedula");
  AddKey(&caja, "nombre");
  ViewKey(caja);
  FILE *fichero;
  char line[150];
  fichero = fopen(arch, "r");
  while(!feof(fichero)){ 
	   fgets(line, 150, fichero);
	   key *aux = caja;
	   while(aux){
      char *clave = ReturnValue(line, aux->clave);
		 AddValue(&aux, clave);
		 aux = aux->next;
	   }
	   ViewValue(caja);
   }
   rewind(fichero);
   fclose(fichero);
   return 0;
}

void WriteDB(){
    FILE *fp = NULL;
	key *nuevo = NULL;
	
	key *aux = new key;
	AddKey(&nuevo, "direccion");
	AddValue(&nuevo, "UCAB");
	
    char result[50];
    int i;

    fp=fopen("temp.bin", "wb+");

    if(fp != NULL)
    {
		fwrite(nuevo, sizeof(key), 1, fp);
		AddKey(&nuevo, "nombre");
		AddValue(&nuevo, "Jorge");
		fwrite(nuevo, sizeof(key), 1, fp);
        rewind(fp);
        fread(aux, sizeof(key), 2, fp);
    }

    printf("Result\n");
       printf("=> %s\n", aux->valor);
	   aux = aux->next;
	    printf("=> %s\n", aux->valor);

    fclose(fp);
}

