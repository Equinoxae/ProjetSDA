#ifndef MatCarre
#define MatCarre 

#include "MatriceCarre.h"

#endif //MatCarre

typedef struct LabCercle{

    MatriceCarre * map;

}LabyrintheCercle;

static struct timeval temps_debut_cercle,temps_fin_cercle;

//affichage du graph
static int v_graph_cercle = 0;
static int d_graph_cercle = 0;

static int case_width_cercle = 20;

// Manual Research 
static int manual_search_cercle = 0;

// Start
static int start_x_cercle= 0;
static int start_y_cercle = 0;
static int manual_start_cercle = 0;

// lineaire
static int linear_cercle = 0;

//DJI
static int Dij_cercle = 0;
static int Dij_rech_cercle = 0;

//AStar
static int AStar_cercle = 0;
static int AStar_rech_cercle = 0;

// accesseur
void set_v_cercle();

void set_d_cercle();

void set_Manual_rech_cercle();

void set_Start_cercle(int x,int y);

void set_Manual_Start_cercle();

void set_Construction_cercle(int val);

void set_LinearGenCercle();

void set_Dij_cercle();

void set_Dij_rech_cercle();

void set_AStar_cercle();

void set_AStar_rech_cercle();

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

// lance la recherche
void dijkstraCercle(LabyrintheCercle * lab);

// lance la recherche
void A_StarCercle(LabyrintheCercle * lab);

void printCercle(int w, int h, int x, int y, char* color);

void printCoteCercle(int l, int h, int x, int y, int cot, char* color);

// Affiche un point sur le graphe
void SetCerclePointGraphe(int x, int y, char * color);
