#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
/*
#include <X11/xpm.h>
 */
#include "graph.h"

#define NAME "graph"

#define BORDER_WIDTH 4


#define icon_width 32
#define icon_height 32
static char icon_bits[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x3f, 0xc0, 0xff,
  0xff, 0x0f, 0xc0, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff,
  0xff, 0xe0, 0xff, 0xff, 0x7f, 0xf0, 0xff, 0xff, 0x7f, 0xf0, 0xff, 0xff,
  0x3f, 0xf8, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff,
  0x1f, 0xfe, 0xff, 0xff, 0x1f, 0xfe, 0x00, 0xff, 0x1f, 0xfe, 0x00, 0xfc,
  0x1f, 0xfe, 0x00, 0xf0, 0x1f, 0xfe, 0xff, 0xf1, 0x3f, 0xfc, 0xff, 0xf0,
  0x3f, 0xf8, 0xff, 0xf0, 0x7f, 0xf0, 0x7f, 0xf0, 0xff, 0x80, 0x1f, 0xf8,
  0xff, 0x01, 0x00, 0xf8, 0xff, 0x07, 0x00, 0xfc, 0xff, 0x3f, 0x40, 0xfc,
  0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x3f, 0xff,
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0x87, 0xff,
  0xff, 0xff, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, };


/* XPM */
/*
static char * icon_xpm[] = {
"40 40 2 1",
" 	c #00000000FFFF",
".	c #FFFF00000000",
"                                        ",
"                                        ",
"                                        ",
"                                        ",
"                                        ",
"                                        ",
"                    ......              ",
"                 .........              ",
"               ...........              ",
"              .....                     ",
"             ....                       ",
"           .....                        ",
"          .....                         ",
"          .....                         ",
"         .....                          ",
"         ....                           ",
"        .....                           ",
"        ....                            ",
"        ....       .........            ",
"        ....        ..........          ",
"        ....        ............        ",
"        ....       .        ....        ",
"        ....                 ...        ",
"         ....               ....        ",
"         .....              ....        ",
"          .....            .....        ",
"           .......       ......         ",
"            ...................         ",
"              ................          ",
"                 ......... ...          ",
"                           ..           ",
"                            .           ",
"                          ..            ",
"                         ...            ",
"                        ...             ",
"                       ....             ",
"                       . .              ",
"                         .              ",
"                                        ",
"                                        "};
*/

static int init = 0;

#define CHECKINIT(fun) \
  do {                                                                  \
    if (!init) {                                                        \
        fprintf(stderr, "%s: graph non initialisé dans %s\n", NAME, #fun); \
        abort();                                                        \
    }                                                                   \
  } while (0)                                                          
    

static Display *display;
static int screen;
static Screen *screen_ptr;
static unsigned long white, black;
static Window window;
static GC gc;
static char *fontname = "-misc-fixed-*-*-*-*-*-*-*-*-*-*-*-*";
static XFontStruct *font_info;
static XSizeHints *size_hints;

static Pixmap shadow;

void initgraph(int larg, int haut)
{
    Pixmap icon_pixmap;
    char *window_name = "Fenetre graphique";
    char *icon_name = "graph";
    XTextProperty windowName, iconName;
    XWMHints *wm_hints;
    unsigned long wattrmask;
    XSetWindowAttributes wattr;
    unsigned long gcattrmask;
    XGCValues gcattr;
    XEvent report;

    /* déja initialisée ? */
    if (init) {
        fprintf(stderr, "%s: graphique deja initialise\n", NAME);
        return;
    }

    /* allocation mémoire */
    if (!(size_hints = XAllocSizeHints())) {
        fprintf(stderr, "%s: pb allocation SizeHints\n", NAME);
        abort();
    }
    if (!(wm_hints = XAllocWMHints())) {
        fprintf(stderr, "%s: pb allocation WMHints\n", NAME);
        abort();
    }
    
    /* connection au serveur X */
    if ((display = XOpenDisplay(NULL)) == NULL) {
        fprintf(stderr, "%s: impossible de se connecter au serveur X %s\n",
                NAME, XDisplayName(NULL));
        abort();
    }

    screen = DefaultScreen(display);
    screen_ptr = DefaultScreenOfDisplay(display);
    black = BlackPixel(display, screen);
    white = WhitePixel(display, screen);

    /* on crée la fenêtre */
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 0, 0, larg, haut, BORDER_WIDTH,
                                 black, white);
    wattrmask = CWEventMask;
    wattr.event_mask = ExposureMask;
    XChangeWindowAttributes(display, window, wattrmask, &wattr);

    /* Création de l'icone */
    /*
    XpmCreatePixmapFromData(display, window, icon_xpm, &icon_pixmap, 
                            NULL, NULL);
    */
    icon_pixmap = XCreateBitmapFromData(display, window, icon_bits, 
                                        icon_width, icon_height);
    
    /* la taille minimale demandée */
    size_hints->flags = PMinSize | PMaxSize;
    size_hints->min_width = larg;
    size_hints->min_height = haut;
    size_hints->max_width = larg;
    size_hints->max_height = haut;

    /* les noms de la fenetre et de l'icone */
    if (XStringListToTextProperty(&window_name, 1, &windowName) == 0) {
        fprintf(stderr, "%s: pb allocation windowName\n", NAME);
        abort();
    }
    if (XStringListToTextProperty(&icon_name, 1, &iconName) == 0) {
        fprintf(stderr, "%s: pb allocation iconName\n", NAME);
        abort();
    }    
    
    /* quelques conseils pour le WindowManager */
    wm_hints->initial_state = NormalState;
    wm_hints->input = True;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = StateHint | IconPixmapHint | InputHint;
    XSetWMProperties(display, window, &windowName, &iconName, NULL, 0,
                     size_hints, wm_hints, NULL);
    XFree(wm_hints);
    
    /* les attributs de dessin */
    if ((font_info = XLoadQueryFont(display, fontname)) == NULL) {
        fprintf(stderr, "%s: fonte \"%s\" non trouvée\n", NAME, fontname);
        abort();
    }
    gcattr.foreground = black;
    gcattr.background = white;
    gcattrmask = GCForeground | GCBackground;       
    gc = XCreateGC(display, window, gcattrmask, &gcattr);
    XSetFont(display, gc, font_info->fid);
    XSetForeground(display, gc, black);

    /* affiche la fenêtre */
    XMapRaised(display, window);

    /* il faut attendre un Expose avant de dessiner ... */
    XWindowEvent(display, window, ExposureMask, &report);
    
/*    wattr.event_mask = NoEventMask;
    wattr.bit_gravity = NorthWestGravity;
    wattr.backing_store = Always;
    wattrmask = CWEventMask | CWBitGravity | CWBackingStore;
    XChangeWindowAttributes(display, window, wattrmask, &wattr);
*/
    wattr.backing_store = Always;
    wattr.save_under = True;
    XChangeWindowAttributes(display, window,
                          CWBackingStore | CWSaveUnder,
                          &wattr);

	shadow = XCreatePixmap(display, window, larg, haut, DefaultDepth(display, screen));
	XSetForeground(display, gc, white);
   XFillRectangle(display,shadow,gc,0,0,larg, haut);
	XSetForeground(display, gc, black);

   init = 1;
	cleargraph();

    return;
}


void closegraph()
{
    CHECKINIT(closegraph);

    XFree(size_hints);
    XFreeFont(display, font_info);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    init = 0;    
    return;
}


void flushgraph(void)
{
    CHECKINIT(flushgraph);

    XFlush(display);
}

unsigned long newcolor(float rouge, float vert, float bleu)
{
    XColor color;
    unsigned long fgcolor;

    CHECKINIT(setcolor);

    color.red = rouge * 65535;
    color.green = vert * 65535;
    color.blue = bleu * 65535;

    if (XAllocColor(display, DefaultColormap(display, screen), &color))
        fgcolor = color.pixel;
    else {
        fprintf(stderr, "graph: ne peut allouer la couleur (%f,%f,%f)\n", 
                rouge, vert, bleu);
        fgcolor = black;
    }
    XSetForeground(display, gc, fgcolor);
    
    return fgcolor;
}

void setcolor(unsigned long fgcolor)
{
    XSetForeground(display, gc, fgcolor);
    
    return;
}


void cleargraph(void)
{
    XWindowAttributes wattr;

    CHECKINIT(cleargraph);

   XGetWindowAttributes(display,window,&wattr);

	XSetForeground(display, gc, white);
   XFillRectangle(display,shadow,gc,0,0,wattr.width, wattr.height);
	XSetForeground(display, gc, black);

/*	XClearWindow( display, window ); */
}


void putpixel(int x, int y)
{
    CHECKINIT(putpixel);

    XDrawPoint(display, shadow, gc, x, y);
}


void line(int x1, int y1, int x2, int y2)
{
    CHECKINIT(line);

    XDrawLine(display, shadow, gc, x1, y1, x2, y2);
}

void refresh()
{
    XWindowAttributes wattr;
    XGetWindowAttributes(display,window,&wattr);
    XCopyArea(display, shadow, window, gc, 
                 0, 0, wattr.width, wattr.height, 0, 0);

	XSync( display, 0 );
}


void waitgraph(void)
{
    XEvent report;
    XWindowAttributes wattr;

    CHECKINIT(waitgraph);

/*    XGetWindowAttributes(display,window,&wattr);
    XCopyArea(display, shadow, window, gc, 
                 0, 0, wattr.width, wattr.height, 0, 0);
*/

    XSelectInput(display, window, KeyPressMask | ExposureMask);
    do {
        XNextEvent(display, &report);
        switch (report.type) {
        case Expose:
            /* Unless this is the last contiguous expose,
               don't draw the window (sic.) */
            if (report.xexpose.count != 0)
                break;
            /* On dessine la fenêtre */
/*            XCopyArea(display, shadow, window, gc, 
                     0, 0, wattr.width, wattr.height, 0, 0);
*/            /* fprintf(stderr, "%s: ne peut redessiner la fenêtre...\n", NAME); */
            break;
        case KeyPress:
            return;
        default:
            break;
        }
    } while (1);
}

