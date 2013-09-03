/*
Created by Mario Avenoso
8/13

RULES:
1:There are two players who start of the two far sides of the board
2:One Side is Red and the other Blue
3:Moving in turns, each side can only move in the same manner as a Chess's Knight "L"
or two spaces in one direction and one over
4:From the position the player lands, there color will spread out in all vetrical, horizontal and
digoinal directions
5:If the players color comes in contact with the other players color, the new color with take over 
that one space and stop
6:If the players color come in contact with there own color, that players color will keep going
7:The colored spot, the player is on can not be changed

V.7: 8/28/13 - 9/1/13
[Bug Fix] stoped game from crashing if you typed a letter for an X,Y input
[Added] Changed game feild to "*" from "0"
[Bug Fix] Issue where players color would place its self in locations where it wassn't ment to go
[Bug Fix] Issue where player was given all real possible movement options
[Code Change] fixed some inconsistances in varible useage

V.6: 8/28/13
[Bug fix] Which allowed the player to move anywhere on the board without checking
if it was a real move the player could make

V.5: 8/28/13
First Release of the game

*/

#include<iostream>
#include<Windows.h>
#include <iomanip>
using namespace std;

const int grid_x = 7;
const int grid_y = 10;
int g_grid[grid_x][grid_y]={ //7x10 is the grind size 3= unpassible, 2= blue, 1= red, 0= free, 4 player 1, 5 player 2
	{3,3,3,0,0,0,0,3,3,3},
	{3,3,0,0,0,0,0,0,3,3},
	{3,0,0,0,0,0,0,0,0,3},
	{0,0,0,0,0,0,0,0,0,0},
	{3,0,0,0,0,0,0,0,0,3},
	{3,3,0,0,0,0,0,0,3,3},
	{3,3,3,0,0,0,0,3,3,3}
};

//Players starting location
int player1_x=3;
int player1_y=0;
int player1 = 4;

int player2_x=3;
int player2_y=9;
int player2 = 5;
//end players location



void print_g();
void s_print();
void span1(int,int);//spread out from point
void span2(int,int);
bool vaild1(int,int);//this function checks for vaild moves
bool move1(int,int);//this function will move player one
void listmoves1();//this will list all the vaild moves the player can make.

bool vaild2(int,int);//this function checks for vaild moves
bool move2(int,int);//this function will move player one
void listmoves2();//this will list all the vaild moves the player can make.
void populate();//will put players on map to start
void clear();//uses system clear to clear screen then print new display
void score();//this function will calc how may spaces each player has in total
void find_winner();//will find the winnter of the game
int main()
{
	system("title Light Knight");
	//set location of players on map
	g_grid[player1_x][player1_y]=player1;
	g_grid[player2_x][player2_y]=player2;
	//locations set

	clear();
	cout<<endl;
	//g_grid[player1_x][4]=player1;
	//g_grid[player2_x][6]=player2;
	//span1(player1_x,4);
	//span2(player2_x,6);
	
	//s_print();



	int x1,y1,x2,y2,i;
	i=0;
	//g_grid[12][12]=4;
	while(i<6)
	{
		
		x1=y1=x2=y2=0;
		cout<<"There are "<<5-i<<" moves left"<<endl<<endl;
		listmoves1();
		cout<<"Player 1 X: ";
		cin>>x1;
		cout<<"Player 1 Y: ";
		cin>>y1;
		while(!move1(x1,y1))
		{
			x1=y1=x2=y2=0;//clear the data
			cout<<"Not a vaild move, try again"<<endl;
			cout<<"Player 1 X: ";
			//cin>>x1;
			while ( !( cin>> x1 ) || cin.get() != '\n' ) {
			  cerr<<"\nInvalid input\nPlayer 1 X: ";
			  cin.clear();
			  cin.ignore ( 1,  EOF);
			}
			cout<<"Player 1 Y: ";
			//cin>>y1;
			while ( !( cin>> y1 ) || cin.get() != '\n' ) {
			  cerr<<"\nInvalid input\nPlayer 1 Y: ";
			  cin.clear();
			  cin.ignore ( 1,  EOF);
			}
		}
		clear();
		cout<<"There are "<<5-i<<" moves left"<<endl<<endl;
		listmoves2();
		cout<<"Player 2 X: ";
		cin>>x2;
		cout<<"Player 2 Y: ";
		cin>>y2;
		while(!move2(x2,y2))
		{
			x1=y1=x2=y2=0;//clear the data
			cout<<"Not a vaild move, try again"<<endl;
			cout<<"Player 2 X: ";
			//cin>>x2;
			while ( !( cin>> x2 ) || cin.get() != '\n' ) {
			  cerr<<"\nInvalid input\nPlayer 2 X: ";
			  cin.clear();
			  cin.ignore ( 1,  EOF);
			}
			cout<<"Player 2 Y: ";
			//cin>>y2;
			while ( !( cin>> y2 ) || cin.get() != '\n' ) {
			  cerr<<"\nInvalid input\nPlayer 2 Y: ";
			  cin.clear();
			  cin.ignore ( 1,  EOF);
			}
		}
		clear();
		i++;
	}

	cout<<endl;
	//s_print();
	find_winner();
	system("pause");
	return 0;
}


void clear()
{
	system("cls");
	score();
	print_g();
}

void score()
{
	HANDLE  hConsole;
	 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(hConsole, 15);//set things back to normal
	double p1 = 0;
	double p2 = 0;
	for(int x=0;x<grid_x;x++)
	{
		for(int y=0;y<grid_y;y++)
		{
			if(g_grid[x][y]==1)
			{
				p1++;
			}
			else if(g_grid[x][y]==2)
			{
				p2++;
			}
			else if(g_grid[x][y]==4)
			{
				p1++;
			}
			else if(g_grid[x][y]==5)
			{
				p2++;
			}
		}
		//cout<<endl;
	}
	SetConsoleTextAttribute(hConsole, 12);//red	
	cout<<"Player 1 has: "<<p1<<" "<<setprecision(3)<<(p1/46)*100<<"% ";
	SetConsoleTextAttribute(hConsole, 9);//blue	
	cout<<"Player 2 has: "<<p2<<" "<<setprecision(3)<<(p2/46)*100<<"% ";
	SetConsoleTextAttribute(hConsole, 15);//set things back to normal
	cout<<" | Of 46 spaces"<<endl<<endl;
}

void find_winner()
{
	clear();//reset print display
	HANDLE  hConsole;
	 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(hConsole, 15);//set things back to normal
	double p1 = 0;
	double p2 = 0;
	for(int x=0;x<grid_x;x++)
	{
		for(int y=0;y<grid_y;y++)
		{
			if(g_grid[x][y]==1)
			{
				p1++;
			}
			else if(g_grid[x][y]==2)
			{
				p2++;
			}
			else if(g_grid[x][y]==4)
			{
				p1++;
			}
			else if(g_grid[x][y]==5)
			{
				p2++;
			}
		}
		//cout<<endl;
	}
	if(p1>p2)
	{
		SetConsoleTextAttribute(hConsole, 12);//red	
		cout<<endl<<endl<<"Player 1";
		SetConsoleTextAttribute(hConsole, 15);//white	
		cout<<" is the winner, Conrtoling: "<<p1<<" spaces at "<< setprecision(3)<<(p1/46)*100<<"% ";
	}
	else if(p1<p2)
	{
		SetConsoleTextAttribute(hConsole, 9);//blue	
		cout<<endl<<endl<<"Player 2";
		SetConsoleTextAttribute(hConsole, 15);//white	
		cout<<" is the winner, Conrtoling: "<<p2<<" spaces at "<< setprecision(3)<<(p2/46)*100<<"% ";
	}
	else if(p1==p2)
	{
		cout<<endl<<endl<<"The game is a draw, ";
		SetConsoleTextAttribute(hConsole,12);//red
		cout<<"Player 1 ";
		SetConsoleTextAttribute(hConsole, 15);//white
		cout<<"and ";
		SetConsoleTextAttribute(hConsole, 9);//blue
		cout<<"Player 2 ";
		SetConsoleTextAttribute(hConsole, 15);//white
		cout<<"both control "<<p1<<" spaces at "<<setprecision(3)<<(p2/46)*100<<"% ";
	}
	cout<<endl<<endl;
	SetConsoleTextAttribute(hConsole, 15);//set things back to normal
	
}

void print_g()
{
	HANDLE  hConsole;
	 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(hConsole, 15);//set things back to normal
	cout<<" ";
	for(int i=0;i<10;i++)
	{
		cout<<i;
	}
	cout<<endl;
	
	for(int x = 0; x<grid_x;x++)
	{ 
		SetConsoleTextAttribute(hConsole, 15);//set things back to normal
		cout<<x;
		for(int y=0;y<grid_y;y++)
		{   
			if(g_grid[x][y]==3)//spaces outside the game board
			{
				SetConsoleTextAttribute(hConsole, 15);//set things back to normal
				cout<<" ";
			}
			else if(g_grid[x][y]==2)//blue spaces
			{
				SetConsoleTextAttribute(hConsole, 9);//blue
				cout<<"B";
			}
			else if(g_grid[x][y]==1)//red spaces
			{
				SetConsoleTextAttribute(hConsole, 12);//red
				cout<<"R";
			}
			else if(g_grid[x][y]==0)//un claimed spaces
			{
				SetConsoleTextAttribute(hConsole, 15);//set things back to normal
				cout<<"*";
			}
			else if(g_grid[x][y]==4)//player 1's location
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout<<"1";
			}
			else if(g_grid[x][y]==5)//player 2's location
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout<<"2";
			}
		}//end y for loop
		cout<<endl;//next line
	}//end x for loop
	SetConsoleTextAttribute(hConsole, 15);//set things back to normal
}//end print function

void span1(int px, int py)
{
	int loop=0;
	int x = px;
	int y = py;
	
	//up
	while(x>0)
	{
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
		
		
	}
	x = px;//reset x
	y = py;//reset y
	//down
	while(x<grid_x)
	{
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
		
	}
	x = px;//reset x
	y = py;//reset y
	//left
	while(y>0)
	{
		y--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//right
	while(y<grid_y-1)
	{
		y++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//up left
	while(y>0 && x>0)
	{
		y--;
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//up right
	while(y<grid_y && x>0)
	{
		y++;
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//down left
	while(y>0 && x<grid_x)
	{
		y--;
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//down right
	while(y<grid_y && x<grid_x)
	{
		y++;
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player2)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==2)//check to see if crossed path with other color
			{
				g_grid[x][y]=1;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				break;
			}
			else if(g_grid[x][y]==player1)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=1;
			}
		}
		else
			break;
	}
}


void span2(int px, int py)
{
	int loop=0;
	int x = px;
	int y = py;
	
	//up
	while(x>0)
	{
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
		
	}
	x = px;//reset x
	y = py;//reset y
	//down
	while(x<grid_x)
	{
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;	
	}
	x = px;//reset x
	y = py;//reset y
	//left
	while(y>0)
	{
		y--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//right
	while(y<grid_y-1)
	{
		y++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//up left
	while(y>0 && x>0)
	{
		y--;
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//up right
	while(y<grid_y && x>0)
	{
		y++;
		x--;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//down left
	while(y>0 && x<grid_x)
	{
		y--;
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
	x = px;//reset x
	y = py;//reset y
	//down right
	while(y<grid_y && x<grid_x)
	{
		y++;
		x++;
		if(x >=0 && y >=0 && x<grid_x && y <grid_y)
		{
			if(g_grid[x][y]==player1)//do not override player space, must be first
			{
				break;
			}
			else if(g_grid[x][y]==1)//check to see if crossed path with other color
			{
				g_grid[x][y]=2;
				break;
			}
			else if(g_grid[x][y]==3)//check to make sure not out of bonds
			{
				//g_grid[x][y]=3;
				break;
			}
			else if(g_grid[x][y]==player2)//check for self
			{
				//g_grid[x][y]=3;
				break;
			}
			else
			{
				g_grid[x][y]=2;
			}
		}
		else
			break;
	}
}
void s_print()
{

	cout<<" ";
	for(int i=0;i<10;i++)
	{
		cout<<i;
	}
	cout<<endl;
	
	for(int x = 0; x<grid_x;x++)
	{ cout<<x;
		for(int y=0;y<grid_y;y++)
		{   
			if(g_grid[x][y]==3)//spaces outside the game board
			{
				cout<<" ";
			}
			else if(g_grid[x][y]==2)//blue spaces
			{
				cout<<"B";
			}
			else if(g_grid[x][y]==1)//red spaces
			{
				cout<<"R";
			}
			else if(g_grid[x][y]==0)//un claimed spaces
			{
				cout<<" ";
			}
			else if(g_grid[x][y]==4)//player 1's location
			{
				cout<<"1";
			}
			else if(g_grid[x][y]==5)//player 2's location
			{
				cout<<"2";
			}
		}//end y for loop
		cout<<endl;//next line
	}//end x for loop

}


void listmoves1()
{
	int kmove[8][2]={//This is all possible moves a knight can make in chess in a turn.
	{-2,-1},
	{-2,1},
	{-1,2},
	{1,2},
	{2,-1},
	{2,1},
	{-1,-2},
	{1,-2}
					};
	int i =1;
	cout<<"The Vaid moves you can make are:"<<endl<<endl;
	for(int kx=0;kx<8;kx++)
	{
		for(int ky=0;ky<2;ky=ky+2)
		{
			if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==3)//check for bondrys
			{
				break;//not a vaid move
			}
			else if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==player2)//check for player 2
			{
				break;//not a vaid move
			}
			else if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==0 
				|| g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==1 
				|| g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==2 )
			{
				if(kmove[kx][ky]+player1_x >=0 && kmove[kx][ky+1]+player1_y >=0
					&&kmove[kx][ky]+player1_x<grid_x && kmove[kx][ky+1]+player1_y <grid_y)
				{
					cout<<i<<": X "<<kmove[kx][ky]+player1_x<<", Y "<<kmove[kx][ky+1]+player1_y<<endl;//displays vaild moves to make
					i++;
				}
				else
					break;
			}
			
			else
			{
				break;
			}

		}
		//cout<<endl;
	}
	
}



bool vaild1(int x,int y)
{
	int kmove[8][2]={//This is all possible moves a knight can make in chess in a turn.
	{-2,-1},
	{-2,1},
	{-1,2},
	{1,2},
	{2,-1},
	{2,1},
	{-1,-2},
	{1,-2}
					};

	

	if(g_grid[x][y]==3)//the move you want is outside the game zone
	{
		return false;
	}
	
	for(int kx=0;kx<8;kx++)
	{
		for(int ky=0;ky<2;ky=ky+2)
		{
			if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==3)//check for bondrys
			{
				break;//not a vaid move
			}
			else if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==player2)//check for player 2
			{
				break;//not a vaid move
			}
			else if(g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==0 
				|| g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==1 
				|| g_grid[player1_x+kmove[kx][ky]][player1_y+kmove[kx][ky+1]]==2 )
			{
				if(kmove[kx][ky]+player1_x >=0 && kmove[kx][ky+1]+player1_y >=0
					&&kmove[kx][ky]+player1_x<grid_x && kmove[kx][ky+1]+player1_y <grid_y
					&& kmove[kx][ky]+player1_x ==x && kmove[kx][ky+1]+player1_y == y)
				{
					
					return true;
				}
				else
					break;
			}
			
			else
			{
				break;
			}


		}
		//cout<<endl;
	}
	
	return false;// if not match is found in loop then this is not a vaild move

}

bool move1(int x, int y)
{
	int old_x = player1_x;
	int old_y = player1_y;

	if(vaild1(x,y))
	{
		player1_x = x;
		player1_y = y;
		g_grid[old_x][old_y]=1;
		g_grid[x][y]=player1;
		
		//cout<<old_x;
		span1(x,y);
		
		return true;
	}
	else
	{
		return false;
	}
	
}

void listmoves2()
{
	int kmove[8][2]={//This is all possible moves a knight can make in chess in a turn.
	{-2,-1},
	{-2,1},
	{-1,2},
	{1,2},
	{2,-1},
	{2,1},
	{-1,-2},
	{1,-2}
					};
	int i =1;
	cout<<"The Vaid moves you can make are:"<<endl<<endl;
	for(int kx=0;kx<8;kx++)
	{
		for(int ky=0;ky<2;ky=ky+2)
		{
			
			if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==3)//check for bondrys
			{
				break;//not a vaid move
			}

			else if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==player1)//check for player 1
			{
				break;//not a vaid move
			}
			else if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==0 
				|| g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==1 
				|| g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==2 )
			{
				if(player2_x + kmove[kx][ky] >=0 && player2_y + kmove[kx][ky+1] >=0
					&&kmove[kx][ky]+player2_x<grid_x && kmove[kx][ky+1]+player2_y <grid_y)
				{
					cout<<i<<": X "<<kmove[kx][ky]+player2_x<<", Y "<<kmove[kx][ky+1]+player2_y<<endl;//displays vaild moves to make
					i++;
				}
				else
				{
					break;
				}
			}
			
			else
			{
				break;
			}

		}
		//cout<<endl;
	}
	
}



bool vaild2(int x,int y)
{
	int kmove[8][2]={//This is all possible moves a knight can make in chess in a turn.
	{-2,-1},
	{-2,1},
	{-1,2},
	{1,2},
	{2,-1},
	{2,1},
	{-1,-2},
	{1,-2}
					};

	

	if(g_grid[x][y]==3)//the move you want is outside the game zone
	{
		return false;
	}
	
	for(int kx=0;kx<8;kx++)
	{
		for(int ky=0;ky<2;ky=ky+2)
		{
			if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==3)//check for bondrys
			{
				break;//not a vaid move
			}
			else if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==player1)//check for player 1
			{
				break;//not a vaid move
			}
			else if(g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==0 
				|| g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==1 
				|| g_grid[player2_x+kmove[kx][ky]][player2_y+kmove[kx][ky+1]]==2 )
			{
				if(kmove[kx][ky]+player2_x >=0 && kmove[kx][ky+1]+player2_y >=0
					&&kmove[kx][ky]+player2_x<grid_x && kmove[kx][ky+1]+player2_y <grid_y
					&& kmove[kx][ky]+player2_x ==x && kmove[kx][ky+1]+player2_y == y)
				{
					return true;
				}
				else
					break;
			}
			
			else
			{
				break;
			}


		}
		//cout<<endl;
	}
	
	return false;// if no match is found in loop then this is not a vaild move

}

bool move2(int x, int y)
{
	int old_x = player2_x;
	int old_y = player2_y;

	if(vaild2(x,y))
	{
		player2_x = x;
		player2_y = y;
		g_grid[old_x][old_y]=2;//set the location the player was in to the players color
		g_grid[x][y]=player2;//set the player in the new location
		
		//cout<<old_x;
		span2(x,y);
		
		return true;
	}
	else
	{
		return false;
	}
	
}
