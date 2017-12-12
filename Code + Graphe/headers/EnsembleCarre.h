#include "MatriceCarre.h"

/* Noeud de l'ensemble */
typedef struct NoeudCarre{
    /* data*/
    int x; // [x,y]
    int y;
	int cote;//

    /* list suite */
    struct NoeudCarre * next ;
    struct NoeudCarre * previous;
}NoeudCarre;


/* Ensemble */

typedef struct EnsCarre{
    int taille;
    struct NoeudCarre * premier;
    struct NoeudCarre * dernier;
}EnsCarre;

// Noeud fonction //

NoeudCarre *NoeudCarreAlloc();
NoeudCarre *NoeudCarreInit(int x,int y,int c);
void NoeudCarreSuppr(NoeudCarre *n);

// Ensemble fonction //

EnsCarre * EnsCarreAlloc(); // création d’un nouvel ensemble

void EnsCarreFree(EnsCarre *e); // libération éventuelle de la mémoire utilisée

int EnsCarreEstVide(EnsCarre *e); // teste si un ensemble est vide

void EnsCarreAjoute(EnsCarre *e, int x, int y, int c); // ajoute un couple à un ensemble

void EnsCarreAjouteNoeudCarre(EnsCarre *e,NoeudCarre * n); // ajoute un noeud

void EnsCarreAjouteTrie(EnsCarre *e, NoeudCarre *n,MatriceCarre *heuristique); // ajoute un noeud ordonnée (n < n+1)

int EnsCarreFind(EnsCarre *e, int x, int y); // trouve si un couple est dans l'ensemble

NoeudCarre *EnsCarreFindIndex(EnsCarre *e, int index); // trouve un noeud dans l'ensemble et le retourne

NoeudCarre *EnsCarreFindSupprIndex(EnsCarre *e, int index); // trouve une noeud dans l'ensemble, le retire de l'ensemble et le retourne

void EnsCarreSuppr(EnsCarre *e, int x, int y); // retire un couple à un ensemble

NoeudCarre * EnsCarreDepilePremier(EnsCarre *e); // retire le premier noeud de l'ensemble

void EnsCarreSupprPremier(EnsCarre *e); // supprime le premier noeud

void EnsCarreSupprDernier(EnsCarre *e); // supprime le dernier noeud

int EnsCarreEstDans(EnsCarre *e, int x,int y); // teste si un couple appartient à un ensemble

int EnsCarreTaille(EnsCarre *e); // nombre d’éléments dans l’ensemble

void EnsCarrePrint(EnsCarre *e); // affiche l'ensemble dans la console

NoeudCarre * EnsCarreTirage(EnsCarre *e,int l); // tire un couple aléatoirement dans un ensemble, et le retire de l’ensemble
