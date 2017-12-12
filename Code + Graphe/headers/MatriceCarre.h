
typedef struct MurCarre{

  	int c1; // coté |
  	int c2; // coté / 
  	int c3; // coté \
	
	int v;

} MurCarre;

typedef struct MatriceCarre{

  	int h;
  	int l;
  	MurCarre* * points; //on a un tab de MurHexa. **-> tab de pointeurs 

} MatriceCarre;

MurCarre * MurCarreAlloc(); //constructeur

MurCarre * MurCarreAlloc2(int c1, int c2, int c3, int v); //constructeur

MatriceCarre * MatCarreAlloc(int h1,int l1); // création d’une nouvelle Matrice h * l initialisée à 0

void MatCarreFree(MatriceCarre * m); // libération éventuelle de la mémoire utilisée

MurCarre * MatCarreVal(MatriceCarre * m,int p); // renvoie la valeur entière à la position p d'une Matrice[x,y]

MurCarre * MatCarreVal2(MatriceCarre * m,int x,int y); // renvoie la valeur entière Matrice[x,y]

void MatCarreSet(MatriceCarre * m,int p,MurCarre * v); // stocke une valeur entière dans Matrice[x,y] a la potion p

void MatCarreSet2(MatriceCarre * m,int x,int y,MurCarre* v); // stocke une valeur entière dans Matrice[x,y]


int MatCarreGetL(MatriceCarre * m); // récupère la largeur

int MatCarreGetH(MatriceCarre * m); // récupère la hauteur
