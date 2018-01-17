#include "EnsembleHexa.h"

typedef struct LabHexa{

    MatriceHexa * map;

}LabyrintheHexa;

// accesseur
void set_v_hexa();

void set_d_hexa();

void set_Manual_rech_hexa();

void set_Start_hexa(int x,int y);

void set_LinearGenHexa();

void set_Slow_gen();

void set_Slow_rech();

void set_Dij_hexa();

void set_Dij_rech_hexa();

void set_AStar_hexa();

void set_AStar_rech_hexa();

// difference en 2 moment
double time_diff_hexa(struct timeval x , struct timeval y);

// génération du labyrinthe
LabyrintheHexa *LabHexaCreate(int w,int h);

// Libère le labyrinthe 
void LabHexaFree(LabyrintheHexa *lab);

// construit les bords
void LabHexaInit(LabyrintheHexa *lab, int w ,int h); 

// Verifie la constructibilité des case autour d'une case 
void verifHexaTour(LabyrintheHexa *lab  , EnsHexa *v, int x,int y);

// Construit les murs du labyrinthe depuis les graines
void LabHexaConstruit(LabyrintheHexa *lab ,EnsHexa *v);

// gestionnaire des fonctions de recherche
void lanceRechercheHexa(LabyrintheHexa *lab);

// lance la recherche manuelle
void recherche_manuelle_hexa(LabyrintheHexa * lab);

// lance la recherche
void dijkstra_hexa(LabyrintheHexa * lab);

// lance la recherche
void A_Star_hexa(LabyrintheHexa * lab);

// calcule l'heuristique entre 2 points hexagonaux (odd-r coordonate)
int HexaHeuristique(int x_start, int y_start, int x_end, int y_end);

//affiche une case
void printHexa(int w, int h, int x, int y, char* color);

//affiche un coté d'une case
void printCoteHexa(int x, int y, int cot, char* color);

//affiche un point au centre d'une case
void printPointHexa(int x, int y, char* color);
