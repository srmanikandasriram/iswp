#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<process.h>

int mainmenu()
{
	clrscr();
	cout<<"\nWelcome to Intesoft Word Processor help";
	cout<<"\n---------------------------------------";
	cout<<"\n\n\n";
	cout<<"Contents\n";
	cout<<"\n1.Getting Started";
	cout<<"\n2.File Menu";
	cout<<"\n3.Edit Menu";
	cout<<"\n4.Format Menu";
	cout<<"\n5.View Menu";
	cout<<"\n6.Exit\n";
	int n;
	cout<<"\nEnter your choice:";
	cin>>n;
	return n;
}
void main()
{
	clrscr();
	int n;
again:
	n = mainmenu();
	switch(n)
	{
	case 1:
		{
		/* getting started */
		clrscr();
		cout<<"\nOpening screen";
		cout<<"\n--------------";
		cout<<"\nWhen you open intesoft word processor a splash screen will open followed by the login screen.Please enter your username and password to enter the working screen";
		cout<<"\nWork area";
		cout<<"\n---------";
		cout<<"\nREFRESH : press the left top button to refresh the screen.\nPress Esc to start working with the current document ";
		cout<<"\n\n\n===============================================================================";
		cout<<"\nB:Back to main menu \t \t E:Exit\n";
		char ch;
		do{
		ch=getch();
		}while(ch!='E'&&ch!='e'&&ch!='B'&&ch!='b');
		if(ch=='B'|| ch=='b')
			goto again;
		else
		{
			clrscr();
			exit(0);
		}
		break;
		}

	case 2:
		{
		clrscr();
		cout<<"\nNew";
		cout<<"\n---";
		cout<<"\nOpens a new document. When you open a new document it will be asssigned a default name by intesoft word processor. gTo change the default name of the document go to file -> save as and type the desired name for the file";
		cout<<"\nOpen";
		cout<<"\n----";
		cout<<"\nGo to file-> open and type the file name with the extension '.dat.This will open an already existing file. It will be added to the tabs on the left hand side of your screen. \nYou can toggle between currently  opened document by clicking on the respective tabs";
		cout<<"\nSave";
		cout<<"\n----";
		cout<<"\nGo to file -> save to save your document.";
		cout<<"\n\n\n===============================================================================";
		cout<<"\nB:Back to main menu \t \t E:Exit\n";
		char ch;
		do{
		ch=getch();
		}while(ch!='E'&&ch!='e'&&ch!='B'&&ch!='b');
		if(ch=='B'|| ch=='b')
			goto again;
		else
		{
			clrscr();
			exit(0);
		}
		break;
		}

	case 3:

		{
		clrscr();
		cout<<"\nCut";
		cout<<"\n---";
		cout<<"\nGo to edit -> cut. Left click at the start position. Then left click on the ending position.";
		cout<<"\nCopy";
		cout<<"\n----";
		cout<<"\nGo to edit -> copy. Left click at the start position . Then left click on the ending position.";
		cout<<"\nPaste";
		cout<<"\n-----";
		cout<<"\nGo to edit -> paste. CLick on the position where you want to paste the cut or copied text.";
		cout<<"\n\n\n===============================================================================";
		cout<<"\nB:Back to main menu \t \t E:Exit\n";
		char ch;
		do{
		ch=getch();
		}while(ch!='E'&&ch!='e'&&ch!='B'&&ch!='b');
		if(ch=='B'|| ch=='b')
			goto again;
		else
		{
			clrscr();
			exit(0);
		}
		break;
		}
	case 4:
		{
		clrscr();
		cout<<"\nFont";
		cout<<"\n----";
		cout<<"\nGo to format -> font. A font dialog box will open. Select the desired font and also the colour and then click okay. The changes will be applied.";
		cout<<"\n\n\n===============================================================================";
		cout<<"\nB:Back to main menu \t \t E:Exit\n";
		char ch;
		do{
		ch=getch();
		}while(ch!='E'&&ch!='e'&&ch!='B'&&ch!='b');
		if(ch=='B'|| ch=='b')
			goto again;
		else
		{
			clrscr();
			exit(0);
		}
		break;
		}
	case 5:

		{

		clrscr();
		cout<<"\nFiledetails";
		cout<<"\n-----------";
		cout<<"\nGo to view -> filedetails. You can see the details of the current file.";
		cout<<"\nStatusbar";
		cout<<"\n---------";
		cout<<"\nYou can toggle whether status bar should be visible or not";
		cout<<"\n\n\n===============================================================================";
		cout<<"\nB:Back to main menu \t \t E:Exit\n";
		char ch;
		do{
		ch=getch();
		}while(ch!='E'&&ch!='e'&&ch!='B'&&ch!='b');
		if(ch=='B'|| ch=='b')
			goto again;
		else
		{
			clrscr();
			exit(0);
		}
		break;
		}
	case 6 :
		exit(0);
		break;
	}
 }