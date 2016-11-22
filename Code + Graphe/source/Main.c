#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Labyrinthe.h"
#include "graph.h"

// utilisation : ./program [-v] [-d] [-l <largeur>] [-h <hauteur>] [-g <%graine>] <fichier>
int main(int argc, char *argv[]){

    Labyrinthe *lab;
    int h = 200;
    int l = 300;
    float g = 0.005;
    char * fichier;

    int i;
    for(i = 1;i<argc;i++){
        if ( !strcmp(argv[i],"-v"))
            set_v();
        else if ( !strcmp(argv[i],"-d"))
            set_d();
        else if ( !strcmp(argv[i],"-l"))
            l = atoi(argv[++i]);
        else if ( !strcmp(argv[i],"-h"))
            h = atoi(argv[++i]);
        else if ( !strcmp(argv[i],"-g"))
            g = atof(argv[++i]);
		else if ( !strcmp(argv[i],"-A"))
			set_AStar();
		else if ( !strcmp(argv[i],"-Ad"))
			set_AStar_rech();
		else if ( !strcmp(argv[i],"-D"))
			set_Dij();
		else if ( !strcmp(argv[i],"-Dd"))
			set_Dij_rech();	
		else if ( !strcmp(argv[i],"-Auto"))
			set_Auto();	
        else
            sprintf(fichier,"%s.pgm",argv[i]);

    }

    if( h < 10 || l < 10 ){
        printf("Taille invalide ! La largeur et la hauteur doivent être > 10\n");
        exit(2);
    }

    if( g > 0.3 ){
        printf("Ratio invalide ! Le ration doit être < 0.3\n");
        exit(3);
    }

    lab = LabCreate(l,h,g);

	lanceRecherche(lab);

    MatSauve(lab->map,fichier);

	LabFree(lab);

    /*
    STAT

    50*50 (2 500) : 
    100*100 (10 000) : 
    200*200 (40 000) : 
    300*300 (90 000) :
    400*400 (160 000):
    400*500 (200 000):
    500*500 (250 000):
    600*600 (360 000):
    */



    return 0;
}
