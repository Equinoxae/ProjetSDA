#include "Matrice.h"

/* Noeud de l'ensemble */
typedef struct Noeud{
    /* data*/
    int x; // [x,y]
    int y;

    /* list suite */
    struct Noeud * next ;
    struct Noeud * previous;
}Noeud;


/* Ensemble */

typedef struct Ens{
    int taille;
    struct Noeud * premier;
    struct Noeud * dernier;
}Ens;

// Noeud fonction //

Noeud *NoeudAlloc();
Noeud *NoeudInit(int x,int y);
void NoeudSuppr(Noeud *n);

// Ensemble fonction //

Ens * EnsAlloc(); // création d’un nouvel ensemble

void EnsFree(Ens *e); // libération éventuelle de la mémoire utilisée

int EnsEstVide(Ens *e); // teste si un ensemble est vide

void EnsAjoute(Ens *e, int x, int y); // ajoute un couple à un ensemble

void EnsAjouteNoeud(Ens *e,Noeud * n); // ajoute un noeud

void EnsAjouteTrie(Ens *e, Noeud *n,Matrice *heuristique); // ajoute un noeud ordonnée (n < n+1)

int EnsFind(Ens *e, int x, int y); // trouve si un couple est dans l'ensemble

Noeud *EnsFindIndex(Ens *e, int index); // trouve un noeud dans l'ensemble et le retourne

Noeud *EnsFindSupprIndex(Ens *e, int index); // trouve une noeud dans l'ensemble, le retire de l'ensemble et le retourne

void EnsSuppr(Ens *e, int x, int y); // retire un couple à un ensemble

Noeud * EnsDepilePremier(Ens *e); // retire le premier noeud de l'ensemble

void EnsSupprPremier(Ens *e); // supprime le premier noeud

void EnsSupprDernier(Ens *e); // supprime le dernier noeud

int EnsEstDans(Ens *e, int x,int y); // teste si un couple appartient à un ensemble

int EnsTaille(Ens *e); // nombre d’éléments dans l’ensemble

void EnsPrint(Ens *e); // affiche l'ensemble dans la console

Noeud * EnsTirage(Ens *e); // tire un couple aléatoirement dans un ensemble, et le retire de l’ensemble
