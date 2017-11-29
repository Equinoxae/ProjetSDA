#include <stdlib.h>
#include <stdio.h>
#include "MatriceHexa.h"

MurHexa * MurHexaAlloc(){
	
	MurHexa * m = malloc(sizeof(MurHexa));

	m->c1 = 1;
	m->c2 = 1;
	m->c3 = 1;

	return m;

}

MurHexa * MurHexaAlloc2(int c1, int c2, int c3){

	MurHexa * m = malloc(sizeof(MurHexa));

	m->c1 = c1;
	m->c2 = c2;
	m->c3 = c3;

	return m;

}

MatriceHexa * MatHexaAlloc(int l1,int h1){

  MatriceHexa * m = malloc(sizeof(MatriceHexa));

  m->l = l1;
  m->h = h1;
  m->points = calloc(l1*h1,sizeof(MurHexa));

  return m;

}

void MatHexaFree(MatriceHexa * m){
  free(m->points);
  free(m);
}

MurHexa * MatHexaVal(MatriceHexa * m, int p){
  return m->points[p];
}

MurHexa * MatHexaVal2(MatriceHexa * m, int x, int y){
  return m->points[x*m->l + y];
}

void MatHexaSet(MatriceHexa * m, int p, MurHexa * v){
  m->points[p] = v;
}

void MatHexaSet2(MatriceHexa * m, int x,int y, MurHexa * v){
  m->points[x*m->l+y] = v;
}

int MatHexaGetL(MatriceHexa * m){
    return m->l;
}

int MatHexaGetH(MatriceHexa * m){
    return m->h;
}
