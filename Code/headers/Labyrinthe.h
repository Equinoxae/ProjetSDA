#include "Ensemble.h"
#include "Matrice.h"

typedef struct Lab{
    Matrice * map;
}Labyrinthe;


Labyrinthe *LabCreate(int w,int h,double r);

void LabFree(Labyrinthe *lab);

void LabInit(Labyrinthe *lab,Ens *c, Ens *v, int w ,int h); // construit les bords initialise les Ens

void LabSupprBordInter(Labyrinthe *lab, Ens *v); // Supprime les bord interireur du Labyrinthe *des case disponnible a la construction

int EstConstructible(Labyrinthe *lab , Ens *c, Noeud * point, int init);

void Granularise(Labyrinthe *lab ,Ens *c ,Ens *v , int nb);

void LabConstruit(Labyrinthe *lab ,Ens *c ,Ens *v);

void LabPrint(Labyrinthe *lab);
