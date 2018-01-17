#include <stdlib.h>
#include <stdio.h>
#include "Matrice.h"

Matrice * MatAlloc(int l1,int h1){

  Matrice * m = malloc(sizeof(Matrice));

  m->l = l1;
  m->h = h1;
  m->points = calloc(l1*h1,sizeof(int));
  return m;

}

void MatFree(Matrice * m){
  free(m->points);
  free(m);
}

int MatVal(Matrice * m, int p){
  return m->points[p];
}

int MatVal2(Matrice * m, int x, int y){
  return m->points[y*m->l + x];
}

void MatSet(Matrice * m, int p, int v){
  m->points[p] = v;
}

void MatSet2(Matrice * m, int x,int y, int v){
  m->points[y*m->l+x] = v;
}

void MatSauve(Matrice * m,char* file){
    FILE * f ;

    f = fopen(file,"w");
    fprintf(f, "P5\n");
    fprintf(f, "%i %i \n1\n",m->l,m->h);

    int i;
    for(i = 0 ; i < m->l * m->h ; i++ ){
        fprintf(f, "%c",!m->points[i]);
    }

    fclose(f);
}

Matrice * MatLit(char* file){
  FILE * f ;

  f = fopen(file,"r");

  int h;
  int l;
  int res;


  res = fscanf(f,"P5\n%i %i\n1\n",&h,&l);

  Matrice * m ;
  m = MatAlloc(h,l);

  int i;

  char in;
  for(i = 0; i < h*l;i++){
	res = fscanf(f,"%c",&in);
    	MatSet(m,i,in);
    }

    fclose(f);
  if(res == 0)
	exit(res);

    return m;

}

int MatGetL(Matrice * m){
    return m->l;
}

int MatGetH(Matrice * m){
    return m->h;
}
