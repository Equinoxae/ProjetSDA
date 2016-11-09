#include "Ensemble.h"
#include "Matrice.h"

typedef struct Lab{
    Matrice * map;
}Labyrinthe;


Labyrinthe *LabCreate(int w,int h,float r);

void LabFree(Labyrinthe *lab);

int EstConstruit(Labyrinthe *lab , int x ,int y);

int EstConstructible(Labyrinthe *lab  , Ens *v, Noeud * point, int init);

void LabInit(Labyrinthe *lab, Ens *v, int w ,int h); // construit les bords initialise les Ens

void verifTour(Labyrinthe *lab  , Ens *v, Noeud * point,int init);

void Granularise(Labyrinthe *lab ,Ens *v, Ens * v_fin , int nb);

void LabConstruit(Labyrinthe *lab ,Ens *v);

void LabPrint(Labyrinthe *lab);
