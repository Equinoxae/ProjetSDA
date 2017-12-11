#include "MatriceHexa.h"

/* Noeud de l'ensemble */
typedef struct NoeudHexa{
    /* data*/
    int x; // [x,y]
    int y;
	int cote;//

    /* list suite */
    struct NoeudHexa * next ;
    struct NoeudHexa * previous;
}NoeudHexa;


/* Ensemble */

typedef struct EnsHexa{
    int taille;
    struct NoeudHexa * premier;
    struct NoeudHexa * dernier;
}EnsHexa;

// Noeud fonction //

NoeudHexa *NoeudHexaAlloc();
NoeudHexa *NoeudHexaInit(int x,int y,int c);
void NoeudHexaSuppr(NoeudHexa *n);

// Ensemble fonction //

EnsHexa * EnsHexaAlloc(); // création d’un nouvel ensemble

void EnsHexaFree(EnsHexa *e); // libération éventuelle de la mémoire utilisée

int EnsHexaEstVide(EnsHexa *e); // teste si un ensemble est vide

void EnsHexaAjoute(EnsHexa *e, int x, int y, int c); // ajoute un couple à un ensemble

void EnsHexaAjouteNoeudHexa(EnsHexa *e,NoeudHexa * n); // ajoute un noeud

void EnsHexaAjouteTrie(EnsHexa *e, NoeudHexa *n,MatriceHexa *heuristique); // ajoute un noeud ordonnée (n < n+1)

int EnsHexaFind(EnsHexa *e, int x, int y); // trouve si un couple est dans l'ensemble

NoeudHexa *EnsHexaFindIndex(EnsHexa *e, int index); // trouve un noeud dans l'ensemble et le retourne

NoeudHexa *EnsHexaFindSupprIndex(EnsHexa *e, int index); // trouve une noeud dans l'ensemble, le retire de l'ensemble et le retourne

void EnsHexaSuppr(EnsHexa *e, int x, int y); // retire un couple à un ensemble

NoeudHexa * EnsHexaDepilePremier(EnsHexa *e); // retire le premier noeud de l'ensemble

void EnsHexaSupprPremier(EnsHexa *e); // supprime le premier noeud

void EnsHexaSupprDernier(EnsHexa *e); // supprime le dernier noeud

int EnsHexaEstDans(EnsHexa *e, int x,int y); // teste si un couple appartient à un ensemble

int EnsHexaTaille(EnsHexa *e); // nombre d’éléments dans l’ensemble

void EnsHexaPrint(EnsHexa *e); // affiche l'ensemble dans la console

NoeudHexa * EnsHexaTirage(EnsHexa *e,int l); // tire un couple aléatoirement dans un ensemble, et le retire de l’ensemble
