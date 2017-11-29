#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "LabyrintheHexa.h"
#include "graph.h"
#include "Heap.h"
#include <string.h>
// génération du labyrinthe
LabyrintheHexa *LabHexaCreate(int w,int h,float r){}

// Libère le labyrinthe 
void LabHexaFree(LabyrintheHexa *lab){}

// verifie si une case est un mur
int EstHexaConstruit(LabyrintheHexa *lab , int x ,int y){}

// Vérifie si une case est constructible
int EstHexaConstructible(LabyrintheHexa *lab  , Ens *v, Noeud * point, int init){}

// construit les bords
void LabHexaInit(LabyrintheHexa *lab, int w ,int h){}

// Verifie la constructibilité des case autour d'une case 
void verifhexaTour(LabyrintheHexa *lab  , Ens *v, Noeud * point,int init){}

// granularise le labyrinthe avec un nombre de graine
void GranulariseHexa(LabyrintheHexa *lab ,Ens *v, int nb){}

// Construit les murs du labyrinthe depuis les graines
void LabHexaConstruit(LabyrintheHexa *lab ,Ens *v){}

// Affiche le labyrinthe dans la console
void LabHexaPrint(LabyrintheHexa *lab){}

// Affiche un point sur le graphe
void SetHexaPointGraphe(int x, int y, char * color){}

// gestionnaire des fonctions de recherche
void lanceHexaRecherche(LabyrintheHexa *lab){}

// lance la recherche
void dijkstraHexa(LabyrintheHexa * lab){}

// lance la recherche
void A_StarHexa(LabyrintheHexa * lab){}


void printCase(){

	//afficher case : 3 lignes à dessiner
	setcolor(newcolor(255,127,0)); //oraaaaaaaaaaange
	line (0, 10, 0, 20); //x1, y1, x2, y2 coté 1
	line (0, 10, 10, 0); //x1, y1, x2, y2 coté 2
	line (10, 0, 20, 10); //x1, y1, x2, y2 coté 3

}
