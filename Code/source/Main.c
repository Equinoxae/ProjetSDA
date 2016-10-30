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

    printf("FINI\n" );
    LabPrint(lab);

    return 0;
}
