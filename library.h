#include <stdio.h>		/* Para las funciones de Putpcx() */
#include <dos.h>		/* delay (), getvect () */
#include <stdlib.h>		/* exit () y abs () */
#include <conio.h>		/* getch(), kbhit() clrscr (), cgets, gotoxy */
#include <string.h>
#include "modox.h"

#ifdef __cplusplus
#define __CPPARGS ...
     #else
#define __CPPARGS
#endif

#define KEYBD  0x9			/* Interrupci¢n 9 */

/* C¢digos de teclas pulsadas/apagadas mediante INT 9 handler */
#define ENTER_PULSADO         13
#define RIGHT_ARROW_PULSADO   77
#define RIGHT_ARROW_APAGADO  205
#define UP_ARROW_PULSADO      72
#define UP_ARROW_APAGADO     200
#define LEFT_ARROW_PULSADO    75
#define LEFT_ARROW_APAGADO   203
#define DOWN_ARROW_PULSADO    80
#define DOWN_ARROW_APAGADO   208
#define ESC		       1
#define LETRA_A_PULSADO       30
#define LETRA_A_APAGADO      158
#define LETRA_S_PULSADO       31
#define LETRA_S_APAGADO      159
#define LETRA_D_PULSADO       32
#define LETRA_D_APAGADO      160
#define LETRA_W_PULSADO       17
#define LETRA_W_APAGADO      145
#define LETRA_X_PULSADO       45
#define LETRA_X_APAGADO      173
#define ALT_IZQ_PULSADO       56
#define ALT_IZQ_APAGADO      184
#define INS_PULSADO           82
#define INS_APAGADO          210
#define NUM5_PULSADO          76
#define NUM5_APAGADO         204
#define MUN 458			/* Tama¤o del primer mu¤eco */
#define MUN2 482		/* Tama¤o del segundo mu¤eco */
#define MUN3 274		/* Tama¤o de la car tula de los mu¤ecos */
#define MUN4 258		/* Tama¤o de la cuadr¡cula de la pantalla*/
#define PAG4 600

#define LADRILLOS 70		/* Numero de ladrillos que apareceran en pantalla */
#define CASILLAS 115		/* Hay 115 casillas en las que podemos poner ladrillos */

void keyBoardInit (void);                       /*************************/
void keyCheck(void);                            /* Rutinas de Teclado    */
void interrupt (*oldvec)(__CPPARGS);            /*                       */
void interrupt myInt(__CPPARGS);                /*************************/

void InitT2 (void);
void timer_on (void);
unsigned int timer_off (void);

void paleta (char, char, char, char);		/*************************/
void carga (char *);                            /* Funciones para cargar */
void descomprime (int);                         /* la imagen Pcx         */
void PutPcx (char *,int);                       /*************************/

void modotexto (void);				/* Repone el modo texto */

void spritejug1 (void);				/* Asigna los valores del */
void spritejug2 (void);                         /* sprite a la matriz */
void pantalla (void);
void constru_panta (void);

void scrollarr (void);				/* Rutinas de scroll */
void scrollabj (void);				/* arriba y abajo */
void fundido (void);
void borrar (int,char);

/* Funciones gr ficas */

void Retrace (void);
void getx (int,int,int,int,int,char *);		/* getimage */
void putx (int,int,int,char *);			/* putimage no imprime color 21*/
void putm (int,int,int,char *,float);
void putb (int,int,int,char *,char,char,char *,char,char,char,char *,char *,char *,char *,char *);
void putz (int,int,int,char,char,char,char,char *);
void linea (int,int,int,int,int,char,char);		/* line (x1,y1,x2,y2,c,B/L) */
void fuentes (char *,int,int,int,char);


FILE *fp;
int x,y,longcas=115;
static unsigned int timer_hold,timer_diff;
char dib [MUN], dib2 [MUN], dib3 [MUN], dib4 [MUN], dib5 [MUN], dib6 [MUN], dib7 [MUN2], dib8 [MUN2], dib9 [MUN2], dib10[MUN2], dib11[MUN2], dib12[MUN], dib13[MUN3];
char dib14 [MUN], dib15 [MUN], dib16 [MUN], dib17 [MUN], dib18 [MUN], dib19 [MUN], dib20 [MUN2], dib21 [MUN2], dib22 [MUN2], dib23[MUN2], dib24[MUN2], dib25[MUN], dib26[MUN3];
char ladrillo [MUN4],muro [MUN4],bomba [MUN4],fuego [MUN4],salida [MUN4],bomba1 [MUN4],bomba2 [MUN4],bomba3 [MUN],suelo [MUN4],ultitra [MUN2];
char fuego01[MUN4],fuego02[MUN4],fuego03[MUN4],fuego04[MUN4],fuego05[MUN4],fuego06[MUN4],fuego07[MUN4],fuego11[MUN4],fuego12[MUN4],fuego13[MUN4],fuego14[MUN4],fuego15[MUN4],fuego16[MUN4],fuego17[MUN4],fuego21[MUN4],fuego22[MUN4],fuego23[MUN4],fuego24[MUN4],fuego25[MUN4],fuego26[MUN4],fuego27[MUN4],fuego31[MUN4],fuego32[MUN4],fuego33[MUN4],fuego34[MUN4],fuego35[MUN4],fuego36[MUN4],fuego37[MUN4];
char muerto11 [MUN2],muerto12 [MUN2],muerto13 [MUN2],muerto14 [MUN2],muerto15 [MUN2],muerto16 [MUN2],muerto17 [MUN2],muerto18 [MUN2];
char muerto21 [MUN2],muerto22 [MUN2],muerto23 [MUN2],muerto24 [MUN2],muerto25 [MUN2],muerto26 [MUN2],muerto27 [MUN2],muerto28 [MUN2];
char murod1 [MUN4],murod2 [MUN4],murod3 [MUN4],murod4 [MUN4];
char randi [11][19]=
			    {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
			     8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,
			     8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
			     8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,
			     8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
			     8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,
			     8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
			     8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,
			     8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
			     8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,
			     8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};
char randi2 [10][18]=
			    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			     9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};

char colmap [CASILLAS]={ 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 3, 5, 7, 9,11,13,15,17, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 1, 3, 5, 7, 9,11,13,15,17, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 1, 3, 5, 7, 9,11,13,15,17, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 1, 3, 5, 7, 9,11,13,15, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
char filmap [CASILLAS]={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
char casillas [CASILLAS]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114};
char azar [CASILLAS];
typedef struct {		/* Estructura de teclas posibles */
    int rightArrow;
    int leftArrow;
    int upArrow;
    int downArrow;
    int ins;
    int num5;
    int esc;
    int altizq;
    int letA;
    int letS;
    int letW;
    int letX;
    int letD;
    int enter;

} KEYBOARD;

KEYBOARD keyBoard;
unsigned char scanCode;

void PutPcx(char *nom,int pagina)
	{
	int x1,y1,x2,y2;
	carga(nom);
	getc(fp);getc(fp);getc(fp);getc(fp);
	fseek (fp,4,0);
	x1=getw(fp);
	y1=getw(fp);
	x2=getw(fp);
	y2=getw(fp);
	x=x2-x1;
	y=y2-y1;
	descomprime (pagina);
	}

void paleta (char color,char rojo,char verde,char azul)

	{
	outportb (0x3c8,color);
	outportb (0x3c9, rojo);
	outportb (0x3c9, verde);
	outportb (0x03c9, azul);
	}

void carga (char *txt)

	{
	if ((fp=fopen (txt,"rb"))==NULL)
		{
                modotexto();
		puts ("Archivo no se encuentra");
                exit (1);
                }
	}

void descomprime (int pagi)

	{
	char dato [2000];
	unsigned int dat;
	register int zx,zy;
	char rep=1;
	char con;
	char ch;
	unsigned char r,g,b;
	dat=0;
	fseek (fp,-768,SEEK_END);
	while (feof(fp)==0)
		{
		r=getc(fp);
		g=getc(fp);
		b=getc(fp);
		r=63*r/255;
		g=63*g/255;
		b=63*b/255;
		paleta (dat,r,g,b);
		if (dat<255) dat++;
		}
	rewind (fp);
	fseek (fp,128,0);
	dat=0,zx=0,zy=0;
	while (feof(fp)==0)
		{
		ch=getc(fp);
		if (feof(fp)!=0) goto end;
		if ((ch&192)==192)
			{
			rep=(ch&63);
			ch=getc(fp);
			}
		for (con=0;con<rep;con++)
			{
			PutPixelX (zx,zy+pagi,ch);
			zx++;
			if (zx>x){zy++,zx=0;}
			if (zy>y) goto end;
			}
		rep=1;
		}
	end:    fclose(fp);
	}

void putm (int a,int b,int c,char *p,float d)
	{
        register int x,y;
	int n=2;
        for (x=a;x<=a+p[0];x++)
		for (y=b;y<=b+p[1];y++)
                	{if (p[n]!=21) linea (a-((d-1)*p[0]/2)+(x-a)*d,b-((d-1)*p[1]/2)+(y-b)*d,a-((d-1)*p[0]/2)+(x-a)*d+d,b-((d-1)*p[1]/2)+(y-b)*d+d,c,p[n],'R');n++;}
        }

void putb (int a,int b,int c,char *p,char top1,char top2,char *pp,char top3,char top4,char ext,char *p1,char *p2,char *p3,char *p4,char *p5)
	{
        register int x,y,z;
	int n=2,to1=top1,to2=top2,to3=top3,to4=top4;
        for (x=a;x<=a+p[0];x++)
		for (y=b;y<=b+p[1];y++)
                        {
                        PutPixelX (x,y+c,p5[n]);
                        if (top1==ext) {to1=top1-1;PutPixelX (x+(to1*16),y+c,p1[n]);}
                        if (top2==ext) {to2=top2-1;PutPixelX (x-(to2*16),y+c,p2[n]);}
                        if (top3==ext) {to3=top3-1;PutPixelX (x,y+c-(to3*16),p4[n]);}
                        if (top4==ext) {to4=top4-1;PutPixelX (x,y+c+(to4*16),p3[n]);}
			for (z=1;z<to1;z++) PutPixelX (x+(z*16),y+c,p[n]);
                        for (z=1;z<to2;z++) PutPixelX (x-(z*16),y+c,p[n]);
                        for (z=1;z<to3;z++) PutPixelX (x,y+c-(z*16),pp[n]);
                        for (z=1;z<to4;z++) PutPixelX (x,y+c+(z*16),pp[n]);
			n++;
			}
        }

void putz (int a,int b,int c,char top1,char top2,char top3,char top4,char *p)
	{
        register int x,y,z;
	int n=2;
        for (x=a;x<=a+p[0];x++)
		for (y=b;y<=b+p[1];y++)
                        {
                        PutPixelX (x,y+c,p[n]);
			for (z=1;z<top1;z++) PutPixelX (x+(z*16),y+c,p[n]);
                        for (z=1;z<top2;z++) PutPixelX (x-(z*16),y+c,p[n]);
                        for (z=1;z<top3;z++) PutPixelX (x,y+c-(z*16),p[n]);
                        for (z=1;z<top4;z++) PutPixelX (x,y+c+(z*16),p[n]);
			n++;
			}
        }

void putx (int a,int b,int c,char *p)
	{
        register int x,y;
	int n=2;
        for (x=a;x<=a+p[0];x++)
		for (y=b;y<=b+p[1];y++)
                	{if (p[n]!=21) PutPixelX (x,y+c,p[n]);n++;}
        }

void getx (int a,int b,int c,int d,int e,char *p)
	{
        register int x,y;
	int n=2;
        p[0]=(c-a);
        p[1]=(d-b);
        for (x=a;x<=c;x++)
		for (y=b;y<=d;y++)
                        p[n++]=GetPixelX (x,y+e);
        }

void pantalla ()
	{
        getx (196,47,211,62,PAG4,ladrillo);
        getx (178,47,193,62,PAG4,muro);
        getx (96,47,111,62,PAG4,bomba);
        getx (80,47,95,62,PAG4,fuego);
        getx (63,47,78,62,PAG4,salida);
        getx (196,65,211,80,PAG4,suelo);
        getx (1,109,21,130,PAG4,ultitra);
        getx (214,47,229,62,PAG4,bomba1);
        getx (239,47,254,62,PAG4,bomba2);
        getx (265,47,280,62,PAG4,bomba3);
        getx (214,65,229,80,PAG4,murod1);
        getx (232,65,247,80,PAG4,murod2);
        getx (250,65,265,80,PAG4,murod3);
        getx (268,65,283,80,PAG4,murod4);
        getx (0,64,20,85,PAG4,muerto11);
        getx (23,64,43,85,PAG4,muerto12);
        getx (49,64,69,85,PAG4,muerto13);
        getx (73,64,93,85,PAG4,muerto14);
        getx (97,64,117,85,PAG4,muerto15);
        getx (121,64,141,85,PAG4,muerto16);
        getx (145,64,165,85,PAG4,muerto17);
        getx (169,64,189,85,PAG4,muerto18);
        getx (0,87,20,108,PAG4,muerto21);
        getx (23,87,43,108,PAG4,muerto22);
        getx (49,87,69,108,PAG4,muerto23);
        getx (73,87,93,108,PAG4,muerto24);
        getx (97,87,117,108,PAG4,muerto25);
        getx (121,87,141,108,PAG4,muerto26);
        getx (145,87,165,108,PAG4,muerto27);
        getx (169,87,189,108,PAG4,muerto28);
        getx (1,162,16,177,PAG4,fuego01);
        getx (20,162,35,177,PAG4,fuego02);
        getx (39,162,54,177,PAG4,fuego03);
	getx (58,162,73,177,PAG4,fuego04);
	getx (77,162,92,177,PAG4,fuego05);
	getx (96,162,111,177,PAG4,fuego06);
	getx (115,162,130,177,PAG4,fuego07);
	getx (134,162,149,177,PAG4,fuego11);
	getx (153,162,168,177,PAG4,fuego12);
	getx (172,162,187,177,PAG4,fuego13);
	getx (191,162,206,177,PAG4,fuego14);
	getx (210,162,225,177,PAG4,fuego15);
        getx (229,162,244,177,PAG4,fuego16);
	getx (248,162,263,177,PAG4,fuego17);
        getx (1,180,16,195,PAG4,fuego21);
        getx (20,180,35,195,PAG4,fuego22);
        getx (39,180,54,195,PAG4,fuego23);
	getx (58,180,73,195,PAG4,fuego24);
	getx (77,180,92,195,PAG4,fuego25);
	getx (96,180,111,195,PAG4,fuego26);
	getx (115,180,130,195,PAG4,fuego27);
	getx (134,180,149,195,PAG4,fuego31);
	getx (153,180,168,195,PAG4,fuego32);
	getx (172,180,187,195,PAG4,fuego33);
	getx (191,180,206,195,PAG4,fuego34);
	getx (210,180,225,195,PAG4,fuego35);
        getx (229,180,244,195,PAG4,fuego36);
	getx (248,180,263,195,PAG4,fuego37);
        }

void spritejug1 ()
	{
        getx (0,0,18,23,PAG4,dib);
	getx (21,0,39,23,PAG4,dib2);
        getx (39,0,57,23,PAG4,dib3);
        getx (60,0,78,23,PAG4,dib4);
        getx (81,0,99,23,PAG4,dib5);
        getx (99,0,117,23,PAG4,dib6);
        getx (120,0,139,23,PAG4,dib7);
        getx (139,0,158,23,PAG4,dib8);
        getx (160,0,179,23,PAG4,dib9);
        getx (182,0,201,23,PAG4,dib10);
        getx (204,0,223,23,PAG4,dib11);
        getx (225,0,243,23,PAG4,dib12);
        getx (0,46,15,62,PAG4,dib13);
        }

void spritejug2 ()
	{
        getx (0,23,18,46,PAG4,dib14);
	getx (21,23,39,46,PAG4,dib15);
        getx (39,23,57,46,PAG4,dib16);
        getx (60,23,78,46,PAG4,dib17);
        getx (81,23,99,46,PAG4,dib18);
        getx (99,23,117,46,PAG4,dib19);
        getx (120,23,139,46,PAG4,dib20);
        getx (139,23,158,46,PAG4,dib21);
        getx (160,23,179,46,PAG4,dib22);
        getx (182,23,201,46,PAG4,dib23);
        getx (204,23,223,46,PAG4,dib24);
        getx (225,23,243,46,PAG4,dib25);
        getx (15,46,30,62,PAG4,dib26);
        }

void constru_panta ()
	{
        int fui,gui;
        randomize ();

        /* Valor par no pasa el mu¤eco          */
        /* Valor 1 ser  el fondo (nada)         */
        /* Valor 10 ser  ladrillo	        */
        /* Valor 20 ser  ladrillo con bomba	*/
        /* Valor 30 ser  ladrillo con fuego	*/
        /* Valor 40 ser  upgrade bomba       	*/
        /* Valor 50 ser  upgrade fuego		*/
        /* Valor 5 ser  bomba		        */
        /* Valor 6 ser  ladrillo destruy‚ndose  */
	/* Valor 8 ser  muro                    */

        for (fui=0;fui<CASILLAS;fui++)
        	{
                gui=rand() % longcas;
                azar[fui]=casillas[gui];
                casillas[gui]=casillas[longcas-1];
                longcas--;
                }
        for (fui=18;fui<LADRILLOS;fui++)
        	{
        	randi[filmap[azar[fui]]][colmap[azar[fui]]]=10;
                }

        for (fui=0;fui<6;fui++)
        	{
        	randi[filmap[azar[fui]]][colmap[azar[fui]]]=20;
                }
        for (fui=6;fui<18;fui++)
        	{
        	randi[filmap[azar[fui+5]]][colmap[azar[fui+5]]]=30;
                }

/*        for (fui=1;fui<10;fui++)
        	for (gui=1;gui<18;gui++)
                        switch (randi[fui][gui])
                        	{
                                case 1:randi[fui][gui]=(rand () % 2)+1;break;
                                }*/
        for (fui=0;fui<11;fui++)
        	for (gui=0;gui<19;gui++)
                	switch (randi[fui][gui])
                        	{
                                case 1:putx (8+gui*16,24+fui*16,200,suelo);putx (8+gui*16,24+fui*16,400,suelo);break;
                                case 8:putx (8+gui*16,24+fui*16,200,muro);putx (8+gui*16,24+fui*16,400,muro);break;
                                default:putx (8+gui*16,24+fui*16,200,ladrillo);putx (8+gui*16,24+fui*16,400,ladrillo);
                                }
        }

void Retrace ()
	{
        do {} while ((inport (0x3da) & 8)!= 0);
        do {} while ((inport (0x3da) & 8)== 0);
        }

void scrollarr ()
	{
        int r;
        for( r=0; r<200 ; r++ )
	   {
	   SetAddress( r*80 );			/* Scroll hacia arriba */
	   WaitVRetrace();
	   }

        getch();				/* Esperamos una pulsaci¢n */
        }

void scrollabj ()
	{
        int r;
        for( ; r>0 ; r-=3 )
	   {
  	   SetAddress( r*80 );			/* Efecto de ca¡da */
	   WaitVRetrace();
	   }

        getch ();
        }

void modotexto ()
	{
        asm mov ax, 3				/* Volvemos a texto 80x25 */
        asm int 10h
        }

void borrar (int pagin,char col)
	{
        int x,y;
        for (x=0;x<320;x++)
        	for (y=0;y<200;y++)
                	PutPixelX (x,y+pagin,col);
        }

void linea (int q1,int w1,int q2,int w2,int pag,char color,char opcion)
	{
        register int t,distancia;
        int xerr=0,yerr=0,delta_x,delta_y;
        int incx,incy;

        /* En el caso de que queramos dibujar un cuadrado */
        /* B -->  cuadrado      //////       L -->  l¡nea */
        /* R -->  cuadrado relleno                        */
        switch (opcion)
        	{
                case 'B':linea (q1,w1,q2,w1,pag,color,'L');linea (q1,w1,q1,w2,pag,color,'L');linea (q1,w2,q2,w2,pag,color,'L');linea (q2,w1,q2,w2,pag,color,'L');break;
                case 'R':for (t=0;t<(q2-q1);t++) {linea (q1+t,w1,q1+t,w2,pag,color,'L');}break;
                case 'L':
                {

	/* Calculamos las distancias en ambas direcciones */
	delta_x=q2-q1;
	delta_y=w2-w1;

	/* Calculamos la direcci¢n del incremento, un incremento de 0 */
        /* Significa una l¡nea vertical o una linea horizontal */
	if (delta_x>0) incx =1;
        	else if (delta_x==0) incx =0;
                	else incx=-1;
        if (delta_y>0) incy =1;
        	else if (delta_y==0) incy =0;
                	else incy=-1;

        /* Determinamos que distancia es mayor */
        delta_x=abs(delta_x);
        delta_y=abs(delta_y);
        if (delta_x>delta_y) distancia =delta_x;
        	else distancia=delta_y;

        /* Dibujar la l¡nea */
        for (t=0;t<=distancia+1;t++)
        	{
        	PutPixelX (q1,w1+pag,color);
                xerr+=delta_x;
                yerr+=delta_y;
                if (xerr>distancia)
                	{
                        xerr-=distancia;
                        q1+=incx;
                        }
                if (yerr>distancia)
                	{
                        yerr-=distancia;
                        w1+=incy;
                        }
                }
                }break;
                }
        }

/****************************************************************************
** Comprueba el c¢digo de tecla INT 9 interrupt y asigna el estado correcto *
****************************************************************************/
void keyCheck(void)
	{
        if (scanCode>=200 || scanCode<=210)
                switch (scanCode)
                	{
                        case RIGHT_ARROW_APAGADO: keyBoard.rightArrow = 0;break;
        		case UP_ARROW_APAGADO: keyBoard.upArrow = 0;break;
                        case LEFT_ARROW_APAGADO: keyBoard.leftArrow = 0;break;
                        case DOWN_ARROW_APAGADO: keyBoard.downArrow = 0;break;
                        case NUM5_APAGADO: keyBoard.num5 = 0;break;
                        case INS_APAGADO: keyBoard.ins = 0;break;
                        }
        if (scanCode>=72 || scanCode<=82)
                switch (scanCode)
                	{
                        case RIGHT_ARROW_PULSADO: keyBoard.rightArrow = 1;break;
		        case UP_ARROW_PULSADO: keyBoard.upArrow = 1;break;
		        case LEFT_ARROW_PULSADO: keyBoard.leftArrow = 1;break;
		        case DOWN_ARROW_PULSADO: keyBoard.downArrow = 1;break;
                        case NUM5_PULSADO: keyBoard.num5 = 1;break;
                        case INS_PULSADO: keyBoard.ins = 1;break;
                        }
        if (scanCode>=145 || scanCode<=184)
        	switch (scanCode)
                	{
                        case LETRA_D_APAGADO: keyBoard.letD = 0;break;
        		case LETRA_W_APAGADO: keyBoard.letW = 0;break;
        		case LETRA_A_APAGADO: keyBoard.letA = 0;break;
        		case LETRA_X_APAGADO: keyBoard.letX = 0;break;
                        case LETRA_S_APAGADO: keyBoard.letS = 0;break;
                        case ALT_IZQ_APAGADO: keyBoard.altizq = 0;break;
                        }
        if (scanCode>=17 || scanCode<=56)
        	switch (scanCode)
                	{
                        case LETRA_D_PULSADO: keyBoard.letD = 1;break;
                        case LETRA_W_PULSADO: keyBoard.letW = 1;break;
                        case LETRA_A_PULSADO: keyBoard.letA = 1;break;
                        case LETRA_X_PULSADO: keyBoard.letX = 1;break;
                        case LETRA_S_PULSADO: keyBoard.letS = 1;break;
                        case ALT_IZQ_PULSADO: keyBoard.altizq = 1;break;
                        }
        if (scanCode==ESC) keyBoard.esc=1;
	}

/****************************************************************************
** Keyboard interrupt 9							   **
****************************************************************************/
void interrupt myInt(__CPPARGS)
	{
  	register char x;

  	scanCode = inp(0x60); // read keyboard data port
  	x = inp(0x61);
  	outp(0x61, (x | 0x80));
  	outp(0x61, x);
  	outp(0x20, 0x20);
  	keyCheck();

	}

/****************************************************************************
**									   **
****************************************************************************/
void keyBoardInit(void)
	{
  	keyBoard.rightArrow=0;
  	keyBoard.upArrow=0;
  	keyBoard.leftArrow=0;
  	keyBoard.downArrow=0;
  	keyBoard.esc=0;
  	keyBoard.altizq=0;
  	keyBoard.letA=0;
  	keyBoard.letS=0;
  	keyBoard.letW=0;
  	keyBoard.letX=0;
  	keyBoard.letD=0;
        keyBoard.ins=0;
  	keyBoard.num5=0;
        keyBoard.enter=0;
	}

void fuentes (char *Ber,int aer,int ber,int der,char cer)
	{
	char *Ker=NULL;
        char Xer[118]={0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};
	char Yer[118]={0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13};
	char data1 [31]={ 34, 42, 43, 50, 52, 58, 61, 65, 66, 67, 68, 69, 70, 75, 79, 83, 88, 92, 98, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data2 [31]={ 30, 31, 32, 33, 34, 37, 38, 43, 48, 51, 57, 58, 59, 60, 65, 70, 74, 79, 83, 87, 92, 93, 94, 95,  0,  0,  0,  0,  0,  0,  0};
        char data3 [31]={ 31, 32, 33, 34, 38, 39, 43, 47, 55, 64, 73, 82, 83, 92, 93, 94, 95, 87, 88,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data4 [31]={ 30, 31, 32, 33, 34, 38, 39, 43, 44, 46, 48, 53, 54, 57, 63, 66, 72, 74, 80, 83, 89, 92, 96, 97,101,102,103,104,  0,  0,  0};
        char data5 [31]={ 28, 29, 30, 31, 32, 33, 34, 39, 48, 55, 56, 57, 58, 59, 60, 65, 74, 83, 92, 93, 94, 95,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data6 [31]={ 28, 29, 30, 31, 32, 33, 34, 38, 47, 56, 64, 65, 66, 67, 68, 69, 73, 82, 91,100,109,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data7 [31]={ 31, 32, 33, 34, 39, 43, 47, 55, 64, 73, 82, 83, 92, 93, 94, 96,104, 86, 87, 78, 69, 70, 68, 67,  0,  0,  0,  0,  0,  0,  0};
        char data8 [31]={ 27, 29, 30, 35, 39, 44, 48, 52, 55, 56, 57, 58, 59, 60, 61, 62, 65, 70, 74, 79, 83, 88, 92, 97,101, 98, 99,  0,  0,  0,  0};
        char data9 [31]={ 30, 31, 32, 33, 34, 41, 50, 59, 58, 67, 76, 85, 92, 93, 94, 95, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data10 [31]={32, 33, 34, 35, 36, 43, 52, 60, 69, 78, 87, 95,104,109,110,111,112,100,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data11 [31]={21, 28, 29, 33, 34, 38, 42, 47, 50, 56, 57, 58, 65, 66, 73, 76, 82, 85, 91, 86, 95, 96,105,106,107,  0,  0,  0,  0,  0,  0};
        char data12 [31]={20, 29, 38, 47, 55, 64, 73, 82, 91, 92, 93, 94, 86,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
	char data13 [31]={20, 29, 35, 36, 38, 39, 44, 45, 47, 48, 53, 54, 56, 57, 61, 62, 64, 67, 69, 71, 73, 76, 77, 80, 82, 89, 91, 98,107,  0,  0};
	char data14 [31]={20, 29, 30, 35, 38, 39, 44, 47, 48, 53, 56, 58, 62, 64, 67, 70, 73, 77, 79, 82, 86, 88, 91, 96,  0,  0,  0,  0,  0,  0,  0};
        char data15 [31]={33, 34, 35, 40, 41, 44, 45, 47, 48, 49, 54, 55, 58, 63, 64, 72, 73, 80, 82, 83, 88, 93, 94, 95, 96,  0,  0,  0,  0,  0,  0};
        char data16 [31]={30, 31, 32, 33, 37, 38, 43, 48, 52, 57, 60, 65, 66, 67, 68, 74, 83, 92,101,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data17 [31]={32, 33, 34, 35, 39, 40, 41, 44, 45, 47, 49, 54, 55, 63, 64, 72, 73, 80, 82, 83, 84, 85, 88, 93, 94, 95, 96,105,106,116,117};
        char data18 [31]={30, 31, 32, 33, 38, 43, 46, 48, 52, 57, 60, 66, 67, 68, 74, 77, 83, 86, 87, 92, 96, 97, 98,101,  0,  0,  0,  0,  0,  0,  0};
        char data19 [31]={31, 32, 33, 39, 42, 48, 57, 67, 77, 86, 95,103,102,101, 91,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data20 [31]={26, 28, 29, 30, 31, 32, 33, 34, 40, 49, 58, 66, 75, 84, 93,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data21 [31]={28, 29, 30, 35, 38, 43, 47, 52, 55, 60, 64, 69, 73, 77, 78, 82, 85, 87, 92, 93, 96, 97, 98,  0,  0,  0,  0,  0,  0,  0,  0};
        char data22 [31]={19, 20, 29, 35, 38, 43, 47, 48, 52, 57, 60, 66, 69, 75, 77, 84, 85, 93,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data23 [31]={19, 28, 36, 37, 42, 45, 46, 50, 51, 54, 56, 59, 60, 63, 65, 67, 69, 72, 74, 76, 78, 81, 83, 84, 87, 89, 92, 96, 97,  0,  0};
        char data24 [31]={29, 33, 38, 42, 48, 50, 57, 58, 66, 67, 74, 76, 77, 82, 86, 91, 96, 97,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data25 [31]={19, 20, 25, 29, 34, 39, 42, 48, 50, 57, 58, 67, 75, 84, 93,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data26 [31]={20, 29, 30, 31, 32, 33, 34, 42, 50, 58, 66, 74, 83, 91, 92, 93, 94, 95, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
        char data27 [31]={ 4,  5,  7, 13, 15, 16, 20, 29, 30, 35, 38, 39, 44, 47, 48, 53, 56, 58, 62, 64, 67, 70, 73, 77, 79, 82, 86, 88, 91, 96,  0};

	char *data [27]={ data1, data2, data3, data4, data5, data6, data7, data8, data9,data10,data11,data12, data13,data14,data15,data16,data17,data18,data19,data20,data21,data22,data23,data24, data25,data26,data27};
	int buer=0,ger=0,her=0,BBer=0;
	for (buer=0;buer<strlen(Ber);buer++)
               	  {
		  ger=Ber[buer]-65;
        	  if (ger==100)
                  	{
                     	Ker=data27;
                      	for (her=0;her<31;her++)
        			{
		        	BBer=Ker[her];
                                if (*(Ker+her)!=0) PutPixelX (aer+Xer[BBer],ber+Yer[BBer]+der,cer);
                                }
		        aer=aer+10;
                        goto sal;
                        }
                if (ger==-33)
                	{
			aer=aer+10;
                        goto sal;
                        }
                Ker=data[ger];
                for (her=0;her<31;her++)
	        	{
        		BBer=*(Ker+her);
  	                if (*(Ker+her)!=0) PutPixelX (aer+Xer[BBer],ber+Yer[BBer]+der,cer);
               		}
	        aer=aer+10;
                sal:
                }
        }

void fundido ()
	{
        int i,j;
        int r,g,b;
        for (i=0;i<64;i++)
        	{
                Retrace ();
                for (j=0;j<256;j++)
                	{
                         outportb (0x3c7,j);
			 r=inportb (0x3c9);
                         g=inportb (0x3c9);
                         b=inportb (0x3c9);
                         if (r>0) r--;
                         if (g>0) g--;
                         if (b>0) b--;
			 paleta (j,r,g,b);
                         }
                }
        }

unsigned int timer_off()
	{
	asm mov al,0x80; /* latch timer 2 */
	asm out 0x43,al;
	asm in al,0x42;
	asm mov ah,al;
	asm in al,0x42;
	asm xchg ah,al;
	asm mov bx,timer_hold;
	asm sub ax,bx;
	asm neg ax;
	asm mov timer_diff,ax; /* calc timer_hold - ax to timer_diff */
	return(_AX);
	}

void timer_on()
	{
	asm mov al,0x80;  /* latch timer 2 */
	asm out 0x43,al;  /* save value in timer_hold */
	asm in al,0x42;
	asm mov bl,al;
	asm in al,0x42;
	asm mov bh,al;
	asm mov timer_hold,bx;
	}

void InitT2()
	{
	asm in al,0x61   /* no signal on speaker! */
	asm and al,0xfd
	asm or  al,1
	asm out 0x61,al

	asm mov al,0xb4  /* program timer 2 with modus 2 */
	asm out 0x43,al  /* and counter value of 0 (2^16)*/
	asm mov al,0
	asm out 0x42,al
	asm out 0x42,al
	}



/* Para colocar un pixel en distintos planos, hay que hacer lo siguiente:

                  pixel (x,y,color);          plano visible
                  pixel (x,y+240,color);      primer plano
                  pixel (x,y+480,color);      segundo plano
                  pixel (x,y+720,color);      tercer plano

                 PARA HACER VISIBLE UN PLANO BASTA CON PONER

      <<<<  SetPage13x (a);    siendo 'a' el n£mero de la p gina  >>>>

*/
