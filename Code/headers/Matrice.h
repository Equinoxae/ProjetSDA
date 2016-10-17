
struct matrice{

  unsigned int h;
  unsigned int l;
  int * points;

};

typedef struct matrice Matrice;

Matrice MatAlloc(int h1,int l1); // création d’une nouvelle Matrice h * l initialisée à 0

void MatFree(Matrice m); // libération éventuelle de la mémoire utilisée

int MatVal(Matrice m,int p); // renvoie la valeur entière a la potion p d'une Matrice[x,y]

int MatVal2(Matrice m,int x,int y); // renvoie la valeur entière Matrice[x,y]


void MatSet(Matrice m,int p,int v); // stocke une valeur entière dans Matrice[x,y] a la potion p

void MatSet2(Matrice m,int x,int y,int v); // stocke une valeur entière dans Matrice[x,y]

void MatSauve(Matrice m,char* file); // enregistre une Matrice dans un fichier

Matrice MatLit(char* file); // lit une Matrice dans un fichier
