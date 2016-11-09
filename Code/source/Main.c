#include <stdlib.h>
#include <stdio.h>
#include "Labyrinthe.h"

// utilisation : ./program largeur(>10) hauteur(>10) ratio_granularisation( <= 0.3)
int main(int argc, char *argv[]){

    Labyrinthe *lab;

    if(argc != 4){
        printf("Format d'appel non valide.\nUtilisez : ./program largeur(>10) hauteur(>10) ratio_granularisation( <= 0.3) \n");
        exit(1);
    }

    int arg1 = atoi(argv[1]);

    int arg2 = atoi(argv[2]);

    float arg3 = atof(argv[3]);

    if(arg1< 10 || arg2 < 10 ){
        printf("Taille invalide ! La largeur et la hauteur doivent être > 10\n");
        exit(2);
    }

    if( arg3 > 0.3 ){
        printf("Ratio invalide ! Le ration doit être < 0.3\n");
        exit(3);
    }

    lab = LabCreate(arg1,arg2, arg3 );

    MatSauve(lab->map,"Labyrinthe.pgm");

    printf("FINI\n" );
    LabPrint(lab);

    /*
    STAT

    50*50 (2 500) : 0.060s
    100*100 (10 000) : 0.505s
    200*200 (40 000) : 10.228s
    300*300 (90 000) : 1m0.543s
    400*400 (160 000): 3m50.151s
    400*500 (200 000): 4m28.105s
    500*500 (250 000): 9m31.116s
    600*600 (360 000): 28m37.985s
    */

    return 0;
}
