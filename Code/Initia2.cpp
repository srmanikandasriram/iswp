#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>

char username[20],password[20],ch1;
int i;

struct settings
{
	char username[20],password[20];
	int type;
}curuser,buff;

int checkusername();
int checkpassword(char duplicate[]);
int authorize();

void main()
{
	ifstream ifile;
	ofstream ofile;
	int ch=0;
	int found=1;
	do{		
		clrscr();
		cout<<"\n Welcome to Intesoft Word Processor User Manager!";
		cout<<"\n1. Create new user";
		cout<<"\n2. Search and Modify userdetails";
		cout<<"\n3. Delete user";
		cout<<"\n4. View all users";
		cout<<"\n5. Delete all users";
		cout<<"\n6. Exit";
		cout<<"\n Enter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1:
			/* New User */
			clrscr();
			cout<<"\n Welcome to Intesoft Word Processor User Manager!";
			cout<<"\n Create new user ";
			char duplicate[20];
			do{
				cout<<"\n\n I Enter user name (Max 20 characters): ";
				cin>>curuser.username;
				cout<<"\n checking availability of username...";
			}while(checkusername()==1);
			do{
				cout<<"\n\n II Enter password (5-20 characters): ";
				i=0;ch1='*';
				while(ch1!=13)
				{
					ch1=getch();
					if(ch1>31&&ch1<127)
					{
						curuser.password[i++]=ch1;					
						cout<<"*";
					}					
				}
				curuser.password[i]='\0';				
				cout<<"\n II Re-enter password : ";
				i=0;ch1='*';
				while(ch1!=13)
				{
					ch1=getch();
					if(ch1>31&&ch1<127)
					{
						duplicate[i++]=ch1;					
						cout<<"*";
					}				
				}
				duplicate[i]='\0';
			}while(checkpassword(duplicate)==1);
			cout<<"\n III Enter account type:";
			cout<<"\n 1. Administrator (requires Authorization)";
			cout<<"\n 2. Limited";
			cout<<"\n Enter your choice:";
			cin>>curuser.type;
			if(curuser.type==1&&authorize()==1)
					cout<<"\n Account creation failed! ";
			else
			{
					ofile.open("settings.dat",ios::binary|ios::out|ios::app);
					ofile.write((char*)&curuser,sizeof(curuser));
					ofile.close();
					cout<<"\n Account successfully created! ";
			}
			cout<<"\n Returning to Main Menu...";
			delay(2000);
			break;
		case 2:
			/* Search and Modify user */
			clrscr();
			cout<<"\n Welcome to Intesoft Word Processor User Manager!";
			cout<<"\n Search user ";
			cout<<"\n\n Enter user name : ";
			cin>>curuser.username;
			cout<<"\n Enter password : ";
			i=0;ch1='*';
			while(ch1!=13)
			{
				ch1=getch();
				if(ch1>31&&ch1<127)
				{
					curuser.password[i++]=ch1;					
					cout<<"*";
				}				
			}
			curuser.password[i]='\0';
			fstream file("Settings.dat",ios::binary|ios::in|ios::out);
			while(file.read((char*)&buff,sizeof(buff)))
			{
				if(strcmp(buff.username,curuser.username)==0&&strcmp(buff.password,curuser.password)==0)
				{
					found=0;
					cout<<"\n User account found.";
					break;
				}
			}
			if(found==1)
				cout<<"\n User account does not exist! ";
			else
			{
				cout<<"\n User account Modify ";
				cout<<"\n 1. Change Password";
				cout<<"\n 2. Change Type";
				cout<<"\n 3. Make no change";
				cout<<"\n Enter your choice :";
				int ch=3;
				cin>>ch;
				switch(ch)
				{
				case 1:
					cout<<"\n Enter Current password :";
					i=0;ch1='*';
					while(ch1!=13)
					{
						ch1=getch();
						if(ch1>31&&ch1<127)
						{
							password[i++]=ch1;					
							cout<<"*";
						}				
					}
					password[i]='\0';
					if(strcmp(curuser.password,password)!=0)
					{
						cout<<"\n Password incorrect ";
						cout<<"\n returning to Main Menu... ";
						break;
					}
					do{
						cout<<"\n Enter New password (5-20 characters): ";
						i=0;ch1='*';
						while(ch1!=13)
						{
							ch1=getch();
							if(ch1>31&&ch1<127)
							{
								curuser.password[i++]=ch1;					
								cout<<"*";
							}				
						}
						curuser.password[i]='\0';
						cout<<"\n Re-enter password : ";
						i=0;ch1='*';
						while(ch1!=13)
						{
							ch1=getch();
							if(ch1>31&&ch1<127)
							{
								duplicate[i++]=ch1;					
								cout<<"*";
							}				
						}
						duplicate[i]='\0';
					}while(checkpassword(duplicate)==1);
					file.seekp(-sizeof(buff),ios::cur);
					file.write((char *)&curuser,sizeof(curuser));
					cout<<"\n Password changed successfully. ";
					break;
				case 2:
					cout<<"\n Enter account type:";
					cout<<"\n 1. Administrator (requires Authorization)";
					cout<<"\n 2. Limited";
					cout<<"\n Enter your choice:";
					cin>>curuser.type;
					if(curuser.type==1&&authorize()==1)
						cout<<"\n Account modification failed! ";
					else
					{
						file.seekp(-sizeof(buff),ios::cur);
						file.write((char*)&curuser,sizeof(curuser));
						cout<<"\n Account successfully modified! ";
					}
					break;
				}
			}
			file.close();
			cout<<"\n Returning to Main Menu...";
			delay(2000);
			break;
		case 3:
			/* Delete User */
			clrscr();
			cout<<"\n Welcome to Intesoft Word Processor User Manager!";
			cout<<"\n Delete user ";
			cout<<"\n\n Enter user name : ";
			cin>>curuser.username;
			cout<<"\n Enter password : ";
			i=0;ch1='*';
			while(ch1!=13)
			{
				ch1=getch();
				if(ch1>31&&ch1<127)
				{
					curuser.password[i++]=ch1;					
					cout<<"*";
				}				
			}
			curuser.password[i]='\0';
			if(strcmp(curuser.username,"admin")==0)
				cout<<"\n Master User account cannot be deleted!";
			else
			{
				ifile.open("Settings.dat",ios::binary|ios::in);
				ofile.open("Newsettings.dat",ios::binary|ios::out);
				while(ifile.read((char*)&buff,sizeof(buff)))
				{
					if(strcmp(buff.username,curuser.username)==0&&strcmp(buff.password,curuser.password)==0)
					{
						found=0;
						cout<<"\n User account found.";
					}
					else
					{
						ofile.write((char *)&buff,sizeof(buff));
					}
				}
				ifile.close();
				ofile.close();
				remove("settings.dat");
				rename("newsettings.dat","settings.dat");
				if(found==1)
					cout<<"\n User account does not exist! ";
				else
					cout<<"\n User account Deleted successfully.";
			}
			cout<<"\n Returning to Main Menu...";
			delay(2000);
			break;
		case 4:
			/* View All Users */
			clrscr();
			cout<<"\n Welcome to Intesoft Word Processor User Manager!";
			cout<<"\n View all users ";
			ifile.open("Settings.dat",ios::binary|ios::in);
			while(ifile.read((char *)&curuser,sizeof(curuser)))
			{
				cout<<"\n Username : "<<curuser.username;
				cout<<"\n Account Type : ";
				if(curuser.type==1)
					cout<<"Administrator\n";
				else
					cout<<"Limited\n";
			}
			ifile.close();
			cout<<"\n Press any key to return to Main Menu.";
			getch();
			break;
		case 5:
			/* Delete All Users */
			clrscr();
			cout<<"\n Welcome to Intesoft Word Processor User Manager!";
			cout<<"\n Delete all users ";
			cout<<"\n\n Enter Master Password : ";
			i=0;ch1='*';
			while(ch1!=13)
			{
				ch1=getch();
				if(ch1>31&&ch1<127)
				{
					password[i++]=ch1;					
					cout<<"*";
				}				
			}
			password[i]='\0';
			ifile.open("Settings.dat",ios::binary|ios::in);
			ifile.read((char *)&curuser,sizeof(curuser));
			if(strcmp(buff.password,curuser.password)==0)
			{
				cout<<"\n Password accepted. Deleting all the users except Master user...";
				ifile.close();
				ofile.open("settings.dat",ios::binary|ios::out);
				ofile.write((char *)&curuser,sizeof(curuser));
				ofile.close();
				cout<<"\n All users deleted successfully.";
			}
			else
			{
				cout<<"\n Password incorrect!";
				ifile.close();
			}
			cout<<"\n Returning to Main Menu...";
			delay(2000);
			break;
		}
	}while(ch!=6);
	cout<<"\n Thank You!";
	delay(1000);
	clrscr();
}

int checkusername()
{
	if(strlen(curuser.username)>20)
	{
		cout<<"\n Username is too long.";
		return 1;
	}
	ifstream ifile("Settings.dat",ios::binary|ios::in);
	while(ifile.read((char *)&buff,sizeof(buff)))
		if(strcmp(buff.username,curuser.username)==0)
		{
			cout<<"\n Username is not available! Please choose another username.";
			ifile.close();
			return 1;
		}
	ifile.close();
	cout<<"\n Username is available!";
	return 0;
}

int checkpassword(char duplicate[])
{
	if(strlen(curuser.password)<5||strlen(curuser.password)>20)
	{
		cout<<"\n Password must be 5-20 characters long. Please enter a valid password";
		return 1;
	}
	if(strcmp(curuser.password,duplicate)!=0)
	{
		cout<<"\n Passwords entered don't match. Please enter the same password in both the fields.";
		return 1;
	}
	return 0;
}

int authorize()
{
	cout<<"\n Authorization:";
	cout<<"\n\n Username:";
	cin>>username;
	cout<<"\n Password:";
	i=0;ch1='*';
	while(ch1!=13)
	{
		ch1=getch();
		if(ch1>31&&ch1<127)
		{
			password[i++]=ch1;					
			cout<<"*";
		}				
	}
	password[i]='\0';
	ifstream ifile("Settings.dat",ios::binary|ios::in);
	while(ifile.read((char*)&buff,sizeof(buff)))
	{
		if(strcmp(buff.username,username)==0&&strcmp(buff.password,password)==0&&buff.type==1)
		{
			ifile.close();
			cout<<"\n Authorization completed.";
			return 0;
		}
	}
	ifile.close();
	cout<<"\n Authorization failed!";
	return 1;
}
