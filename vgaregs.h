/*
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
²²±±±±±±±±±±±±±± C O M P I L E R ±±±96±±±± S O F T W A R E ±±±±±±±±±±±±±²²  
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
²²                                                                      ²²  
²²  VGAREGS.H                                                           ²²  
²²                                                                      ²²  
²²  #include "VGAREGS.H"                                                ²²  
²²                                                                      ²²  
²²  1996 Compiler SoftWare. Para dudas y contactos leer el fichero de   ²²  
²²  texto COMPILER.NFO del subdirectorio INFO.                          ²²   
²²                                                                      ²²
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²:-)²²²²
*/

#define ATTR_ADDR               0x3c0
#define MISC_ADDR               0x3c2
#define VGAENABLE_ADDR          0x3c3
#define SEQU_ADDR               0x3c4
#define GRAC_ADDR               0x3ce
#define CRTC_ADDR               0x3d4
#define STATUS_ADDR             0x3da
#define CHIPSTECH_ADDR          0x3d6

/*
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
²²                       DECLARACIONES DE FUNCIONES                     ²²
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
*/

void UnProtectCRTC( void );
unsigned char RegisterIn( int, char );
void RegisterOut( int, char, unsigned char );

void SetAddress( unsigned int );
void SetPage( char );
void WaitVRetrace( void );
void WaitHRetrace( void );
void MaskPlanes( char );
void EnableAllPlanes( void );

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* Funciones para no usar dos.h : */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void OutPortb( int , unsigned char );              /* = outportb y outp */
void OutPortw( int , int );                        /* = outport y outpw */
unsigned char InPortb( int );                      /* = inportb */
unsigned int InPortw( int );                       /* = inport */


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± UnProtectCRTC();                                                     ±±
±±                                                                      ±±
±± Desprotege el CRTC para poder modificar los registros que controla.  ±±
±± Ver registro 11h en la tabla de registros de art¡culo, CRTC bit 7.   ±±
±±                                                                      ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void UnProtectCRTC( void )
{
 int v ;
	OutPortb( CRTC_ADDR, 0x11 );         /* ¡ndice = 11h */
	v = InPortb( CRTC_ADDR + 1 );        /* 3d5h */
	v = v & 0x7F;                        /* bit 7 = 0 */
	OutPortb( CRTC_ADDR, 0x11 );         /* ¡ndice = 11h */
	OutPortw( CRTC_ADDR, 0x11 | ( v << 8 ) );        /* desproteger */
}


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± RegisterIn();                                                        ±±
±±                                                                      ±±
±± Devuelve el valor que contiene el registro especificado.             ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

unsigned char RegisterIn( int Controlador, char index )
{
 unsigned char valor;

  switch ( Controlador )
   {
      case MISC_ADDR:
	      valor = InPortb(0x3cc);  
	      break;
		      /* 0x3c2 es de escritura y 0x3cc de lectura */

      case ATTR_ADDR:                           
	      InPortb(STATUS_ADDR);   /* reseteamos el flip-flop */
				      /* el ¡ndice *DEBE* tener activado el */
				      /* bit 5. ( p. ej. sum ndole 32 ); */
	      OutPortb(ATTR_ADDR, index);
	      valor = InPortb(ATTR_ADDR+1);
	      break;

      case SEQU_ADDR:
      case GRAC_ADDR:
      case CRTC_ADDR:
      case CHIPSTECH_ADDR:
	      OutPortb(Controlador, index);     /* las 3 son iguales */
	      valor = InPortb(Controlador+1);
	      break;

      case VGAENABLE_ADDR:
      default:                      
	      valor = InPortb(Controlador);     /* resto de puertos */
	      break;
   } /* fin de switch */

 InPortb( STATUS_ADDR );              /* (faltaba) */
 OutPortb( ATTR_ADDR, 0x20 );         /* permitir escritura a pantalla */
 return(valor);        /* devolvemos el valor */
}



/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± RegisterOut();                                                       ±±
±±                                                                      ±±
±± Escribe el valor "valor" en el registro especificado.                ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void RegisterOut( int Controlador, char index, unsigned char valor )
{
  switch (Controlador)
    {
      case ATTR_ADDR:
	   InPortb(STATUS_ADDR);           /* resetear flip-flop */
	   OutPortb(ATTR_ADDR, index);
	   OutPortb(ATTR_ADDR, valor);  /* hecho ... */
	   break;

      case SEQU_ADDR:
	   if (index == 1)                 /* este es el caso m s extra¤o */
	    {
	     OutPortw(SEQU_ADDR, 0x0100);           /* resetear el secuenc. */
	     OutPortw(SEQU_ADDR, valor<<8 | 1);     /* enviar valor */ 
	     OutPortw(SEQU_ADDR, 0x0300);
	     break;
	    };
      case GRAC_ADDR:
      case CRTC_ADDR:
      case CHIPSTECH_ADDR:
	   OutPortw( Controlador , index | valor<<8);
	   break;

      case MISC_ADDR:
      case VGAENABLE_ADDR:
      default:
	   OutPortb(Controlador, valor);
	   break;
    } /* fin de switch */

    InPortb( STATUS_ADDR );              /* (faltaba) */
    OutPortb( ATTR_ADDR, 0x20 );         /* permitir escritura a pantalla */
}


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± SetAddress();                                                        ±±
±±                                                                      ±±
±± Selecciona el offset en memoria a considerar la esquina sup-izq. de  ±±
±± la pantalla.                                                         ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void SetAddress( unsigned int offst )
{
asm {
  mov dx, 3d4h          /* CRTC Controller */
  mov bx, [offst]       /* offset en memoria */
  mov al, 0ch           /* indice 0ch */
  mov ah, bh            /* byte alto */
  out dx, ax
  mov al, 0dh           /* indice 0dh */
  mov ah, bl            /* byte bajo */
  out dx, ax
     }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± SetPage( 0, 1, 2 ¢ 3 )                                               ±±
±±                                                                      ±±
±± Se le pasa el n§ de p gina a la que queremos cambiar y usa la func.  ±±
±± SetAddress para colocarla como p gina de visualizaci¢n.              ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void SetPage ( char num )
{
  SetAddress( (num*16000) );
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± MaskPlanes();                                                        ±±
±±                                                                      ±±
±± Enmascara los planos especificados para impedir la escritura.        ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

 void MaskPlanes( char mask )
 {
  asm {
	mov dx, SEQU_ADDR   /* SEQUENCER */
	mov al, 2           /* index 2 */
	out dx, al
	inc dx
	mov al, [mask]
	out dx, al          /* enviar m scara */
     }

 }

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± EnableAllPlanes();                                                   ±±
±±                                                                      ±±
±± Desenmascara todos los planos.                                       ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void EnableAllPlanes( void )
 {
   MaskPlanes( 0xF );        /* 0x0F = 1111b */
 }

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
 
 WaitVRetrace();

 3dah (Read Only): Input Status #1 Register
	bit 0: Si es 1, retrazo horizontal, 0 el haz a£n no ha parado.
	bit 3: Si es 1, retrazo vertical: el haz est  volviendo.
	       Si es 0 a£n est  redibujando la pantalla.

 El retrazo vertical es muy importante. Es el tiempo que tarda en volver el
 haz de refresco a la esquina superior izquierda de la pantalla. En este
 tiempo podemos modificar la pantalla de manera que todos los cambios sean
 simult neos y aparezcan todos de golpe evitando los tradicionales problemas
 de doubled-sprites (cuando aparecen dos sprites uno al lado del otro) y los
 sprites o figuras partidas en una l¡nea de la pantalla.
 
 Adem s cuando nos esperamos a un retrazo vert. antes de dibujar a pantalla
 hacemos que se ralentice el programa de manera que vaya a la misma velocidad
 con el turbo o sin el (aprox), eliminando diferencias de velocidad.

±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void WaitVRetrace()
{
  asm mov dx, 03dah; 
vert1:; 
  asm { 
	in al, dx; 
	test al, 8; 
	jnz vert1
      }
vert2:; 
  asm { 
	in al, dx; 
	test al, 8; 
	jz vert2;
      }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
 
 WaitHRetrace();

 3dah (Read Only): Input Status #1 Register
	bit 0: Si es 1, retrazo horizontal, 0 el haz a£n no ha parado.
	bit 3: Si es 1, retrazo vertical: el haz est  volviendo.
	       Si es 0 a£n est  redibujando la pantalla.

 El retrazo horizontal es un cort¡simo per¡odo de tiempo durante el cual el
 rayo pasa desde la derecha a la linea inferior comenzando en su izquierda.

	El retrazo horizontal es tan corto que si lo ponemos dentro de una
 funci¢n C cuando vuelva de ella probablemente est‚ en otra l¡nea.
 Lo mejor que podemos hacer para evitar esto es ponerlo directamente en el
 bucle principal en un bloque ensamblador, cuya velocidad nos ser  necesaria
 en operaciones gr ficas.

±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void WaitHRetrace()
{
  asm mov dx, 03dah; 
horiz1:; 
  asm { 
	in al, dx; 
	test al, 1; 
	jnz horiz1
      }
horiz2:; 
  asm { 
	in al, dx; 
	test al, 1; 
	jz horiz2;
      }
}

/*
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
²²                    FUNCIONES DE PUERTOS MS-DOS                       ²²
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
*/


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± InPortb( puerto );                                                   ±±
±± Lee del puerto "puerto" y devuelve el valor que tiene. ( 1 byte ).   ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

unsigned char InPortb( int port )
{
asm {
	mov dx , [port]
	in al , dx
    }
return ( _AL );
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± InPortw( puerto );                                                   ±±
±± Lee del puerto "puerto" y devuelve el valor que tiene. ( 1 word ).   ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

unsigned int InPortw( int port )
{
asm {
	mov dx , [port]
	in ax , dx
    }
return ( _AX );
}


/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± OutPortb( puerto, valor );                                           ±±
±± Escribe el byte valor en el puerto "puerto".                         ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void OutPortb ( int port, unsigned char dato )
{
asm {
	mov dx , [port]
	mov al , [dato]
	out dx , al
    }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±± OutPortw( puerto, valor );                                           ±±
±± Escribe el word valor en el puerto "puerto".                         ±±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

void OutPortw ( int port, int dato )
{
asm {
	mov dx , [port]
	mov ax , [dato]
	out dx , ax
    }
}

