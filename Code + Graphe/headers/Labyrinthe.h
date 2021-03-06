#include "Ensemble.h"

typedef struct Lab{
    Matrice * map;
}Labyrinthe;

// accesseur
void set_v();

void set_d();

void set_Dij();

void set_Dij_rech();

void set_AStar();

void set_AStar_rech();

void set_Manual_rech();

void set_Auto();

void set_Start(int x,int y);

void set_Manual_Start();

void set_LinearGen();

void set_CaseWidth(int x);

// difference en 2 moment
double time_diff(struct timeval x , struct timeval y);

// génération du labyrinthe
Labyrinthe *LabCreate(int w,int h,float r);

// Libère le labyrinthe 
void LabFree(Labyrinthe *lab);

// verifie si une case est un mur
int EstConstruit(Labyrinthe *lab , int x ,int y);

// Vérifie si une case est constructible
int EstConstructible(Labyrinthe *lab  , Ens *v, Noeud * point, int init);

// construit les bords
void LabInit(Labyrinthe *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifTour(Labyrinthe *lab  , Ens *v, Noeud * point,int init);

// granularise le labyrinthe avec un nombre de graine
void Granularise(Labyrinthe *lab ,Ens *v, int nb);

// Construit les murs du labyrinthe depuis les graines
void LabConstruit(Labyrinthe *lab ,Ens *v);

// Affiche le labyrinthe dans la console
void LabPrint(Labyrinthe *lab);

// Affiche un point sur le graphe
void SetPointGraphe(int x, int y, char * color);

// gestionnaire des fonctions de recherche
void lanceRecherche(Labyrinthe *lab);

// lance la recherche manuelle
void recherche_manuelle(Labyrinthe * lab);

// lance la recherche
void dijkstra(Labyrinthe * lab);

// lance la recherche
void A_Star(Labyrinthe * lab);

