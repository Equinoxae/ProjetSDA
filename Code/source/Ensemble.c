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
    return (EnsTaille(e) == 0)? 1 : 0;
}

void EnsAjoute(Ens *e, int x, int y){

    printf("%i,%i\n", x,y);

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
        printf("%i\n",index );
        if (n->x == x && n->y == y) {
            return index;
        }
        n = n->next;
        index++;
    }
    return -1;
}

void EnsSuppr(Ens *e, int x, int y){

    int index = EnsFind(e, x, y);

    printf("%i\n",index);
    if(index == -1){
        return;
    }
    else if (index == 0) {
        Noeud * n = e->premier;
        e->premier = e->premier->next;
        NoeudSuppr(n);
    }
    else {
        Noeud *before = e->premier;
        while (index > 1) {
            before = before->next;
            index--;
        }
        Noeud * n = before->next;
        before->next = before->next->next;
        NoeudSuppr(n);
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

Noeud * EnsTirage(Ens *e){
    int * res = malloc(sizeof(int)*2);
    int index;

    /* tirage */

    srand(time(NULL));
    index = rand() % EnsTaille(e);

    /* recherche */

    Noeud * n = e->premier;
    while (index > 0) {
        n = n->next;
        index--;
    }

    return n;
}
