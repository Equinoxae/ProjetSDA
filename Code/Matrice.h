
struct matrice{

  unsigned int h;
  unsigned int l;
  Point* points;

};

matrice MatAlloc(int h,intl); // création d’une nouvelle matrice h * l initialisée à 0

MatFree : libération éventuelle de la mémoire utilisée

MatVal : renvoie la valeur entière matrice[x,y]

MatSet : stocke une valeur entière dans matrice[x,y]

MatSauve : enregistre une matrice dans un fichier

MatLit : lit une matrice dans un fichier
