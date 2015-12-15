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
