#ifndef MatCarre
#define MatCarre 

#include "MatriceCarre.h"

#endif //MatCarre

typedef struct LabCercle{

    MatriceCarre * map;

}LabyrintheCercle;


// accesseur
void set_v_cercle();

void set_d_cercle();

void set_Construction_cercle(int val);

void set_CaseWidth_cercle(int x);

// difference en 2 moments
double time_diff(struct timeval x , struct timeval y);

// génération du labyrinthe
LabyrintheCercle* LabCercleCreate(int w,int h);

// Libère le labyrinthe 
void LabCercleFree(LabyrintheCercle *lab);

// construit les bords
void LabCercleInit(LabyrintheCercle *lab, int w ,int h); 

// Construit les murs du labyrinthe 
void LabCercleConstruit(LabyrintheCercle *lab);

// Affiche le labyrinthe dans la console
void LabCerclePrint(LabyrintheCercle *lab);

// Affiche un point sur le graphe
void SetHCerclePointGraphe(int x, int y, char * color);

// gestionnaire des fonctions de recherche
void lanceCercleRecherche(LabyrintheCercle *lab);

// affiche un cercle
void printCercle(int w, int h, int x, int y, char* color);

//affiche un coté du cercle
void printCoteCercle(int l, int h, int x, int y, int cot, char* color);

