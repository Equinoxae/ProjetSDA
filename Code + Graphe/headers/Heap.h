
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

Data * data_init(int x_ ,int y_,int h,int c);

Heap * heap_init(int size);
void heap_push(Heap * h, Data * value);
Data * heap_pop(Heap * h);
int HeapEstVide(Heap * h);
void HeapFree(Heap * h);
