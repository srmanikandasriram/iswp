#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct settings
{
	char username[20],password[20];
	int type;
	void getuser();
	int usercheck();
}curuser;

int settings::usercheck()
{
	/* this function returns 1 if user already exists and 0 if it does not exist*/
	settings t;
	fstream ifile("settings.dat",ios::binary | ios::in);
	while(!ifile.eof())
	{
		ifile.read((char *)&t,sizeof(t));
		if(strcmp(t.username,username)==0&&strcmp(t.password,password)==0)
		{
			ifile.close();
			return 1;
		}
	}
	ifile.close();
	return 0;
}

void settings::getuser()
{
	/* inputs username and password */
	gotoxy(30,15);cout<<"Enter username: ";
	gets(username);
	int i=0,j; 
	char ch;
	do{
		gotoxy(30,17);cout<<" Please enter a Password that is greater than 6 characters long";
		gotoxy(30,19);cout<<"Password:";
		i=0;
		char ch;
		while(ch!=13)
		{
			ch=getch();
			password[i++]=ch;
			gotoxy(40+j++,19);cout<<"*";
		}
		password[i]='\0';
	}while(strlen(password)<6);
}

int mainmenu()
{

clrscr();
gotoxy(30,15);cout<<"1.create new user";
gotoxy(30,17);cout<<"2.search for userdetails";
gotoxy(30,19);cout<<"3. deleteuser";
gotoxy(30,21);cout<<"4. view all users";
gotoxy(30,23);cout<<"5. delte all users";
int n;
cin>>n;
return n;
}
void main()
{
	fstream ifile,ofile;
	settings u,t;
	char ch,user1[20],pass1[20];
	int a=1,b,c,d,e;
again:
	int i = mainmenu();
	switch(i)
	{
case 1:
	{
newuser:
		/* adding a user */
		clrscr();
	ofile.open("settings.dat",ios::binary|ios::out|ios::app);
	u.getuser();
	if(u.usercheck()==1){cout<<"\n Sorry  User already exists!returning to main menu...";ofile.close();getch();goto newuser;}
	ofile.write((char*)&u,sizeof(u));
	ofile.close();
	cout<<"\n User added.press m to return to main menu ";
	cin>>ch;
	if(ch == 'm')
	goto again;
	break;
	}
case 2:
{
	/* searching for user */
	clrscr();
	gotoxy(30,15);cout<<" Enter username:";
	gets(user1);
	ifile.open("settings.dat",ios::binary | ios::in);
	while(!ifile.eof())
	{
	ifile.read((char*)&u,sizeof(u));
	if(strcmp(u.username,user1) == 0)
	{a=0;break;}}
	if(a==0) {gotoxy(30,17); cout<<user1;}
	else {gotoxy(30,17);cout<<"\n not found";}
	ifile.close();
	cout<<"\n Press m to return to main menu";
	cin>>ch;
	if(ch=='m')
	goto again;
}
deluser:
case 3:
{	/* deleting user */
	clrscr();
	gotoxy(20,13);cout<<"\n Entet details of the user to delete: ";
	t.getuser();
	if(t.usercheck()==0){cout<<"\n user not found"; getch();goto again;}
	ifstream ifi("settings.dat",ios::binary);
	ofstream ofi("newsettings.dat",ios::binary);
	while(!ifi.eof())
	{
	ifi.read((char*)&u,sizeof(u));
	if(strcmp(t.username,u.username)!=0)
		ofi.write((char*)&u,sizeof(u));
	}
	ifi.close();
	ofi.close();
	remove("settings.dat");
	rename("newsettings.dat","settings.dat");
	cout<<"\n user deleted.. press m to return to main menu";
	cin>>ch;
	if(ch=='m')
	goto again;
	break;

}

case 4:
{       clrscr();
	gotoxy(30,10);cout<<" the existing users :";
	ifstream file("settings.dat",ios::binary);
	if(file)
	{
	gotoxy(30,12);cout<<"username       password";
	while(file.read((char*)&u,sizeof(u)))
       {
	gotoxy(30,16+i);cout<<u.username<<"\t\t"<<u.password;
	i+=2;
	}
	file.close();
	}
	cout<<"\n Press m to return to main menu";
	cin>>ch;
	if(ch=='m')
	goto again;
}
case 5:
{ofile.open("newsettings.dat",ios::binary|ios::in);
ofile.close();
remove("settings.dat");
rename("newsettings.dat","settings.dat");
goto again;
}
}
}
