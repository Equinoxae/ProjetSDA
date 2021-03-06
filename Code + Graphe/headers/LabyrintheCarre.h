#ifndef MatCarre
#define MatCarre 

#include "EnsembleCarre.h"

#endif //MatCarre

typedef struct LabCarre{

    MatriceCarre * map;

}LabyrintheCarre;

// accesseur
void set_v_carre();

void set_d_carre();

void set_Manual_rech_carre();

void set_Start_carre(int x,int y);

void set_Manual_Start_carre();

void set_Construction_Carre(int val);

void set_LinearGenCarre();

void set_Dij_carre();

void set_Dij_rech_carre();

void set_AStar_carre();

void set_AStar_rech_carre();


// difference en 2 moments
double time_diff(struct timeval x , struct timeval y);

// génération du labyrinthe
LabyrintheCarre *LabCarreCreate(int w,int h);

// Libère le labyrinthe 
void LabCarreFree(LabyrintheCarre *lab);
// construit les bords
void LabCarreInit(LabyrintheCarre *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifCarreTour(LabyrintheCarre *lab  , EnsCarre *v, int x,int y);

// Construit les murs du labyrinthe 
void LabCarreConstruit(LabyrintheCarre *lab ,EnsCarre *v);
void LabCarreConstruit2(LabyrintheCarre *lab ,EnsCarre *v);

// Affiche un point sur le graphe
void SetHCarrePointGraphe(int x, int y, char * color);

// gestionnaire des fonctions de recherche
void lanceCarreRecherche(LabyrintheCarre *lab);

// lance la recherche
void dijkstraCarre(LabyrintheCarre * lab);

// lance la recherche
void A_StarCarre(LabyrintheCarre * lab);

// affiche une case 
void printCarre(int w, int h, int x, int y, char* color);

// affiche un coté d'une case
void printCoteCarre(int x, int y, int cot, char* color);

// Affiche un point sur le graphe
void SetCarrePointGraphe(int x, int y, char * color);
