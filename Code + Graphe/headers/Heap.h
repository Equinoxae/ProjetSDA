
/* Noeud de l'ensemble */
typedef struct{
    /* data*/
    int x; // [x,y]
    int y;
    int heuristique;
    int cout;

}Data;

typedef struct heap
{
	unsigned int size; // Size of the allocated memory (in number of items)
	unsigned int count; // Count of the elements in the heap
	Data ** data; // Array with the elements
}Heap;

Data * data_init(int x_ ,int y_,int c,int h);


/* initialise le tas */
Heap * heap_init(int size);

/* ajoute un noeud dans le tas */
void heap_push(Heap * h, Data * value);

/* Supprime le sommet du tas */
Data * heap_pop(Heap * h);

/* verrifie si le tas est vide */
int HeapEstVide(Heap * h);

/* libère le tas */
void HeapFree(Heap * h);
