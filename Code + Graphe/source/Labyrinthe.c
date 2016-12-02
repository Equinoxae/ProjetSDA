 #include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "Labyrinthe.h"
#include "graph.h"
#include <string.h>

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

void set_Auto(){
	Auto = 1;
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
        initgraph((W)*3,(H)*3);
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
    long int dif_sec;
    printf("Génération : %ld.%ld secondes\n", dif_sec = ( temps_fin.tv_sec - temps_debut.tv_sec) ,
        (temps_fin.tv_usec  + 1000000 * dif_sec) - temps_debut.tv_usec );


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

    if(EstConstruit(lab,x,y) || ( !init && (x<= 1|| y <= 1 || x >= h-2 || y >= w-2) ) )
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

    int cb;
    int x = point->x;
    int y = point->y;

    // Case Gauche
    if( !EstConstruit(lab , x , y-1 ) ){
		Noeud * g = NoeudInit(x,y-1);
        if(EstConstructible(lab,v,g,init)){
            EnsAjoute(v,x,y-1);
            if(d_graph)
                SetPointGraphe(x,y-1,"rouge");
        }
        else{
            EnsSuppr(v,x,y-1);
            if(d_graph)
                SetPointGraphe(x,y-1,"blanc");
        }
		NoeudSuppr(g);
    }
    // Case En-Haut
    if( !EstConstruit(lab , x-1 , y ) ){
		Noeud * h = NoeudInit(x-1,y);
        if(EstConstructible(lab,v,h,init)){
            EnsAjoute(v,x-1,y);
            if(d_graph)
                SetPointGraphe(x-1,y,"rouge");
        }
        else{
            EnsSuppr(v,x-1,y);
            if(d_graph)
                SetPointGraphe(x-1,y,"blanc");
        }
		NoeudSuppr(h);
    }
    // Case Droite
    if( !EstConstruit(lab , x , y+1 ) ){
		Noeud * d = NoeudInit(x,y+1);
        if(EstConstructible(lab,v,d,init)){
            EnsAjoute(v,x,y+1);
            if(d_graph)
                SetPointGraphe(x,y+1,"rouge");
        }
        else{
            EnsSuppr(v,x,y+1);
            if(d_graph)
                SetPointGraphe(x,y+1,"blanc");
        }
		NoeudSuppr(d);
    }
    // Case En-Bas
    if( !EstConstruit(lab , x+1 , y )){
		Noeud * b = NoeudInit(x+1,y);
        if(EstConstructible(lab,v,b,init)){

            EnsAjoute(v,x+1,y);
            if(d_graph)
                SetPointGraphe(x+1,y,"rouge");
        }
        else{
            EnsSuppr(v,x+1,y);
            if(d_graph)
                SetPointGraphe(x+1,y,"blanc");
        }
		NoeudSuppr(b);
    }

	NoeudSuppr(point);
}

// Init matice
void LabInit(Labyrinthe *lab, int w ,int h){

    int i;

    for(i = 0; i < w ; i++){
		MatSet2(lab->map, 0, i, 1);

		if(v_graph)
           	SetPointGraphe(0,i,"noir");
	}

    for(i = 1; i < h-1 ; i++){
		MatSet2(lab->map, i, w-1, 1);

		if(v_graph)
           	SetPointGraphe(i,w-1,"noir");
	}


	for(i = w-1; i >= 0; i--){
		MatSet2(lab->map, h-1, i, 1);

		if(v_graph)
           	SetPointGraphe(h-1,i,"noir");
	}

	for(i = h-2; i > 0; i--){
		MatSet2(lab->map,i, 0, 1);

		if(v_graph)
           	SetPointGraphe(i,0,"noir");
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

	MatSet2(lab->map, gg , 1 , 1);

	if(v_graph)
		SetPointGraphe(gg,1,"noir");

	verifTour(lab,v,NoeudInit(gg,1),1);

	// Noeud haut

	MatSet2(lab->map, 1 , gh , 1);

	if(v_graph)
		SetPointGraphe(1 , gh ,"noir");

	verifTour(lab,v,NoeudInit(1,gh),1);

	// Noeud droite

	MatSet2(lab->map, gd , l-2 , 1);

	if(v_graph)
		SetPointGraphe(gd,l-2,"noir");

	verifTour(lab,v,NoeudInit(gd,l-2),1);

	// Noeud bas

	MatSet2(lab->map, h-2 , gb , 1);

	if(v_graph)
		SetPointGraphe(h-2 , gb ,"noir");

	verifTour(lab,v,NoeudInit(h-2,gb),1);

    int count = 0;
    int res;

    while( count < nb /*&& !EnsEstVide(v)*/){

        Noeud * tirage = NoeudInit(rand()%(h-2)+1,rand()%(l-2)+1);

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

		//NoeudSuppr(tirage);
    }
}

// construit
void LabConstruit(Labyrinthe *lab  , Ens * v){

    int res;

    while( !EnsEstVide(v) ){
        Noeud * tirage = EnsTirage(v);

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


    putpixel(y*3,x*3);
    putpixel(y*3,x*3+1);
    putpixel(y*3,x*3+2);
    putpixel(y*3+1,x*3);
    putpixel(y*3+1,x*3+1);
    putpixel(y*3+1,x*3+2);
    putpixel(y*3+2,x*3);
    putpixel(y*3+2,x*3+1);
    putpixel(y*3+2,x*3+2);

    refresh();
}

void lanceRecherche(Labyrinthe *lab){

	if(!Auto && Dij)
		waitgraph();

	if(Dij)
		dijkstra(lab);

	if(!Auto && AStar)
		waitgraph();

	if(AStar)
		A_Star(lab);

	if(v_graph){
		waitgraph();
		closegraph();
	}


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

    MatSet2(dist,1,1,0);
	if(Dij_rech)
	    SetPointGraphe(1,1, "vert");
    EnsAjoute(plusPetit,1,1);

    int l = lab->map->l;
    int h = lab->map->h;



    while(!EnsEstVide(plusPetit) && MatVal2(dist,h-2,l-2) == INT_MAX){

        Noeud * n = EnsDepilePremier(plusPetit);

        int u = n->x*l+n->y;
        int min = MatVal(dist,u);

		NoeudSuppr(n);

        MatSet(isSet,u,1);

        if (!MatVal(isSet,u+1) && !MatVal(lab->map,u+1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+1)){
            MatSet(dist ,u+1 ,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u+1)/l , (u+1)%l);
			if(Dij_rech)
	            SetPointGraphe((int)(u+1)/l , (u+1)%l, "vert");
        }

        if (!MatVal(isSet,u-1) && !MatVal(lab->map,u-1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-1)){
            MatSet(dist,u-1,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u-1)/l , (u-1)%l);
			if(Dij_rech)
			    SetPointGraphe((int)(u-1)/l,(int)(u-1)%l, "vert");
        }

        if (!MatVal(isSet,u+l) && !MatVal(lab->map,u+l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+l)){
            MatSet(dist,u+l,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u+l)/l , (u+l)%l);
			if(Dij_rech)
	        	SetPointGraphe((int)(u+l)/l,(int)(u+l)%l, "vert");
        }


        if (!MatVal(isSet,u-l) && !MatVal(lab->map,u-l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-l)){
            MatSet(dist,u-l,MatVal(dist,u)+1);
            EnsAjoute(plusPetit, (int)(u-l)/l , (u-l)%l);
			if(Dij_rech)
	            SetPointGraphe((int)(u-l)/l,(int)(u-l)%l, "vert");
        }


    }

    // print
    int d = MatVal2(dist,h-2,l-2);
	printf("Dijsktra : %i\n",d);
    int p = (h-2)*l+l-2;
	if(v_graph)
		while(d>=0){

		    SetPointGraphe((int)(p-l)/l+1,(int)(p-l)%l, "rouge");

			if(!d){
		        // fin
		    }
		    else if(MatVal(dist,p-1) == d-1){
		        p = p-1;
		    }
		    else if(MatVal(dist,p-l) == d-1){
		        p = p-l;
		    }
		    else if(MatVal(dist,p+1) == d-1){
		        p = p+1;
		    }
		    else if(MatVal(dist,p+l) == d-1){
		        p = p+l;
		    }
		    else if(MatVal(dist,p) == INT_MAX){
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
    long int dif_sec;
    printf("Dijsktra : %ld.%ld secondes\n", dif_sec = ( temps_fin.tv_sec - temps_debut.tv_sec) ,
        (temps_fin.tv_usec  + 1000000 * dif_sec) - temps_debut.tv_usec );

	MatFree(dist);
	MatFree(isSet);
	EnsFree(plusPetit);

}

void A_Star(Labyrinthe * lab){

    // temps_debut
    gettimeofday(&temps_debut,NULL);

	int l = lab->map->l;
    int h = lab->map->h;

	Ens * openList = EnsAlloc();
	Matrice * heuristique = MatAlloc(l,h);
	Matrice * cout = MatAlloc(l,h);
	Matrice * closedList = MatAlloc(l,h);

	EnsAjouteTrie(openList,NoeudInit(1,1),heuristique);
	MatSet2(cout,1,1,0);
	MatSet2(heuristique,1,1,0);
	if(AStar_rech)
    	SetPointGraphe(1,1, "vertf");

    while(!EnsEstVide(openList) && MatVal2(closedList,h-2,l-2) == 0){

        Noeud * u = EnsDepilePremier(openList);
		MatSet2(closedList,u->x,u->y,MatVal2(cout,u->x,u->y));

		if (!MatVal2(lab->map,u->x,u->y-1)){

            Noeud *v = NoeudInit(u->x,u->y-1);
            if( MatVal2(cout,v->x,v->y) == 0){
				if( MatVal2(heuristique,v->x,v->y) == 0){
					EnsAjouteTrie(openList,v,heuristique);
					MatSet2(cout,v->x,v->y,MatVal2(cout,u->x,u->y)+1);
					MatSet2(heuristique,v->x,v->y,
							MatVal2(cout,v->x,v->y)+(h-2- v->x) * (h-2- v->x) + (l-2 - v->y) * (l-2 - v->y) );
					if(AStar_rech)
	                	SetPointGraphe(v->x,v->y, "vertf");
				}
				else{
					NoeudSuppr(v);
				}
			}
			else
				NoeudSuppr(v);
        }

		if (!MatVal2(lab->map,u->x-1,u->y)){

            Noeud *v = NoeudInit(u->x-1,u->y);

            if( MatVal2(cout,v->x,v->y) == 0){
				if( MatVal2(heuristique,v->x,v->y) == 0){
					EnsAjouteTrie(openList,v,heuristique);
					MatSet2(cout,v->x,v->y,MatVal2(cout,u->x,u->y)+1);
					MatSet2(heuristique,v->x,v->y,
							MatVal2(cout,v->x,v->y)+(h-2- v->x) * (h-2- v->x) + (l-2 - v->y) * (l-2 - v->y) );  	if(AStar_rech)
                		SetPointGraphe(v->x,v->y, "vertf");
				}
				else{
					NoeudSuppr(v);
				}
			}
			else
				NoeudSuppr(v);

        }

		if (!MatVal2(lab->map,u->x,u->y+1)){

            Noeud *v = NoeudInit(u->x,u->y+1);
            if( MatVal2(cout,v->x,v->y) == 0){
				if( MatVal2(heuristique,v->x,v->y) == 0){
					EnsAjouteTrie(openList,v,heuristique);
					MatSet2(cout,v->x,v->y,MatVal2(cout,u->x,u->y)+1);
					MatSet2(heuristique,v->x,v->y,
							MatVal2(cout,v->x,v->y)+(h-2- v->x) * (h-2- v->x) + (l-2 - v->y) * (l-2 - v->y) );
					if(AStar_rech)
	                	SetPointGraphe(v->x,v->y, "vertf");
				}
				else{
					NoeudSuppr(v);
				}
			}
			else
				NoeudSuppr(v);
        }


		if (!MatVal2(lab->map,u->x+1,u->y)){

            Noeud *v = NoeudInit(u->x+1,u->y);

			if( MatVal2(cout,v->x,v->y) == 0){
				if( MatVal2(heuristique,v->x,v->y) == 0){
					EnsAjouteTrie(openList,v,heuristique);
					MatSet2(cout,v->x,v->y,MatVal2(cout,u->x,u->y)+1);
					MatSet2(heuristique,v->x,v->y,
							MatVal2(cout,v->x,v->y)+(h-2- v->x) * (h-2- v->x) + (l-2 - v->y) * (l-2 - v->y) );
					if(AStar_rech)
	                	SetPointGraphe(v->x,v->y, "vertf");
				}
				else{
					NoeudSuppr(v);
				}
			}
			else
				NoeudSuppr(v);
        }

		NoeudSuppr(u);

    }


	// print
    int d = MatVal2(closedList,h-2,l-2);
	printf("A* : %i\n",d);
    int p = (h-2)*l+l-2;

	if(v_graph)
		while(d>0){

		    SetPointGraphe((int)(p-l)/l+1,(int)(p-l)%l, "bleu");

			if(!(d-1)){
				SetPointGraphe(1,1, "bleu");
		        // fin
		    }
		    else if(MatVal(closedList,p-1) == d-1){
		        p = p-1;
		    }
		    else if(MatVal(closedList,p-l) == d-1){
		        p = p-l;
		    }
		    else if(MatVal(closedList,p+1) == d-1){
		        p = p+1;
		    }
		    else if(MatVal(closedList,p+l) == d-1){
		        p = p+l;
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
    long int dif_sec;
    printf("A* : %ld.%ld secondes\n", dif_sec = ( temps_fin.tv_sec - temps_debut.tv_sec) ,
        (temps_fin.tv_usec  + 1000000 * dif_sec) - temps_debut.tv_usec );

	MatFree(cout);
	MatFree(heuristique);
	MatFree(closedList);
	EnsFree(openList);

}
