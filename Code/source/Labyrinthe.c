#include <stdlib.h>
#include <stdio.h>
#include "Labyrinthe.h"

Labyrinthe *LabCreate(int w,int h,double r)
{
    if(r >= 0.3){
        exit(1);
    }

    //var
    Labyrinthe * l;
    Ens * c; // case construite
    Ens * v; // case vide (constructible)

    // taille bordure
    int W = w + 1;
    int H = h + 1;
    printf("fuck it\n" );
    // init
    l->map = MatAlloc(W,H);
    c = EnsAlloc();
    v = EnsAlloc();

    printf("hello1\n");
    LabInit( l, c, v, W, H);

    printf("hello2\n");

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
    printf("haha\n" );
    int i,j;
    for(i = 0; i < w ; i++){
        for(j = 0 ; j < h ; j++){
            if( i == 0 || i == w || j == 0 || j == h ){
                MatSet2(lab->map, i, j, 1);
                EnsAjoute(c, i, j);
                printf("hihi\n" );
            }
            else{
                printf("hoho\n" );
                EnsAjoute(v , i ,j);
            }
        }
    }

        printf("hi\n");
        printf("%i\n",EnsTaille(v) );
        printf("Fuuuuck\n" );
    EnsSuppr(v,1,1); // départ
    EnsSuppr(v, w-1 , h-1 ); // Arrivée

        printf("hi\n");
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

int EstConstructible(Labyrinthe *lab ,  Ens *c, int * point, int init)
{
    int x = point[0];
    int y = point[1];

    if( EnsEstDans(c,point[0],point[1]) ){

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

        int * tirage = EnsTirage(v);
        res = EstConstructible(lab, c , tirage  , 1);

        if(res == 1){

            MatSet2(lab->map, tirage[0] ,tirage[1] , 1);
            EnsAjoute(c, tirage[0] ,tirage[1]);
            EnsSuppr(v, tirage[0] ,tirage[1]);

            count++;
        }
        else if(res == -1)
        {
            EnsSuppr(v, tirage[0] ,tirage[1]);
        }

    }

}

void LabConstruit(Labyrinthe *lab , Ens *c , Ens *v){
    int res;

    while(!EnsEstVide(v)){

        int * tirage = EnsTirage(v);
        res = EstConstructible(lab, c , tirage  , 0);

        if(res == 1){

            MatSet2(lab->map, tirage[0] ,tirage[1] , 1);
            EnsAjoute(c, tirage[0] ,tirage[1]);
            EnsSuppr(v, tirage[0] ,tirage[1]);

        }
        else if(res == -1)
        {
            EnsSuppr(v, tirage[0] ,tirage[1]);
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
