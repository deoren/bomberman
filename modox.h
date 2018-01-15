/*
±±±±±±±±±±±±±±±±±C±O±M±P±I±L±E±R±±±±±±±±±±±S±O±F±T±W±A±R±E±±±±±±±±±±±±±±±±
±±                                                                      ±±
±±  MODOX.h                                                             ±±
±±                                                                      ±±
±±  Esta librer¡a es introductoria. Una versi¢n m s potente y v lida    ±±
±±  para todos los modos 13x de resoluciones nxn de pantalla ser  dada  ±±
±±  durante la explicaci¢n de los scrolles hardware.                    ±±
±±                                                                      ±±
±±  #include "MODOX.h"                                                  ±±
±±                                                                      ±±
±±  1996 Compiler SoftWare. Para dudas y contactos leer el fichero de   ±±
±±  texto COMPILER.NFO                                                  ±±
±±                                                                      ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#include "vgaregs.h"                 /* Funciones modo x y puertos */

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±±                       DECLARACIONES DE FUNCIONES                     ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void Set_320x200X ( void );
void Set_320x240X ( void );
void PutPixelX( int, int, char ); 
unsigned char GetPixelX( int, int );
void ClearMem( char );

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± Set_320x200X();                                                      ±±
±±                                                                      ±±
±± Inicializa el Modo 13X de 320x200 a 256 colores en sistema 1x4.      ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void Set_320x200X ( )            
  {
    asm  mov ax , 13h                          /* inicializamos modo 13h est ndar */
    asm  int 10h
        
        OutPortw( SEQU_ADDR , 0x0604 );       /* ponemos el bit CHAIN-4 a 0 */
        OutPortw( CRTC_ADDR , 0xE317);        /* ajuste del modo de palabras */
        OutPortw( CRTC_ADDR , 0x0014);        /* ajuste del modo de dobles palabras */
        OutPortw( SEQU_ADDR , 0x0F02);        /* seleccionar los cuatro planos para...*/

    asm {                                    /* ...borrar la pantalla */
         mov ax , 0xA000 
         mov es , ax
         xor di , di
         xor ax , ax
         mov cx , 0x8000
         rep stosw
        }                                                  
  }


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± Set_320x240X();                                                      ±±
±±                                                                      ±±
±± Inicializa el Modo X de 320x240 a 256 colores en sistema 1x4.        ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void Set_320x240X( )
        {

        Set_320x200X( );       /* primero inicializamos 13X */

        OutPortb(0x3C2, 0xE3);  
        OutPortw(CRTC_ADDR, 0x2C11);         /* permitir escritura */
        OutPortw(CRTC_ADDR, 0x0D06);         /* Total vertical */
        OutPortw(CRTC_ADDR, 0x3E07);         /* Overflow Register */
        OutPortw(CRTC_ADDR, 0xEA10);         /* Vertical retrace start */
        OutPortw(CRTC_ADDR, 0xAC11);         /* Vertical retrace end y Write prot. */
        OutPortw(CRTC_ADDR, 0xDF12);         /* Vertical display enable end */
        OutPortw(CRTC_ADDR, 0xE715);         /* Start vertical blanking */
        OutPortw(CRTC_ADDR, 0x0616);         /* End vertical blanking */

        }


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± ClearMem( color );                                                   ±±
±±                                                                      ±±
±± Borra los 64k del segmento VGA al color especificado.                ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void ClearMem ( char color )     
{
  EnableAllPlanes();
  OutPortb( SEQU_ADDR , 0x02 );                  
  OutPortb( SEQU_ADDR+1, 0xF );  /* activamos los 4 planos */   
asm {  
        mov ax, 0xa000
        mov es, ax
        xor di, di
        mov cx, 32768
	mov al, [color]
        mov ah, al
        rep stosw               /* borramos 65536 bytes */
    }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± PutPixelX();                                                         ±±
±±                                                                      ±±
±± Coloca un punto en la primera p gina en (X,Y) de color color.        ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void PutPixelX( int x, int y, char color ) 
{
unsigned int offs;

OutPortb( SEQU_ADDR , 0x02 );                  /* funci¢n seleccionar plano */
OutPortb( SEQU_ADDR+1, 0x01 << ( x & 3 ) );    /* esto calcula autom ticamente 
                                                  el plano a partir de los 2 
                                                  £ltimos bits de la coord.x*/

offs = (y<<6) + (y<<4) + (x>>2);                 /* calculamos el offset */
                                                 /* esta l¡nea equivale a
                                                    off = (80*y) + (x/4) ; 
                                                   pero es MUCHO m s r pida.*/
asm {
        mov ax , 0xa000
        mov es , ax
        mov di , offs
        mov al , color
        stosb                                      /* ponemos el punto */
    }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± GetPixelX();                                                         ±±
±±                                                                      ±±
±± Devuelve el color de un pixel en (X,Y) en sistema 1x4.               ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

unsigned char GetPixelX(int x, int y)
        {
unsigned int offs;

        OutPortw(GRAC_ADDR, 0x04);
        OutPortw(GRAC_ADDR+1, x & 3 );     /* n§ de plano */

offs = (y<<6) + (y<<4) + (x>>2);                 /* calculamos el offset */
                                                 /* esta l¡nea equivale a
                                                   off = (80*y) + (x/4) ; 
                                                   pero es MUCHO m s r pida.*/
asm {
        mov ax , 0xa000
        mov es , ax
        mov di , offs                          /* lo leemos */
        mov al, es:[di]
    }

   return( _AL );                              /* y lo devolvemos */
}

