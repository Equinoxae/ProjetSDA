#include "EnsembleHexa.h"

typedef struct LabHexa{

    MatriceHexa * map;

}LabyrintheHexa;

static struct timeval temps_debut_hexa,temps_fin_hexa;

/* affichage du graph */
static int v_graph_hexa = 0;
static int d_graph_hexa = 0;

// Manual Research 
static int manual_search_hexa = 0;

// Start
static int start_x_hexa = 0;
static int start_y_hexa = 0;
static int manual_start_hexa = 0;

// accesseur
void set_v_hexa();

void set_d_hexa();

void set_Manual_rech_hexa();

void set_Start_hexa(int x,int y);

void set_Manual_Start_hexa();

// difference en 2 moment
double time_diff(struct timeval x , struct timeval y);

// génération du labyrinthe
LabyrintheHexa *LabHexaCreate(int w,int h);

// Libère le labyrinthe 
void LabHexaFree(LabyrintheHexa *lab);

// verifie si une case est un mur
int EstHexaConstruit(LabyrintheHexa *lab , int x ,int y);

// Vérifie si une case est constructible
int EstHexaConstructible(LabyrintheHexa *lab  , EnsHexa *v, NoeudHexa * point);

// construit les bords
void LabHexaInit(LabyrintheHexa *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifHexaTour(LabyrintheHexa *lab  , EnsHexa *v, int x,int y);

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

void printHexa(int w, int h, int x, int y, char* color);

void printCoteHexa(int x, int y, int cot, char* color);
