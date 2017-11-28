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
    while (n != NULL) {
        Noeud * tmp = n;
		n=n->next;
        NoeudSuppr(tmp);
	//e->taille--;
    }
    free(e);
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

void EnsAjouteNoeud(Ens *e,Noeud * n){

    if(e->dernier == NULL){
        e->premier = n;
        e->dernier = e->premier;
    }
    else{
        Noeud * n = n;
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;
    }
    e->taille++;

}


void EnsAjouteTrie(Ens *e, Noeud *n,Matrice *heuristique){

	if( e->premier == NULL && e->dernier == NULL){
		e->premier = n;
		e->dernier = n;
		e->taille++;
	}
	else{
		if(MatVal2(heuristique,e->premier->x,e->premier->y) >= MatVal2(heuristique,n->x,n->y)){
			e->premier->previous = n;
			n->next = e->premier;
			e->premier = n;
			e->taille++;
		}
		else if(MatVal2(heuristique,e->dernier->x,e->dernier->y) <= MatVal2(heuristique,n->x,n->y)){
			e->dernier->next = n;
			n->previous = e->dernier;
			e->dernier = n;
			e->taille++;
		}
		else{
			Noeud * np = e->premier->next;

			while(np != e->dernier){
				if(MatVal2(heuristique,n->x,n->y) <= MatVal2(heuristique,np->x,np->y)){
					n->next = np;
					n->previous = np->previous;
					np->previous->next = n;
					np->previous = n;
					e->taille++;
					return;
				}

				np = np->next;

			}

		}

	}

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

            NoeudSuppr(n);
            e->taille--;
            n = NULL;
        }
        else
            n = n->next;
    }

}

Noeud * EnsDepilePremier(Ens *e){
	Noeud *n = e->premier;

	if(n->next!=NULL){
	n->next->previous = NULL;
		e->premier = n->next;
	}
	else{
		e->premier = NULL;
		e->dernier = NULL;
	}

	e->taille--;
	return n;
}

void EnsSupprPremier(Ens *e){
    Noeud *n = e->premier;

	if(n->next!=NULL)
    	n->next->previous = NULL;
	else
		e->dernier = NULL;

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
Noeud * EnsTirage(Ens *e,int l){
    /* tirage */
    int index;    

    if(l)
	index = 0;
    else
    	index = rand() % EnsTaille(e);
    return EnsFindSupprIndex(e,index);
}
