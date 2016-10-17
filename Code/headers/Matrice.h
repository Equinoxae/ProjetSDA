
typedef MATRICE;

struct matrice{

  unsigned int h;
  unsigned int l;
  int * points;

};

matrice MatAlloc(int h1,int l1); // création d’une nouvelle matrice h * l initialisée à 0

void MatFree(matrice m); // libération éventuelle de la mémoire utilisée

int MatVal(matrice m,int p); // renvoie la valeur entière a la potion p d'une matrice[x,y]

int MatVal2(matrice m,int x,inty); // renvoie la valeur entière matrice[x,y]


void MatSet(matrice m,int p,int v); // stocke une valeur entière dans matrice[x,y] a la potion p

void MatSet2(matrice m,int x,int y,int v); // stocke une valeur entière dans matrice[x,y]

void MatSauve(matrice m,char* file); // enregistre une matrice dans un fichier

matrice MatLit(char* file); // lit une matrice dans un fichier
