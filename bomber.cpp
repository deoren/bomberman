/*

Bomberman ver 0.6nobugs last modified 12/01/00

made by Enrique Huerta Mezquita and Carlos Huerta Mezquita

contact us at enriquemail@mixmail.com | solrac@webmadrid.com

This program is free and you are welcome to use its code in your

own as long as you credit the authors as the contributers.

The authors are not liable for any damages caused by an improper 

use of this software.

For more stuff and new releases about this and other Freesource

Company proyects visit http://www11.brinkster.com/freesource

*/

#include "library.h"				//own library

#define EX explosion [etapa [des1 [nb]/2]
#define EU explosion [etapa [des2 [nb]/2]
#define EXTENSION1 1				//initial power for both players
#define EXTENSION2 1
#define BOMBAS1 1				//initial bombs for both players
#define BOMBAS2 1

void main (void)
	{
	int T=0;
        int PA=200;
        char fragor [1788],nzf=0;
        float zf [24]={1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3};
        char mirarx,mirary,mirarbx,mirarby,muerte1=0,muerte2=0,avav1=0,avav2=0;
        char estallido2 [8]={0,0,0,0,0,0,0,0},estallido1 [8]={0,0,0,0,0,0,0,0};
        char upup=0,dodo=0,riri=0,lele=0,des2 [8]={0,0,0,0,0,0,0,0},etapa [6]={14,7,21,7,14,0},sumas;
        char demolerup1 [8]={0,0,0,0,0,0,0,0},demolerdo1 [8]={0,0,0,0,0,0,0,0},demolerle1 [8]={0,0,0,0,0,0,0,0},demolerri1 [8]={0,0,0,0,0,0,0,0},hz1 [8]={0,0,0,0,0,0,0,0};
        char demolerup2 [8]={0,0,0,0,0,0,0,0},demolerdo2 [8]={0,0,0,0,0,0,0,0},demolerle2 [8]={0,0,0,0,0,0,0,0},demolerri2 [8]={0,0,0,0,0,0,0,0},hz2 [8]={0,0,0,0,0,0,0,0};
        char des1 [8]={0,0,0,0,0,0,0,0};
        char ext2=(EXTENSION2 +1),tropiezo=0,top_up [8]={0,0,0,0,0,0,0,0},top_down [8]={0,0,0,0,0,0,0,0},top_left [8]={0,0,0,0,0,0,0,0},top_right [8]={0,0,0,0,0,0,0,0};
        char ext1=(EXTENSION1 +1),top__up [8]={0,0,0,0,0,0,0,0},top__down [8]={0,0,0,0,0,0,0,0},top__left [8]={0,0,0,0,0,0,0,0},top__right [8]={0,0,0,0,0,0,0,0};
        char PAG=1,q1,q2,tt1 [8]={0,0,0,0,0,0,0,0},tt2 [8]={0,0,0,0,0,0,0,0},TT1 [8]={0,0,0,0,0,0,0,0},TT2 [8]={0,0,0,0,0,0,0,0},follow1=0,follow2=0;
        char rubber1 [600],rubber2 [600],*rubb1 [2]={rubber1,rubber2};
        char rubber3 [600],rubber4 [600],*rubb2 [2]={rubber3,rubber4};
        char SPt1 [8]={0,0,0,0,0,0,0,0},SPt2 [8]={0,0,0,0,0,0,0,0},ocupado1 [8]={0,0,0,0,0,0,0,0},ocupado2 [8]={0,0,0,0,0,0,0,0};
        char bxy1 [258],bxy2 [258],bxy3 [258],bxy4 [258],bxy5 [258],bxy6 [258],bxy7 [258],bxy8 [258];
        char buv1 [258],buv2 [258],buv3 [258],buv4 [258],buv5 [258],buv6 [258],buv7 [258],buv8 [258];
        char nb=0,nbaux=0,nbaux2=0,nbmm1=BOMBAS1,nbmm2=BOMBAS2,nbm1=0,nbm2=0,r1,r2,ex11,ex13,ex21,ex23;
        char orden [16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int b1j1 [8],b2j1 [8],b1j2 [8],b2j2 [8],ex12,ex14,ex22,ex24,hb1j2 [8],hb2j2 [8],hb1j1 [8],hb2j1 [8];
        int x=278,y=161,u=22,v=33,M1=0,M2=0,MO2=1,MO1=1,xb=x,yb=y,xb2=x,yb2=y,ub=u,vb=v,ub2=u,vb2=v;
        int xes,bp1=0,bp2=0,orn=0,pnum=0,hasta_aqui=0;
        int y3,x3,u3,v3,limpia1,limpia2;
	char *l[4],*l2[4],*l3[4],*l4[4],*ll[4],*ll2[4],*ll3[4],*ll4[4],*ll5[4],*explosion[29],*muerto1c[19],*muerto2c[19];
        char *deshaz[8]={murod1,murod2,murod3,murod4,suelo};
        char *bombayfuego[2]={bomba,fuego};

        InitT2 ();
        Set_320x200X();				//initializing mode13x

        PutPcx("default.pcx",600);		//loads pcx image

	spritejug1();				//gets players graphics
        spritejug2();

        pantalla ();
        borrar (200,1);
        borrar (400,1);
        constru_panta ();

        borrar (0,0);
        fuentes ("BOMBERMAN GAME",10,20,0,200);
        fuentes ("PROGRAMMERS",10,40,0,200);
        fuentes ("CARLOS HUERTA MEZQUITA",10,55,0,125);
        fuentes ("ENRIQUE HUERTA MEZQUITA",10,70,0,125);
        fuentes ("KEYS",10,100,0,200);
        fuentes ("UP DOWN LEFT RIGHT FIRE",10,115,0,210);
        fuentes ("PLAYER ONE  W X A D ALTIZQ",10,130,0,125);
        fuentes ("PLAYER TWO  KEYPAD INS",10,145,0,125);
        fuentes ("PRESS ANY KEY TO CONTINUE",10,175,0,125);
        getch ();

        keyBoardInit ();
	oldvec=getvect (KEYBD);
	setvect (KEYBD,myInt);

        l [0]=dib,l [1]=dib2,l [2]=dib,l [3]=dib3;
        l2 [0]=dib4,l2 [1]=dib5,l2 [2]=dib4,l2 [3]=dib6;
        l3 [0]=dib7,l3 [1]=dib8,l3 [2]=dib7,l3 [3]=dib9;
        l4 [0]=dib10,l4 [1]=dib11,l4 [2]=dib10,l4 [3]=dib12;

        ll [0]=dib14;ll [1]=dib15;ll [2]=dib14;ll [3]=dib16;
        ll2 [0]=dib17;ll2 [1]=dib18;ll2 [2]=dib17;ll2 [3]=dib19;
        ll3 [0]=dib20;ll3 [1]=dib21;ll3 [2]=dib20;ll3 [3]=dib22;
        ll4 [0]=dib23;ll4 [1]=dib24;ll4 [2]=dib23;ll4 [3]=dib25;

        ll5 [0]=bomba2,ll5 [1]=bomba1,ll5 [2]=bomba2,ll5 [3]=bomba3;

        explosion [1]=fuego01,explosion [2]=fuego02,explosion [3]=fuego03,explosion [4]=fuego04,explosion [5]=fuego05,explosion [6]=fuego06;explosion [7]=fuego07,
        explosion [8]=fuego11,explosion [9]=fuego12,explosion [10]=fuego13,explosion [11]=fuego14,explosion [12]=fuego15,explosion [13]=fuego16;explosion [14]=fuego17,
        explosion [15]=fuego21,explosion [16]=fuego22,explosion [17]=fuego23,explosion [18]=fuego24,explosion [19]=fuego25,explosion [20]=fuego26;explosion [21]=fuego27,
        explosion [22]=fuego31,explosion [23]=fuego32,explosion [24]=fuego33,explosion [25]=fuego34,explosion [26]=fuego35,explosion [27]=fuego36;explosion [28]=fuego37;

        muerto1c [0]=muerto11,muerto1c [1]=muerto12,muerto1c [2]=muerto11,muerto1c [3]=muerto12,muerto1c [4]=muerto11,muerto1c [5]=muerto12,muerto1c [6]=muerto13,muerto1c [7]=muerto14,muerto1c [8]=muerto15,muerto1c [9]=muerto16,muerto1c [10]=muerto17,muerto1c [11]=muerto18,muerto1c [12]=ultitra,muerto1c [13]=ultitra,muerto1c [14]=ultitra,muerto1c [15]=ultitra,muerto1c [16]=ultitra,muerto1c [17]=ultitra,muerto1c [18]=ultitra;
        muerto2c [0]=muerto21,muerto2c [1]=muerto22,muerto2c [2]=muerto21,muerto2c [3]=muerto22,muerto2c [4]=muerto21,muerto2c [5]=muerto22,muerto2c [6]=muerto23,muerto2c [7]=muerto24,muerto2c [8]=muerto25,muerto2c [9]=muerto26,muerto2c [10]=muerto27,muerto2c [11]=muerto28,muerto2c [12]=ultitra,muerto2c [13]=ultitra,muerto2c [14]=ultitra,muerto2c [15]=ultitra,muerto2c [16]=ultitra,muerto2c [17]=ultitra,muerto2c [18]=ultitra;

	getx (xb,yb,xb+18,yb+23,400,rubb1[1]);
        getx (ub,vb,ub+18,vb+23,400,rubb2[1]);

        do
           {
           timer_on();
           x3=x;y3=y;
           u3=u;v3=v;

	   if (limpia1==1) {limpia1=0;putx (((x+1)/16)*16+8,((y-10)/16)*16+24,PA,suelo);}
	   if (limpia2==1) {limpia2=0;putx (((u+1)/16)*16+8,((v-10)/16)*16+24,PA,suelo);}

           for (nb=0;nb<8;nb++)
	           {
		   if (SPt1 [nb]==1)//
			   {
			   SPt1 [nb]=0;
		           putz (hb1j1 [nb],hb2j1 [nb],PA,top__right [nb],top__left [nb],top__up [nb],top__down [nb],suelo);
                           pnum++;if (pnum>15) pnum=0;
	                   }

		   if (SPt2 [nb]==1)//
			   {
			   SPt2 [nb]=0;
		           putz (hb1j2 [nb],hb2j2 [nb],PA,top_right [nb],top_left [nb],top_up [nb],top_down [nb],suelo);
                           pnum++;if (pnum>15) pnum=0;
			   }
	           }

	   if (muerte1==0)
           	{
	   	if (!keyBoard.rightArrow && !keyBoard.leftArrow && !keyBoard.upArrow && !keyBoard.downArrow) {M1=0;q1=0;}
			else
			{
			if (keyBoard.upArrow) {y--;y--;MO1=2;q1=1;}
		     		else if (keyBoard.downArrow && !keyBoard.upArrow) {y++;y++;MO1=1;q1=2;}
		        		else if (keyBoard.leftArrow) {x--;x--;MO1=4;q1=3;}
		   				else if (keyBoard.rightArrow && !keyBoard.leftArrow) {x++;x++;MO1=3;q1=4;}
			}

	        if (keyBoard.ins && randi [((y-10)/16)][((x+1)/16)]!=5 && randi [((y-10)/16)][((x+1)/16)]!=7 && randi [((y-10)/16)][((x+1)/16)]!=11 && follow1==0 && ocupado1 [nbm1]==0 && bp1<nbmm1 && estallido1 [nbm1]==0)
			{
                        bp1++;
			b1j1[nbm1]=(((x+1)/16)*16)+8;b2j1[nbm1]=(((y-10)/16)*16)+24;
			randi [((y-10)/16)][((x+1)/16)]=5;
			randi2 [((y-10)/16)][((x+1)/16)]=(nbm1*2);follow1++;
			ocupado1 [nbm1]=1;nbm1++;if (nbm1>7) nbm1=0;
                        }
	        if (follow1!=0) {follow1++;if (follow1>7) follow1=0;}
           	}
	                else
	                {
			q1=0;M1=0;MO1=0;
			}

           if (muerte2==0)
           	{
	        if (!keyBoard.letD && !keyBoard.letA && !keyBoard.letW && !keyBoard.letX) {M2=0;q2=0;}
			else
			{
			if (keyBoard.letW) {v--;v--;MO2=2;q2=1;}
		     		else if (keyBoard.letX && !keyBoard.letW) {v++;v++;MO2=1;q2=2;}
		        		else if (keyBoard.letA) {u--;u--;MO2=4;q2=3;}
		   				else if (keyBoard.letD && !keyBoard.letA) {u++;u++;MO2=3;q2=4;}
			}

	        if (keyBoard.altizq && randi [((v-10)/16)][((u+1)/16)]!=5 && randi [((v-10)/16)][((u+1)/16)]!=7 && randi [((v-10)/16)][((u+1)/16)]!=11 && follow2==0 && ocupado2 [nbm2]==0 && bp2<nbmm2 && estallido2 [nbm2]==0)
			{
                        bp2++;
			b1j2[nbm2]=(((u+1)/16)*16)+8;b2j2[nbm2]=(((v-10)/16)*16)+24;
			randi [((v-10)/16)][((u+1)/16)]=5;
			randi2 [((v-10)/16)][((u+1)/16)]=((nbm2*2)+16);follow2++;
			ocupado2 [nbm2]=1;nbm2++;if (nbm2>7) nbm2=0;
			}
	        if (follow2!=0) follow2++;if (follow2>7) follow2=0;
                }
                	else
                        {
			q2=0;M2=0;MO2=0;
			}

           switch (q1)
           	{
    	   	case 1:if (randi[(y-17)/16][(x+1)/16]==5 && y==((y-17)/16)*16+31) y=y3;break;
      	   	case 2:if (randi[(y-2)/16][(x+1)/16]==5 && y==((y-2)/16)*16+3) y=y3;break;
                case 3:if (randi[(y-10)/16][(x-6)/16]==5 && x==((x-6)/16)*16+20) x=x3;break;
	   	case 4:if (randi[(y-10)/16][(x+9)/16]==5 && x==((x+9)/16)*16-8) x=x3;break;
                }

           if ((!(randi[(y-17)/16][(x-6)/16]%2) || !(randi[(y-17)/16][(x+9)/16]%2)) || (!(randi[(y-2)/16][(x-6)/16]%2) || !(randi[(y-2)/16][(x+9)/16]%2)))
	   	{
          	y=y3;
           	x=x3;
                ex11=randi[(y-10)/16][(x-7)/16];ex12=((x-7)/16)*16+22;
	        ex13=randi[(y-10)/16][(x+10)/16];ex14=((x+10)/16)*16-10;
                ex21=randi[(y-18)/16][(x+1)/16];ex22=((y-18)/16)*16+33;
	        ex23=randi[(y-1)/16][(x+1)/16];ex24=((y-1)/16)*16+1;
           	switch (q1)
           		{
           		case 1:r1=randi[(y-17)/16-1][(x+9)/16-1];r2=randi[(y-17)/16][(x+9)/16-1];if (r1%2 && r2%2 && r1!=5 && (!(ex11==5 && x==ex12))) {x--;x--;} else {r1=randi[(y-17)/16-1][(x-6)/16+1];r2=randi[(y-17)/16][(x-6)/16+1];if (r1%2 && r2%2 && r1!=5 && (!(ex13==5 && x==ex14))) {x++;x++;}};break;
   			case 2:r1=randi[(y-2)/16+1][(x+9)/16-1];r2=randi[(y-2)/16][(x+9)/16-1];if (r1%2 && r2%2 && r1!=5 && (!(ex11==5 && x==ex12))) {x--;x--;} else {r1=randi[(y-2)/16+1][(x-6)/16+1];r2=randi[(y-2)/16][(x-6)/16+1];if (r1%2 && r2%2 && r1!=5 && (!(ex13==5 && x==ex14))) {x++;x++;}};break;
           		case 3:r1=randi[(y-2)/16-1][(x-6)/16-1];r2=randi[(y-2)/16-1][(x-6)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex21==5 && y==ex22))) {y--;y--;} else {r1=randi[(y-17)/16+1][(x-6)/16-1];r2=randi[(y-17)/16+1][(x-6)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex23==5 && y==ex24))) {y++;y++;}};break;
   			case 4:r1=randi[(y-2)/16-1][(x+9)/16+1];r2=randi[(y-2)/16-1][(x+9)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex21==5 && y==ex22))) {y--;y--;} else {r1=randi[(y-17)/16+1][(x+9)/16+1];r2=randi[(y-17)/16+1][(x+9)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex23==5 && y==ex24))) {y++;y++;}};break;
                	}
	   	}

           switch (q2)
           	{
    	   	case 1:if (randi[(v-17)/16][(u+1)/16]==5 && v==((v-17)/16)*16+31) v=v3;break;
      	   	case 2:if (randi[(v-2)/16][(u+1)/16]==5 && v==((v-2)/16)*16+3) v=v3;break;
                case 3:if (randi[(v-10)/16][(u-6)/16]==5 && u==((u-6)/16)*16+20) u=u3;break;
	   	case 4:if (randi[(v-10)/16][(u+9)/16]==5 && u==((u+9)/16)*16-8) u=u3;break;
                }

           if ((!(randi[(v-17)/16][(u-6)/16]%2) || !(randi[(v-17)/16][(u+9)/16]%2)) || (!(randi[(v-2)/16][(u-6)/16]%2) || !(randi[(v-2)/16][(u+9)/16]%2)))
	   	{
           	v=v3;
           	u=u3;
                ex11=randi[(v-10)/16][(u-7)/16];ex12=((u-7)/16)*16+22;
	        ex13=randi[(v-10)/16][(u+10)/16];ex14=((u+10)/16)*16-10;
                ex21=randi[(v-18)/16][(u+1)/16];ex22=((v-18)/16)*16+33;
	        ex23=randi[(v-1)/16][(u+1)/16];ex24=((v-1)/16)*16+1;
           	switch (q2)
           		{
                        case 1:r1=randi[(v-17)/16-1][(u+9)/16-1];r2=randi[(v-17)/16][(u+9)/16-1];if (r1%2 && r2%2 && r1!=5 && (!(ex11==5 && u==ex12))) {u--;u--;} else {r1=randi[(v-17)/16-1][(u-6)/16+1];r2=randi[(v-17)/16][(u-6)/16+1];if (r1%2 && r2%2 && r1!=5 && (!(ex13==5 && u==ex14))) {u++;u++;}};break;
   			case 2:r1=randi[(v-2)/16+1][(u+9)/16-1];r2=randi[(v-2)/16][(u+9)/16-1];if (r1%2 && r2%2 && r1!=5 && (!(ex11==5 && u==ex12))) {u--;u--;} else {r1=randi[(v-2)/16+1][(u-6)/16+1];r2=randi[(v-2)/16][(u-6)/16+1];if (r1%2 && r2%2 && r1!=5 && (!(ex13==5 && u==ex14))) {u++;u++;}};break;
           		case 3:r1=randi[(v-2)/16-1][(u-6)/16-1];r2=randi[(v-2)/16-1][(u-6)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex21==5 && v==ex22))) {v--;v--;} else {r1=randi[(v-17)/16+1][(u-6)/16-1];r2=randi[(v-17)/16+1][(u-6)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex23==5 && v==ex24))) {v++;v++;}};break;
   			case 4:r1=randi[(v-2)/16-1][(u+9)/16+1];r2=randi[(v-2)/16-1][(u+9)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex21==5 && v==ex22))) {v--;v--;} else {r1=randi[(v-17)/16+1][(u+9)/16+1];r2=randi[(v-17)/16+1][(u+9)/16];if (r1%2 && r2%2 && r1!=5 && (!(ex23==5 && v==ex24))) {v++;v++;}};break;
                	}
	   	}

	if (randi[((v-10)/16)][((u+1)/16)]==7) {nbmm2++;randi[((v-10)/16)][((u+1)/16)]=1;putx (((u+1)/16)*16+8,((v-10)/16)*16+24,PA,suelo);limpia2=1;}
       	if (randi[((v-10)/16)][((u+1)/16)]==11) {ext2++;randi[((v-10)/16)][((u+1)/16)]=1;putx (((u+1)/16)*16+8,((v-10)/16)*16+24,PA,suelo);limpia2=1;}
	if (randi[((y-10)/16)][((x+1)/16)]==7) {nbmm1++;randi[((y-10)/16)][((x+1)/16)]=1;putx (((x+1)/16)*16+8,((y-10)/16)*16+24,PA,suelo);limpia1=1;}
	if (randi[((y-10)/16)][((x+1)/16)]==11) {ext1++;randi[((y-10)/16)][((x+1)/16)]=1;putx (((x+1)/16)*16+8,((y-10)/16)*16+24,PA,suelo);limpia1=1;}

	nbaux2=0;
        if (orn<pnum) hasta_aqui=(16-pnum+orn); else hasta_aqui=(orn-pnum);
        for (nbaux=0;nbaux<hasta_aqui;nbaux++)
   		{
                if (nbaux+pnum>15) nbaux2=16;
                nb=orden [nbaux+pnum-nbaux2];
		if (nb<10)
                {
                if (estallido1 [nb]==1)//
                	{
                        putb (hb1j1 [nb],hb2j1 [nb],PA,EX+4],top__right [nb],top__left [nb],EX+5],top__up [nb],top__down [nb],ext1,EX+2],EX+1],EX+7],EX+6],EX+3]);
                        mirarby=(hb2j1 [nb]-24)/16;mirarbx=(hb1j1 [nb]-8)/16;
                        mirary=((y-10)/16);mirarx=((x+1)/16);if (((mirarx<(mirarbx+top__right [nb]) && mirarx>(mirarbx-top__left [nb]) && mirary==mirarby) || (mirary<(mirarby+(top__down [nb])) && mirary>(mirarby-(top__up [nb])) && mirarx==mirarbx)) && muerte1==0) {muerte1=1;x--;}
                        mirary=((v-10)/16);mirarx=((u+1)/16);if (((mirarx<(mirarbx+top__right [nb]) && mirarx>(mirarbx-top__left [nb]) && mirary==mirarby) || (mirary<(mirarby+(top__down [nb])) && mirary>(mirarby-(top__up [nb])) && mirarx==mirarbx)) && muerte2==0) {muerte2=1;u--;}
                        if (demolerup1 [nb]>0 || demolerdo1 [nb]>0 || demolerle1 [nb]>0 || demolerri1 [nb]>0)
                        	{
	                        if (demolerup1 [nb]==1) {putx (hb1j1 [nb],hb2j1 [nb]-(top__up [nb]*16),PA,deshaz [hz1 [nb]/2]);randi [((hb2j1 [nb]-24)/16)-top__up [nb]][(hb1j1 [nb]-8)/16]=hz1 [nb]/9;}
				if (demolerup1 [nb]==2 || demolerup1 [nb]==3) {putx (hb1j1 [nb],hb2j1 [nb]-(top__up [nb]*16),PA,bombayfuego[demolerup1 [nb]-2]);if (hz1 [nb]>2) demolerup1 [nb]+=3;}
				if (demolerup1 [nb]==7 || demolerup1 [nb]==11) {putx (hb1j1 [nb],hb2j1 [nb]-(top__up [nb]*16),PA,suelo);if (hz1 [nb]>2) demolerup1 [nb]+=3;}
	                        if (demolerdo1 [nb]==1) {putx (hb1j1 [nb],hb2j1 [nb]+(top__down [nb]*16),PA,deshaz [hz1 [nb]/2]);randi [((hb2j1 [nb]-24)/16)+top__down [nb]][(hb1j1 [nb]-8)/16]=hz1 [nb]/9;}
				if (demolerdo1 [nb]==2 || demolerdo1 [nb]==3) {putx (hb1j1 [nb],hb2j1 [nb]+(top__down [nb]*16),PA,bombayfuego[demolerdo1 [nb]-2]);if (hz1 [nb]>2) demolerdo1 [nb]+=3;}
				if (demolerdo1 [nb]==7 || demolerdo1 [nb]==11) {putx (hb1j1 [nb],hb2j1 [nb]+(top__down [nb]*16),PA,suelo);if (hz1 [nb]>2) demolerdo1 [nb]+=3;}
	                        if (demolerle1 [nb]==1) {putx (hb1j1 [nb]-(top__left [nb]*16),hb2j1 [nb],PA,deshaz [hz1 [nb]/2]);randi [((hb2j1 [nb]-24)/16)][(hb1j1 [nb]-8)/16-top__left [nb]]=hz1 [nb]/9;}
				if (demolerle1 [nb]==2 || demolerle1 [nb]==3) {putx (hb1j1 [nb]-(top__left [nb]*16),hb2j1 [nb],PA,bombayfuego[demolerle1 [nb]-2]);if (hz1 [nb]>2) demolerle1 [nb]+=3;}
				if (demolerle1 [nb]==7 || demolerle1 [nb]==11) {putx (hb1j1 [nb]-(top__left [nb]*16),hb2j1 [nb],PA,suelo);if (hz1 [nb]>2) demolerle1 [nb]+=3;}
	                        if (demolerri1 [nb]==1) {putx (hb1j1 [nb]+(top__right [nb]*16),hb2j1 [nb],PA,deshaz [hz1 [nb]/2]);randi [((hb2j1 [nb]-24)/16)][(hb1j1 [nb]-8)/16+top__right [nb]]=hz1 [nb]/9;}
				if (demolerri1 [nb]==2 || demolerri1 [nb]==3) {putx (hb1j1 [nb]+(top__right [nb]*16),hb2j1 [nb],PA,bombayfuego[demolerri1 [nb]-2]);if (hz1 [nb]>2) demolerri1 [nb]+=3;}
				if (demolerri1 [nb]==7 || demolerri1 [nb]==11) {putx (hb1j1 [nb]+(top__right [nb]*16),hb2j1 [nb],PA,suelo);if (hz1 [nb]>2) demolerri1 [nb]+=3;}
                                hz1 [nb]++;
				if (hz1 [nb]==10)
					{
                                        if (demolerup1 [nb]==5) randi [((hb2j1 [nb]-24)/16)-top__up [nb]][(hb1j1 [nb]-8)/16]=7;
					if (demolerup1 [nb]==6) randi [((hb2j1 [nb]-24)/16)-top__up [nb]][(hb1j1 [nb]-8)/16]=11;
                                        if (demolerdo1 [nb]==5) randi [((hb2j1 [nb]-24)/16)+top__down [nb]][(hb1j1 [nb]-8)/16]=7;
					if (demolerdo1 [nb]==6) randi [((hb2j1 [nb]-24)/16)+top__down [nb]][(hb1j1 [nb]-8)/16]=11;
                                        if (demolerle1 [nb]==5) randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)-top__left [nb]]=7;
					if (demolerle1 [nb]==6) randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)-top__left [nb]]=11;
                                        if (demolerri1 [nb]==5) randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)+top__right [nb]]=7;
					if (demolerri1 [nb]==6) randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)+top__right [nb]]=11;
					demolerup1 [nb]=0;demolerdo1 [nb]=0;demolerle1 [nb]=0;demolerri1 [nb]=0;hz1 [nb]=0;
					}
                                }
             		des1 [nb]++;if (des1 [nb]>12)
					{
                                        des1 [nb]=0;estallido1 [nb]=0;
                                        randi [(hb2j1 [nb]-24)/16][(hb1j1 [nb]-8)/16]=1;
		           		putz (hb1j1 [nb],hb2j1 [nb],PA,top__right [nb],top__left [nb],top__up [nb],top__down [nb],suelo);SPt1 [nb]=1;
					}
                        }
		}
                else
                {
                nb-=20;
                if (estallido2 [nb]==1)//
                	{
                        putb (hb1j2 [nb],hb2j2 [nb],PA,EU+4],top_right [nb],top_left [nb],EU+5],top_up [nb],top_down [nb],ext2,EU+2],EU+1],EU+7],EU+6],EU+3]);
                        mirarby=(hb2j2 [nb]-24)/16;mirarbx=(hb1j2 [nb]-8)/16;
                        mirary=((v-10)/16);mirarx=((u+1)/16);if (((mirarx<(mirarbx+top_right [nb]) && mirarx>(mirarbx-top_left [nb]) && mirary==mirarby) || (mirary<(mirarby+(top_down [nb])) && mirary>(mirarby-(top_up [nb])) && mirarx==mirarbx)) && muerte2==0) {muerte2=1;u--;}
                        mirary=((y-10)/16);mirarx=((x+1)/16);if (((mirarx<(mirarbx+top_right [nb]) && mirarx>(mirarbx-top_left [nb]) && mirary==mirarby) || (mirary<(mirarby+(top_down [nb])) && mirary>(mirarby-(top_up [nb])) && mirarx==mirarbx)) && muerte1==0) {muerte1=1;x--;}
                        if (demolerup2 [nb]>0 || demolerdo2 [nb]>0 || demolerle2 [nb]>0 || demolerri2 [nb]>0)
                        	{
	                        if (demolerup2 [nb]==1) {putx (hb1j2 [nb],hb2j2 [nb]-(top_up [nb]*16),PA,deshaz [hz2 [nb]/2]);randi [((hb2j2 [nb]-24)/16)-top_up [nb]][(hb1j2 [nb]-8)/16]=hz2 [nb]/9;}
				if (demolerup2 [nb]==2 || demolerup2 [nb]==3) {putx (hb1j2 [nb],hb2j2 [nb]-(top_up [nb]*16),PA,bombayfuego[demolerup2 [nb]-2]);if (hz2 [nb]>2) demolerup2 [nb]+=3;}
				if (demolerup2 [nb]==7 || demolerup2 [nb]==11) {putx (hb1j2 [nb],hb2j2 [nb]-(top_up [nb]*16),PA,suelo);if (hz2 [nb]>2) demolerup2 [nb]+=3;}
	                        if (demolerdo2 [nb]==1) {putx (hb1j2 [nb],hb2j2 [nb]+(top_down [nb]*16),PA,deshaz [hz2 [nb]/2]);randi [((hb2j2 [nb]-24)/16)+top_down [nb]][(hb1j2 [nb]-8)/16]=hz2 [nb]/9;}
				if (demolerdo2 [nb]==2 || demolerdo2 [nb]==3) {putx (hb1j2 [nb],hb2j2 [nb]+(top_down [nb]*16),PA,bombayfuego[demolerdo2 [nb]-2]);if (hz2 [nb]>2) demolerdo2 [nb]+=3;}
				if (demolerdo2 [nb]==7 || demolerdo2 [nb]==11) {putx (hb1j2 [nb],hb2j2 [nb]+(top_down [nb]*16),PA,suelo);if (hz2 [nb]>2) demolerdo2 [nb]+=3;}
	                        if (demolerle2 [nb]==1) {putx (hb1j2 [nb]-(top_left [nb]*16),hb2j2 [nb],PA,deshaz [hz2 [nb]/2]);randi [((hb2j2 [nb]-24)/16)][(hb1j2 [nb]-8)/16-top_left [nb]]=hz2 [nb]/9;}
				if (demolerle2 [nb]==2 || demolerle2 [nb]==3) {putx (hb1j2 [nb]-(top_left [nb]*16),hb2j2 [nb],PA,bombayfuego[demolerle2 [nb]-2]);if (hz2 [nb]>2) demolerle2 [nb]+=3;}
				if (demolerle2 [nb]==7 || demolerle2 [nb]==11) {putx (hb1j2 [nb]-(top_left [nb]*16),hb2j2 [nb],PA,suelo);if (hz2 [nb]>2) demolerle2 [nb]+=3;}
	                        if (demolerri2 [nb]==1) {putx (hb1j2 [nb]+(top_right [nb]*16),hb2j2 [nb],PA,deshaz [hz2 [nb]/2]);randi [((hb2j2 [nb]-24)/16)][(hb1j2 [nb]-8)/16+top_right [nb]]=hz2 [nb]/9;}
				if (demolerri2 [nb]==2 || demolerri2 [nb]==3) {putx (hb1j2 [nb]+(top_right [nb]*16),hb2j2 [nb],PA,bombayfuego[demolerri2 [nb]-2]);if (hz2 [nb]>2) demolerri2 [nb]+=3;}
				if (demolerri2 [nb]==7 || demolerri2 [nb]==11) {putx (hb1j2 [nb]+(top_right [nb]*16),hb2j2 [nb],PA,suelo);if (hz2 [nb]>2) demolerri2 [nb]+=3;}
				hz2 [nb]++;
				if (hz2 [nb]==10)
					{
                                        if (demolerup2 [nb]==5) randi [((hb2j2 [nb]-24)/16)-top_up [nb]][(hb1j2 [nb]-8)/16]=7;
					if (demolerup2 [nb]==6) randi [((hb2j2 [nb]-24)/16)-top_up [nb]][(hb1j2 [nb]-8)/16]=11;
                                        if (demolerdo2 [nb]==5) randi [((hb2j2 [nb]-24)/16)+top_down [nb]][(hb1j2 [nb]-8)/16]=7;
					if (demolerdo2 [nb]==6) randi [((hb2j2 [nb]-24)/16)+top_down [nb]][(hb1j2 [nb]-8)/16]=11;
                                        if (demolerle2 [nb]==5) randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)-top_left [nb]]=7;
					if (demolerle2 [nb]==6) randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)-top_left [nb]]=11;
                                        if (demolerri2 [nb]==5) randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)+top_right [nb]]=7;
					if (demolerri2 [nb]==6) randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)+top_right [nb]]=11;

					demolerup2 [nb]=0;demolerdo2 [nb]=0;demolerle2 [nb]=0;demolerri2 [nb]=0;hz2 [nb]=0;}
                                }
             		des2 [nb]++;if (des2 [nb]>12)
					{
					des2 [nb]=0;estallido2 [nb]=0;
                                        randi [(hb2j2 [nb]-24)/16][(hb1j2 [nb]-8)/16]=1;
			                putz (hb1j2 [nb],hb2j2 [nb],PA,top_right [nb],top_left [nb],top_up [nb],top_down [nb],suelo);SPt2 [nb]=1;
					}
                        }
                }
		}
	for (nb=0;nb<8;nb++)
   		{
                if (ocupado1 [nb]==1)//
                	{
                	if (tt1 [nb]%10 || (tt1 [nb]-1)%10)
                		{
		                putx (b1j1 [nb],b2j1 [nb],PA,*(ll5+(tt1 [nb]/10)));
	                        }
        	        tt1 [nb]++;if (tt1 [nb]>39) {tt1 [nb]=0;TT1 [nb]++;if (TT1 [nb]>2) {TT1 [nb]=0;estallido1 [nb]=1;ocupado1 [nb]=0;bp1--;orden [orn++]=nb;if (orn>15) orn=0;
			top__up [nb]=ext1;top__down [nb]=ext1;top__left [nb]=ext1;top__right [nb]=ext1;upup=0;dodo=0;riri=0;lele=0;hb1j1 [nb]=b1j1 [nb];hb2j1 [nb]=b2j1 [nb];
			for (tropiezo=1;tropiezo<ext1;tropiezo++)
				{
                                if (!(randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16]%10) && upup==0) {demolerup1 [nb]=randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16]/10;randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16]=6;}
                                if ((randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16]==7 || randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16]==11) && upup==0) {demolerup1 [nb]=randi [((b2j1 [nb]-24)/16)-tropiezo][(b1j1 [nb]-8)/16];top__up [nb]=tropiezo;upup=1;randi [((hb2j1 [nb]-24)/16)-top__up [nb]][(hb1j1 [nb]-8)/16]=1;}
				if (!(randi [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]%2) && upup==0) {top__up [nb]=tropiezo;upup=1;}
                                	else if (randi [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]==5 && upup==0) {top__up [nb]=tropiezo;upup=1;if (estallido1 [randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]/2]==0 && randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]<16) {TT1 [randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]/2]=2;tt1 [randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]/2]=38;} else if (estallido2 [(randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]-16)/2]==0) {TT2 [(randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]-16)/2]=2;tt2 [(randi2 [(b2j1 [nb]-24)/16-tropiezo][(b1j1 [nb]-8)/16]-16)/2]=38;}}

                                if (!(randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16]%10) && dodo==0) {demolerdo1 [nb]=randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16]/10;randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16]=6;}
                                if ((randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16]==7 || randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16]==11) && dodo==0) {demolerdo1 [nb]=randi [((b2j1 [nb]-24)/16)+tropiezo][(b1j1 [nb]-8)/16];top__down [nb]=tropiezo;dodo=1;randi [((hb2j1 [nb]-24)/16)+top__down [nb]][(hb1j1 [nb]-8)/16]=1;}
				if (!(randi [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]%2) && dodo==0) {top__down [nb]=tropiezo;dodo=1;}
                                	else if (randi [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]==5 && dodo==0) {top__down [nb]=tropiezo;dodo=1;if (estallido1 [randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]/2]==0 && randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]<16) {TT1 [randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]/2]=2;tt1 [randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]/2]=38;} else if (estallido2 [(randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]-16)/2]==0) {TT2 [(randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]-16)/2]=2;tt2 [(randi2 [(b2j1 [nb]-24)/16+tropiezo][(b1j1 [nb]-8)/16]-16)/2]=38;}}

                                if (!(randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo]%10) && lele==0) {demolerle1 [nb]=randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo]/10;randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo]=6;}
                                if ((randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo]==7 || randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo]==11) && lele==0) {demolerle1 [nb]=randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)-tropiezo];top__left [nb]=tropiezo;lele=1;randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)-top__left [nb]]=1;}
				if (!(randi [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]%2) && lele==0) {top__left [nb]=tropiezo;lele=1;}
	                               	else if (randi [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]==5 && lele==0) {top__left [nb]=tropiezo;lele=1;if (estallido1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]/2]==0 && randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]<16) {TT1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]/2]=2;tt1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]/2]=38;} else if (estallido2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]-16)/2]==0) {TT2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]-16)/2]=2;tt2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16-tropiezo]-16)/2]=38;}}

                                if (!(randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo]%10) && riri==0) {demolerri1 [nb]=randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo]/10;randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo]=6;}
                                if ((randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo]==7 || randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo]==11) && riri==0) {demolerri1 [nb]=randi [(b2j1 [nb]-24)/16][((b1j1 [nb]-8)/16)+tropiezo];top__right [nb]=tropiezo;riri=1;randi [((hb2j1 [nb]-24)/16)][((hb1j1 [nb]-8)/16)+top__right [nb]]=1;}
				if (!(randi [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]%2) && riri==0) {top__right [nb]=tropiezo;riri=1;}
                                	else if (randi [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]==5 && riri==0) {top__right [nb]=tropiezo;riri=1;if (estallido1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]/2]==0 && randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]<16) {TT1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]/2]=2;tt1 [randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]/2]=38;} else if (estallido2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]-16)/2]==0) {TT2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]-16)/2]=2;tt2 [(randi2 [(b2j1 [nb]-24)/16][(b1j1 [nb]-8)/16+tropiezo]-16)/2]=38;}}
				}}}
		  	}
                if (ocupado2 [nb]==1)//
                	{
                	if (tt2 [nb]%10 || (tt2 [nb]-1)%10)
                		{
		                putx (b1j2 [nb],b2j2 [nb],PA,*(ll5+(tt2 [nb]/10)));
	                        }
        	        tt2 [nb]++;if (tt2 [nb]>39) {tt2 [nb]=0;TT2 [nb]++;if (TT2 [nb]>2) {TT2 [nb]=0;estallido2 [nb]=1;ocupado2 [nb]=0;bp2--;orden [orn++]=nb+20;if (orn>15) orn=0;
			top_up [nb]=ext2;top_down [nb]=ext2;top_left [nb]=ext2;top_right [nb]=ext2;upup=0;dodo=0;riri=0;lele=0;hb1j2 [nb]=b1j2 [nb];hb2j2 [nb]=b2j2 [nb];
			for (tropiezo=1;tropiezo<ext2;tropiezo++)
				{
                                if (!(randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16]%10) && upup==0) {demolerup2 [nb]=randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16]/10;randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16]=6;}
                                if ((randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16]==7 || randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16]==11) && upup==0) {demolerup2 [nb]=randi [((b2j2 [nb]-24)/16)-tropiezo][(b1j2 [nb]-8)/16];top_up [nb]=tropiezo;upup=1;randi [((hb2j2 [nb]-24)/16)-top_up [nb]][(hb1j2 [nb]-8)/16]=1;}
                                if (!(randi [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]%2) && upup==0) {top_up [nb]=tropiezo;upup=1;}
                                	else if (randi [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]==5 && upup==0) {top_up [nb]=tropiezo;upup=1;if (estallido2 [(randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]-16)/2]==0 && randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]>14) {TT2 [(randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]-16)/2]=2;tt2 [(randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]-16)/2]=38;} else if (estallido1 [randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]/2]==0) {TT1 [randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]/2]=2;tt1 [randi2 [(b2j2 [nb]-24)/16-tropiezo][(b1j2 [nb]-8)/16]/2]=38;}}
                                if (!(randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16]%10) && dodo==0) {demolerdo2 [nb]=randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16]/10;randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16]=6;}
                                if ((randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16]==7 || randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16]==11) && dodo==0) {demolerdo2 [nb]=randi [((b2j2 [nb]-24)/16)+tropiezo][(b1j2 [nb]-8)/16];top_down [nb]=tropiezo;dodo=1;randi [((hb2j2 [nb]-24)/16)+top_down [nb]][(hb1j2 [nb]-8)/16]=1;}
				if (!(randi [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]%2) && dodo==0) {top_down [nb]=tropiezo;dodo=1;}
                                	else if (randi [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]==5 && dodo==0) {top_down [nb]=tropiezo;dodo=1;if (estallido2 [(randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]-16)/2]==0 && randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]>14) {TT2 [(randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]-16)/2]=2;tt2 [(randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]-16)/2]=38;} else if (estallido1 [randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]/2]==0) {TT1 [randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]/2]=2;tt1 [randi2 [(b2j2 [nb]-24)/16+tropiezo][(b1j2 [nb]-8)/16]/2]=38;}}
                                if (!(randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo]%10) && lele==0) {demolerle2 [nb]=randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo]/10;randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo]=6;}
                                if ((randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo]==7 || randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo]==11) && lele==0) {demolerle2 [nb]=randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)-tropiezo];top_left [nb]=tropiezo;lele=1;randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)-top_left [nb]]=1;}
				if (!(randi [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]%2) && lele==0) {top_left [nb]=tropiezo;lele=1;}
                                	else if (randi [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]==5 && lele==0) {top_left [nb]=tropiezo;lele=1;if (estallido2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]-16)/2]==0 && randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]>14) {TT2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]-16)/2]=2;tt2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]-16)/2]=38;} else if (estallido1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]/2]==0) {TT1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]/2]=2;tt1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16-tropiezo]/2]=38;}}
                                if (!(randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo]%10) && riri==0) {demolerri2 [nb]=randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo]/10;randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo]=6;}
                                if ((randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo]==7 || randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo]==11) && riri==0) {demolerri2 [nb]=randi [(b2j2 [nb]-24)/16][((b1j2 [nb]-8)/16)+tropiezo];top_right [nb]=tropiezo;riri=1;randi [((hb2j2 [nb]-24)/16)][((hb1j2 [nb]-8)/16)+top_right [nb]]=1;}
				if (!(randi [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]%2) && riri==0) {top_right [nb]=tropiezo;riri=1;}
                                	else if (randi [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]==5 && riri==0) {top_right [nb]=tropiezo;riri=1;if (estallido2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]-16)/2]==0 && randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]>14) {TT2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]-16)/2]=2;tt2 [(randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]-16)/2]=38;} else if (estallido1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]/2]==0) {TT1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]/2]=2;tt1 [randi2 [(b2j2 [nb]-24)/16][(b1j2 [nb]-8)/16+tropiezo]/2]=38;}}
				}}}
		  	}
                }

        getx (x,y,x+19+muerte1,y+23,PA,rubb1[PAG-1]);
        getx (u,v,u+19+muerte2,v+23,PA,rubb2[PAG-1]);

        if (M1>19) M1=0;
	if (M2>19) M2=0;

        //the next condition will print at first the player which is upper
        if ((y-v)<0)
        	{
	        switch (MO1)
	        	{
	                // abajojug1
	        	case 1:putx (x,y,PA,l[M1++/5]);break;
			// arribajug1
	        	case 2:putx (x,y,PA,l2[M1++/5]);break;
			//derechajug1
	        	case 3:putx (x,y,PA,l3[M1++/5]);break;
			//izquierdajug1
	        	case 4:putx (x,y,PA,l4[M1++/5]);break;
	                }
	        switch (MO2)
	        	{
			//abajojug2
	        	case 1:putx (u,v,PA,ll[M2++/5]);break;
			//arribajug2
	        	case 2:putx (u,v,PA,ll2[M2++/5]);break;
			//derechajug2
			case 3:putx (u,v,PA,ll3[M2++/5]);break;
			//izquierdajug2
	        	case 4:putx (u,v,PA,ll4[M2++/5]);break;
	                }
                }
                else
                {
	        switch (MO2)
	        	{
			//abajojug2
	        	case 1:putx (u,v,PA,ll[M2++/5]);break;
			//arribajug2
	        	case 2:putx (u,v,PA,ll2[M2++/5]);break;
			//derechajug2
			case 3:putx (u,v,PA,ll3[M2++/5]);break;
			//izquierdajug2
	        	case 4:putx (u,v,PA,ll4[M2++/5]);break;
	                }
	        switch (MO1)
	        	{
	                // abajojug1
	        	case 1:putx (x,y,PA,l[M1++/5]);break;
			// arribajug1
	        	case 2:putx (x,y,PA,l2[M1++/5]);break;
			//derechajug1
	        	case 3:putx (x,y,PA,l3[M1++/5]);break;
			//izquierdajug1
	        	case 4:putx (x,y,PA,l4[M1++/5]);break;
	                }
                }

        if (muerte1==1)
		{
                putx (x,y+1,PA,muerto1c [avav1/5]);avav1++;if (avav1>94) muerte1++;
		}
        if (muerte2==1)
		{
                putx (u,v+1,PA,muerto2c [avav2/5]);avav2++;if (avav2>94) muerte2++;
		}
        if ((muerte1==2 && muerte2==0) || (muerte2==2 && muerte1==0) || (muerte1==2 && muerte2==2)) goto FIN;

        SetPage (PAG++);
        WaitVRetrace();
        if (PAG>2) {PAG=1;PA=200;putx (xb2,yb2,200,rubb1[0]);xb=x;yb=y;putx (ub2,vb2,200,rubb2[0]);ub=u;vb=v;}
        	else {PA=400;putx (xb,yb,400,rubb1[1]);xb2=x;yb2=y;putx (ub,vb,400,rubb2[1]);ub2=u;vb2=v;}
        do T=timer_off ();while (T<30000 && T>0);

           }
           while (!keyBoard.esc);

        FIN:

        fundido ();

        setvect(KEYBD,oldvec);

 	modotexto ();
	}
