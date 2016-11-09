#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Labyrinthe.h"

Labyrinthe *LabCreate(int w,int h,float r){
    // init random
    srand(time(NULL));

    //var
    Labyrinthe * l = malloc(sizeof(Labyrinthe));
    Ens * v, *v_init; // case vide (constructible)

    // taille bordure
    int W = w + 2;
    int H = h + 2;

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
        }
        else{
            EnsSuppr(v,x,y-1);
        }
    }
    // Case En-Haut
    if( !EstConstruit(lab , x-1 , y ) ){
        if(EstConstructible(lab,v,NoeudInit(x-1,y),init)){
            EnsAjoute(v,x-1,y);
        }
        else{
            EnsSuppr(v,x-1,y);
        }
    }
    // Case Droite
    if( !EstConstruit(lab , x , y+1 ) ){
        if(EstConstructible(lab,v,NoeudInit(x,y+1),init)){
            EnsAjoute(v,x,y+1);
        }
        else{
            EnsSuppr(v,x,y+1);
        }
    }
    // Case En-Bas
    if( !EstConstruit(lab , x+1 , y )){
        if(EstConstructible(lab,v,NoeudInit(x+1,y),init)){
            EnsAjoute(v,x+1,y);
        }
        else{
            EnsSuppr(v,x+1,y);
        }
    }
}

// Init matice
void LabInit(Labyrinthe *lab,  Ens *v, int w ,int h){

    int i,j;
    for(i = 0; i < w ; i++){
        for(j = 0 ; j < h ; j++){
            if( i == 0 || i == w-1 || j == 0 || j == h-1 ){
                MatSet2(lab->map, i, j, 1);
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
            verifTour(lab,v_fin,tirage,1);
            count++;

        }

        EnsSuppr(v,tirage->x,tirage->y);

    }

    printf("Granularise : Non-Const. : %i \n" ,EnsTaille(v_fin) );
    LabPrint(lab);

    EnsSuppr(v,0,0);
}

// construit
void LabConstruit(Labyrinthe *lab  , Ens * v){

    int res;

    while( !EnsEstVide(v) ){
        Noeud * tirage = EnsTirage(v);

        if(EstConstructible(lab,v,tirage,0)){
            MatSet2(lab->map, tirage->x ,tirage->y , 1);
            verifTour(lab ,v,tirage,0);
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
