
#include <stdlib.h>
#include <stdio.h>

matrice MatAlloc(int h1,int l1){

  matrice m;

  m->h = h1;
  m->l = l1;
  m->points = malloc(h * l * sizeof(int));

  int i;
  int j;

  for(i = 0; i < l; i++ ){
    for(j = 0; j < h; j++){

      m->points[i * l + j] =  ;

    }// end j
  } // end i

  return m;

}

void MatFree(matrice m){
  free(m);
}

int MatVal(matrice m, int p){
  return m.points[p];
}

int MatVal2(matrice m, int x, int y){
  return m.points[x*m.l + y];
}

void MatSet(matrice m, int p, int v){
  m[p]->v;
}

void MatSet2(matrice m, int x,int y, int v){
  m[x*m.l+y]->v;
}

void MatSauve(matrice m,char* file){
  File* f = NULL;

  f = fopen("./"+file,"w");
  fprintf(f, "%i %i \n",m.h,m.l);
  int i;
  for(i = 0 ; i < m.h * m.l ; i++ ){
    putc(m.points[i]);
    putc(' ');
  }
  fclose(f);
}

matrice MatLit(char* file){
  File* f = NULL;

  f = fopen(file,"r");

  int h;
  int l;

  fscanf(f,"%i %i\n",h,l)

  matrice m = NULL;
  m = MatAlloc(h,l);

  int i;

  char in[2];
  for(i = 0; i < h*l;i++){
    fgetc(in,2,f);
    MatSet(m,i,in[0]);
    }

    close(f);

    return m;

}
