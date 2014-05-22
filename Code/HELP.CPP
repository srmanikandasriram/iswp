#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<process.h>

int mainmenu()
{
	cleardevice();
	char ch;
	int i=0;
	int a[6]={15,15,15,15,15,15};
	settextstyle(7,0,7);
	outtextxy(170,20,"HELP");
	settextstyle(8,0,2);
	outtextxy(170,100,"1.Getting Started");
	outtextxy(170,130,"2.File");
	outtextxy(170,160,"3.Edit");
	outtextxy(170,190,"4.Format");
	outtextxy(170,220,"5.View");
	outtextxy(170,250,"6.Exit");
	do
	{
		ch = getch();
		if (ch==50)
		{
			a[i]=15;
			a[i+1]=5;
			i++;
		}
		if(ch==56)
		{
			a[i]=15;
			a[i-1]=5;
			i--;
		}
		settextstyle(8,0,2);
		setcolor(a[0]);
		outtextxy(170,100,"1.Getting Started");
		setcolor(a[1]);
		outtextxy(170,130,"2.File");
		setcolor(a[2]);
		outtextxy(170,160,"3.Edit");
		setcolor(a[3]);
		outtextxy(170,190,"4.Format");
		setcolor(a[4]);
		outtextxy(170,220,"5.View");
		setcolor(a[5]);
		outtextxy(170,250,"6.Exit");
	} while(ch!=13);
	int n=i+1;
	return n;
}
void main()
{
	clrscr();
	int gdriver=DETECT, gmode;
	initgraph(&gdriver,&gmode,"");
	int n;
again:
	n = mainmenu();
	switch(n)
	{
	case 1:		 
		/* getting started */
		setfillstyle(1,0);
		bar(0,0,getmaxx(),getmaxy());
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,20,"Opening screen");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,50,"When you open intesoft word processor a splash screen will open followed by the login screen. please ");
		outtextxy(20,60,"enter your username and password to enter the working screen");
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,80,"Work area");
		setcolor(15);
		settextstyle(2,0,0);
		outtextxy(20,110,"REFRESH : press the left top button to refresh the screen");
		outtextxy(20,120,"Press Esc to start working with the current document");
		outtextxy(550,470,"press m to return to help main menu");
		char ch=getch();
		if(ch=='m')
			goto again;
		break;		 
	case 2:		 
		/*file*/
		setfillstyle(1,0);
		bar(0,0,getmaxx(),getmaxy());
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,20,"1.New");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,50,"Opens a new document. When you open a new document it will be asssigned a default name by intesoft word");
		outtextxy(20,60,"processor. Go to file -> save as and type the desired name for the file");
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,80,"2. open");
		setcolor(15);
		settextstyle(2,0,0);
		outtextxy(20,110,"Go to file-> open and type the file name with the extension '.dat'");
		outtextxy(20,120,"Opens an already existing file. It will be added to the tabs on the left of your screen. You can toggle ");
		outtextxy(20,130,"between currently  opened document by clicking on the tab");
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,150,"3. Save");
		setcolor(15);
		settextstyle(2,0,0);
		outtextxy(20,170,"Go to file -> save to save your document.  ");
		outtextxy(450,470,"press m to return to help main menu");
		ch=getch();
		if(ch=='m')
			goto again;
		break;
	case 3:
		/* edit*/
		setfillstyle(1,0);
		bar(0,0,getmaxx(),getmaxy());
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,20,"1. Cut");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,50,"Go to edit -> cut. Left click at the start position. Then left click on the ending position.");
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,80,"2.copy");
		setcolor(15);
		settextstyle(2,0,0);
		outtextxy(20,110,"Go to edit -> copy. Left click at the start position . Then left click on the ending position.");
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,130,"3. Paste");
		setcolor(15);
		settextstyle(2,0,0);
		outtextxy(20,150,"Go to edit -> paste. CLick on the position where you want to paste it.");
		outtextxy(550,470,"press m to return to help main menu");
		ch=getch();
		if(ch=='m')
			goto again;
		break;
	case 4:
		/*format*/
		setfillstyle(1,0);
		bar(0,0,getmaxx(),getmaxy());
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,20,"1. font");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,50,"Go to format -> font. A font dialog box willl open. Select the font and also the colour");
		outtextxy(20,60,"and then click okay. The changes will be applied.");
		outtextxy(550,470,"press m to return to help main menu");
		ch=getch();
		if(ch=='m')
			goto again;
		break;
	case 5:
		/*view*/
		setfillstyle(1,0);
		bar(0,0,getmaxx(),getmaxy());
		setcolor(5);
		settextstyle(7,0,2);
		outtextxy(20,20,"1. filedetails");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,50,"Go to view -> filedetails. You can see the details of the current file.");
		settextstyle(7,0,2);
		setcolor(5);
		outtextxy(20,70,"2.Status Bar");
		settextstyle(2,0,0);
		setcolor(15);
		outtextxy(20,90,"You can toggle whether status bar should be visible or not");
		outtextxy(550,470,"press m to return to help main menu");
		ch=getch();
		if(ch=='m')
			goto again;
		break;
	case 6 :
		exit(0);
		break;
	}
	closegraph();
 }