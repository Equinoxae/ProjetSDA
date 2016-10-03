
struct matrice{

  unsigned int h;
  unsigned int l;
  unsigned char* points;

};

matrice MatAlloc(int h,intl); // création d’une nouvelle matrice h * l initialisée à 0

MatFree // libération éventuelle de la mémoire utilisée

char MatVal(int x,int y); // renvoie la valeur entière matrice[x,y]

void MatSet(int x,int y); // stocke une valeur entière dans matrice[x,y]

void MatSauve(matrice m); // enregistre une matrice dans un fichier

matrice MatLit(char* file); // lit une matrice dans un fichier
