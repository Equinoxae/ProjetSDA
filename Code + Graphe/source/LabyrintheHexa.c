#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "LabyrintheHexa.h"
#include "graph.h"
#include <string.h>

void set_v_hexa(){
    v_graph_hexa = 1;
}

void set_d_hexa(){
    v_graph_hexa = 1;
    d_graph_hexa = 1;
}

void set_Manual_rech_hexa(){
	set_Manual_Start_hexa();
	set_v_hexa();
	manual_search_hexa = 1;
}

void set_Start_hexa(int x,int y){
	start_x_hexa = x;
	start_y_hexa = y;
}


void set_Manual_Start_hexa(){
	manual_start_hexa = 1;
}

double time_diff_hexa(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff/1000000;
}

// génération du labyrinthe
LabyrintheHexa *LabHexaCreate(int w,int h){
	// init random
    srand(time(NULL));

    // temps_debut
    gettimeofday(&temps_debut_hexa,NULL);

    //var
    LabyrintheHexa * l = malloc(sizeof(LabyrintheHexa));
    EnsHexa * v; // mur destructible

    // taille bordure
    int W = w ;
    int H = h ;

	if(v_graph_hexa){
        initgraph(W*20+10 +1 , H*20 + 10 + 1);
        flushgraph();
    }

	l->map = MatHexaAlloc(W,H);

	v = EnsHexaAlloc();

	LabHexaInit(l,W,H);
	
	printf("fin init\n");
	
	//waitgraph();
	
	LabHexaConstruit(l,v);

	waitgraph();

	return l;
}

// Libère le labyrinthe 
void LabHexaFree(LabyrintheHexa *lab){
	MatHexaFree(lab->map);
    free(lab);

}

// verifie si une case est un mur
int EstHexaConstruit(LabyrintheHexa *lab , int x ,int y){}

// Vérifie si une case est constructible
int EstHexaConstructible(LabyrintheHexa *lab  , EnsHexa *v, NoeudHexa * point){}

// construit les bords
void LabHexaInit(LabyrintheHexa *lab, int w ,int h){
int i,j;
	for(j = 0; j < h;j++){
		for(i = 0; i < w ; i++){
			MatHexaSet2(lab->map,i ,j , MurHexaAlloc() );

			if(v_graph_hexa)
		       	printHexa(w, h, i, j , "noir");
		}
	}
}

// Verifie la constructibilité des case autour d'une case 
void verifHexaTour(LabyrintheHexa *lab  , EnsHexa *v, int x, int y){
	// ligne paire
	int w = lab->map->l;
	int h = lab->map->h;
	
	
	if( y% 2 == 0){
		// gauche
		if( x-1 >= 0){
			MurHexa * m = MatHexaVal2(lab->map,x-1, y);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,1);
				if(d_graph_hexa)
					printCoteHexa(x,y,1,"rouge");
			}
		}
		// haut gauche
		if(y-1 >= 0 && x-1 >= 0){
			MurHexa * m = MatHexaVal2(lab->map,x-1, y-1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,2);
				if(d_graph_hexa)
					printCoteHexa(x,y,2,"rouge");
			}
		}
		// haut droit		
		if(y-1 >= 0){
			MurHexa * m = MatHexaVal2(lab->map,x, y-1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,3);
				if(d_graph_hexa)
					printCoteHexa(x,y,3,"rouge");
			}
		}
		// droite
		if( x+1 < w){
			MurHexa * m = MatHexaVal2(lab->map,x+1, y);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,4);
				if(d_graph_hexa)
					printCoteHexa(x,y,4,"rouge");
			}
		}
		// bas droit
		if(y+1 < h){
			MurHexa * m = MatHexaVal2(lab->map,x, y+1);

			if(m->v == 0){
				EnsHexaAjoute(v,x,y,5);
				if(d_graph_hexa)
					printCoteHexa(x,y,5,"rouge");
			}
		}
		// bas gauche
		if(y+1 < h && x-1 >= 0){
		
			MurHexa * m = MatHexaVal2(lab->map,x-1, y+1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,6);
				if(d_graph_hexa)
					printCoteHexa(x,y,6,"rouge");
			}
		}
		
	}
	// Ligne impaire
	else{
		// gauche
		if( x-1 >= 0){
		
			MurHexa * m = MatHexaVal2(lab->map,x-1, y);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,1);
				if(d_graph_hexa)
					printCoteHexa(x,y,1,"rouge");
			}
		}
		
		// haut gauche
		if(y-1 >= 0){
		
			MurHexa * m = MatHexaVal2(lab->map,x, y-1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,2);
				if(d_graph_hexa)
					printCoteHexa(x,y,2,"rouge");
			}
		}
		
		// haut droit		
		if(y-1 >= 0 && x+1 < w ){
		
			MurHexa * m = MatHexaVal2(lab->map,x+1, y-1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,3);
				if(d_graph_hexa)
					printCoteHexa(x,y,3,"rouge");
			}
		}
		
		// droite
		if( x+1 < w){
		
			MurHexa * m = MatHexaVal2(lab->map,x+1, y);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,4);
				if(d_graph_hexa)
					printCoteHexa(x,y,4,"rouge");
			}
		}
		
		// bas droit
		if(y+1 < h && x+1 < w){
		
			MurHexa * m = MatHexaVal2(lab->map,x+1, y+1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,5);
				if(d_graph_hexa)
					printCoteHexa(x,y,5,"rouge");
			}
		}
		
		// bas gauche
		if(y+1 < h){
		
			MurHexa * m = MatHexaVal2(lab->map,x, y+1);
		
			if(m->v == 0){
				EnsHexaAjoute(v,x,y,6);
				if(d_graph_hexa)
					printCoteHexa(x,y,6,"rouge");
			}
		}
	
	}


}

// granularise le labyrinthe avec un nombre de graine
void GranulariseHexa(LabyrintheHexa *lab ,EnsHexa *v, int nb){ // nada 
}

// Construit les murs du labyrinthe depuis les graines
void LabHexaConstruit(LabyrintheHexa *lab ,EnsHexa *v){
	
	// trouve le premier mur et ajoute ses coté en liste
	EnsHexaAjoute(v,lab->map->l/2 - 1,lab->map->h/2 - 1,0);
	
	/*for(int i = 1; i <= 6; i++){
		EnsHexaAjoute(v,lab->map->l/2,lab->map->h/2,i);
		if(d_graph_hexa)
			printCoteHexa(lab->map->l/2,lab->map->h/2,i,"rouge");
	}*/
	
	printf("start %i\n",v->taille);
	
	while(!EnsHexaEstVide(v)){
		NoeudHexa * n = EnsHexaTirage(v,0);
		
		printf("tirage %i\n",v->taille);
		printf("%i %i %i\n",n->x,n->y,n->cote);

		
		MurHexa * m, * voisin, * first;
		int x_v,y_v;


		m = MatHexaVal2(lab->map,n->x,n->y);
		m->v = 1;

		switch(n->cote)
		{
			case 1:		
				// trouve le voisin
				voisin = MatHexaVal2(lab->map,n->x-1,n->y);
				if(voisin->v == 0){
					// casse le mur					
					m->c1 =0;
					// visite le voisin
					voisin->v = 1; 
					
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,1,"blanc");
					
					// je verifie le tour
					verifHexaTour(lab,v,n->x-1,n->y);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,1,"noir");
				}
				
				break;
			case 2:
				
				// trouve le voisin
				if(n->y%2 == 0)
					voisin = MatHexaVal2(lab->map,n->x-1,n->y-1);
				else
					voisin = MatHexaVal2(lab->map,n->x,n->y-1);
				
				if(voisin->v == 0){
					// visite le voisin
					voisin->v = 1;
					// casse le mur
					m->c2 =0;
					
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,2,"blanc");
					
					// vérifi le tour
					if(n->y%2 == 0)
						verifHexaTour(lab,v,n->x-1,n->y-1);
					else
						verifHexaTour(lab,v,n->x,n->y-1);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,2,"noir");
				}
				
				break;
				
			case 3:
				
				// trouve le voisin
				if(n->y%2 == 0)
					voisin = MatHexaVal2(lab->map,n->x,n->y-1);
				else
					voisin = MatHexaVal2(lab->map,n->x+1,n->y-1);
				
				if(voisin->v == 0){
					//casse le mur
					m->c3 =0;
					// visite le voisin 
					voisin->v = 1;
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,3,"blanc");
					
					// verifi le tour
					if(n->y%2 == 0)
						verifHexaTour(lab,v,n->x,n->y-1);
					else
						verifHexaTour(lab,v,n->x+1,n->y-1);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,3,"noir");
				}
				
				break;
			case 4:
			
				// trouve le voisin			
				voisin = MatHexaVal2(lab->map,n->x+1,n->y);
				
				if(voisin->v == 0){
					// casse le mur
					voisin->c1 = 0;
					
					// visite le voisin
					voisin->v = 1;
					
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,4,"blanc");
					
					// verifie le  tour
					verifHexaTour(lab,v,n->x+1,n->y);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,4,"noir");
				}
				break;
			case 5:
				
				// trouve le voisin
				if(n->y%2 == 0)
					voisin = MatHexaVal2(lab->map,n->x,n->y+1);
				else
					voisin = MatHexaVal2(lab->map,n->x+1,n->y+1);
				
				if(voisin->v == 0){
				
					// casse le mur
					voisin->c2 =0;
					
					// visite le voisin
					voisin->v = 1;
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,5,"blanc");
					
					// verifie le tour
					if(n->y%2 == 0)
						verifHexaTour(lab,v,n->x,n->y+1);
					else
						verifHexaTour(lab,v,n->x+1,n->y+1);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,5,"noir");
				}
				break;
			case 6:
				
				// trouve le voisin
				if(n->y%2 == 0)
					voisin = MatHexaVal2(lab->map,n->x-1,n->y+1);
				else
					voisin = MatHexaVal2(lab->map,n->x,n->y+1);
				
				if(voisin->v == 0){
					// casse le mur
					voisin->c3 = 0;
					
					// visite le voisin
					voisin->v = 1;
					
					if(v_graph_hexa)
						printCoteHexa(n->x,n->y,6,"blanc");
					
					// verifi le tour
					if(n->y%2 == 0)
						verifHexaTour(lab,v,n->x-1,n->y+1);
					else
						verifHexaTour(lab,v,n->x,n->y+1);
				} 
				else{
					if(d_graph_hexa)
						printCoteHexa(n->x,n->y,6,"noir");
				}
				break;
			case 0:
				verifHexaTour(lab,v,n->x,n->y);
				break;
		
		}
		printf("next %i\n",v->taille);
	
		free(n);
		if(d_graph_hexa)
			usleep(10 * 1000);

	}
	

}

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


void printHexa(int w, int h, int x, int y, char * color){

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

void printCoteHexa(int x, int y, int cot, char * color){

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

	//printf("%i %i\n",x,y);

	int col = (y%2 == 0)? 0 : 10;
	
	
	switch(cot){
		case 1:
			line(0 + c + col, 11 + l, 0 + c + col, 19 + l); 	// '|'
			//line(0 + c + col, 10 + l, 0 + c + col, 20 + l); 	// '|'
			break;
		case 2:
			//line(0 + c + col, 10 + l, 10 + c + col, 0 + l); 	// '/'
			line(1 + c + col, 9 + l, 9 + c + col, 1 + l); 	// '/'
			break;
		case 3:
			//line(10 + c + col, 0 + l, 20 + c + col, 10 + l); 	// '\'
			line(11 + c + col, 1 + l, 19 + c + col, 9 + l); 	// '\'
			break;
		case 4:
			//line(20 + c + col, 10 + l, 20 + c + col,  20 + l); 	// '|'
			line(20 + c + col, 11 + l, 20 + c + col,  19 + l); 	// '|'
			break;
		case 5:
			//line(10 + c + col, 30 + l , 20 + c + col, 20 + l); 	// '/'
			line(11 + c + col, 29 + l , 19 + c + col, 21 + l); 	// '/'
			break;
		case 6:
			//line(0 + c + col, 20 + l , 10 + c + col, 30 + l); 	// '\'
			line(1 + c + col, 21 + l , 9 + c + col, 29 + l); 	// '\'
			break;
		default:
			printf("error");
			break;
	}
	
	refresh();
}

