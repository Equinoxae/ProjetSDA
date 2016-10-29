#include <stdlib.h>
#include <stdio.h>
#include "Matrice.h"

Matrice * MatAlloc(int l1,int h1){

  Matrice * m = malloc(sizeof(Matrice));

  m->h = h1;
  m->l = l1;
  m->points = calloc(l1*h1,sizeof(int));
  return m;

}

void MatFree(Matrice * m){
  free(m->points);
}

int MatVal(Matrice * m, int p){
  return m->points[p];
}

int MatVal2(Matrice * m, int x, int y){
  return m->points[x*m->l + y];
}

void MatSet(Matrice * m, int p, int v){
  m->points[p] = v;
}

void MatSet2(Matrice * m, int x,int y, int v){
  m->points[x*m->l+y] = v;
}

void MatSauve(Matrice * m,char* file){
    FILE * f ;

    f = fopen(file,"w");
    fprintf(f, "%i %i \n",m->h,m->l);

    int i;
    for(i = 0 ; i < m->h * m->l ; i++ ){
        putc(m->points[i],f);
        putc(' ',f);
    }

    fclose(f);
}

Matrice * MatLit(char* file){
  FILE * f ;

  f = fopen(file,"r");

  int h;
  int l;

  fscanf(f,"%i %i\n",&h,&l);

  Matrice * m ;
  m = MatAlloc(h,l);

  int i;

  char in;
  for(i = 0; i < h*l;i++){
    in = (char)fgetc(f);
    fgetc(f);
    MatSet(m,i,in);
    }

    close(f);

    return m;

}

int MatGetL(Matrice * m){
    return m->l;
}

int MatGetH(Matrice * m){
    return m->h;
}
