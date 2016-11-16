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

Labyrinthe *LabCreate(int w,int h,float r){
    // init random
    srand(time(NULL));

    //var
    Labyrinthe * l = malloc(sizeof(Labyrinthe));
    Ens * v, *v_init; // case vide (constructible)



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
    v_init = EnsAlloc();

    // Tour + Graine
    LabInit( l, v_init, W, H);

    Granularise(l ,v_init , v , (int)( w * h * r ) );

    // Expention graine
    LabConstruit(l, v);

    EnsFree(v);
    EnsFree(v_init);

    if(v_graph){
       waitgraph();
       dijkstra(l);
       waitgraph();
       closegraph();
    }

    return l;
}

void LabFree(Labyrinthe *lab){
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
        if(EstConstructible(lab,v,NoeudInit(x,y-1),init)){
            EnsAjoute(v,x,y-1);
            if(d_graph)
                SetPointGraphe(x,y-1,"rouge");
        }
        else{
            EnsSuppr(v,x,y-1);
            if(d_graph)
                SetPointGraphe(x,y-1,"blanc");
        }
    }
    // Case En-Haut
    if( !EstConstruit(lab , x-1 , y ) ){
        if(EstConstructible(lab,v,NoeudInit(x-1,y),init)){
            EnsAjoute(v,x-1,y);
            if(d_graph)
                SetPointGraphe(x-1,y,"rouge");
        }
        else{
            EnsSuppr(v,x-1,y);
            if(d_graph)
                SetPointGraphe(x-1,y,"blanc");
        }
    }
    // Case Droite
    if( !EstConstruit(lab , x , y+1 ) ){
        if(EstConstructible(lab,v,NoeudInit(x,y+1),init)){
            EnsAjoute(v,x,y+1);
            if(d_graph)
                SetPointGraphe(x,y+1,"rouge");
        }
        else{
            EnsSuppr(v,x,y+1);
            if(d_graph)
                SetPointGraphe(x,y+1,"blanc");
        }
    }
    // Case En-Bas
    if( !EstConstruit(lab , x+1 , y )){
        if(EstConstructible(lab,v,NoeudInit(x+1,y),init)){
            EnsAjoute(v,x+1,y);
            if(d_graph)
                SetPointGraphe(x+1,y,"rouge");
        }
        else{
            EnsSuppr(v,x+1,y);
            if(d_graph)
                SetPointGraphe(x+1,y,"blanc");
        }
    }
}

// Init matice
void LabInit(Labyrinthe *lab,  Ens *v, int w ,int h){

    int i,j; //x , y
    for(i = 0; i < h ; i++){
        for(j = 0 ; j < w ; j++){
            if( i == 0 || i == h-1 || j == 0 || j == w-1 ){
                MatSet2(lab->map, i, j, 1);
        if(v_graph)
            SetPointGraphe(i,j,"noir");
            }
            else{
                EnsAjoute(v, i, j);
            }
        }
    }

}

void Granularise(Labyrinthe *lab  , Ens *v, Ens * v_fin , int nb){

    int count = 0;
    int res;

    if(nb == 0){
        printf("Ratio trop petit !\n");
        exit(50);
    }

    while( count < nb && !EnsEstVide(v)){

        Noeud * tirage = EnsTirage(v);

        if( EstConstructible(lab , v, tirage,1 ) ){

            MatSet2(lab->map, tirage->x ,tirage->y , 1);
        if(v_graph)
        SetPointGraphe(tirage->x,tirage->y,"noir");
            verifTour(lab,v_fin,tirage,1);
            count++;

        }
        else if(d_graph){
            SetPointGraphe(tirage->x,tirage->y,"blanc");
        }

        EnsSuppr(v, tirage->x ,tirage->y);
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
        else if(d_graph){
                SetPointGraphe(tirage->x,tirage->y,"blanc");
        }

        EnsSuppr(v, tirage->x ,tirage->y);
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
    else if (!strcmp(color,"vert") )
            setcolor(newcolor(0,1,0));
    else if (!strcmp(color,"bleu"))
            setcolor(newcolor(0,0,1));


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

void dijkstra(Labyrinthe * lab){


    Matrice * dist = MatAlloc(lab->map->l,lab->map->h);
    //int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i

    Matrice * isSet = MatAlloc(lab->map->l,lab->map->h);
    //bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    int V = lab->map->l*lab->map->h;

    // Initialize all distances as INFINITE and stpSet[] as false
    int i;
    for (i = 0; i < V; i++)
        MatSet(dist,i,INT_MAX);

    // Distance of source vertex from itself is always 0
    MatSet2(dist,1,1,0);
    SetPointGraphe(1,1, "vert");
    printf("%i \n",MatVal2(isSet,1,1));

    int l = lab->map->l;
    int h = lab->map->h;

    // Find shortest path for all vertices
    int count;
    for (count = lab->map->l + 2; count < V -1 - l; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        int u;

        // Initialize min value
        int min = INT_MAX;

        int v;
        for (v = 0; v < V-l; v++){



            if (!MatVal(lab->map,v)
            && !MatVal(isSet,v) && MatVal(dist,v) <= min){
                min = MatVal(dist,v);
                u = v;
            }
        }

        // Mark the picked vertex as processed
        MatSet(isSet,u,1);


        if (!MatVal(isSet,u+1) && !MatVal(lab->map,u+1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+1)){
            MatSet(dist,u+1,MatVal(dist,u)+1);
            SetPointGraphe((int)(u+1)/l,(int)(u+1)%l, "vert");
        }

        if (!MatVal(isSet,u-1) && !MatVal(lab->map,u-1)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-1)){
            MatSet(dist,u-1,MatVal(dist,u)+1);
            SetPointGraphe((int)(u-1)/l,(int)(u-1)%l, "vert");
        }

        if (!MatVal(isSet,u+l) && !MatVal(lab->map,u+l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u+l)){
            MatSet(dist,u+l,MatVal(dist,u)+1);
            SetPointGraphe((int)(u+l)/l,(int)(u+l)%l, "vert");
        }

        if (!MatVal(isSet,u-l) && !MatVal(lab->map,u-l)
                                    && MatVal(dist,u)+1 < MatVal(dist,u-l)){
            MatSet(dist,u-l,MatVal(dist,u)+1);
            SetPointGraphe((int)(u-l)/l,(int)(u-l)%l, "vert");
        }


        // print the constructed distance array

    }


    int d = MatVal2(dist,h-2,l-2);
    int p = (h-2)*l+l-2;

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
        else{
            printf("erreur chemin\n");
            d=0;
        }
        d--;
    }
}
