// #include "Recherche.h"
// #include "Martrice.h"
//
// int aleatoire(Labyrinthe * lab, Ens * file){
//     int x = file->dernier->x;
//     int y = file->dernier->y;
//
// }
//
// void heuristique(Labyrinthe * lab){
//
// }
//
// void dijkstra(Labyrinthe * lab){
//
//
//     Matrice * dist = MatAlloc(lab->map->l,lab->map->h);
//     //int dist[V];     // The output array.  dist[i] will hold the shortest
//     // distance from src to i
//
//     Matrice * isSet = MatAlloc(lab->map->l,lab->map->h);
//     //bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
//     // path tree or shortest distance from src to i is finalized
//
//     int V = lab->map->l*lab->map->h;
//
//     // Initialize all distances as INFINITE and stpSet[] as false
//     for (int i = 0; i < v; i++)
//         MatSet(dist,i,INT_MAX);
//
//     // Distance of source vertex from itself is always 0
//     MatSet2(dist,1,1,0);
//     SetPointGraphe(1,1, "vert");
//
//     int l = lab->map->l;
//
//     // Find shortest path for all vertices
//     for (int count = lab->map->l + 2; count < V -1 - l; count++) {
//         // Pick the minimum distance vertex from the set of vertices not
//         // yet processed. u is always equal to src in first iteration.
//         int u;
//
//         // Initialize min value
//         int min = INT_MAX;
//
//         for (int v = l; v < V-l; v++){
//             if (!MatVal(lab->map,v) && !MatVal(isSet,v) && MatVal(dist,v) <= min){
//                 min = MatVal(dist,u);
//                 u = v;
//             }
//         }
//
//         // Mark the picked vertex as processed
//         MatSet(isSet,u,1);
//
//
//         if (!MatVal(isSet,u+1) && !MatVal(lab->map,u+1) && MatVal(dist,u) != INT_MAX
//                                     && MatVal(dist,u)+1 < MatVal(dist,u+1)){
//             MatSet(dist,u+1,MatVal(dist,u)+1);
//             SetPointGraphe((int)(u+1)/l,(int)(u+1)%l, "vert");
//         }
//
//         if (!MatVal(isSet,u-1) && !MatVal(lab->map,u-1) && MatVal(dist,u) != INT_MAX
//                                     && MatVal(dist,u)+1 < MatVal(dist,u-1)){
//             MatSet(dist,u-1,MatVal(dist,u)+1);
//             SetPointGraphe((int)(u-1)/l,(int)(u-1)%l, "vert");
//         }
//
//         if (!MatVal(isSet,u+l) && !MatVal(lab->map,u+l) && MatVal(dist,u) != INT_MAX
//                                     && MatVal(dist,u)+1 < MatVal(dist,u+l)){
//             MatSet(dist,u+l,MatVal(dist,u)+1);
//             SetPointGraphe((int)(u+l)/l,(int)(u+l)%l, "vert");
//         }
//
//         if (!MatVal(isSet,u-l) && !MatVal(lab->map,u-l) && MatVal(dist,u) != INT_MAX
//                                     && MatVal(dist,u)+1 < MatVal(dist,u-l)){
//             MatSet(dist,u-l,MatVal(dist,u)+1);
//             SetPointGraphe((int)(u-l)/l,(int)(u-l)%l, "vert");
//         }
//
//
//         // print the constructed distance array
//
//     }
// }
//
// void A_star(Labyrinthe * lab){
//
// }
