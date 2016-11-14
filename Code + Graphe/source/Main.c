#include <stdlib.h>
#include <stdio.h>
#include "Labyrinthe.h"
#include "graph.h"

// utilisation : ./program [-v] [-d] [-l <largeur>] [-h <hauteur>] [-g <%graine>] <fichier>
int main(int argc, char *argv[]){

    Labyrinthe *lab;
    int h = 200;
    int l = 300;
    float g = 0.005
    char * fichier;

    if(argc != 4){
        printf("Format d'appel non valide.\nUtilisez : ./program largeur(>10) hauteur(>10) ratio_granularisation( <= 0.3) \n");
        exit(1);
    }

    int i;
    for(i = 1;i<argc;i++){
        switch (argv[i]) {
            case "-v":
                set_v(1);
                break;
            case "-d":
                set_v(1);
                set_d(1);
                break;
            case "-l"
                l = atoi(argv[++i]);
                break;
            case "-h":
                h = atoi(argv[++i]);
            case "-g"
                g = atof(argv[++i]);
            default:
                sprintf(fichier,"%s.pgm",argv[i]);
        }
    }

    if(x< 10 || y < 10 ){
        printf("Taille invalide ! La largeur et la hauteur doivent être > 10\n");
        exit(2);
    }

    if( g > 0.3 ){
        printf("Ratio invalide ! Le ration doit être < 0.3\n");
        exit(3);
    }

    lab = LabCreate(x,y,g);

    MatSauve(lab->map,fichier);

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

    closegraph();

    return 0;
}
