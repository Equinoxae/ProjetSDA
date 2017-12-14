#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "LabyrintheCarre.h"
#include "graph.h"
#include <string.h>
#include <unistd.h>

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

void set_Construction_Carre(int val){
	contruction_value = val;
}

void set_Manual_Start_carre(){
	manual_start_carre = 1;
}

void set_LinearGenCarre(){
	linear_carre = 1;
}

void set_Dij_carre(){
	Dij_carre = 1;
}

void set_Dij_rech_carre(){
	Dij_carre = 1;
	Dij_rech_carre = 1;
	v_graph_carre = 1;
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

	//initialisation fenêtre de la bonne taille
	if(v_graph_carre){
        initgraph(W*20+1 , H*20+1);
        flushgraph();
    }

	l->map = MatCarreAlloc(W,H);

	v = EnsCarreAlloc();

	LabCarreInit(l,W,H);
	
	if(contruction_value == 1){ //construire
		
		LabCarreConstruit(l, v); 
		
	}else{
		
		LabCarreConstruit2(l, v); 
	
	}
	
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
	
	int w = lab->map->l;
	int h = lab->map->h;
		
	// gauche
	if( x-1 >= 0){ //>= 0 car sinn on est dehors
	
		MurCarre * m = MatCarreVal2(lab->map,x-1, y);
	
		if(m->v == 0){ //vérif si on peut construire
			EnsCarreAjoute(v,x,y,1); //noter pos actuelle
			if(d_graph_carre)
				printCoteCarre(x,y,1,"rouge"); //afficher coté en rouge
		}
	}
	
	// haut 		
	if(y-1 >= 0){
	
		MurCarre * m = MatCarreVal2(lab->map,x, y-1);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,2);
			if(d_graph_carre)
				printCoteCarre(x,y,2,"rouge");
		}
	}
	
	// droite
	if( x+1 < w){
	
		MurCarre * m = MatCarreVal2(lab->map,x+1, y);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,3);
			if(d_graph_carre)
				printCoteCarre(x,y,3,"rouge");
		}
	}
	
	// bas 
	if(y+1 < h){
	
		MurCarre * m = MatCarreVal2(lab->map,x, y+1);
	
		if(m->v == 0){
			EnsCarreAjoute(v,x,y,4);
			if(d_graph_carre)
				printCoteCarre(x,y,4,"rouge");
		}
	}
}

// granularise le labyrinthe avec un nombre de graine
void GranulariseCarre(LabyrintheCarre *lab ,EnsCarre *v, int nb){ // nada 
}

// Construit les murs du labyrinthe depuis les graines
void LabCarreConstruit(LabyrintheCarre *lab ,EnsCarre *v){
	
	// trouve le premier mur et ajoute ses cotés en liste
	EnsCarreAjoute(v,lab->map->l/2,lab->map->h/2,0);

	
	while(!EnsCarreEstVide(v)){
		NoeudCarre * n = EnsCarreTirage(v,linear_carre);
		
		//NoeudCarre * n = EnsCarreTirage(v,0);  //n = case que j'ai tirée
		
		MurCarre * m, * voisin, * first;
		switch(n->cote)
		{
			case 1: //suppression case de gauche
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;

				voisin = MatCarreVal2(lab->map,n->x-1,n->y);
				if(voisin->v == 0){ //si == 0, il n'est pas marqué 
					m->c1 =0; //péter le mur à gauche: vérif sur le bloc actuel
					voisin->v = 1; 
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,1,"blanc"); //màj affichage
					verifCarreTour(lab,v,n->x-1,n->y); //vérifier tour
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,1,"noir");
				}
				
				break;
			case 2: //suppression case du haut
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
			
				voisin = MatCarreVal2(lab->map,n->x,n->y-1);
				if(voisin->v == 0){ //si == 0, il n'est pas marqué 
					m->c2 =0; //péter le mur à gauche
					voisin->v = 1; 
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,2,"blanc"); //màj affichage
					verifCarreTour(lab,v,n->x,n->y-1); //vérifier tour
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,2,"noir");
				}
				
				break;

			case 3: //suppression case de droite
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
			
				voisin = MatCarreVal2(lab->map,n->x+1,n->y);
				if(voisin->v == 0){
					voisin->c1 =0;
					voisin->v = 1; 
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,3,"blanc");
					verifCarreTour(lab,v,n->x+1,n->y);
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,3,"noir");
				}
				break;
				
			case 4: //suppression case du bas
				m = MatCarreVal2(lab->map,n->x,n->y);
				m->v = 1;
			
				voisin = MatCarreVal2(lab->map,n->x,n->y+1); //+1 car on va ver sle bas: -1 c'est qd on vers le haut 
				if(voisin->v == 0){ //si == 0, il n'est pas marqué 
					voisin->c2 =0; //péter le mur à gauche
					voisin->v = 1; //passer la valeur du voisin à 1
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,4,"blanc"); //màj affichage
					verifCarreTour(lab,v,n->x,n->y+1); //vérifier tour
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,4,"noir");
				}
				break;

			case 0:
				first = MatCarreVal2(lab->map,n->x,n->y);
				first->v = 1;
				verifCarreTour(lab,v,n->x,n->y);
				break;		
		}
	
		//waitgraph();
		if(d_graph_carre)
			usleep(5*1000);
			//waitgraph();
	
	}
}


// Construit les murs du labyrinthe depuis les graines
void LabCarreConstruit2(LabyrintheCarre *lab ,EnsCarre *v){
	
	// trouve le premier mur et ajoute ses cotés en liste


	for (int i=0; i<lab->map->l*lab->map->h; i++){
		
		MatCarreSetValue(lab->map, i, i); //i = position dans tableau
		verifCarreTour(lab,v,i%lab->map->l,i/lab->map->h); //vérifier tour
	
	}
	
	while(!EnsCarreEstVide(v)){
		NoeudCarre * n = EnsCarreTirage(v,0);
		
		MurCarre * m, * voisin;
		int old; //ancienne valeur
		int new; //new val
		
		switch(n->cote)
		{
			case 1: //suppression case de gauche
				m = MatCarreVal2(lab->map,n->x,n->y);

				voisin = MatCarreVal2(lab->map,n->x-1,n->y);
				if(voisin->v != m->v){ //si == 0, il n'est pas marqué 
					m->c1 =0; //péter le mur à gauche: vérif sur le bloc actuel
					old = voisin->v;
					new = m->v;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,1,"blanc"); //màj affichage
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,1,"noir");
				}
				
				break;
			case 2: //suppression case du haut
				m = MatCarreVal2(lab->map,n->x,n->y);
			
				voisin = MatCarreVal2(lab->map,n->x,n->y-1);
				if(voisin->v != m->v){ //si == 0, il n'est pas marqué 
					m->c2 =0; //péter le mur à gauche
					old = voisin->v;
					new = m->v;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,2,"blanc"); //màj affichage
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,2,"noir");
				}
				
				break;

			case 3: //suppression case de droite
				m = MatCarreVal2(lab->map,n->x,n->y);
			
				voisin = MatCarreVal2(lab->map,n->x+1,n->y);
				if(voisin->v != m->v){
					voisin->c1 =0;
					old = voisin->v;
					new = m->v;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,3,"blanc");
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,3,"noir");
				}
				break;
				
			case 4: //suppression case du bas
				m = MatCarreVal2(lab->map,n->x,n->y);
			
				voisin = MatCarreVal2(lab->map,n->x,n->y+1); //+1 car on va ver sle bas: -1 c'est qd on vers le haut 
				if(voisin->v != m->v){ //si == 0, il n'est pas marqué 
					voisin->c2 =0; //péter le mur à gauche
					old = voisin->v;
					new = m->v;
					if(v_graph_carre)
						printCoteCarre(n->x,n->y,4,"blanc"); //màj affichage
				} 
				else{
					if(d_graph_carre)
						printCoteCarre(n->x,n->y,4,"noir");
				}
				break;	
		}
	
		for (int i=0; i<lab->map->l*lab->map->h; i++){
			
			MurCarre * m2 = MatCarreVal(lab->map, i);
			if(m2->v == old)
				m2->v = new;
		}
	
		if(d_graph_carre)
			usleep(5*1000);
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
void dijkstraCarre(LabyrintheCarre * lab){
	
		/*ich bin die Beste une ich weiss alles über dir 
		ich bin Anne ich mag Katze, ich spiele Klavier
		ich kann deutsch und ich habe deutsch in der schule gelernt
		ich war auch drei Monate in Berlin um ein Praktikum in Web Entwicklung zu machen und mein deutsch zu verbessern
		es war toll. Mein Praktikumsleiter war sehr froh, süss mit mir und ich habe viel gelernt*/
	
	 // temps_debut
    /*gettimeofday(&temps_debut_carre,NULL);

    MatriceCarre * dist = MatCarreAlloc(lab->map->l,lab->map->h);
    MatriceCarre * isSet = MatCarreAlloc(lab->map->l,lab->map->h);

    // Ensemble donnant le sommet avec la distance la plus petite en premiere position
    EnsCarre *plusPetit = EnsCarreAlloc();

    int V = lab->map->l*lab->map->h;

    int i;
    for (i = 0; i < V; i++)
        MatCarreSet(dist, i, MurCarreAlloc2(0, 0, NT_MAX));
		MatCarreSet(isSet, i, MurCarreAlloc());

    MatCarreSet2(dist,start_x_carre,start_y_carre,0);
	if(Dij_rech_carre)
	    SetCarrePointGraphe(start_x_carre,start_y_carre, "vert");
    EnsCarreAjoute(plusPetit,start_x_carre,start_y_carre);

    int l = lab->map->l;
    int h = lab->map->h;



    while(!EnsEstVide(plusPetit) && MatCarreVal2(dist,h-2,l-2)->v == INT_MAX){

        NoeudCarre * n = EnsCarreDepilePremier(plusPetit);

        int u = n->x*l+n->y;
        int min = MatCarreVal(dist,u);

		NoeudCarreSuppr(n);

        MatCarreSet(isSet,u,1);

        if (!MatCarreVal(isSet,u+1) && !MatCarreVal(lab->map,u+1)
                                    && MatCarreVal(dist,u)+1 < MatCarreVal(dist,u+1)){
            MatCarreSet(dist ,u+1 ,MatCarreVal(dist,u)+1);
            EnsCarreAjoute(plusPetit, (int)(u+1)/l , (u+1)%l);
			if(Dij_rech_carre)
	            SetCarrePointGraphe((u+1)%l, (int)(u+1)/l , "vert");
        }

        if (!MatCarreVal(isSet,u-1) && !MatCarreVal(lab->map,u-1)
                                    && MatCarreVal(dist,u)+1 < MatVal(dist,u-1)){
            MatCarreSet(dist,u-1,MatCarreVal(dist,u)+1);
            EnsCarreAjoute(plusPetit, (int)(u-1)/l , (u-1)%l);
			if(Dij_rech_carre)
			    SetCarrePointGraphe((int)(u-1)%l,(int)(u-1)/l, "vert");
        }

        if (!MatCarreVal(isSet,u+l) && !MatCarreVal(lab->map,u+l)
                                    && MatCarreVal(dist,u)+1 < MatCarreVal(dist,u+l)){
            MatCarreSet(dist,u+l,MatCarreVal(dist,u)+1);
            EnsCarreAjoute(plusPetit, (int)(u+l)/l , (u+l)%l);
			if(Dij_rech_carre)
	        	SetCarrePointGraphe((int)(u+l)%l,(int)(u+l)/l, "vert");
        }


        if (!MatCarreVal(isSet,u-l) && !MatCarreVal(lab->map,u-l)
                                    && MatCarreVal(dist,u)+1 < MatCarreVal(dist,u-l)){
            MatCarreSet(dist,u-l,MatCarreVal(dist,u)+1);
            EnsCarreAjoute(plusPetit, (int)(u-l)/l , (u-l)%l);
			if(Dij_rech_carre)
	            SetCarrePointGraphe((int)(u-l)%l,(int)(u-l)/l, "vert");
        }
    }

    // print
    int d = MatCarreVal2(dist,h-2,l-2);
	printf("\nDijsktra\n longueur du chemin : %i\n",d);
    int p = (h-2)*l+l-2;
	if(v_graph_carre)
		while(d>=0){

		    SetCarrePointGraphe((int)(p-l)%l,(int)(p-l)/l+1, "rouge");

			if(!d){
		        // fin
		    }
		    
		    else if(MatCarreVal(dist,p-l)->v == d-1){
		        p = p-l;
		    }
			else if(MatCarreVal(dist,p-1)->v == d-1){
		        p = p-1;
		    }	    
		    else if(MatCarreVal(dist,p+l)->v == d-1){
		        p = p+l;
		    }
			else if(MatCarreVal(dist,p+1)->v == d-1){
		        p = p+1;
		    }
		    else if(MatCarreVal(dist,p)->v == INT_MAX){
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
    gettimeofday(&temps_fin_carre,NULL);
    printf(" temps d'execution: %.5f secondes\n", time_diff_carre(temps_debut_carre,temps_fin_carre));

	MatCarreFree(dist);
	MatCarreFree(isSet);
	EnsCarreFree(plusPetit);*/
	
}

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
	
	//afficher case : 3 lignes à dessiner
	line(0 + c, 0 + l, 0 + c, 20 + l); //x1, y1, x2, y2 coté 1
	line(20 + c, 0 + l, 0 + c, 0 + l); //x1, y1, x2, y2 coté 2

	// ligne du bas
	if( y = h-1)
		line(0 + c,  20 + l , 20 + c, 20 + l);

	//ligne de droite
	if( x = w-1)
		line(20 + c, 20 + l, 20 + c,  0 + l);

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
	
	switch(cot){
		case 1:
			line(0 + c, 1 + l, 0 + c, 19 + l); 	// '|' côté de 
			break;
		case 2:
			line(1 + c, 0 + l , 19 + c, 0 + l); 	// '-' côté du haut
			break;
		case 3:
			line(20 + c, 19 + l, 20 + c,  1 + l); 	// '|' côté de droite
			break;
		case 4:
			line(1 + c, 20 + l, 19 + c, 20 + l); 	// '_' côté du bas
			break;
	}
	
	refresh();
}

