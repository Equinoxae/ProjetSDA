#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "LabyrintheCarre.h"
#include "graph.h"
#include <string.h>

void set_v_carre(){
    v_graph_carre = 1;
}

void set_d_carre(){
    v_graph_carre = 1;
    d_graph_carre = 1;
}

void set_Manual_rech_carre(){
	set_Manual_Start_carre();
	set_v_carre();
	manual_search_carre = 1;
}

void set_Start_carre(int x,int y){
	start_x_carre = x;
	start_y_carre = y;
}


void set_Manual_Start_carre(){
	manual_start_carre = 1;
}

double time_diff_carre(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff/1000000;
}

// génération du labyrinthe
LabyrintheCarre *LabCarreCreate(int w,int h){
	// init random
    srand(time(NULL));

    // temps_debut
    gettimeofday(&temps_debut_carre,NULL);

    //var
    LabyrintheCarre * l = malloc(sizeof(LabyrintheCarre));
    EnsCarre * v; // mur destructible

    // taille bordure
    int W = w ;
    int H = h ;

	if(v_graph_carre){
        initgraph(W*20+10 +1 , H*20 + 10 + 1);
        flushgraph();
    }

	l->map = MatCarreAlloc(W,H);

	v = EnsCarreAlloc();

	LabCarreInit(l,W,H);
	
	waitgraph();

	return l;
}

// Libère le labyrinthe 
void LabCarreFree(LabyrintheCarre *lab){
	MatCarreFree(lab->map);
    free(lab);

}

// verifie si une case est un mur
int EstCarreConstruit(LabyrintheCarre *lab , int x ,int y){}

// Vérifie si une case est constructible
int EstCarreConstructible(LabyrintheCarre *lab  , EnsCarre *v, NoeudCarre * point){}

// construit les bords
void LabCarreInit(LabyrintheCarre *lab, int w ,int h){
int i,j;
	for(j = 0; j < h;j++){
		for(i = 0; i < w ; i++){
			MatCarreSet2(lab->map,i ,j , MurCarreAlloc() );

			if(v_graph_carre)
		       	printCarre(w, h, i, j , "noir");
		}
	}
}

// Verifie la constructibilité des case autour d'une case 
void verifCarreTour(LabyrintheCarre *lab  , EnsCarre *v, int x, int y){
	// ligne paire
	int w = lab->map->l;
	int h = lab->map->h;
		
	// gauche
	if( x-1 >= 0){
	
		MurCarre * m = MatCarreVal2(lab->map,x-1, y);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,1);
			if(d_graph_carre)
				printCoteCarre(x,y,1,"rouge");
		}
	}
	
	// haut droit		
	if(y-1 > 0){
	
		MurCarre * m = MatCarreVal2(lab->map,x, y-1);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,3);
			if(d_graph_carre)
				printCoteCarre(x,y,3,"rouge");
		}
	}
	
	// droite
	if( x+1 < w){
	
		MurCarre * m = MatCarreVal2(lab->map,x+1, y);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,4);
			if(d_graph_carre)
				printCoteCarre(x,y,4,"rouge");
		}
	}
	
	// bas droit
	if(y+1 < h){
	
		MurCarre * m = MatCarreVal2(lab->map,x, y+1);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,5);
			if(d_graph_carre)
				printCoteCarre(x,y,5,"rouge");
		}
	}
}

// granularise le labyrinthe avec un nombre de graine
void GranulariseCarre(LabyrintheCarre *lab ,EnsCarre *v, int nb){ // nada 
}

// Construit les murs du labyrinthe depuis les graines
void LabCarreConstruit(LabyrintheCarre *lab ,EnsCarre *v){
	
	// trouve le premier mur et ajoute ses coté en liste
	EnsCarreAjoute(v,lab->map->l/2,lab->map->h/2,0);

	
	while(!EnsCarreEstVide(v)){
		NoeudCarre * n = EnsCarreTirage(v,0);
		
		MurCarre * m, * voisin, * first;
		switch(n->cote)
		{
			case 1:
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
			
				voisin = MatCarreVal2(lab->map,n->x-1,n->y);
				if(voisin->v == 0){
					m->c1 =0;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,1,"blanc");
					verifCarreTour(lab,v,n->x-1,n->y);
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,1,"noir");
				}
				
				break;
			case 2:
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
				
				if(n->y%2 == 0)
					voisin = MatCarreVal2(lab->map,n->x-1,n->y-1);
				else
					voisin = MatCarreVal2(lab->map,n->x,n->y-1);
				
				if(voisin->v == 0){
					m->c2 =0;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,2,"blanc");
					
					if(n->y%2 == 0)
						verifCarreTour(lab,v,n->x-1,n->y-1);
					else
						verifCarreTour(lab,v,n->x,n->y-1);
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,2,"noir");
				}
				
				break;

			case 3:
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
			
				voisin = MatCarreVal2(lab->map,n->x+1,n->y);
				if(voisin->v == 0){
					voisin->c1 =0;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,4,"blanc");
					verifCarreTour(lab,v,n->x+1,n->y);
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,4,"noir");
				}
				break;
			case 4:
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
				
				if(n->y%2 == 0)
					voisin = MatCarreVal2(lab->map,n->x,n->y+1);
				else
					voisin = MatCarreVal2(lab->map,n->x+1,n->y+1);
				
				if(voisin->v == 0){
					voisin->c2 =0;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,5,"blanc");
					
					if(n->y%2 == 0)
						verifCarreTour(lab,v,n->x,n->y+1);
					else
						verifCarreTour(lab,v,n->x+1,n->y+1);
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,5,"noir");
				}
				break;

			case 0:
				first = MatCarreVal2(lab->map,n->x,n->y);
				first->v = 1;
				verifCarreTour(lab,v,n->x,n->y);
				break;
		
		}
	
		//waitgraph();
	
	}
	

}

// Affiche le labyrinthe dans la console
void LabCarrePrint(LabyrintheCarre *lab){}

// Affiche un point sur le graphe
void SetCarrePointGraphe(int x, int y, char * color){}

// gestionnaire des fonctions de recherche
void lanceCarreRecherche(LabyrintheCarre *lab){}

// lance la recherche
void dijkstraCarre(LabyrintheCarre * lab){}

// lance la recherche
void A_StarCarre(LabyrintheCarre * lab){}


void printCarre(int w, int h, int x, int y, char * color){

	if (!strcmp(color,"blanc"))
            setcolor(newcolor(1,1,1));
    else if (!strcmp(color,"noir"))
            setcolor(newcolor(0,0,0));
    else if (!strcmp(color,"rouge"))
            setcolor(newcolor(1,0,0));
    else if (!strcmp(color,"vert") ){
		setcolor(newcolor(0,1,0));
	}
	else if (!strcmp(color,"vertf") ){
		setcolor(newcolor(0,0.4,0));
	}
    else if (!strcmp(color,"bleu"))
            setcolor(newcolor(0,0.5,1));
    else if (!strcmp(color,"gris"))
    		setcolor(newcolor(0.9,0.9,0.9));

	int l = y * 20;
	int c = x * 20;

	int col = (y%2 == 0)? 0 : 10;
	
	//afficher case : 3 lignes à dessiner
	line(0 + c + col, 10 + l, 0 + c + col, 20 + l); //x1, y1, x2, y2 coté 1
	line(0 + c + col, 10 + l, 10 + c + col, 0 + l); //x1, y1, x2, y2 coté 2
	line(10 + c + col, 0 + l, 20 + c + col, 10 + l); //x1, y1, x2, y2 coté 3

	// coté gauche '\'
	if( x = 0 && y%2 == 1)
		line(0, 20 + l , 10 , 30 + l);

	// ligne du bas '\/'
	if( y = h-1){
		line(0 + c + col, 20 + l , 10 + c + col, 30 + l);
		line(10 + c + col, 30 + l , 20 + c + col, 20 + l);
	}

	if( x = w-1)
		line(20 + c + col, 10 + l, 20 + c + col,  20 + l);

	refresh();

}

void printCoteCarre(int x, int y, int cot, char * color){

	if (!strcmp(color,"blanc"))
            setcolor(newcolor(1,1,1));
    else if (!strcmp(color,"noir"))
            setcolor(newcolor(0,0,0));
    else if (!strcmp(color,"rouge"))
            setcolor(newcolor(1,0,0));
    else if (!strcmp(color,"vert") ){
		setcolor(newcolor(0,1,0));
	}
	else if (!strcmp(color,"vertf") ){
		setcolor(newcolor(0,0.4,0));
	}
    else if (!strcmp(color,"bleu"))
            setcolor(newcolor(0,0.5,1));
    else if (!strcmp(color,"gris"))
    		setcolor(newcolor(0.9,0.9,0.9));
	
	int l = y * 20;
	int c = x * 20;

	int col = (y%2 == 0)? 0 : 10;
	
	switch(cot){
		case 1:
			line(0 + c + col, 11 + l, 0 + c + col, 19 + l); 	// '|'
			break;
		case 2:
			line(1 + c + col, 9 + l, 9 + c + col, 1 + l); 	// '/'
			break;
		case 3:
			line(20 + c + col, 11 + l, 20 + c + col,  19 + l); 	// '|'
			break;
		case 4:
			line(11 + c + col, 29 + l , 19 + c + col, 21 + l); 	// '/'
			break;
	}
	
	refresh();
}

