#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "Ensemble.h"

/* Noued */

Noeud *NoeudAlloc(){
    Noeud *n = malloc(sizeof(Noeud));

    n->x = -1;
    n->y = -1;
    n->next = NULL;

    return n;
}

Noeud *NoeudInit(int x,int y){
    Noeud *n = malloc(sizeof(Noeud));

    n->x = x;
    n->y = y;
    n->next = NULL;

    return n;
}


void NoeudSuppr(Noeud *n){
    free(n);
}

/* Ensemble */

Ens * EnsAlloc(){
    Ens *e = malloc(sizeof(Ens));
    //assert(e != NULL);

    Noeud * n = NoeudAlloc();
    e->premier = n;

    return e;
}

void EnsFree(Ens *e){
    //assert(e != NULL);

    Noeud * n = e->premier;
    Noeud * next;
    while (n != NULL) {
        next = n->next;
        free(n);
        n = next;
    }

}

int EnsEstVide(Ens *e){
    return (EnsTaille(e) == 0);
}

void EnsAjoute(Ens *e, int x, int y){

    Noeud * n = e->premier;
    while (n->next != NULL) {
        n = n->next;
    }

    n->x = x;
    n->y = y;
    n->next = NoeudAlloc();
}

int EnsFind(Ens *e, int x, int y){

    int index = 0;

    Noeud * n = e->premier;
    while (n->next != NULL) {
        if (n->x == x && n->y == y) {
            return index;
        }
        n = n->next;
        index++;
    }
    return -1;
}

void EnsSuppr(Ens *e, int x, int y){
    int founded = 0;

    Noeud * n = e->premier;

    if(n == NULL)
        exit(2);

    if(n->x == x && n->y == y){
        e->premier = e->premier->next;
        NoeudSuppr(n);
        founded = 1;
    }
    else{
        Noeud *before = e->premier;
        while (before->next != NULL && !founded) {
            if (before->next->x == x && before->next->y == y) {
                n = before->next;
                before->next = before->next->next;
                NoeudSuppr(n);
                founded = 1;
            }
            before = before->next;
        }
    }
}

int EnsEstDans(Ens *e, int x,int y){
    return (EnsFind(e,x,y) != -1)? 1 : 0;
}

int EnsTaille(Ens *e){

    Noeud * n = e->premier;
    int length = 0;
    while (n->next != NULL) {
        length++;
        n = n->next;
    }

    return length;
}

void EnsPrint(Ens *e){

    Noeud * n = e->premier;
    while (n->next != NULL) {
        printf("x : %i , y : %i\n",n->x,n->y);
        n = n->next;
    }
}

Noeud * EnsTirage(Ens *e,int taille){
    int index;

    /* tirage */
    index = rand() % taille;//EnsTaille(e);

    /* recherche */

    Noeud * n = e->premier;
    while (index > 0) {
        n = n->next;
        index--;
    }
    return n;
}
