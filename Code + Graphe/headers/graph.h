#ifndef GRAPH_H
#define GRAPH_H

/* ouvre une fen�tre de taille larg*haut */
void initgraph(int larg, int haut);

/* ferme la fen�tre */
void closegraph(void);

/* force l'affichage */
void flushgraph(void);

/* change la couleur du trac�: R,V,B \in [0.0, 1.0] */
unsigned long newcolor(float rouge, float vert, float bleu);
void setcolor(unsigned long);

/* efface la fen�tre */
void cleargraph(void);

/* trace un point */
void putpixel(int x, int y);

/* trace un segment */
void line(int x1, int y1, int x2, int y2);

/* trace un cercle */
void point(int x, int y, int r);
void circle(int x, int y, int r);
void arc(int x, int y, int r, int angle_start, int angle_end);

/* Get Event */ 
void getClic(int * x, int * y);
char * getKey();


/* rafraichit */
void refresh(void);

/* bloque l'ex�cution jusqu'� ce que l'utilisateur
   appuie sur une touche */
void waitgraph(void);

#endif /* ! GRAPH_H */


