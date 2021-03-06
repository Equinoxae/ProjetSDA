 #include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "Labyrinthe.h"
#include "graph.h"
#include "Heap.h"
#include <string.h>

// Statics

static struct timeval temps_debut,temps_fin;

/* affichage du graph */
static int v_graph = 0;
static int d_graph = 0;

static int case_width = 3;

// Dijkstra 
static int Dij = 0;
static int Dij_rech = 0;

// A*
static int AStar = 0;
static int AStar_rech = 0;

// Manual Research 
static int manual_search = 0;

// Execution automatique
static int Auto = 0;

// Start
static int start_x = 1;
static int start_y = 1;
static int manual_start = 0;

// Linear
static int linear = 0;

// Accesseur
void set_v(){
    v_graph = 1;
}

void set_d(){
    v_graph = 1;
    d_graph = 1;
}

void set_Dij(){
	Dij = 1;
}

void set_Dij_rech(){
	Dij = 1;
	Dij_rech = 1;
	v_graph = 1;
}

void set_AStar(){
	AStar = 1;
}

void set_AStar_rech(){
	AStar = 1;
	AStar_rech = 1;
	v_graph = 1;
}

void set_Manual_rech(){
	set_Manual_Start();
	set_v();
	manual_search = 1;
}

void set_Auto(){
	Auto = 1;
}

void set_Start(int x,int y){
	start_x = x;
	start_y = y;
}


void set_Manual_Start(){
	manual_start = 1;
}

void set_LinearGen(){
	linear = 1;
}

void set_CaseWidth(int x){
	if(x < 0 || x > 20){
		printf("Taille de case invalide ! La largeur et la hauteur de la case doit être >= 0 et <= 20\n");
	    exit(6);
	}

	case_width = x;	
}

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff/1000000;
}

Labyrinthe *LabCreate(int w,int h,float r){
    // init random
    srand(time(NULL));

    // temps_debut
    gettimeofday(&temps_debut,NULL);

    //var
    Labyrinthe * l = malloc(sizeof(Labyrinthe));
    Ens * v; // case vide (constructible)

    // taille bordure
    int W = w + 2;
    int H = h + 2;

    if(v_graph){
        initgraph((W)*case_width,(H)*case_width);
        flushgraph();
    }

    // init
    l->map = MatAlloc(W,H);
    // Ensemble vide
    v = EnsAlloc();

    // Tour + Graine
    LabInit( l, W, H);

    Granularise(l , v , (int)( w * h * r ) );

    // Expention graine
    LabConstruit(l, v);

    // temps_fin
    gettimeofday(&temps_fin,NULL);
    printf("Génération\n temps d'execution: %.5f secondes\n", time_diff(temps_debut,temps_fin));;


    EnsFree(v);

    return l;
}

void LabFree(Labyrinthe *lab){
	MatFree(lab->map);
    free(lab);
}

// Tests

int EstConstruit(Labyrinthe *lab , int x ,int y){
    return MatVal2(lab->map , x , y );
}

int EstConstructible(Labyrinthe *lab , Ens *v, Noeud * point, int init){

    int x = point->x;
    int y = point->y;
    int w = MatGetL(lab->map);
    int h = MatGetH(lab->map);

    if(EstConstruit(lab,x,y) || ( !init && (x<= 1|| y <= 1 || x >= w-2 || y >= h-2) ) )
        return 0;

    int res = 0;

    int adjcent[4] = {0,0,0,0}; // W , N , E , S <OK>
    int adj_count = 0;

    // Case Gauche
    if( EstConstruit(lab , x , y-1 ) ){
        adjcent[0] = 1;
        adj_count++;
    }
    // Case En-Haut
    if( EstConstruit(lab , x-1 , y ) ){
        adjcent[1] = 1;
        adj_count++;
    }
    // Case Droite
    if( EstConstruit(lab , x , y+1 ) ){
        adjcent[2] = 1;
        adj_count++;
    }
    // Case En-Bas
    if( EstConstruit(lab , x+1 , y ) ){
        adjcent[3] = 1;
        adj_count++;
    }

    if(adj_count == 0){

        if(init){

            // Case Haut Gauche
            if( EstConstruit(lab , x-1 , y-1 ) ){
                res += 1;
            }
            // Case En-Haut Droite
            if( EstConstruit(lab , x-1 , y+1 ) ){
                res +=1;
            }
            // Case Bas Droite
            if( EstConstruit(lab , x+1 , y+1 ) ){
                res +=1;
            }
            // Case Bas Gauche
            if( EstConstruit(lab , x+1 , y-1 ) ){
                res +=1;
            }

            res = !(res >= 1);

        }
    }
    else if(adj_count == 1){ // si il y a strictement un coté : Construit / Supprime

        //<OK>
        if(adjcent[0] == 1){ // Si a gauche
            res = (!EstConstruit(lab,x-1,y+1) && !EstConstruit(lab,x+1,y+1) );
        }
        else if(adjcent[1] == 1){ // Si en-haut
            res = (!EstConstruit(lab,x+1,y-1) && !EstConstruit(lab,x+1,y+1) );
        }
        else if(adjcent[2] == 1){ // si a droite
            res = (!EstConstruit(lab,x-1,y-1) && !EstConstruit(lab,x+1,y-1) );
        }
        else if(adjcent[3] == 1){ // si en bas
            res = (!EstConstruit(lab,x-1,y-1) && !EstConstruit(lab,x-1,y+1) );
        }
    }
    else // plus d'un coté : Supprime
    {
        res = 0;
    }

    return res;
}

void verifTour(Labyrinthe *lab  , Ens *v, Noeud * point,int init){

    int x = point->x;
    int y = point->y;

    // Case En-Haut
    if( !EstConstruit(lab , x , y-1 ) ){
		Noeud * g = NoeudInit(x,y-1);
        if(EstConstructible(lab,v,g,init)){
            EnsAjoute(v,x,y-1);
            if(d_graph)
                SetPointGraphe(x,y-1,"rouge");
        }
        
		NoeudSuppr(g);
    }

	// Case Gauche
    if( !EstConstruit(lab , x-1 , y ) ){
		Noeud * h = NoeudInit(x-1,y);
        if(EstConstructible(lab,v,h,init)){
            EnsAjoute(v,x-1,y);
            if(d_graph)
                SetPointGraphe(x-1,y,"rouge");
        }
        
		NoeudSuppr(h);
    }

    
    // Case En-Bas
    if( !EstConstruit(lab , x , y+1 ) ){
		Noeud * d = NoeudInit(x,y+1);
        if(EstConstructible(lab,v,d,init)){
            EnsAjoute(v,x,y+1);
            if(d_graph)
                SetPointGraphe(x,y+1,"rouge");
        }
        
		NoeudSuppr(d);
    }

	// Case Droite
    if( !EstConstruit(lab , x+1 , y )){
		Noeud * b = NoeudInit(x+1,y);
        if(EstConstructible(lab,v,b,init)){

            EnsAjoute(v,x+1,y);
            if(d_graph)
                SetPointGraphe(x+1,y,"rouge");
        }
        
		NoeudSuppr(b);
    }

	NoeudSuppr(point);
}

// Init matice
void LabInit(Labyrinthe *lab, int w ,int h){

    int i;

    for(i = 0; i < w ; i++){
		MatSet2(lab->map, i, 0, 1);

		if(v_graph)
           	SetPointGraphe(i,0,"noir");
	}

    for(i = 1; i < h-1 ; i++){
		MatSet2(lab->map,w-1, i, 1);

		if(v_graph)
           	SetPointGraphe(w-1,i,"noir");
	}


	for(i = w-1; i >= 0; i--){
		MatSet2(lab->map, i, h-1, 1);

		if(v_graph)
           	SetPointGraphe(i,h-1,"noir");
	}

	for(i = h-2; i > 0; i--){
		MatSet2(lab->map, 0, i, 1);

		if(v_graph)
           	SetPointGraphe(0, i,"noir");
	}

}

void Granularise(Labyrinthe *lab  , Ens *v, int nb){

	int h = lab->map->h;
	int l = lab->map->l;

	int gg = rand()%(h-10)+5;
	int gh = rand()%(l-10)+5;
	int gd = rand()%(h-10)+5;
	int gb = rand()%(l-10)+5;

	// Noeud gauche

	MatSet2(lab->map, 1 , gg , 1);

	if(v_graph)
		SetPointGraphe(1, gg ,"noir");

	verifTour(lab,v,NoeudInit(1 , gg),1);

	// Noeud haut

	MatSet2(lab->map, gh, 1 , 1);

	if(v_graph)
		SetPointGraphe(gh , 1 ,"noir");

	verifTour(lab,v,NoeudInit(gh, 1),1);

	// Noeud droite

	MatSet2(lab->map, l-2 , gd, 1);
	if(v_graph)
		SetPointGraphe(l-2 , gd,"noir");

	verifTour(lab,v,NoeudInit(l-2 , gd),1);

	// Noeud bas

	MatSet2(lab->map, gb, h-2  , 1);

	if(v_graph)
		SetPointGraphe(gb, h-2 ,"noir");

	verifTour(lab,v,NoeudInit(gb, h-2 ),1);

    int count = 0;

    while( count < nb){

        Noeud * tirage = NoeudInit(rand()%(l-2)+1,rand()%(h-2)+1);

        if( EstConstructible(lab , v, tirage,1 ) ){

            MatSet2(lab->map, tirage->x ,tirage->y , 1);

        	if(v_graph)
        		SetPointGraphe(tirage->x,tirage->y,"noir");

			verifTour(lab,v,tirage,1);
            count++;

        }
        else if(d_graph && !EstConstruit(lab,tirage->x,tirage->y)){
            SetPointGraphe(tirage->x,tirage->y,"blanc");
        }
    }
}

// construit
void LabConstruit(Labyrinthe *lab  , Ens * v){

    while( !EnsEstVide(v) ){
        Noeud * tirage = EnsTirage(v,linear);

        if(EstConstructible(lab,v,tirage,0)){
            MatSet2(lab->map, tirage->x ,tirage->y , 1);
        	if(v_graph)
        		SetPointGraphe(tirage->x,tirage->y,"noir");
            verifTour(lab ,v,tirage,0);
        }
        else if(d_graph && !EstConstruit(lab,tirage->x,tirage->y)){
            SetPointGraphe(tirage->x,tirage->y,"blanc");
			NoeudSuppr(tirage);
        }
		else
			NoeudSuppr(tirage);

    }

}

void LabPrint(Labyrinthe *lab){

    int w = MatGetL(lab->map);
    int h = MatGetH(lab->map);

    int i,j;
    for(i = 0; i < w ; i++){
        printf("%i\t: ", i );
        for(j = 0 ; j < h ; j++){
            char c = EstConstruit(lab,i,j) ? '0' : ' ';

            printf("%c ", c );
        }
        printf("\n");
    }
}

void SetPointGraphe(int x, int y, char * color){

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

	fullrectangle(x*case_width,y*case_width,case_width,case_width);

    /*putpixel(x*3,y*3);
    putpixel(x*3+1,y*3);
    putpixel(x*3+2,y*3);
    putpixel(x*3,y*3+1);
    putpixel(x*3+1,y*3+1);
    putpixel(x*3+2,y*3+1);
    putpixel(x*3,y*3+2);
    putpixel(x*3+1,y*3+2);
    putpixel(x*3+2,y*3+2);*/

    refresh();
}

void lanceRecherche(Labyrinthe *lab){


	if(manual_search){
		
		int x, y;
		
		int * px = &x;
		int * py = &y;
		
		getClic(px,py);
		
		while(EstConstruit(lab, x/case_width,y/case_width)){
			getClic(px,py);
		}
		
		set_Start(x/case_width,y/case_width);
		
		SetPointGraphe(start_x,start_y,"vert");

		printf("s = %i %i \n",start_x,start_y );
		
		recherche_manuelle(lab);
		
	}
	else{

		if(v_graph && !Auto && Dij)
			waitgraph();

		if(Dij)
			dijkstra(lab);

		if(v_graph && !Auto && AStar)
			waitgraph();

		if(AStar)
			A_Star(lab);

		
	}
	
	if(v_graph){
			waitgraph();
			closegraph();
		}

}
void recherche_manuelle(Labyrinthe * lab){
	
	int x = start_x;
	int y = start_y;
	int prev_x = 0;
	int prev_y = 0;

	int end_x = lab->map->l-2;
	int end_y = lab->map->h-2;
	char * k ="";
	
	SetPointGraphe(end_x,end_y,"rouge");

	while ( !(x == end_x && y == end_y) && strcmp(k,"esc")){
		printf("Appuiez sur une touche\n");
		
		//printf("dir : %s\n",k);
				
		if(!strcmp(k,"left")){
			if(!EstConstruit(lab,x-1,y)){
				
				prev_x = x;
				prev_y = y;
				
				x--;
				printf("dir : %s\n",k);
			}
		}
		else if(!strcmp(k,"right")){
			if(!EstConstruit(lab,x+1,y)){
				
				prev_x = x;
				prev_y = y;
				
				x++;
				printf("dir : %s\n",k);
			}
		}
		else if(!strcmp(k,"up")){
			if(!EstConstruit(lab,x,y-1)){
				
				prev_x = x;
				prev_y = y;
				
				y--;
				printf("dir : %s\n",k);
			}
		}
		else if(!strcmp(k,"down")){
			if(!EstConstruit(lab,x,y+1)){				
				prev_x = x;
				prev_y = y;
				
				y++;
				printf("dir : %s\n",k);
			}
		}
		else{
		
		}
		
		SetPointGraphe(prev_x,prev_y,"gris");
		SetPointGraphe(x,y,"vert");
		
		printf("pos : %i %i\n",x,y);
		
		k = getKey();
		
	}
	
	
	if (x == end_x && y == end_y)
		printf("Vous avez gagné !\n");
	else
		printf("Vous avez abandonné...\n");
}
void dijkstra(Labyrinthe * lab){

    // temps_debut
    gettimeofday(&temps_debut,NULL);

    Matrice * dist = MatAlloc(lab->map->l,lab->map->h);
    Matrice * isSet = MatAlloc(lab->map->l,lab->map->h);

    // Ensemble donnant le sommet avec la distance la plus petite en premiere position
    Ens *plusPetit = EnsAlloc();

    int V = lab->map->l*lab->map->h;

    int i;
    for (i = 0; i < V; i++)
        MatSet(dist,i,INT_MAX);

    MatSet2(dist,start_x,start_y,0);
	if(Dij_rech)
	    SetPointGraphe(start_x,start_y, "vert");
    EnsAjoute(plusPetit,start_x,start_y);

    int l = lab->map->l;
    int h = lab->map->h;
    
    while(!EnsEstVide(plusPetit) && MatVal2(dist,l-2,h-2) == INT_MAX){

        Noeud * n = EnsDepilePremier(plusPetit);

        int u = n->y*l+n->x;

		NoeudSuppr(n);

        MatSet(isSet,u,1);

        if (!MatVal(isSet,u+1) && !MatVal(lab->map,u+1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+1)){
            MatSet(dist ,u+1 ,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u+1)%l , (u+1)/l);
			if(Dij_rech)
	            SetPointGraphe((u+1)%l, (int)(u+1)/l , "vert");
        }

        if (!MatVal(isSet,u-1) && !MatVal(lab->map,u-1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-1)){
            MatSet(dist,u-1,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u-1)%l , (u-1)/l);
			if(Dij_rech)
			    SetPointGraphe((int)(u-1)%l,(int)(u-1)/l, "vert");
        }

        if (!MatVal(isSet,u+l) && !MatVal(lab->map,u+l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+l)){
            MatSet(dist,u+l,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u+l)%l , (u+l)/l);
			if(Dij_rech)
	        	SetPointGraphe((int)(u+l)%l,(int)(u+l)/l, "vert");
        }


        if (!MatVal(isSet,u-l) && !MatVal(lab->map,u-l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-l)){
            MatSet(dist,u-l,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u-l)%l , (u-l)/l);
			if(Dij_rech)
	            SetPointGraphe((int)(u-l)%l,(int)(u-l)/l, "vert");
        }


    }

    // print
    int d = MatVal2(dist,l-2,h-2);
	printf("\nDijsktra\n longuleur du chemin : %i\n",d);
    int p = (l)*(h-2)+l-2;
	if(v_graph)
		while(d>=0){

		    SetPointGraphe((int)(p)%l,(int)(p)/l, "rouge");

			if(!d){
			// fin
		    }
		    else if(MatVal(dist,p) == INT_MAX){
		        printf("Il n'y a pas de chemin vers la sortie\n");
		        d=0;
		    }		    
		    else if(MatVal(dist,p-l) == d-1){
		        p = p-l;
		    }
			else if(MatVal(dist,p-1) == d-1){
		        p = p-1;
		    }	    
		    else if(MatVal(dist,p+l) == d-1){
		        p = p+l;
		    }
			else if(MatVal(dist,p+1) == d-1){
		        p = p+1;
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

	MatFree(dist);
	MatFree(isSet);
	EnsFree(plusPetit);

}

void A_Star(Labyrinthe * lab){

    // temps_debut
    gettimeofday(&temps_debut,NULL);

	int l = lab->map->l;
    int h = lab->map->h;

    Heap * openList = heap_init(l*h);
    Matrice * estMarque = MatAlloc(l,h);
	Matrice * closedList = MatAlloc(l,h);

    heap_push(openList,data_init(start_x,start_y,0, ((l-start_x)-2 -1)*((l-start_x)-2 -1) + ((h-start_y)-2 -1)*((h-start_y)-2 -1)) );
	MatSet2(estMarque,start_x,start_y,1);

	if(AStar_rech)
    	SetPointGraphe(start_x,start_y, "vertf");

    while(!HeapEstVide(openList) && MatVal2(closedList,l-2,h-2) == 0){

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
    int d = MatVal2(closedList,l-2,h-2);
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

}
