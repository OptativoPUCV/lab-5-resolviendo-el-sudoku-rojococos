#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}



/*Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}*/



Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    for(size_t l = 0; l < 9; l++)
        for(size_t k = 0; k < 9; k++)
            new->sudo[l][k] = n->sudo[l][k];
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int i,j;
   //i sera fila y j sera columna
   
   
   int pos;
   //verificar columnas
   for(j=0;j<9;j++){
      int *arr = (int*) calloc(9, sizeof(int));
      for(i=0;i<9;i++){
         if(n->sudo[i][j] != 0){
            pos = n->sudo[i][j] - 1; //pos -1 porque las pos del array van del 0 al 8
            arr[pos]++;
            if(arr[pos] > 1)
               return 0;
         }
      }  
      free(arr);
      
   }
   //verificar filas
   for(i=0;i<9;i++){
      int *arr = (int*) calloc(9, sizeof(int));
      for(j=0;j<9;j++){
         if(n->sudo[i][j] != 0){
            pos = n->sudo[i][j] - 1;
            arr[pos]++;
            if(arr[pos] > 1) return 0;
         }
      }
      free(arr);
   }

   //verificar subcuadrados
   for(i=0;i<9;i+=3){
      for(j=0;j<9;j+=3){

         //verificar cada subcuadrado
         int *arr = (int*) calloc(9, sizeof(int));
         for(int k=i;k<i+3;k++)
            for(int l=j;l<j+3;l++){
               if(n->sudo[k][l] != 0){
                  pos = n->sudo[k][l] - 1;
                  arr[pos]++;
                  if(arr[pos] > 1)
                     return 0;
               }
            }
         free(arr);               
      }
   }

   
   
   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   int aux = 1;
   int fila = 0;
   int columna = 0;
   int seguro = 2;
   
   //buscar la pos vacia o 0
   for (int r = 0; r < 9 && seguro != 1; r++) {
       for (int t = 0; t < 9 && seguro != 1; t++) {
           if (n->sudo[r][t] == 0) {
               fila = r;
               columna = t;
               seguro = 1;
            }
       }
   }


   //rellenar la pos vacia con todo numero del 1 al 9   
   while(aux < 10){
      Node *nuevo = copy(n);
      nuevo->sudo[fila][columna] = aux;

      
      if(is_valid(nuevo)){
         
         pushFront(list,nuevo);
      }
      aux++;
   }
   return list;
}


int is_final(Node* n){
   for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
         if(n->sudo[i][j] == 0)
            return 0;
   
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack *s = createStack();
   push(s,initial);

   while(1){
      Node *n = top(s);
      if(n == NULL)return NULL;
      
      (* cont)++;
      pop(s);
      if(is_final(n)) return n;
      List *adj = get_adj_nodes(n);
      free(n);
      Node * aux = first(adj);
      
      while(aux != NULL){
         push(s,aux);
         aux = next(adj);
      }      
   }
      
   
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/