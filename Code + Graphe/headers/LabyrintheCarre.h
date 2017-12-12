#include "EnsembleCarre.h"

typedef struct LabCarre{

    MatriceCarre * map;

}LabyrintheCarre;

static struct timeval temps_debut_carre,temps_fin_carre;

/* affichage du graph */
static int v_graph_carre = 0;
static int d_graph_carre = 0;

// Manual Research 
static int manual_search_carre = 0;

// Start
static int start_x_carre= 0;
static int start_y_carre = 0;
static int manual_start_carre = 0;

// accesseur
void set_v_carre();

void set_d_carre();

void set_Manual_rech_carre();

void set_Start_carre(int x,int y);

void set_Manual_Start_carre();

// difference en 2 moment
double time_diff(struct timeval x , struct timeval y);

// génération du labyrinthe
LabyrintheCarre *LabCarreCreate(int w,int h);

// Libère le labyrinthe 
void LabCarreFree(LabyrintheCarre *lab);

// verifie si une case est un mur
int EstCarreConstruit(LabyrintheCarre *lab , int x ,int y);

// Vérifie si une case est constructible
int EstCarreConstructible(LabyrintheCarre *lab  , EnsCarre *v, NoeudCarre * point);

// construit les bords
void LabCarreInit(LabyrintheCarre *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifCarreTour(LabyrintheCarre *lab  , EnsCarre *v, int x,int y);

// granularise le labyrinthe avec un nombre de graine
void GranulariseCarre(LabyrintheCarre *lab ,EnsCarre *v, int nb);

// Construit les murs du labyrinthe depuis les graines
void LabCarreConstruit(LabyrintheCarre *lab ,EnsCarre *v);

// Affiche le labyrinthe dans la console
void LabCarrePrint(LabyrintheCarre *lab);

// Affiche un point sur le graphe
void SetHCarrePointGraphe(int x, int y, char * color);

// gestionnaire des fonctions de recherche
void lanceCarreRecherche(LabyrintheCarre *lab);

// lance la recherche
void dijkstraCarre(LabyrintheCarre * lab);

// lance la recherche
void A_StarCarre(LabyrintheCarre * lab);

void printCarre(int w, int h, int x, int y, char* color);

void printCoteCarre(int x, int y, int cot, char* color);
