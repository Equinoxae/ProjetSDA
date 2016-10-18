
/* Noeud de l'ensemble */
struct noeud{
    /* data*/
    int * data; // [x,y]

    /* list suite */
    struct noeud * next ;
};

typedef struct noeud Noeud;

Noeud *NoeudAlloc();
void NoeudSuppr(Noeud *node);

/* Ensemble */

struct ensemble{
    struct Noeud * premier;
};

typedef struct ensemble Ens;

Ens EnsAlloc(); // création d’un nouvel ensemble

void EnsFree(Ens e); // libération éventuelle de la mémoire utilisée

int EnsEstVide(Ens e); // teste si un ensemble est vide

void EnsAjoute(Ens e, int x, int y); // ajoute un couple à un ensemble

int EnsFind(Ens e, int x, int y);

void EnsSuppr(Ens e, int x, int y); // retire un couple à un ensemble

int EnsEstDans(Ens e, int x,int y); // teste si un couple appartient à un ensemble

int EnsTaille(Ens e); // nombre d’éléments dans l’ensemble

int * EnsTirage(Ens e); // tire un couple aléatoirement dans un ensemble, et le retire de l’ensemble
