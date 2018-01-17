#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "LabyrintheCercle.h"
#include "graph.h"
#include <string.h>
#include <unistd.h>
#include <Heap.h>


// Static
static struct timeval temps_debut_cercle,temps_fin_cercle;

//affichage du graph
static int v_graph_cercle = 0;
static int d_graph_cercle = 0;

// hauteur de l'étage
static int case_width_cercle = 20;


// Accesseur
void set_v_cercle(){
    v_graph_cercle = 1;
}

void set_d_cercle(){
    v_graph_cercle = 1;
    d_graph_cercle = 1;
}

void set_CaseWidth_cercle(int x){
	if(x < 5 || x > 50){
		printf("Taille de case invalide ! La largeur et la hauteur de la case doit être >= 5 et <= 50\n");
	    exit(6);
	}

	case_width_cercle = x;	
}

double time_diff_cercle(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff/1000000;
}

// génération du labyrinthe
LabyrintheCercle *LabCercleCreate(int w,int h){
	// init random
    srand(time(NULL));

    // temps_debut
    gettimeofday(&temps_debut_cercle,NULL);

    //var
    LabyrintheCercle * l = malloc(sizeof(LabyrintheCercle));

    // taille bordure
    int W = w ;
    int H = h ;

	//initialisation fenêtre de la bonne taille
	if(v_graph_cercle){
        initgraph(h*case_width_cercle*2+3 , H*case_width_cercle*2+3);
        flushgraph();
    }

	l->map = MatCarreAlloc(W,H);

	LabCercleInit(l,W,H);
			
	LabCercleConstruit(l); 
	
	// temps_fin
    gettimeofday(&temps_fin_cercle,NULL);
    printf("Génération\n temps d'execution: %.5f secondes\n", time_diff_cercle(temps_debut_cercle,temps_fin_cercle));;
	
	if(v_graph_cercle)
 		waitgraph();
	return l;
}

// Libère le labyrinthe 
void LabCercleFree(LabyrintheCercle *lab){
	MatCarreFree(lab->map);
    free(lab);
}

// construit les bords
void LabCercleInit(LabyrintheCercle *lab, int w ,int h){
int i ,j;
	for(j = 0; j < h;j++){
		for(i = 0; i < w ; i++){
			MatCarreSet2(lab->map,i ,j , MurCarreAlloc() );

		}
		if(v_graph_cercle)
		       	printCercle(w, h, i, j , "noir");
	}
	
	if(v_graph_cercle)
		       	printCercle(w, h, w, h , "noir");
}


// Construit les murs du labyrinthe depuis les graines
void LabCercleConstruit(LabyrintheCercle *lab){

	int l = lab->map->l;
	int h = lab->map->h;	

	MurCarre * m = NULL;

	for(int y = 0;y < h;y++){

		int doors = 0;		

		for(int x = 0;x < l;x++){
			m = MatCarreVal2(lab->map,x,y);
			// première ligne
			if(y == 0){
				doors = 1;
				if(!x==0){
					m->c1 = 0;
					if(v_graph_cercle)
						printCoteCercle(l,h,x,y,1,"blanc");
					
				}			
			}
			else // autres ligne
			{
				if(rand()%2){
					m->c1 = 0;
					if(v_graph_cercle)
						printCoteCercle(l,h,x,y,1,"blanc");
				}
				else{
					doors++;
					m->c2 = 0;
					if(v_graph_cercle)
						printCoteCercle(l,h,x,y,2,"blanc");
				}
			}
			
			if(d_graph_cercle)
				usleep(5*1000);
			//waitgraph();

		}
		
		if(doors == 0){
					int x2 = rand()%l;
					m = MatCarreVal2(lab->map,x2,y);
					m->c2 = 0;
					if(v_graph_cercle)
						printCoteCercle(l,h,x2,y,2,"blanc");
				}
		

	}   

}

void printCercle(int w, int h, int x, int y, char * color){

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
	
	circle(h*case_width_cercle +1 ,h*case_width_cercle +1, y *case_width_cercle );

	refresh();
}

void printCoteCercle(int l, int h, int x, int y, int cot, char * color){

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

	float pi = 3.14152965358979323846;

	switch(cot){
		case 1:
			break;
		case 2:
			arc(h*case_width_cercle +1 ,h*case_width_cercle +1 , y*case_width_cercle,
								 (360/l * (x)) *64 ,(360/l)*64 );
			
			setcolor(newcolor(0,0,0));
								 
			double angle = 360/l*(x) * pi / 180;
			double c = cos(angle);
			double s = sin(angle);
			
			line(h*case_width_cercle + 1 + c * y * case_width_cercle,
				h*case_width_cercle + 1 - s * y * case_width_cercle,
				h*case_width_cercle + 1 + c * (y+1) * case_width_cercle,
				h*case_width_cercle + 1 - s * (y+1) * case_width_cercle);
			
			break;
	}
	
	refresh();
}
