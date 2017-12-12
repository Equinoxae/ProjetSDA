#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "EnsembleHexa.h"

/* Noeud Hexa */

NoeudHexa *NoeudHexaAlloc(){
    NoeudHexa *n = malloc(sizeof(NoeudHexa));

    n->x = -1;
    n->y = -1;
    n->cote = 0;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

NoeudHexa *NoeudHexaInit(int x,int y, int c){
    NoeudHexa *n = malloc(sizeof(NoeudHexa));

    n->x = x;
    n->y = y;
    n->cote = c;
    n->next = NULL;
    n->previous = NULL;

    return n;
}

void NoeudHexaSuppr(NoeudHexa *n){
    free(n);
}

/* Ensemble Hexa */

// complexité O(1)
EnsHexa * EnsHexaAlloc(){
    EnsHexa *e = malloc(sizeof(EnsHexa));
    //assert(e != NULL);

    e->taille = 0;
    e->premier = NULL;
    e->dernier = NULL;

    return e;
}

// complexité O(n)
void EnsHexaFree(EnsHexa *e){
    NoeudHexa * n = e->premier;
    while (n != NULL) {
        NoeudHexa * tmp = n;
		n=n->next;
        NoeudHexaSuppr(tmp);
	//e->taille--;
    }
    free(e);
}

// complexité o(1)
int EnsHexaEstVide(EnsHexa *e){
    return (e->premier == NULL);
}

// complexté O(1)
void EnsHexaAjoute(EnsHexa *e, int x, int y, int c){

    if(e->dernier == NULL){
        e->premier = NoeudHexaInit(x,y,c);
        e->dernier = e->premier;
    }
    else{
        NoeudHexa * n = NoeudHexaInit(x,y,c);
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;

   }
    e->taille++;

}

void EnsHexaAjouteNoeudHexa(EnsHexa *e,NoeudHexa * n){

    if(e->dernier == NULL){
        e->premier = n;
        e->dernier = e->premier;
    }
    else{
        NoeudHexa * n = n;
        n->previous = e->dernier;
        e->dernier->next = n;
        e->dernier = n;
    }
    e->taille++;

}


void EnsHexaAjouteTrie(EnsHexa *e, NoeudHexa *n,MatriceHexa *heuristique){

	if( e->premier == NULL && e->dernier == NULL){
		e->premier = n;
		e->dernier = n;
		e->taille++;
	}
	else{
		if(MatHexaVal2(heuristique,e->premier->x,e->premier->y) >= MatHexaVal2(heuristique,n->x,n->y)){
			e->premier->previous = n;
			n->next = e->premier;
			e->premier = n;
			e->taille++;
		}
		else if(MatHexaVal2(heuristique,e->dernier->x,e->dernier->y) <= MatHexaVal2(heuristique,n->x,n->y)){
			e->dernier->next = n;
			n->previous = e->dernier;
			e->dernier = n;
			e->taille++;
		}
		else{
			NoeudHexa * np = e->premier->next;

			while(np != e->dernier){
				if(MatHexaVal2(heuristique,n->x,n->y) <= MatHexaVal2(heuristique,np->x,np->y)){
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
int EnsHexaFind(EnsHexa *e, int x, int y){

    int index = 0;

    NoeudHexa * n = e->premier;
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
NoeudHexa *EnsHexaFindIndex(EnsHexa *e, int index){

    if(index <= EnsHexaTaille(e)/2) {
        NoeudHexa *n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++){
            n=n->next;
        }

        return n;
    }
    else{
        NoeudHexa *n = e->dernier;
        int i;
        for(i = EnsHexaTaille(e); i>index && n->previous != NULL;i--){
            n=n->previous;
        }

        return n;
    }
}

NoeudHexa *EnsHexaFindSupprIndex(EnsHexa *e, int index){
    NoeudHexa *n;

    if(index <= EnsHexaTaille(e)/2) {
        n = e->premier;
        int i;
        for( i = 0; i<index && n->next != NULL  ;i++)
            n=n->next;

    }
    else{
        n = e->dernier;
        int i;
        for(i = EnsHexaTaille(e); i>index && n->previous != NULL;i--)
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
void EnsHexaSuppr(EnsHexa *e, int x, int y){

    NoeudHexa *n = e->premier;
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

            NoeudHexaSuppr(n);
            e->taille--;
            n = NULL;
        }
        else
            n = n->next;
    }

}

NoeudHexa * EnsHexaDepilePremier(EnsHexa *e){
	NoeudHexa *n = e->premier;

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

void EnsHexaSupprPremier(EnsHexa *e){
    NoeudHexa *n = e->premier;

	if(n->next!=NULL)
    	n->next->previous = NULL;
	else
		e->dernier = NULL;

	e->premier = n->next;
    NoeudHexaSuppr(n);
    e->taille--;
}

void EnsHexaSupprDernier(EnsHexa *e){
    NoeudHexa *n = e->dernier;

	if(n->previous!=NULL)
    	n->previous->next = NULL;

	e->dernier = n->previous;
    NoeudHexaSuppr(n);
    e->taille--;
}

// complexité O(n)
int EnsHexaEstDans(EnsHexa *e, int x,int y){
    return (EnsHexaFind(e,x,y) != -1);
}

// complextité O(1)
int EnsHexaTaille(EnsHexa *e){
    return e->taille;
}

// complexité O(n)
void EnsHexaPrint(EnsHexa *e){

    NoeudHexa * n = e->premier;
    printf("{\n");
    while (n != NULL) {
        printf("(%i,%i)",n->x,n->y);
        n = n->next;
    }
    printf("}\n");
}

// complexité O(n/2)
NoeudHexa * EnsHexaTirage(EnsHexa *e,int l){
    /* tirage */
    int index;    

    if(l)
	index = 0;
    else
    	index = rand() % EnsHexaTaille(e);
    return EnsHexaFindSupprIndex(e,index);
}
