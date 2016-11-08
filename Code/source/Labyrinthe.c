// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
// #include "Labyrinthe.h"
//
// Labyrinthe *LabCreate(int w,int h,float r)
// {
//     // init random
//     srand(time(NULL));
//
//     //var
//     Labyrinthe * l = malloc(sizeof(Labyrinthe));
//     Ens * c; // case construite
//     Ens * v; // case vide (constructible)
//
//     // taille bordure
//     int W = w + 2;
//     int H = h + 2;
//
//     // init
//     l->map = MatAlloc(W,H);
//
//     c = EnsAlloc();
//     v = EnsAlloc();
//
//     int tv = LabInit( l, c, v, W, H);
//
//     tv = Granularise(l ,c ,v, tv , (int)( w * h * r ) );
//
//     tv = LabSupprBordInter(l , v , tv);
//
//     LabConstruit(l, c, v , tv);
//
//     return l;
// }
//
// void LabFree(Labyrinthe *lab){
//     MatFree(lab->map);
// }
//
// int LabInit(Labyrinthe *lab, Ens *c,  Ens *v, int w ,int h)
// {
//     int tv_c = 0;
//
//     int i,j;
//     for(i = 0; i < w ; i++){
//         for(j = 0 ; j < h ; j++){
//             if( i == 0 || i == w-1 || j == 0 || j == h-1 ){
//                 MatSet2(lab->map, i, j, 1);
//                 EnsAjoute(c, i, j);
//             }
//             else{
//                 if( (i==1 && j==1) || (i==w-2 && j==h-2) ){
//                     //arrivé et départ
//                 }
//                 else{
//                     EnsAjoute(v , i ,j);
//                     tv_c++;
//                 }
//             }
//         }
//     }
//
//     //EnsSuppr(v,1,1); // départ
//     //EnsSuppr(v, w-2 , h-2 ); // Arrivée
//
//     return tv_c;
//
//     //EnsPrint(v);
//     //scanf("\n");
//
// }
//
// int LabSupprBordInter(Labyrinthe *lab, Ens *v ,int tv)
// {
//     int t = tv;
//     int w = MatGetL(lab->map);
//     int h = MatGetH(lab->map);
//     int i,j;
//     for(i = 0; i < w ; i++){
//         for(j = 0 ; j < h ; j++){
//             if( i == 1 || i == w-2 || j == 1 || j == h-2 ){
//                 EnsSuppr(v, i, j);
//                 t--;
//             }
//         }
//     }
//     return t;
//
// }
//
// int EstConstructible(Labyrinthe *lab ,  Ens *c , Ens *v, Noeud * point, int init)
// {
//     int x = point->x;
//     int y = point->y;
//
//     int res;
//
//     // si le point n'est pas construit sinon supprime supprime
//     if( !MatVal2(lab->map,point->x,point->y) ){
//
//         int adjcent[4] = {0,0,0,0}; // W , N , E , S <OK>
//         int adj_count = 0;
//
//         // Case Gauche
//         if( MatVal2(lab->map , x , y-1 ) ){
//             adjcent[0] = 1;
//             adj_count++;
//         }
//         // Case En-Haut
//         if( MatVal2(lab->map , x-1 , y ) ){
//             adjcent[1] = 1;
//             adj_count++;
//         }
//         // Case Droite
//         if( MatVal2(lab->map , x , y+1 ) ){
//             adjcent[2] = 1;
//             adj_count++;
//         }
//         // Case En-Bas
//         if( MatVal2(lab->map , x+1 , y ) ){
//             adjcent[3] = 1;
//             adj_count++;
//         }
//
//         // si il n'y a rien a coté
//         if( adj_count == 0){
//
//             // on compte les coins présents
//             int coin_count = 0;
//
//             Ens * coins = EnsAlloc();
//                 // coins etendu <OK>
//                 /*
//                    cx . . x
//                     . o . .
//                     . . . .
//                     x . . x
//                 */
//
//             Ens * cote_oppose = EnsAlloc();
//                 // coté opposés <OK>
//                 /*
//                     c . . .
//                     . o . x
//                     . . . x
//                     . x x .
//                 */
//
//
//             Ens *tour = EnsAlloc();
//                 // tour de la case
//                 /*
//                     c x x .
//                     x o x .
//                     x x x .
//                     . . . .
//                 */
//             EnsAjoute(tour,x-1,y-1);
//             EnsAjoute(tour,x-1,y);
//             EnsAjoute(tour,x-1,y+1);
//             EnsAjoute(tour,x,y+1);
//             EnsAjoute(tour,x+1,y+1);
//             EnsAjoute(tour,x+1,y);
//             EnsAjoute(tour,x+1,y-1);
//             EnsAjoute(tour,x,y-1);
//
//             Ens *tour_coin_opp = EnsAlloc();
//                 // tour coin opposee de la case <OK>
//                 /*
//                     c . . .
//                     . o x .
//                     . x x .
//                     . . . .
//                 */
//
//             // Case En-Haut Gauche
//             if( MatVal2(lab->map , x-1 , y-1 ) ){
//
//                 EnsAjoute(coins,x-1,y-1);
//                 EnsAjoute(coins,x-1,y+2);
//                 EnsAjoute(coins,x+2,y+2);
//                 EnsAjoute(coins,x+2,y-1);
//
//                 EnsAjoute(cote_oppose,x,y+2);
//                 EnsAjoute(cote_oppose,x+1,y+2);
//                 EnsAjoute(cote_oppose,x+2,y);
//                 EnsAjoute(cote_oppose,x+2,y+1);
//
//                 EnsAjoute(tour_coin_opp,x,y+1);
//                 EnsAjoute(tour_coin_opp,x+1,y+1);
//                 EnsAjoute(tour_coin_opp,x+1,y);
//
//                 coin_count++;
//             }
//             // Case En-Haut Droite
//             if( MatVal2(lab->map , x-1 , y+1 ) ){
//
//                 EnsAjoute(coins,x-1,y-2);
//                 EnsAjoute(coins,x-1,y+1);
//                 EnsAjoute(coins,x+2,y+1);
//                 EnsAjoute(coins,x+2,y-2);
//
//                 EnsAjoute(cote_oppose,x,y-2);
//                 EnsAjoute(cote_oppose,x+1,y-2);
//                 EnsAjoute(cote_oppose,x+2,y-1);
//                 EnsAjoute(cote_oppose,x+2,y);
//
//                 EnsAjoute(tour_coin_opp,x+1,y);
//                 EnsAjoute(tour_coin_opp,x+1,y-1);
//                 EnsAjoute(tour_coin_opp,x,y-1);
//
//                 coin_count++;
//             }
//             // Case En-Bas Droite
//             if( MatVal2(lab->map , x+1 , y+1 ) ){
//
//                 EnsAjoute(coins,x-2,y-2);
//                 EnsAjoute(coins,x-2,y+1);
//                 EnsAjoute(coins,x+1,y+1);
//                 EnsAjoute(coins,x+1,y-2);
//
//                 EnsAjoute(cote_oppose,x,y-2);
//                 EnsAjoute(cote_oppose,x-1,y-2);
//                 EnsAjoute(cote_oppose,x-2,y);
//                 EnsAjoute(cote_oppose,x-2,y-1);
//
//                 EnsAjoute(tour_coin_opp,x-1,y);
//                 EnsAjoute(tour_coin_opp,x-1,y-1);
//                 EnsAjoute(tour_coin_opp,x,y-1);
//
//                 coin_count++;
//             }
//             // Case En-Bas Gauche
//             if( MatVal2(lab->map , x+1 , y-1 ) ){
//
//                 EnsAjoute(coins,x-2,y-1);
//                 EnsAjoute(coins,x-2,y+2);
//                 EnsAjoute(coins,x+1,y+2);
//                 EnsAjoute(coins,x+1,y-1);
//
//                 EnsAjoute(cote_oppose,x,y+2);
//                 EnsAjoute(cote_oppose,x-1,y+2);
//                 EnsAjoute(cote_oppose,x-2,y+1);
//                 EnsAjoute(cote_oppose,x-2,y);
//
//                 EnsAjoute(tour_coin_opp,x-1,y);
//                 EnsAjoute(tour_coin_opp,x-1,y+1);
//                 EnsAjoute(tour_coin_opp,x,y+1);
//
//                 coin_count++;
//             }
//
//             // Si y a 2 coins : Supprime
//             if(coin_count >= 2)
//                 res = -1;
//             else if (coin_count == 1 ) // Si il y a strictement 1 coin
//             {
//                 Ens * cote_trouve = EnsAlloc();
//
//                 int i,counter_tour = 0;
//                 Noeud * n = tour->premier;
//                 for(i = 0; i<8 && counter_tour < 4 ; i++ , n = n->next){
//                     counter_tour += (EnsEstDans(v,n->x,n->y))? 1 : 0 ;
//                     EnsAjoute(cote_trouve,n->x , n->y);
//                 }
//
//                 int counter_tour_opp = 0;
//                 n = tour_coin_opp->premier;
//                 for(i = 0; i<3 && counter_tour > 0 ; i++ , n = n->next){
//                     counter_tour_opp += (EnsEstDans(v,n->x,n->y))? 1 : 0 ;
//
//                 }
//
//                 // Si auccune case du tour n'est constructible : Construit
//                 // Si + de 3 case constructible : Rien
//
//                 int counter_coin = 0;
//                 n = coins->premier;
//                 for(i = 0; i < 4 && counter_tour > 0 ; i++ , n = n->next){
//                     counter_coin += (MatVal2(lab->map,n->x,n->y))? 1 : 0 ;
//                 }
//
//                 // Si les coin etendu construit != 4 : Rien
//
//
//                 int counter_opp = 0;
//                 n = cote_oppose->premier;
//                 for(i = 0; i < 4 && counter_tour > 0  ; i++ , n = n->next){
//                     counter_opp += (EnsEstDans(v,n->x,n->y))? 1 : 0 ;
//                 }
//
//                 // Si auccune case du tour n'est constructible : Construit
//
//                 //printf("ct : %i cc : %i co : %i , x : %i , y : %i \n",counter_tour,counter_coin,counter_opp ,x,y);
//
//
//                 if(counter_tour == 4 ) //Si il y a plus 3 cases constructibles
//                     res == 0;
//                 if(counter_tour == 0)  //Si il n'y a rien de constructible sur sur le tour et qu'il y a 1 coin//Si il n'y a rien de constructible sur sur le tour et qu'il y a 1 coin
//                     res = 1;
//                 else if( counter_tour == 3  && counter_tour == counter_tour_opp && counter_coin == 4 && counter_opp == 0 ){
//                     res = 1;
//                 }
//                 else if(counter_tour == 1 && counter_tour == counter_tour_opp  && counter_coin >= 3  && counter_opp <= 1){
//                     int count_constructible = 0;
//                     n = cote_trouve->premier;
//                     if(init != -1)
//                         count_constructible += (EstConstructible(lab,c,v,n,-1))? 1 : 0;
//
//                     res = (count_constructible == 0 || init == -1 )? 1 : -1;
//                 }
//                 else if(counter_tour == 2 && counter_tour == counter_tour_opp  && counter_coin < 4 && counter_opp == 0){
//                     int count_constructible = 0;
//                     n = cote_trouve->premier;
//                     for(i = 0 ; i < 2 ; i++){
//                         count_constructible += (EstConstructible(lab,c,v,n,0))? 1 : 0;
//                     }
//
//                     res = (count_constructible == 0 )? 1 : 0;
//                 }
//                 else if (counter_tour == 2){
//                     int w = lab->map->l;
//                     int h = lab->map->h;
//                     if((x == 2 && y == 3 && !MatVal2(lab->map,4,2) ) || (x == 3 && y == 2 && !MatVal2(lab->map,2,4))
//                         || (x == 2 && y == w-4 && !MatVal2(lab->map,4,w-3)) || (x == 3 && y == w-3 && !MatVal2(lab->map,2,w-5))
//                         || (x == h-3 && y == 3 && !MatVal2(lab->map,h-5,2)) || (x == h-4  && y == 2 && !MatVal2(lab->map,h-3,4))
//                         || (x == h-3 && y == w-4 && !MatVal2(lab->map,h-5,w-3)) || (x == h-4 && y == w-3 && !MatVal2(lab->map,h-3,w-5))
//                         )
//                         res = 1;
//                     else
//                         res = 0;
//                 }
//                 else
//                     res == 0;
//
//                 EnsFree(cote_trouve);
//
//                 //res = ( ( (counter_tour == 3 || counter_tour == 1) && counter_coin == 4 && counter_opp <= 1 ) || counter_tour == 0 )? 1 : 0;
//                 //if(res == 1)
//                   // scanf("\n" );
//             }
//             else if(init) // Si y a 0 coins et 0 coté et qu'on initialise : Construit
//                 res = 1;
//             else{ //Si y a 0 coins et 0 coté
//
//                 int i,counter_tour = 0;
//                 Noeud * n = tour->premier;
//                 for(i = 0; i<8 && counter_tour < 1 ; i++ , n = n->next){
//                     counter_tour += (EnsEstDans(v,n->x,n->y))? 1 : 0 ;
//                 }
//
//                 // Si auccune case du tour est constructible (dans v) : Construit sinon Rien
//                 res = (counter_tour == 0)? 1 : 0;
//             }
//
//             EnsFree(tour);
//             EnsFree(tour_coin_opp);
//             EnsFree(coins);
//             EnsFree(cote_oppose);
//
//         }
//         else if(adj_count == 1){ // si il y a strictement un coté : Construit / Supprime
//
//             //<OK>
//             if(adjcent[0] == 1){ // Si a gauche
//                 res = (!MatVal2(lab->map,x-1,y+1) && !MatVal2(lab->map,x+1,y+1) ) ? 1 : -1;
//             }
//             else if(adjcent[1] == 1){ // Si en-haut
//                 res = (!MatVal2(lab->map,x+1,y-1) && !MatVal2(lab->map,x+1,y+1) ) ? 1 : -1;
//             }
//             else if(adjcent[2] == 1){ // si a droite
//                 res = (!MatVal2(lab->map,x-1,y-1) && !MatVal2(lab->map,x+1,y-1) ) ? 1 : -1;
//             }
//             else if(adjcent[3] == 1){ // si en bas
//                 res = (!MatVal2(lab->map,x-1,y-1) && !MatVal2(lab->map,x-1,y+1) ) ? 1 : -1;
//             }
//         }
//         else // plus d'un coté : Supprime
//         {
//             res = -1;
//         }
//
//     }
//     else   //si deja construit : Supprime
//         res = -1;
//
//     return res;
// }
//
// int Granularise(Labyrinthe *lab , Ens *c , Ens *v, int tv, int nb){
//
//     int t = tv;
//     int count = 0;
//     int res;
//
//     if(nb == 0){
//         printf("Ratio trop petit !\n");
//         exit(50);
//     }
//
//     while( count < nb && t > 0){
//
//         Noeud * tirage = EnsTirage(v,t);
//         res = EstConstructible(lab, c , v , tirage  , 1);
//
//         if(res == 1){
//
//             MatSet2(lab->map, tirage->x ,tirage->y , 1);
//             EnsAjoute(c, tirage->x ,tirage->y);
//             EnsSuppr(v, tirage->x ,tirage->y);
//             t--;
//             count++;
//         }
//         else if(res == -1)
//         {
//             EnsSuppr(v, tirage->x ,tirage->y);
//             t--;
//         }
//
//
//         //printf("Granularise : Constuite : %i , Non-Cont. : %i \n",EnsTaille(c) ,EnsTaille(v) );
//
//     }
//
//     printf("Granularise : Constuite : %i , Non-Cont. : %i \n",EnsTaille(c) ,EnsTaille(v) );
//     LabPrint(lab);
//
//     return t;
//
// }
//
// void LabConstruit(Labyrinthe *lab , Ens *c , Ens *v,int tv){
//     int t = tv;
//     int res;
//
//     while(t>0){
//
//         Noeud * tirage = EnsTirage(v,t);
//         res = EstConstructible(lab, c , v , tirage , 0);
//
//         //printf("Construit : %i , Vide %i , x : %i , y : %i\n", EnsTaille(c), tv,tirage->x ,tirage->y  );
//
//         if(tirage->x > lab->map->l || tirage->x < 0 || tirage->y > lab->map->h || tirage->y <0){
//             printf("ERREUR : %i %i\n" , tirage->x , tirage->y);
//             scanf("\n");
//         }
//         else if(res == 1){
//
//             MatSet2(lab->map, tirage->x ,tirage->y , 1);
//             EnsAjoute(c, tirage->x ,tirage->y);
//             EnsSuppr(v, tirage->x ,tirage->y);
//             t--;
//         }
//         else if(res == -1)
//         {
//             EnsSuppr(v, tirage->x ,tirage->y);
//             t--;
//         }
//
//         //if( tv <= 4 )
//         //    LabPrint(lab);
//         // scanf("\n");
//     }
//
// }
//
// void LabPrint(Labyrinthe *lab){
//
//     int w = MatGetL(lab->map);
//     int h = MatGetH(lab->map);
//
//     int i,j;
//     for(i = 0; i < w ; i++){
//         printf("%i\t: ", i );
//         for(j = 0 ; j < h ; j++){
//             char c = MatVal2(lab->map,i,j) ? '0' : ' ';
//
//             printf("%c ", c );
//         }
//         printf("\n");
//     }
// }
