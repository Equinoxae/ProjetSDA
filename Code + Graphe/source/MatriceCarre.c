#include <stdlib.h>
#include <stdio.h>
#include "MatriceCarre.h"

MurCarre * MurCarreAlloc(){
	
	MurCarre * m = malloc(sizeof(MurCarre));

	m->c1 = 1;
	m->c2 = 1;
	m->v = 0;

	return m;

}

MurCarre * MurCarreAlloc2(int c1, int c2,int v){

	MurCarre * m = malloc(sizeof(MurCarre));

	m->c1 = c1;
	m->c2 = c2;
	m->v = v;

	return m;

}

MatriceCarre * MatCarreAlloc(int l1,int h1){

  MatriceCarre * m = malloc(sizeof(MatriceCarre));

  m->l = l1;
  m->h = h1;
  m->points = calloc(l1*h1,sizeof(MurCarre));

  return m;

}

void MatCarreFree(MatriceCarre * m){
  free(m->points);
  free(m);
}

MurCarre * MatCarreVal(MatriceCarre * m, int p){
  return m->points[p];
}

MurCarre * MatCarreVal2(MatriceCarre * m, int x, int y){
  return m->points[y*m->l + x];
}

void MatCarreSet(MatriceCarre * m, int p, MurCarre * v){
  m->points[p] = v;
}

void MatCarreSet2(MatriceCarre * m, int x,int y, MurCarre * v){
  m->points[y*m->l+x] = v;
}

void MatCarreSetValue(MatriceCarre * m, int p, int v){
	m->points[p]->v = v; //->v : accéder à la valeur de la variable
};

void MatCarreSetValue2(MatriceCarre * m, int x,int y, int v){
	m->points[y*m->l+x]->v = v;	
};


int MatCarreGetL(MatriceCarre * m){
    return m->l;
}

int MatCarreGetH(MatriceCarre * m){
    return m->h;
}
