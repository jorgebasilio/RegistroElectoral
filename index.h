struct index{
  char id[10];
  char belongs_to[20];
  char has_one[15];
  index *next;
};

void AddIndex( index **data, char has_one[] ){
  index *aux = new index;
  strcpy(aux->has_one, has_one);
  aux->next = (*data);
  *data = aux;
}

