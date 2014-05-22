
int gdriver= DETECT, gmode;
void initmouse()
{
	union REGS in,out;
	in.x.ax=0;
	int86(0x33,&in,&out);
	in.x.ax=7;
	in.x.cx=0;
	in.x.dx=1023;
	int86(0x33,&in,&out);
	in.x.ax=8;
	in.x.cx=0;
	in.x.dx=767;
	int86(0x33,&in,&out);
}

void showmouse()
{
	union REGS in,out;
	in.x.ax=1;
	int86(0x33,&in,&out);
}

void hidemouse()
{
	union REGS in,out;
	in.x.ax=2;
	int86(0x33,&in,&out);
}
int release()
{
	union REGS in,out;
	in.x.ax=5;
	int86(0x33,&in,&out);
	return out.x.bx;
}
int getcord(int &x,int &y)
{
	union REGS in,out;
	in.x.ax=3;
	int86(0x33,&in,&out);
	x=out.x.cx;
	y=out.x.dx;
	return out.x.bx;
}
int mousehandle(int a)
{
	int x,y;
	showmouse();
	switch(a)
	{
	case 1:
		/* Log In Screen */
		char username[20], password[20];		
		int b,i;
		char ch[2];
		ch[1]='\0';
		while(login)
			if(getcord(x,y)==1)
				if(x>475&&x<630&&y>364&&y<387)	
				{
					/* Username */
					hidemouse();
					i=0;b=480;
					setfillstyle(1,254);
					bar(480,365,630,385);
					do{
						do{
							setcolor(255);
							line(b,367,b,382);
							delay(100);
							setcolor(254);
							line(b,367,b,382);
							delay(100);
						}while(!kbhit());
						ch[0] = getch();
						if(ch[0]>31&&ch[0]<127)
						{
							setcolor(255);
							username[i++]=ch[0];
							outtextxy(b,370,ch);
							b+=textwidth(ch);
						}
						else
						{
							switch(ch[0])
							{
							case 8:
								/* Backspace */
								username[i--]='\0';
								ch[0]=username[i-1];
								setfillstyle(1,254);
								bar(b-textwidth(ch),370,b,380);
								b-=textwidth(ch);
								break;
							case 9:
								/* tab */
								username[i]='\0';
								goto password;
							}
						}
					}while(ch[0] != 13);
					username[i]='\0';
					showmouse();
				}
				else if(x>475&&x<620&&y>394&&y<418)
				{
					/* Password */
					hidemouse();
password:
					i=0;b=480;
					bar(480,395,630,415);
					do{
						do{
							setcolor(255);
							line(b,397,b,412);
							delay(100);
							setcolor(254);
							line(b,397,b,412);
							delay(100);
						}while(!kbhit());
						ch[0] = getch();
						if(ch[0]>31&&ch[0]<127)
						{
							setcolor(255);
							password[i++]=ch[0];
							outtextxy(b,400,"*");
							b+=textwidth("*");
						}
						else if(ch[0]==8)
						{
							password[i--]='\0';
							setfillstyle(1,254);
							bar(b-textwidth("*"),400,b,415);
							b-=textwidth("*");
						}
					}while(ch[0] != 13);					
					password[i]='\0';					
					showmouse();					
				}
				else if(x>390&&x<485&&y>440&&y<463)
				{
					/* OK */
					fstream ifile("Settings.dat",ios::binary|ios::in);
					int found = 1;					
					while(ifile.read((char*)&curuser,sizeof(curuser)-2))
					{							
						if(strcmp(username,curuser.username)==0&&strcmp(password,curuser.password)==0)
						{							
							found = 0;
							login=0;
							ifile.close();
							break;
						}
					}
					if(found == 1)
					{
						ifile.close();
						imgload("c:/ISWP/Images/msg.bmp",200,250,2);
						do{
							while(getcord(x,y)!=1);
							while(getcord(x,y)==1);
						}while(!(x>550&&x<640&&y>387&&y<414));
						cleardevice();
						return login;
					}					
				}
				else if(x>527&&x<629&&y>440&&y<466)
					/* Exit */
					return 0;
		break;
	case 2:
		/* Home Screen */
		do{
			while(getcord(x,y)!=1&&!kbhit());
			while(getcord(x,y)==1);
			if(kbhit())
			{
				getch();
				hidemouse();
				doc[curdoc-1].work();
				continue;
			}
			if(y>92&&y<113&&x<250)
			{
				/* Toolbar */
				doc[curdoc-1].toolbar((int)((x-87)/23));
			}
			else if(y>63&&y<84&&x>86&&x<269)
			{
				// font face
				goto font;			
			}
			else if(y>30&&y<45)
			{
				/* Menu Bar */
				switch((int)((x-55)/15))
				{
				case 0:
				case 1:
					/* File */						
					imgload("c:/ISWP/images/file.bmp",312,27,1);
					while(getcord(x,y)!=1);
					while(getcord(x,y)==1);
					if(y>27&&y<47)
					{
						char name[100];
						int i=0,a=350;
						name[0]='x';
						switch((int)((x-324)/5))
						{
						case 0:
						case 1:
						case 2:
						case 3:
						case 4:
							/* New */
							if(no_of_docs<10)
								doc[no_of_docs].create();
							break;
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
							/* Open */
							do{
								imgload("c:/ISWP/images/open.bmp",250,250,3);
								hidemouse();
								i=1;a=350;
								name[0]=13;
								do{	
									if((int)name[i-1]<32||(int)name[i-1]>126)
										name[--i]='\0';
									setcolor(7);
									outtextxy(350,307,name);
									a=textwidth(name)+350;
									while(!kbhit())
									{										
										setcolor(7);
										line(a,303,a,313);
										delay(100);
										setcolor(0);
										line(a,303,a,313);
										delay(100);
									}
									name[i++]=getch();
									name[i]='\0';													
								}while((int)name[i-1]!=13);
								name[i-1]='\0';
								showmouse();
								while(getcord(x,y)!=1);
								if(y>340&&y<361)
								{
									if(x>503&&x<564)
										break;
									else if(x>437&&x<496)
									{
										if(doc[curdoc].create(name)==0)
											break;
									}
								}
							}while(1);
							doc[curdoc-1].outputtext();
							break;
						case 13:
						case 14:
						case 15:
						case 16:
						case 17:
							/* Save */
							if(doc[curdoc-1].save("")==0)
								break;
						case 20:
						case 21:
						case 22:
						case 23:
						case 24:
						case 25:
						case 26:
						case 27:
							/* Save As*/
							do{
								imgload("c:/ISWP/images/open.bmp",250,250,3);
								hidemouse();
								i=1;a=350;
								name[0]=13;
								do{	
									if((int)name[i-1]<32||(int)name[i-1]>126)
										name[--i]='\0';
									setcolor(7);
									outtextxy(350,307,name);
									a=textwidth(name)+350;
									while(!kbhit())
									{										
										setcolor(7);
										line(a,303,a,313);
										delay(100);
										setcolor(0);
										line(a,303,a,313);
										delay(100);
									}
									name[i++]=getch();
									name[i]='\0';													
								}while((int)name[i-1]!=13);
								name[i-1]='\0';
								showmouse();
								while(getcord(x,y)!=1);
								if(y>340&&y<361)
								{
									if(x>503&&x<564)
										break;
									else if(x>437&&x<496)
									{
										if(doc[curdoc-1].save(name)==0)
											break;
									}
								}
							}while(1);
							doc[curdoc-1].outputtext();
							break;
						case 29:
						case 30:
						case 31:
						case 32:
							/* Exit */
							while(doc[no_of_docs-1].exit()==1&&no_of_docs>0);
							curdoc=no_of_docs;
							break;
							}
						}
						imgload("c:/ISWP/images/menu.bmp",312,27,1);						
						break;
					case 3:
					case 4:
						/* Edit */
						imgload("c:/ISWP/images/edit.bmp",312,27,1);
						while(getcord(x,y)!=1);
						while(getcord(x,y)==1);
						if(y>27&&y<47)
						{
							switch((int)((x-324)/5))
							{
							case 0:
							case 1:
							case 2:
							case 3:
								// Cut
								doc[curdoc-1].updatestatus("Click at the starting position");
								while(getcord(x,y)!=1);
								while(getcord(x,y)==1);								
								start=doc[curdoc-1].select(x,y);								
								if(start==1)						
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].updatestatus("Click at the ending position");
									while(getcord(x,y)!=1);
									while(getcord(x,y)==1);
									end=doc[curdoc-1].select(x,y);									
								}
								if(end==1||end==start)
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].copy(start,end,1);
									doc[curdoc-1].updatestatus("");
								}
								break;
							case 5:
							case 6:
							case 7:
							case 8:
							case 9:
								/* Copy */
								doc[curdoc-1].updatestatus("Click at the starting position");
								while(getcord(x,y)!=1);
								while(getcord(x,y)==1);								
								start=doc[curdoc-1].select(x,y);								
								if(start==1)						
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].updatestatus("Click at the ending position");
									while(getcord(x,y)!=1);
									while(getcord(x,y)==1);
									end=doc[curdoc-1].select(x,y);									
								}
								if(end==1||end==start)
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].copy(start,end,0);
									doc[curdoc-1].updatestatus("");
								}
								break;
							case 12:
							case 13:
							case 14:
							case 15:
							case 16:
								/* Paste */
								doc[curdoc-1].updatestatus("Click at the position to paste");
								do{
									while(getcord(x,y)!=1);
									while(getcord(x,y)==1);
									start=doc[curdoc-1].select(x,y);
								}while(!start);
								doc[curdoc-1].insert(start,0);
								refresh();
								break;
							case 19:
							case 20:
							case 21:
							case 22:
							case 23:
							case 24:
								/* Insert */
								int posx,posy;
								char temp[1];
								temp[1]='\0';
								doc[curdoc-1].updatestatus("Click at the position you want to insert text");
								while(getcord(x,y)!=1);
								while(getcord(x,y)==1);								
								start=doc[curdoc-1].select(x,y);
								setcolor(7);
								posx=355;
								posy=302;
								if(start)
								{
									imgload("c:/ISWP/images/insert.bmp",250,250,0);
									hidemouse();
									ofile.open("insert.dat",ios::binary);
									do{
												do{
													setcolor(7);
													line(posx,posy,posx,posy-10);
													delay(50);
													setcolor(0);
													line(posx,posy,posx,posy-10);
													delay(50);
												}while(!kbhit());
										temp[0]=getch();
										setcolor(7);
										if((int)temp[0]>31&&(int)temp[0]<127)
										{
											ofile.put(temp[0]);								
											outtextxy(posx,posy,temp);
											if(posx>720)
											{
												posx=355;
												posy+=10;												
											}
											posx+=textwidth(temp);
										}
										else if((int)temp[0]==13)
										{
											ofile.close();
											doc[curdoc-1].insert(start,1);
											break;
										}
									}while((int)temp[0]!=27);													
									ofile.close();
									showmouse();
									
								}
								else
									doc[curdoc-1].updatestatus("INVALID POSITION");
								doc[curdoc-1].outputtext();								
								break;
							}
						}
						imgload("c:/ISWP/images/menu.bmp",312,27,1);
						break;
					case 6:
					case 7:
						/* View */
						imgload("c:/ISWP/images/view.bmp",312,27,1);
						while(getcord(x,y)!=1);
						if(y>27&&y<47)
						{
							if(x>324&&x<376)
							{
								// Status Bar
								curuser.statusbar=!(curuser.statusbar);
								doc[curdoc-1].updatestatus("");								
							}
							else if(x>384&&x<437)
							{
								// File Details
								imgload("c:/ISWP/images/fd.bmp",320,320,0);
								doc[curdoc-1].fd();
								doc[curdoc-1].outputtext();
							}
						}							
						imgload("c:/ISWP/images/menu.bmp",312,27,1);
						break;
					case 9:
					case 10:
					case 11:
						/* Format */
						imgload("c:/ISWP/images/format.bmp",312,27,1);
						while(getcord(x,y)!=1);
						if(x>325&&x<347&&y>27&&y<47)
						{
							/* Font */
font:
							imgload("c:/ISWP/images/font.bmp",250,250,1);
							mousehandle(4);
						}						
						imgload("c:/ISWP/images/menu.bmp",312,27,1);
						break;
					case 13:
					case 14:
					case 15:
						/* About */							
						imgload("c:/ISWP/images/about1.bmp",150,170,3);
						while(getcord(x,y)!=1);
						while(getcord(x,y)==1);
						doc[curdoc-1].outputtext();				
						break;
					}
					if(x>1000&&x<1025)
					{
						/* Help */
						hidemouse();
						cleardevice();
						closegraph();						
						spawnl(P_WAIT,"help1.exe",NULL);
						getch();
						initgraph(&gdriver,&gmode,"");
						initpal("c:/ISWP/images/home.bmp");
						initmouse();
						showmouse();
						refresh();
					}
				}
				else if(x>15&&x<45&&y>55&&y<105)
				{
					// Paste & validate data
					doc[curdoc-1].updatestatus("Click at the position to paste");
					do{
						while(getcord(x,y)!=1);
						while(getcord(x,y)==1);
						start=doc[curdoc-1].select(x,y);
					}while(!start);					
					doc[curdoc-1].insert(start,0);
					doc[curdoc-1].outputtext();
				}
				else if(x>55&&x<70)				
				{
					if(y<115&&y>100)
					{
						//FP
					}
					else if(y>80&&y<95)
					{
						// copy
								doc[curdoc-1].updatestatus("Click at the starting position");
								while(getcord(x,y)!=1);
								while(getcord(x,y)==1);								
								start=doc[curdoc-1].select(x,y);								
								if(start==1)						
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].updatestatus("Click at the ending position");
									while(getcord(x,y)!=1);
									while(getcord(x,y)==1);
									end=doc[curdoc-1].select(x,y);									
								}
								if(end==1||end==start)
									doc[curdoc-1].updatestatus("INVALID POSITION");
								else
								{
									doc[curdoc-1].copy(start,end,0);
									doc[curdoc-1].updatestatus("");
								}
					}
					else if(y>55&&y<75)
					{
						// cut
						doc[curdoc-1].updatestatus("Click at the starting position");
						while(getcord(x,y)!=1);
						while(getcord(x,y)==1);								
						start=doc[curdoc-1].select(x,y);								
						if(start==1)						
							doc[curdoc-1].updatestatus("INVALID POSITION");
						else
						{
							doc[curdoc-1].updatestatus("Click at the ending position");
							while(getcord(x,y)!=1);
							while(getcord(x,y)==1);
							end=doc[curdoc-1].select(x,y);									
						}
						if(end==1||end==start)
							doc[curdoc-1].updatestatus("INVALID POSITION");
						else
						{
							doc[curdoc-1].copy(start,end,1);
							doc[curdoc-1].updatestatus("");
						}
					}
				}				
				else if(x>1010&&x<1020)
				{
					// Page Navigator
					if(y>690&&y<700)
					{
						// page up
						doc[curdoc-1].pagenav(-1);
					}
					else if(y>730&&y<740)
					{
						// Page down
						doc[curdoc-1].pagenav(1);
					}
				}
				else if(x>365&&x<985&&y>75&&y<110) //Banner
				{
					// About
					imgload("c:/ISWP/images/about1.bmp",150,170,3);
					while(getcord(x,y)!=1);
					while(getcord(x,y)==1);
					doc[curdoc-1].outputtext();										
				}
				else if(x>76&&x<92&&y>172)
				{
					/* tab close */					
					for(i=0;i<no_of_docs;i++)
						if(y>172+i*70&&y<188+i*70)
						{
							doc[i].exit();
							refresh();					
							break;
						}
					if(no_of_docs==0)
					{
						doc[0].create();
						doc[0].outputtext();
					}
				}
				else if(x>0&&x<100&&y>162)
				{
					/* tab */
					if((int)((y-162)/70)<no_of_docs)
						curdoc=(int)((y-162)/70)+1;					
					doc[curdoc-1].outputtext();
				}
				else if(x>12&&y>12&&x<34&&y<34)
					refresh();
			if(curdoc==0)
				break;			
		}while(!(x>973&&x<1020&&y>0&&y<17));
		break;
	case 3:
		/* MsgBox Handles */
		while(getcord(x,y)!=1);
		while(getcord(x,y)==1);
		if(y>410&&y<432)
		{
			if(x>572&&x<634)	// Cancel
				return 0;
			else if(x>492&&x<554)	// No
				return -1;
			else if(x>413&&x<474)	// Yes
				return 1;
		}
	case 4:
		/* Fonts */
		int num;
		do{
			font.italic=1;			
			while(getcord(x,y)!=1);
			while(getcord(x,y)==1);
			num=(int)((y-358)/12);
			if(x>300&&x<420)
			{
				if(num<7&&num>=0)
				{
					setfillstyle(1,0);
					bar(370,520,630,557);
					::font.font=num;
					outtext("AaBbCcDd",430,525);
				}
			}
			else if(x>440&&x<560)
			{
				if(num<7&&num>=0)
				{
					setfillstyle(1,0);
					bar(370,520,630,557);
					::font.font=num+7;
					outtext("AaBbCcDd",430,525);					
				}
			}
			// font colors
			else if(x>585&&x<713&&y>354&&y<482)
			{ 
				int xx,yy,i;
				xx=(x-585)/8;
				yy=(y-354)/8;
				i=yy*16 + xx;
				::font.color=i;
				outtext("AaBbCcDd",430,525);
			}
			/*heading subheading and normal*/
			if(y>477&&y<487)
			{
				if(x>319&&x<374)
				{
					/*heading */
					setfillstyle(1,0);
					bar(370,520,630,557);
					setfillstyle(1,7);
					bar(303,477,313,487);
					setfillstyle(1,0);
					bar(388,477,398,487);
					bar(524,477,534,487);
					font.justify=0;
					font.underline=1;
					font.font=8;
					line(430,557,523,557);
				}
				else if(x>406&&x<499)
				{
					/*sub-heading*/
					setfillstyle(1,0);
					bar(370,520,630,557);
					setfillstyle(1,7);
					bar(388,477,398,487);
					setfillstyle(1,0);
					bar(303,477,313,487);
					bar(524,477,534,487);
					font.justify=-1;
					font.underline=1;
					font.font=8;
					line(430,557,523,557);
				}
				else if(x>545&&x<580)
				{
					/*Text*/
					setfillstyle(1,0);
					bar(370,520,630,557);
					setfillstyle(1,7);
					bar(524,477,534,487);
					setfillstyle(1,0);
					bar(303,477,313,487);
					bar(388,477,398,487);
					font.justify=-1;
					font.underline=0;
					font.font=0;					
				}		
				outtext("AaBbCcDd",430,525);
			}
			if(y>580&&y<598)
			{
				if(x>651&&x<723)				
					break;// cancel
				else if(x>567&&x<640)
				{
					/* Okay */
					doc[curdoc-1].updatefont(0);
					break;
				}
			}			
		}while(!(x>685&&y>250&&x<832&&y<273));
		doc[curdoc-1].outputtext();
		break;
	}
	return 0;
}
