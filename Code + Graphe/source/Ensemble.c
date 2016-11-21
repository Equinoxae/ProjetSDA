#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "Ensemble.h"

/* Noued */

Noeud *NoeudAlloc(){
    Noeud *n = malloc(sizeof(Noeud));

    n->x = -1;
    n->y = -1;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

Noeud *NoeudInit(int x,int y){
    Noeud *n = malloc(sizeof(Noeud));

    n->x = x;
    n->y = y;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

void NoeudSuppr(Noeud *n){
    free(n);
}

/* Ensemble */

// complexité O(1)
Ens * EnsAlloc(){
    Ens *e = malloc(sizeof(Ens));
    //assert(e != NULL);

    e->taille = 0;
    e->premier = NULL;
    e->dernier = NULL;

    return e;
}

// complexité O(n)
void EnsFree(Ens *e){
    Noeud * n = e->premier;
    Noeud * next;
    while (n != NULL) {
        next = n->next;
        NoeudSuppr(n);
        n = next;
    }

}

// complexité o(1)
int EnsEstVide(Ens *e){
    return (e->premier == NULL);
}

// complexté O(1)
void EnsAjoute(Ens *e, int x, int y){

    if(e->dernier == NULL){
        e->premier = NoeudInit(x,y);
        e->dernier = e->premier;
    }
    else{
        Noeud * n = NoeudInit(x,y);
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;
    }
    e->taille++;

}

void EnsAjouteTrie(Ens *e, Noeud *n){
    Noeud * nl = e->premier;

    while (nl->next != NULL) {
        if (n->x <= nl->x && n->y <= nl->y) {
            if(nl->next == NULL && nl->previous == NULL){
                e->premier = n;
                e->dernier = n;
            }
            else if(nl->next == NULL){
                nl->next = n;
                n->previous = nl;
                e->dernier = n;
            }
            else if(nl->previous == NULL){
                n->next = nl;
                nl->previous = n;
                e->premier = n;
            }
            else{
                n->previous = nl->previous;
                nl->previous->next = n;
                n->next = nl;
                nl->previous = n;
            }
            break;
        }
        n = n->next;
    }

    e->taille++;
}

// complexité O(n)
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

// complexité O(n)
Noeud * EnsFindHeuristique(Ens *e,int x,int y){

    Noeud * n = e->premier;
    while (n->next != NULL) {
        if (n->x == x && n->y == y) {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

// complexité O(n/2)
Noeud *EnsFindIndex(Ens *e, int index){

    if(index <= EnsTaille(e)/2) {
        Noeud *n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++){
            n=n->next;
        }

        return n;
    }
    else{
        Noeud *n = e->dernier;
        int i;
        for(i = EnsTaille(e); i>index && n->previous != NULL;i--){
            n=n->previous;
        }

        return n;
    }
}

Noeud *EnsFindSupprIndex(Ens *e, int index){
    Noeud *n;

    if(index <= EnsTaille(e)/2) {
        n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++)
            n=n->next;

    }
    else{
        n = e->dernier;
        int i;
        for(i = EnsTaille(e); i>index && n->previous != NULL;i--)
            n=n->previous;

    }

    if(n->next == NULL && n->previous == NULL){
        e->premier = NULL;
        e->dernier = NULL;
        e->taille = 0;
    }
    else if(n->next == NULL){
        n->previous->next = NULL;
        e->dernier = n->previous;
        e->taille--;
    }
    else if(n->previous == NULL){
        n->next->previous = NULL;
        e->premier = n->next;
        e->taille--;
    }
    else{
        n->previous->next = n->next;
        n->next->previous = n->previous;
        e->taille--;
    }

    return n;

}

// complexité O(n)
void EnsSuppr(Ens *e, int x, int y){

    Noeud *n = e->premier;
    while (n != NULL) {
        if (n->x == x && n->y == y) {

            if(n->next == NULL && n->previous == NULL){
                e->premier = NULL;
                e->dernier = NULL;
                e->taille = 0;
            }
            else if(n->next == NULL){
                n->previous->next = NULL;
                e->dernier = n->previous;
            }
            else if(n->previous == NULL){
                n->next->previous = NULL;
                e->premier = n->next;
            }
            else{
                n->previous->next = n->next;
                n->next->previous = n->previous;
            }

            //printf("Ensemble supprime => %i %i\n",n->x,n->y);
            //scanf(" ");
            NoeudSuppr(n);
            e->taille--;
            break;
        }
        else
            n = n->next;
    }

}

void EnsSupprPremier(Ens *e){
    Noeud *n = e->premier;

	if(n->next!=NULL)
    	n->next->previous = NULL;

	e->premier = n->next;
    NoeudSuppr(n);
    e->taille--;
}

void EnsSupprDernier(Ens *e){
    Noeud *n = e->dernier;

	if(n->previous!=NULL)
    	n->previous->next = NULL;

	e->dernier = n->previous;
    NoeudSuppr(n);
    e->taille--;
}

// complexité O(n)
int EnsEstDans(Ens *e, int x,int y){
    return (EnsFind(e,x,y) != -1);
}

// complextité O(1)
int EnsTaille(Ens *e){
    return e->taille;
}

// complexité O(n)
void EnsPrint(Ens *e){

    Noeud * n = e->premier;
    printf("{\n");
    while (n != NULL) {
        printf("(%i,%i)",n->x,n->y);
        n = n->next;
    }
    printf("}\n");
}

// complexité O(n/2)
Noeud * EnsTirage(Ens *e){
    int index;

    /* tirage */
    index = rand() % EnsTaille(e);
    //printf("index : %i\n",index );
    return EnsFindSupprIndex(e,index);
}
