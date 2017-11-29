#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Labyrinthe.h"
#include "Matrice.h"
#include "MatriceHexa.h"

// utilisation : ./program [-v] [-d] [-l <largeur>] [-h <hauteur>] [-g <%graine>] [-Auto] [<fichier>]
int main(int argc, char *argv[]){

    Labyrinthe *lab;
    int h = 200;
    int l = 200;
    float g = 0.0001;
    int s_x;
    int s_y;
    char * fichier = "lab_file";

    int i;
	
	char * type = argv[1];

    for(i = 2;i<argc;i++){
	
		if(!strcmp(type,"-c")){
		
		}
		else if (!strcmp(type,"-x")){

		}
		else if (!strcmp(type,"-r")){

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
			else if ( !strcmp(argv[i],"-start"))
		        set_Start(atof(argv[++i]),atof(argv[++i]));
			else if ( !strcmp(argv[i],"-linear"))
				set_LinearGen();
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
		else{
		return 0;
		}


    }

	if(!strcmp(type,"-c")){
		
	}
	else if (!strcmp(type,"-x")){

	}
	else if (!strcmp(type,"-r")){
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
	}

    return 0;
}
