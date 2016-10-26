#include <stdlib.h>
#include <stdio.h>
#include "Labyrinthe.h"

int main(int argc, int *argv[]){

    Labyrinthe *lab;

    lab = LabCreate(20,20, 0.005);

    LabPrint(lab);

    return 0;
}
