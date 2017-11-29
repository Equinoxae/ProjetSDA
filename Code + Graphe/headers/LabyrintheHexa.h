#include "EnsembleHexa.h"

typedef struct LabHexa{

    MatriceHexa * map;

}LabyrintheHexa;

// génération du labyrinthe
LabyrintheHexa *LabHexaCreate(int w,int h,float r);

// Libère le labyrinthe 
void LabHexaFree(LabyrintheHexa *lab);

// verifie si une case est un mur
int EstHexaConstruit(LabyrintheHexa *lab , int x ,int y);

// Vérifie si une case est constructible
int EstHexaConstructible(LabyrintheHexa *lab  , EnsHexa *v, NoeudHexa * point, int init);

// construit les bords
void LabHexaInit(LabyrintheHexa *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifHexaTour(LabyrintheHexa *lab  , EnsHexa *v, NoeudHexa * point,int init);

// granularise le labyrinthe avec un nombre de graine
void GranulariseHexa(LabyrintheHexa *lab ,EnsHexa *v, int nb);

// Construit les murs du labyrinthe depuis les graines
void LabHexaConstruit(LabyrintheHexa *lab ,EnsHexa *v);

// Affiche le labyrinthe dans la console
void LabHexaPrint(LabyrintheHexa *lab);

// Affiche un point sur le graphe
void SetHexaPointGraphe(int x, int y, char * color);

// gestionnaire des fonctions de recherche
void lanceHexaRecherche(LabyrintheHexa *lab);

// lance la recherche
void dijkstraHexa(LabyrintheHexa * lab);

// lance la recherche
void A_StarHexa(LabyrintheHexa * lab);

void printCase();
