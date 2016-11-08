#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Labyrinthe0.h"

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
    int tv_init = w * h;
    LabInit( l, v_init, W, H);

    int tv = Granularise(l ,v_init, tv_init , v , 0 , (int)( w * h * r ) );

    // Expention graine
    //int tv = LabSupprBordInter(l , v);

    LabConstruit(l, v , tv);

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

    if(EstConstruit(lab,x,y))
        return -1;

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
            res = 1;
            Ens * coin = EnsAlloc();
            EnsAjoute(coin,x-1,y-1);
            EnsAjoute(coin,x-1,y+1);
            EnsAjoute(coin,x+1,y+1);
            EnsAjoute(coin,x+1,y-1);

            Noeud * n = coin->premier;
            while(n->next != NULL && res == 1){
                if(EstConstruit(lab,n->x,n->y)){
                    res = 0;
                }
                n=n->next;
            }

            EnsFree(coin);
        }
        else
            res = 0;
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
        res = -1;
    }

    return res;
}

int verifTour(Labyrinthe *lab  , Ens *v, Noeud * point,int tv){
    int t = tv;
    int cb;
    Ens *tour = EnsAlloc();
    EnsAjoute(tour,point->x-1,point->y);
    EnsAjoute(tour,point->x+1,point->y);
    EnsAjoute(tour,point->x,point->y+1);
    EnsAjoute(tour,point->x,point->y-1);

    Noeud * n = tour->premier;
    while(n->next != NULL){
        if(!EstConstruit(lab,n->x,n->y)){
            cb = EstConstructible(lab,v,n,0);
            if(cb){
                EnsAjoute(v,n->x,n->y);
                t++;
            }
            else if(cb == -1){
                EnsSuppr(v,n->x,n->y);
                t--;
            }
        }

        n=n->next;
    }
    EnsFree(tour);
    return t;
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

int Granularise(Labyrinthe *lab  , Ens *v, int tv , Ens * v_fin , int tv_fin, int nb){

    int t = tv;
    int t_fin = tv_fin;
    int count = 0;
    int res;

    if(nb == 0){
        printf("Ratio trop petit !\n");
        exit(50);
    }

    while( count < nb && t > 0){
        Noeud * tirage = EnsTirage(v,t);

        if( EstConstructible(lab , v, tirage,1 ) ){

            MatSet2(lab->map, tirage->x ,tirage->y , 1);
            t_fin = verifTour(lab,v_fin,tirage,t_fin);
            count++;
        }

        EnsSuppr(v, tirage->x ,tirage->y);
        t--;

    }

    printf("Granularise : Non-Const. : %i \n" ,EnsTaille(v) );
    LabPrint(lab);

    return t_fin;
}

// construit
void LabConstruit(Labyrinthe *lab  , Ens *v,int tv){
    int t = tv;
    int res;

    Noeud * tirage;
    while( t > 0){

        tirage = EnsTirage(v,t);

        if(EstConstructible(lab,v,tirage,0)==1){
            MatSet2(lab->map, tirage->x ,tirage->y , 1);
            t=verifTour(lab ,v,tirage,t);
        }

        EnsSuppr(v, tirage->x ,tirage->y);
        t--;
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
