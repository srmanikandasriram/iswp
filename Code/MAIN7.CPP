#include<c:/ISWP/code/invars1.cpp>
#include<c:/ISWP/code/image.cpp>
#include<c:/ISWP/code/file.cpp>
#include<c:/ISWP/code/mouse.cpp>


void refresh()
{
	cleardevice();
	imgload("C:/ISWP/Images/home.bmp",0,0,0);
	char *temp;
	for(int i=0;i<no_of_docs;i++)
	{
		imgload("c:/ISWP/images/tab.bmp",2,(i+1)*69+93,0);
		setcolor(53);
		outtextxy(16,(i+1)*69+128,filename[i]);
	}
	doc[curdoc-1].outputtext();
	outtextxy(90,70,fname[font.font]);
}

void main()
{
	gdriver=installuserdriver("SVGA",NULL);
	cout<<gdriver;
	gmode=1;
	initgraph(&gdriver,&gmode, "");
	initmouse();
	initvars();
	initpal("c:/ISWP/images/splash.bmp");
	imgload("c:/ISWP/images/splash.bmp",0,0,0);
	delay(200);
	cleardevice();
	initpal("c:/ISWP/images/login.bmp");
	imgload("c:/ISWP/images/login.bmp",0,0,0);	
	while(mousehandle(1))
	{
		cleardevice();
		imgload("c:/ISWP/images/login.bmp",0,0,0);
	}
	if(login==1)
	{
		cleardevice();	
		for(int i=0;i<10;i++)
			delete &doc[i];
		closegraph();
		clrscr();	
	}
	cleardevice();
	initpal("c:/ISWP/images/home.bmp");
	imgload("c:/ISWP/images/home.bmp",0,0,0);
	initmouse();
	doc[0].create();
	mousehandle(2);
	cleardevice();	
	for(int i=0;i<10;i++)
		delete &doc[i];
	closegraph();
	clrscr();
}