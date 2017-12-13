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

void set_LinearGenHexa(){
	linear_hexa = 1;
}

void set_Dij_hexa(){
	Dij_hexa = 1;
}

void set_Dij_rech_hexa(){
	Dij_hexa = 1;
	Dij_rech_hexa = 1;
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

// Construit les murs du labyrinthe depuis les graines
void LabHexaConstruit(LabyrintheHexa *lab ,EnsHexa *v){
	
	// trouve le premier mur et ajoute ses coté en liste
	EnsHexaAjoute(v,lab->map->l/2 - 1,lab->map->h/2 - 1,0);
	
	while(!EnsHexaEstVide(v)){
		NoeudHexa * n = EnsHexaTirage(v,linear_hexa);
		
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
	
		free(n);
		if(d_graph_hexa)
			usleep(5 * 1000);

	}
	

}
// gestionnaire des fonctions de recherche
void lanceRechercheHexa(LabyrintheHexa *lab){


	if(manual_search_hexa){

		recherche_manuelle_hexa(lab);
		
	}
	else if(Dij_hexa)
		dijkstra_hexa(lab);
	
	if(v_graph_hexa){
			waitgraph();
			closegraph();
		}

}
void recherche_manuelle_hexa(LabyrintheHexa * lab){
	
	int x = start_x_hexa;
	int y = start_y_hexa;
	int prev_x;
	int prev_y;

	int end_x = lab->map->l-1;
	int end_y = lab->map->h-1;
	char * k ="";
	
	int l = lab->map->l;
	int h = lab->map->h;
	
	printPointHexa(x,y,"vert");
	printPointHexa(end_x,end_y,"rouge");
	flushgraph();
	refresh();

	while ( !(x == end_x && y == end_y) && k != "esc"){
		printf("Appuiez sur une touche\n");
		k = getKey();
		//printf("dir : %s\n",k);
				
		if(!strcmp(k,"left")){
			
			MurHexa *m = MatHexaVal2(lab->map,x,y);
			
			if(m->c1 == 0){
				prev_x = x;
				prev_y = y;
			
				x--;
				printf("dir : %s\n",k);
			}
			
		}
		else if(!strcmp(k,"right")){
			
			MurHexa* m = MatHexaVal2(lab->map,x+1,y);
		
			if(m->c1 == 0){
				prev_x = x;
				prev_y = y;
		
				x++;
				printf("dir : %s\n",k);
			}
			
		}
		else if(!strcmp(k,"up")){
			k = getKey();
			
			if(!strcmp(k,"left")){
			
				if( (y%2 == 1 || x > 0 )&& y > 0 ){
				
					MurHexa *m = MatHexaVal2(lab->map,x,y);
			
					if(m->c2 == 0){
						prev_x = x;
						prev_y = y;
		
						if(y%2 == 0){
							x--;
							y--;
						}
						else{
							x;
							y--;
						}
					}
					printf("dir : up + %s\n",k);
				
				}
			}
			else if(!strcmp(k,"right")){
			
				if((y%2 == 0 || x < l-1 ) && y > 0 ){
				
					MurHexa *m = MatHexaVal2(lab->map,x,y);
			
					if(m->c3 == 0){
						prev_x = x;
						prev_y = y;
		
						if(y%2 == 0){
							x;
							y--;
						}
						else{
							x++;
							y--;
						}
					}
					printf("dir : up + %s\n",k);
				
				}
			
			
			}
						
		}
		else if(!strcmp(k,"down")){
			k = getKey();
			
			if(!strcmp(k,"right")){
			
				if((y%2 == 0 || x < l-1 ) && y < h-1 ){
				
					MurHexa* m = MatHexaVal2(lab->map,y%2 == 0? x : x+1,y+1); 
			
					if(m->c2 == 0){
						prev_x = x;
						prev_y = y;
		
						if(y%2 == 0){
							x;
							y++;
						}
						else{
							x++;
							y++;
						}
					}
					printf("dir : down + %s\n",k);
				
				}
			}
			else if(!strcmp(k,"left")){
			
				if((y%2 == 1 || x > 0 ) && y < h-1 ){
				
					MurHexa* m = MatHexaVal2(lab->map,y%2 == 0 ? x -1 : x,y+1); 
			
					if(m->c3 == 0){ 
						prev_x = x;
						prev_y = y;
		
						if(y%2 == 0){
							x--;
							y++;
						}
						else{
							x;
							y++;
						}
					}
					printf("dir : down + %s\n",k);
				
				}
			
			
			}
		}
		else{
		
		}
		
		printPointHexa(prev_x,prev_y,"grisf");
		printPointHexa(x,y,"vert");
				
		printf("pos : %i %i\n",x,y);
		
	}
	

	
	if (x == end_x && y == end_y)
		printf("Vous avez gagné !\n");
	else
		printf("Vous avez abandonné...\n");
}


void dijkstra_hexa(LabyrintheHexa * lab){

    // temps_debut
    gettimeofday(&temps_debut_hexa,NULL);

    MatriceHexa * dist = MatHexaAlloc(lab->map->l,lab->map->h);
    MatriceHexa * isSet = MatHexaAlloc(lab->map->l,lab->map->h);

    // Ensemble donnant le sommet avec la distance la plus petite en premiere position
    EnsHexa *plusPetit = EnsHexaAlloc();

    int l = lab->map->l;
    int h = lab->map->h;

    int V = h*l;

    int i;
    for (i = 0; i < V; i++){    	
        MatHexaSet(dist,i,MurHexaAlloc2(0,0,0,INT_MAX));
    	MatHexaSet(isSet,i,MurHexaAlloc());
    }

    MatHexaSetValue2(dist,start_x_hexa,start_y_hexa,0);
    
	if(Dij_rech_hexa)
	    printPointHexa(start_x_hexa,start_y_hexa, "vert");
    
    EnsHexaAjoute(plusPetit,start_x_hexa,start_y_hexa,0);


    while(!EnsHexaEstVide(plusPetit) && MatHexaVal2(dist,h-1,l-1)->v == INT_MAX){

        NoeudHexa * n = EnsHexaDepilePremier(plusPetit);

        int u = n->y*l + n->x;

		int ug = u - 1;
		int ud = u + 1;
		int uhg = (u/l%2 == 0) ?  u - l -1 : u - l;
		int uhd = (u/l%2 == 0) ? u - l : u - l + 1  ;
		int ubd = (u/l%2 == 0) ? u + l : u + l + 1 ;
		int ubg = (u/l%2 == 0) ? u + l - 1 : u + l ;
		//printf("%i %i\n",n->x ,n->y);
     	int min = MatHexaVal(dist,u)->v;

        MatHexaSetValue(isSet,u,1);
		// gauche 
		if (!MatHexaVal(lab->map,u)->c1 &&!MatHexaVal(isSet,ug)->v
									&& MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,ug)->v){
            
            //printf("gauche\n");
            
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,ug ,min + 1 );

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (ug)%l, (int)(ug)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((ug)%l, (int)(ug)/l , "vert");
        }
        
		// haut gauche
		if (!MatHexaVal(lab->map,u)->c2 && !MatHexaVal(isSet,uhg)->v
									&& MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,uhg)->v){
            
            
            //printf("h gauche\n");
            
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,uhg ,min + 1);

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (uhg)%l, (int)(uhg)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((uhg)%l, (int)(uhg)/l , "vert");
        }
		// haut droite
		if (!MatHexaVal(lab->map,u)->c3 && !MatHexaVal(isSet,uhd)->v
									&& MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,uhd)->v){ // OK
            
            //printf("h droite\n");
                        
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,uhd ,min +1);

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (uhd)%l, (int)(uhd)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((uhd)%l, (int)(uhd)/l , "vert");
        }
		// droite
		if (!MatHexaVal(isSet,ud)->v && !MatHexaVal(lab->map,ud)->c1
									&& MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,ud)->v){
            
            //printf("droite\n");
            
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,ud ,min + 1);

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (ud)%l, (int)(ud)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((ud)%l, (int)(ud)/l , "vert");
        }
		// bas droite
		if ((n->y%2 == 0 || n->x < l-1 ) && n->y < h-1 && !MatHexaVal(lab->map,ubd)->c2 
					&& !MatHexaVal(isSet,ubd)->v && MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,ubd)->v){
            
            //printf("b droite\n");
                        
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,ubd ,min + 1);

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (ubd)%l, (int)(ubd)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((ubd)%l, (int)(ubd)/l , "vert");
        }
		// bas gauche
		if ((n->y%2 == 1 || n->x > 0 ) && n->y < h-1 && !MatHexaVal(lab->map,ubg)->c3 
					&& !MatHexaVal(isSet,ubg)->v && MatHexaVal(dist,u)->v+1 < MatHexaVal(dist,ubg)->v){
                        
            //printf("b gauche\n");
            
			// remplace l'ancienne valeur
			MatHexaSetValue(dist ,ubg ,min + 1);

			// Ajoute le noeud
            EnsHexaAjoute(plusPetit, (ubg)%l, (int)(ubg)/l, 0);
			if(Dij_rech_hexa)
	            printPointHexa((ubg)%l, (int)(ubg)/l , "vert");
	            
        }

		NoeudHexaSuppr(n);
		if(Dij_rech_hexa)
			usleep(10*1000);


    }

    // print
    int d = MatHexaVal2(dist,h-1,l-1)->v;
	printf("\nDijsktra\n longueur du chemin : %i\n",d);
    int p = (h-1)*l+l-1;
    
	if(v_graph_hexa)
		while(d>=0){

		    printPointHexa((int)p%l,(int)p/l, "rouge");
		    
		    if( Dij_hexa)
		    	usleep(500 * 1000);
		    
		    printPointHexa((int)p%l,(int)p/l, "grisf");
		    
		    int u = p;
			int ug = u - 1;
			int uhg = (u/l%2 == 0) ?  u - l -1 : u - l;
			int uhd = (u/l%2 == 0) ? u - l : u - l + 1  ;
			int ud = u + 1;
			int ubd = (u/l%2 == 0) ? u + l : u + l + 1 ;
			int ubg = (u/l%2 == 0) ? u + l - 1 : u + l ;

			if(!d){
		        // fin
		    }// gauche
		    else if(!MatHexaVal(lab->map,u)->c1 && MatHexaVal(dist,ug)->v == d-1){
		        p = ug;
		    }// haut gauche
			else if(!MatHexaVal(lab->map,u)->c2 && MatHexaVal(dist,uhg)->v == d-1){
		        p = uhg;
		    }// haut droit	    
		    else if(!MatHexaVal(lab->map,u)->c3 && MatHexaVal(dist,uhd)->v == d-1){
		        p = uhd;
		    }// droite
			else if(!MatHexaVal(lab->map,ud)->c1 && MatHexaVal(dist,ud)->v == d-1){
		        p = ud;
		    }// bas droite	    
		    else if(!MatHexaVal(lab->map,ubd)->c2 && MatHexaVal(dist,ubd)->v == d-1){
		        p = ubd;
		    }// bas gauche
			else if(!MatHexaVal(lab->map,ubg)->c3 && MatHexaVal(dist,ubg)->v == d-1){
		        p = ubg;
		    }
		    else if(MatHexaVal(dist,p)->v == INT_MAX){
		        printf("Il n'y a pas de chemin vers la sortie\n");
		        d=0;
		    }
		    else{
		        printf("Erreur\n");
		        d=0;
		    }
		    d--;
		}

    // temps_fin
    gettimeofday(&temps_fin_hexa,NULL);
    printf(" temps d'execution: %.5f secondes\n", time_diff(temps_debut_hexa,temps_fin_hexa));

	MatHexaFree(dist);
	MatHexaFree(isSet);
	EnsHexaFree(plusPetit);

}

void A_Star_hexa(LabyrintheHexa * lab){

    // temps_debut
    /*gettimeofday(&temps_debut,NULL);

	int l = lab->map->l;
    int h = lab->map->h;

    Heap * openList = heap_init(l*h);
    Matrice * estMarque = MatAlloc(l,h);
	Matrice * closedList = MatAlloc(l,h);

    heap_push(openList,data_init(start_x,start_y,0, ((h-start_x)-2 -1)*((h-start_x)-2 -1) + ((l-start_y)-2 -1)*((l-start_y)-2 -1)) );
	MatSet2(estMarque,start_x,start_y,1);

	if(AStar_rech)
    	SetPointGraphe(start_x,start_y, "vertf");

    while(!HeapEstVide(openList) && MatVal2(closedList,h-2,l-2) == 0){


        Data * u = heap_pop(openList);
		MatSet2(closedList,u->x,u->y,u->cout);

		if (!MatVal2(lab->map,u->x-1,u->y)){

            if(!MatVal2(estMarque,u->x-1,u->y)){
                Data * v = data_init(u->x-1,u->y,u->cout+1,u->heuristique+1);
				MatSet2(estMarque,v->x,v->y,1);
                heap_push(openList,v);
                if(AStar_rech)
                    SetPointGraphe(v->x,v->y, "vertf");
            }

        }

		if (!MatVal2(lab->map,u->x,u->y-1)){

            if(!MatVal2(estMarque,u->x,u->y-1)){
                Data * v = data_init(u->x,u->y-1,u->cout+1,u->heuristique+1);
				MatSet2(estMarque,v->x,v->y,1);
                heap_push(openList,v);
                if(AStar_rech)
                    SetPointGraphe(v->x,v->y, "vertf");
            }

        }

		if (!MatVal2(lab->map,u->x+1,u->y)){
            if(!MatVal2(estMarque,u->x+1,u->y)){
                Data * v = data_init(u->x+1,u->y,u->cout+1,u->heuristique-1);
				MatSet2(estMarque,v->x,v->y,1);
                heap_push(openList,v);
                if(AStar_rech)
                    SetPointGraphe(v->x,v->y, "vertf");
            }

        }

		if (!MatVal2(lab->map,u->x,u->y+1)){

            if(!MatVal2(estMarque,u->x,u->y+1)){
                Data * v = data_init(u->x,u->y+1,u->cout+1,u->heuristique-1);
				MatSet2(estMarque,v->x,v->y,1);
                heap_push(openList,v);
                if(AStar_rech)
                    SetPointGraphe(v->x,v->y, "vertf");
            }
        }
		

		free(u);

    }


	// print
    int d = MatVal2(closedList,h-2,l-2);
	printf("\nA*\n longueur du chemin: %i\n",d);
    int p = (h-2)*l+l-2;

	if(v_graph)
		while(d>0){

		    SetPointGraphe((int)(p-l)%l, (int)(p-l)/l+1,"bleu");

			if(!(d-1)){
				SetPointGraphe(start_x,start_y, "bleu");
		        // fin
		    }
		    else if(MatVal(closedList,p-l) == d-1){
		        p = p-l;
		    }
			else if(MatVal(closedList,p-1) == d-1){
		        p = p-1;
		    }
			else if(MatVal(closedList,p+l) == d-1){
		        p = p+l;
		    }
		    else if(MatVal(closedList,p+1) == d-1){
		        p = p+1;
		    }
		    else if(!MatVal(closedList,p)){
		        printf("Il n'y a pas de chemin vers la sortie\n");
		        d=0;
		    }
		    else{
		        printf("Erreur\n");
		        d=0;
		    }
		    d--;
		}

    // temps_fin
    gettimeofday(&temps_fin,NULL);
    printf(" temps d'execution: %.5f secondes\n", time_diff(temps_debut,temps_fin));

	MatFree(estMarque);
	MatFree(closedList);
	HeapFree(openList);
*/
}

// Affiche un point sur le graphe
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
	else if (!strcmp(color,"grisf"))
    		setcolor(newcolor(0.6,0.6,0.6));
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
	else if (!strcmp(color,"grisf"))
    		setcolor(newcolor(0.6,0.6,0.6));
	
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

void printPointHexa(int x, int y, char* color){
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
	else if (!strcmp(color,"grisf"))
    		setcolor(newcolor(0.6,0.6,0.6));
	
	int l = y * 20;
	int c = x * 20;
	int col = (y%2 == 0)? 0 : 10;
		
	point(10 + c + col, 15 + l ,4);

	refresh();
}
