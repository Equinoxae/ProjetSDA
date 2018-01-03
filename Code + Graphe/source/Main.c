#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Labyrinthe.h"
#include "LabyrintheHexa.h"
#include "LabyrintheCarre.h"
#include "graph.h"

// utilisation : ./program {-c/-C/-X/-r}  [-v] [-d] [-l <largeur>] [ -h <hauteur>] [-g <%graine>] [-Auto] [<fichier>]
int main(int argc, char *argv[]){

    Labyrinthe *lab;
    LabyrintheCarre *labc;
	LabyrintheHexa *labx;
	
	//LabyrintheCarre *labc;
    int h = -1;
    int l = -1;
    float g = 0.0001;
    int s_x;
    int s_y;
    char * fichier = "lab_file";

    int i;
	
	char * type = argv[1];

    for(i = 2;i<argc;i++){
	
		if(!strcmp(type,"-c")){
			if ( !strcmp(argv[i],"-v"))
		        set_v_carre();
		        
		    else if (!strcmp(argv[i],"-d"))
		        set_d_carre();
		        
			else if (!strcmp(argv[i],"-l"))
		        l = atoi(argv[++i]);
		        
		    else if (!strcmp(argv[i],"-h"))
		        h = atoi(argv[++i]);
		        
			else if (!strcmp(argv[i],"-M"))
				set_Manual_rech_carre();
				
			else if ( !strcmp(argv[i],"-linear"))
				set_LinearGenCarre();
				
			else if (!strcmp(argv[i],"-start"))
		        set_Start_carre(atof(argv[++i]),atof(argv[++i]));
		        
			else if (!strcmp(argv[i],"-ms"))
				set_Manual_Start_carre();
				
			else if (!strcmp(argv[i], "-construction1"))
				set_Construction_Carre(atoi(argv[++i]));
			else if (!strcmp(argv[i],"-D"))
		        set_Dij_carre();
			else if (!strcmp(argv[i],"-Dd"))
		        set_Dij_rech_carre();
		    else if (!strcmp(argv[i],"-A"))
		    	set_AStar_carre();
			else if (!strcmp(argv[i],"-Ad"))
		        set_AStar_rech_carre();
		}
		else if(!strcmp(type,"-C")){
		
		}
		else if (!strcmp(type,"-x")){
			if ( !strcmp(argv[i],"-v"))
		        set_v_hexa();
		    else if ( !strcmp(argv[i],"-d"))
		        set_d_hexa();
			else if (!strcmp(argv[i],"-l"))
		        l = atoi(argv[++i]);
		    else if (!strcmp(argv[i],"-h"))
		        h = atoi(argv[++i]);
			else if (!strcmp(argv[i],"-D"))
		        set_Dij_hexa();
			else if (!strcmp(argv[i],"-Dd"))
		        set_Dij_rech_hexa();
		    else if (!strcmp(argv[i],"-A"))
		    	set_AStar_hexa();
			else if (!strcmp(argv[i],"-Ad"))
		        set_AStar_rech_hexa();
			else if (!strcmp(argv[i],"-M"))
				set_Manual_rech_hexa();
			else if ( !strcmp(argv[i],"-linear"))
				set_LinearGenHexa();
			else if ( !strcmp(argv[i],"-slow")){
				set_Slow_gen();
				set_Slow_rech();
			}
			else if ( !strcmp(argv[i],"-slowg"))
				set_Slow_gen();
			else if ( !strcmp(argv[i],"-slowr"))
				set_Slow_rech();
			else if (!strcmp(argv[i],"-start"))
		        set_Start_hexa(atof(argv[++i]),atof(argv[++i]));
			else if (!strcmp(argv[i],"-ms"))
				set_Manual_Start_hexa();
		}
		else if (!strcmp(type,"-r")){

		    if (!strcmp(argv[i],"-v"))
		        set_v();
		    else if ( !strcmp(argv[i],"-d"))
		        set_d();
		    else if (!strcmp(argv[i],"-l"))
		        l = atoi(argv[++i]);
		    else if (!strcmp(argv[i],"-h"))
		        h = atoi(argv[++i]);
		    else if (!strcmp(argv[i],"-g"))
		        g = atof(argv[++i]);
			else if (!strcmp(argv[i],"-M"))
				set_Manual_rech();
			else if (!strcmp(argv[i],"-start"))
		        set_Start(atof(argv[++i]),atof(argv[++i]));
			else if (!strcmp(argv[i],"-ms"))
				set_Manual_Start();
			else if (!strcmp(argv[i],"-linear"))
				set_LinearGen();
		    else if (!strcmp(argv[i],"-A"))
		    	set_AStar();
			else if (!strcmp(argv[i],"-Ad"))
		        set_AStar_rech();
			else if (!strcmp(argv[i],"-D"))
		        set_Dij();
			else if (!strcmp(argv[i],"-Dd"))
		        set_Dij_rech();
			else if (!strcmp(argv[i],"-Auto"))
		        set_Auto();
			else if (!strcmp(argv[i],"-cw"))
				set_CaseWidth(atoi(argv[++i]));
		    else if (!strcmp(argv[i],"-file"))
		        sprintf(fichier,"%s.pgm",argv[++i]);
		}
		else{
			return 0;
		}

    }

	// cercle
	if(!strcmp(type,"-C")){
		
	}
	// carré avec bordure
	else if (!strcmp(type,"-c")){
		if(h == -1)
			h = 10;

		if(l == -1)
			l = 10;
			
		if( h < 10 || l < 10 || h > 60 || l > 60){
				printf("Taille invalide ! La largeur et la hauteur doivent être comprises entre 10 et 60 \n");
				exit(8);
		}
		
		labc = LabCarreCreate(l, h);
		
		lanceCarreRecherche(labc);
				
		LabCarreFree(labc);
	}
	
	// hexagone
	else if (!strcmp(type,"-x")){
		if(h == -1)
			h = 10;

		if(l == -1)
			l = 10;

		if (h < 5 || l < 5 || h > 40 || l > 80){
		    printf("Taille invalide ! La largeur doit être >= 5 et <= 80 et la hauteur doit être >= 5 et <= 40\n");
		    exit(2);
		}

		labx = LabHexaCreate(l,h);
		
		lanceRechercheHexa(labx);

		LabHexaFree(labx);

	}
	// rectangle
	else if (!strcmp(type,"-r")){
		if (h == -1)
			h = 200;

		if (l == -1)
			l = 200;


		if ( h < 10 || l < 10 ){
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
