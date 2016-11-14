
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

int EnsFind(Ens *e, int x, int y);

Noeud *EnsFindIndex(Ens *e, int index);

void EnsSuppr(Ens *e, int x, int y); // retire un couple à un ensemble

int EnsEstDans(Ens *e, int x,int y); // teste si un couple appartient à un ensemble

int EnsTaille(Ens *e); // nombre d’éléments dans l’ensemble

void EnsPrint(Ens *e);

Noeud * EnsTirage(Ens *e); // tire un couple aléatoirement dans un ensemble, et le retire de l’ensemble