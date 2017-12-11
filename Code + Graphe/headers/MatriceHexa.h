
typedef struct MurHexa{

  	int c1; // coté |
  	int c2; // coté / 
  	int c3; // coté \
	
	int v;

} MurHexa;

typedef struct MatriceHexa{

  	int h;
  	int l;
  	MurHexa* * points; //on a un tab de MurHexa. **-> tab de pointeurs 

} MatriceHexa;

MurHexa * MurHexaAlloc(); //constructeur

MurHexa * MurHexaAlloc2(int c1, int c2, int c3, int v); //constructeur

MatriceHexa * MatHexaAlloc(int h1,int l1); // création d’une nouvelle Matrice h * l initialisée à 0

void MatHexaFree(MatriceHexa * m); // libération éventuelle de la mémoire utilisée

MurHexa * MatHexaVal(MatriceHexa * m,int p); // renvoie la valeur entière à la position p d'une Matrice[x,y]

MurHexa * MatHexaVal2(MatriceHexa * m,int x,int y); // renvoie la valeur entière Matrice[x,y]

void MatHexaSet(MatriceHexa * m,int p,MurHexa * v); // stocke une valeur entière dans Matrice[x,y] a la potion p

void MatHexaSet2(MatriceHexa * m,int x,int y,MurHexa * v); // stocke une valeur entière dans Matrice[x,y]


int MatHexaGetL(MatriceHexa * m); // récupère la largeur

int MatHexaGetH(MatriceHexa * m); // récupère la hauteur
