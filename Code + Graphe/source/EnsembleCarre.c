#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "EnsembleCarre.h"

/* Noeud Hexa */

NoeudCarre *NoeudCarreAlloc(){
    NoeudCarre *n = malloc(sizeof(NoeudCarre));

    n->x = -1;
    n->y = -1;
    n->cote = 0;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

NoeudCarre *NoeudCarreInit(int x,int y, int c){
    NoeudCarre *n = malloc(sizeof(NoeudCarre));

    n->x = x;
    n->y = y;
    n->cote = c;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

void NoeudCarreSuppr(NoeudCarre *n){
    free(n);
}

/* Ensemble Hexa */

// complexité O(1)
EnsCarre * EnsCarreAlloc(){
    EnsCarre *e = malloc(sizeof(EnsCarre));
    //assert(e != NULL);

    e->taille = 0;
    e->premier = NULL;
    e->dernier = NULL;

    return e;
}

// complexité O(n)
void EnsCarreFree(EnsCarre *e){
    NoeudCarre * n = e->premier;
    while (n != NULL) {
        NoeudCarre * tmp = n;
		n=n->next;
        NoeudCarreSuppr(tmp);
	//e->taille--;
    }
    free(e);
}

// complexité o(1)
int EnsCarreEstVide(EnsCarre *e){
    return (e->premier == NULL);
}

// complexté O(1)
void EnsCarreAjoute(EnsCarre *e, int x, int y, int c){

    if(e->dernier == NULL){
        e->premier = NoeudCarreInit(x,y,c);
        e->dernier = e->premier;
    }
    else{
        NoeudCarre * n = NoeudCarreInit(x,y,c);
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;

   }
    e->taille++;

}

void EnsCarreAjouteNoeudCarre(EnsCarre *e,NoeudCarre * n){

    if(e->dernier == NULL){
        e->premier = n;
        e->dernier = e->premier;
    }
    else{
        NoeudCarre * n = n;
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;
    }
    e->taille++;

}


void EnsCarreAjouteTrie(EnsCarre *e, NoeudCarre *n,MatriceCarre *heuristique){

	if( e->premier == NULL && e->dernier == NULL){
		e->premier = n;
		e->dernier = n;
		e->taille++;
	}
	else{
		if(MatCarreVal2(heuristique,e->premier->x,e->premier->y) >= MatCarreVal2(heuristique,n->x,n->y)){
			e->premier->previous = n;
			n->next = e->premier;
			e->premier = n;
			e->taille++;
		}
		else if(MatCarreVal2(heuristique,e->dernier->x,e->dernier->y) <= MatCarreVal2(heuristique,n->x,n->y)){
			e->dernier->next = n;
			n->previous = e->dernier;
			e->dernier = n;
			e->taille++;
		}
		else{
			NoeudCarre * np = e->premier->next;

			while(np != e->dernier){
				if(MatCarreVal2(heuristique,n->x,n->y) <= MatCarreVal2(heuristique,np->x,np->y)){
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
int EnsCarreFind(EnsCarre *e, int x, int y){

    int index = 0;

    NoeudCarre * n = e->premier;
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
NoeudCarre *EnsCarreFindIndex(EnsCarre *e, int index){

    if(index <= EnsCarreTaille(e)/2) {
        NoeudCarre *n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++){
            n=n->next;
        }

        return n;
    }
    else{
        NoeudCarre *n = e->dernier;
        int i;
        for(i = EnsCarreTaille(e); i>index && n->previous != NULL;i--){
            n=n->previous;
        }

        return n;
    }
}

NoeudCarre*EnsCarreFindSupprIndex(EnsCarre *e, int index){
    NoeudCarre *n;

    if(index <= EnsCarreTaille(e)/2) {
        n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++)
            n=n->next;

    }
    else{
        n = e->dernier;
        int i;
        for(i = EnsCarreTaille(e); i>index && n->previous != NULL;i--)
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
void EnsCarreSuppr(EnsCarre *e, int x, int y){

    NoeudCarre *n = e->premier;
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

            NoeudCarreSuppr(n);
            e->taille--;
            n = NULL;
        }
        else
            n = n->next;
    }

}

NoeudCarre * EnsCarreDepilePremier(EnsCarre *e){
	NoeudCarre *n = e->premier;

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

void EnsCarreSupprPremier(EnsCarre *e){
    NoeudCarre *n = e->premier;

	if(n->next!=NULL)
    	n->next->previous = NULL;
	else
		e->dernier = NULL;

	e->premier = n->next;
    NoeudCarreSuppr(n);
    e->taille--;
}

void EnsCarreSupprDernier(EnsCarre *e){
    NoeudCarre *n = e->dernier;

	if(n->previous!=NULL)
    	n->previous->next = NULL;

	e->dernier = n->previous;
    NoeudCarreSuppr(n);
    e->taille--;
}

// complexité O(n)
int EnsCarreEstDans(EnsCarre*e, int x,int y){
    return (EnsCarreFind(e,x,y) != -1);
}

// complextité O(1)
int EnsCarreTaille(EnsCarre *e){
    return e->taille;
}

// complexité O(n)
void EnsCarrePrint(EnsCarre *e){

    NoeudCarre * n = e->premier;
    printf("{\n");
    while (n != NULL) {
        printf("(%i,%i)",n->x,n->y);
        n = n->next;
    }
    printf("}\n");
}

// complexité O(n/2)
NoeudCarre * EnsCarreTirage(EnsCarre *e,int l){
    /* tirage */
    int index;    

    if(l)
	index = 0;
    else
    	index = rand() % EnsCarreTaille(e);
    return EnsCarreFindSupprIndex(e,index);
}
