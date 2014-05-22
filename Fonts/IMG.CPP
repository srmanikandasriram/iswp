#include<graphics.h>
#include<fstream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char byte;
typedef unsigned short word;

struct dimensions{
	int left,right;
}d;
void main()
{
clrscr();
int gdriver=DETECT, gmode;
gdriver=installuserdriver("SVGA",NULL);
cout<<gdriver;
gmode=5;
initgraph(&gdriver,&gmode,"");
delay(1000);
fstream img("C:/iswp/fonts/TNR.bmp",ios::binary|ios::in);
int magic,width,height,ncolors;
img.read((char *)&magic,2);
img.seekg(16,ios::cur);
img.read((char *)&width,sizeof(word));
img.seekg(2,ios::cur);
img.read((char *)&height,sizeof(word));
img.seekg(22,ios::cur);
img.read((char *)&ncolors,sizeof(word));
img.seekg(18,ios::cur);
ncolors=2;
setrgbpalette(0,255,255,255);
setrgbpalette(1,0,0,0);
long start,start1;
start=img.tellg();
img.close();
char text;
int asc,x,y;
int posx=100,posy=100;
char temp[1];
temp[1]='\0';
char *text1;
strcpy(text1,"My name is S.R.Manikandasriram");
text='B';
int a;
for(int i=0;text1[i]!='\0';i++)
{
	x=0;
	y=height;
	img.open("C:/iswp/fonts/TNR.bmp",ios::binary|ios::in);
	text=text1[i];
	img.seekg(start);
	asc=text;
	asc-=32;
	d.left=10;
	d.right=20;
	if(text!=' ')
	{
	while(y>=32*(asc/19+1))
		{
		img.seekg(width+1,ios::cur);
		y--;
	}
	asc=asc%19;
	img.seekg(asc*30+1,ios::cur);
	start1=img.tellg();
	for(y=1;y<31;y++)
	{
		for(x=1;x<30;x++)
		{
			a=(byte)img.get();
			if(a==0)
			{
				if(x<d.left)
					d.left=x;
				if(x>d.right)
					d.right=x;
			}
		}
		img.seekg(width-28,ios::cur);
	}
	img.close();
	}
	img.open("C:/iswp/fonts/TNR.bmp",ios::binary|ios::in);
	img.seekg(start1+d.left);
	posy+=30;
	for(y=1;y<31;y++,posy--)
	{
		for(x=1;x<30;x++)
		{
			a=(byte)img.get();
			putpixel(posx++,posy,!a);

		}
		img.seekg(width-28,ios::cur);
		posx-=29;
	}
	posx+=d.right-d.left;
	img.close();
}
getch();
closegraph();
}

