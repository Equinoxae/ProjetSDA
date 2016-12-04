#include "Ensemble.h"

static struct timeval temps_debut,temps_fin;

static int v_graph = 0;
static int d_graph = 0;

static int Dij = 0;
static int Dij_rech = 0;

static int AStar = 0;
static int AStar_rech = 0;

static int Auto = 0;

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

void set_Auto();

double time_diff(struct timeval x , struct timeval y);

Labyrinthe *LabCreate(int w,int h,float r);

void LabFree(Labyrinthe *lab);

int EstConstruit(Labyrinthe *lab , int x ,int y);

int EstConstructible(Labyrinthe *lab  , Ens *v, Noeud * point, int init);

void LabInit(Labyrinthe *lab, int w ,int h); // construit les bords initialise les Ens

void verifTour(Labyrinthe *lab  , Ens *v, Noeud * point,int init);

void Granularise(Labyrinthe *lab ,Ens *v, int nb);

void LabConstruit(Labyrinthe *lab ,Ens *v);

void LabPrint(Labyrinthe *lab);

void SetPointGraphe(int x, int y, char * color);

void lanceRecherche(Labyrinthe *lab);

void dijkstra(Labyrinthe * lab);

void A_Star(Labyrinthe * lab);
