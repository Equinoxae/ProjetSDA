#include <stdlib.h>
#include <stdio.h>
#include "Labyrinthe.h"

Labyrinthe *LabCreate(int w,int h,double r)
{
    if(r >= 0.3){
        exit(1);
    }

    //var
    Labyrinthe * l = malloc(sizeof(Labyrinthe));
    Ens * c; // case construite
    Ens * v; // case vide (constructible)

    // taille bordure
    int W = w + 1;
    int H = h + 1;

    // init
    l->map = MatAlloc(W,H);

    c = EnsAlloc();
    v = EnsAlloc();

    LabInit( l, c, v, W, H);

    Granularise(l ,c ,v , (int)( w * h * r ) );

    LabSupprBordInter(l , v);

    LabConstruit(l, c, v);

    return l;
}

void LabFree(Labyrinthe *lab){
    MatFree(lab->map);
}

void LabInit(Labyrinthe *lab, Ens *c,  Ens *v, int w ,int h)
{
    int i,j;
    for(i = 0; i < w ; i++){
        for(j = 0 ; j < h ; j++){
            if( i == 0 || i == w || j == 0 || j == h ){
                MatSet2(lab->map, i, j, 1);
                EnsAjoute(c, i, j);
            }
            else{
                EnsAjoute(v , i ,j);
            }
        }
    }

    printf("v : %i\n",EnsTaille(v) );

    EnsSuppr(v,1,1); // départ
    EnsSuppr(v, w-1 , h-1 ); // Arrivée

}

void LabSupprBordInter(Labyrinthe *lab,  Ens *v)
{
    int w = MatGetL(lab->map);
    int h = MatGetH(lab->map);
    int i,j;
    for(i = 0; i < w ; i++){
        for(j = 0 ; j < h ; j++){
            if( i == 1 || i == w-1 || j == 1 || j == h-1 ){
                EnsSuppr(v, i, j);
            }
        }
    }


}

int EstConstructible(Labyrinthe *lab ,  Ens *c, Noeud * point, int init)
{
    int x = point->x;
    int y = point->y;

    if( !EnsEstDans(c,point->x,point->y) ){

        int adjcent[4] = {0,0,0,0}; // W , N , E , S
        int adj_count = 0;

        // Case Gauche
        if( EnsEstDans(c , x-1 , y ) ){
            adjcent[0] = 1;
            adj_count++;
        }

        // Case En-Haut
        if( EnsEstDans(c , x , y-1 ) ){
            adjcent[1] = 1;
            adj_count++;
        }

        // Case Droite
        if( EnsEstDans(c , x+1 , y ) ){
            adjcent[2] = 1;
            adj_count++;
        }

        // Case En-Bas
        if( EnsEstDans(c , x , y+1 ) ){
            adjcent[3] = 1;
            adj_count++;
        }

        if( adj_count == 0){
            return (init)? 1 : 0;
        }
        else if(adj_count == 1){

            if(adjcent[0] == 1){
                return (!EnsEstDans(c,x+1,y-1) && !EnsEstDans(c,x+1,y+1) ) ? 1 : 0;
            }
            else if(adjcent[1] == 1){
                return (!EnsEstDans(c,x-1,y+1) && !EnsEstDans(c,x+1,y+1) ) ? 1 : 0;
            }
            else if(adjcent[2] == 1){
                return (!EnsEstDans(c,x-1,y-1) && !EnsEstDans(c,x-1,y+1) ) ? 1 : 0;
            }
            else if(adjcent[3] == 1){
                return (!EnsEstDans(c,x-1,y-1) && !EnsEstDans(c,x+1,y-1) ) ? 1 : 0;
            }
        }
        else
        {
            return -1;
        }

    }

    return 0;
}

void Granularise(Labyrinthe *lab , Ens *c , Ens *v , int nb){
    int count = 0;
    int res;

    while( count < nb && !EnsEstVide(v)){

        Noeud * tirage = EnsTirage(v);
        res = EstConstructible(lab, c , tirage  , 1);

        if(res == 1){

            MatSet2(lab->map, tirage->x ,tirage->y , 1);
            EnsAjoute(c, tirage->x ,tirage->y);
            EnsSuppr(v, tirage->x ,tirage->y);

            count++;
        }
        else if(res == -1)
        {
            EnsSuppr(v, tirage->x ,tirage->y);
        }

    }

}

void LabConstruit(Labyrinthe *lab , Ens *c , Ens *v){
    int res;

    while(!EnsEstVide(v)){

        Noeud * tirage = EnsTirage(v);
        res = EstConstructible(lab, c , tirage  , 0);

        if(res == 1){

            MatSet2(lab->map, tirage->x ,tirage->y , 1);
            EnsAjoute(c, tirage->x ,tirage->y);
            EnsSuppr(v, tirage->x ,tirage->y);

        }
        else if(res == -1)
        {
            EnsSuppr(v, tirage->x ,tirage->y);
        }

    }

}

void LabPrint(Labyrinthe *lab){

    int w = MatGetL(lab->map);
    int h = MatGetH(lab->map);

    int i,j;
    for(i = 0; i < w ; i++){
        for(j = 0 ; j < h ; j++){
            printf("%i \n", MatVal2(lab->map,i,j) );
        }
        printf("\n");
    }
}
