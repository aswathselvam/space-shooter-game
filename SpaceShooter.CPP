#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream.h>


int x = 40, y = 400, r = 45, currentScore = 0, life = 3;
int vE = 3, shoot = 0, scale = -30;

char in='i';
void addPlayer();
void deletePlayer();
void storeScore();
void showLeaderboard();
char currentPlayerName[20];

void Game2();
void moveEnemy();
void destroyEnemy(int);
void moveProjectile();
void fire();
void checkCollision();
void dispScore();


class Player
{
	char playerName[20];
	int playerScore;
public:
	void PutData();
	void PutScore(int);
	int GetScore();
	char* GetPlayerName();
	void ShowData();
}obj;

void Player :: PutData()
{
	strcpy ( playerName , currentPlayerName );
	playerScore = currentScore;
}
void Player :: PutScore( int x ) {
	playerScore = x;
}
int Player :: GetScore(){
	return playerScore;
}
char* Player :: GetPlayerName(){
	return playerName;
}
void Player :: ShowData()
{
	cout << playerName << "\t\t\t" << playerScore << endl;
}

class Enemy {
	public:
	int x, y, r;
	Enemy(int inr)
	{
		r = inr;
	}
}e[3] = {Enemy(25),Enemy(25),Enemy(25)};

class Projectile{
	public:
	int x, y, fire, r;
	Projectile(int inr, int inf){
		r = inr;
		fire = inf;
	}
}p[4] = {Projectile(5,0),Projectile(5,0),Projectile(5,0),Projectile(5,0)};

void main(){
	start:
	clrscr();
	cout<<"SPACE INVADER"<<endl;
	ofstream out("score.dat",ios::app);
	out.close();
	cout<<"Start(1)\nLeaderboard(2)\nInstructions(3)\nCredits(4)";
	in=getch();
	if(in == '1'){
		cout<<"Enter player name with initial(min 20 characters): ";
		cin>>currentPlayerName;
		addPlayer();
		do{
			life = 3;
			currentScore = 0;
			Game2();
			dispScore();
			cout<<"\nDo you want to try again(y/n):";
			cin>>in;
		} while(in == 'y');
	} else if(in == '2'){
		cout<<endl;
		showLeaderboard();
		cout<<"\n\n\nPress any key to continue...";
		getch();
		goto start;
	}else if(in == '3'){
		cout<<"\n\nControls:\n"
		<<"'A' to move left\n'D' to move right "
		<<"\n'Space' to shoot\n'Q' to quit at any point during the game"
		<<"\n\nObjective:\nShoot the space rocks (circles) to get score "
		<<"you have 3 lives, \nyou lose a life if a space rock hits you. "
		<<"\nMake your way up in the Leaderboard.\n*Be sure to turn of CAPSLOCK";
		cout<<"\n\n\nPress any key to continue...";
		getch();
		goto start;
	}else if( in == '4'){
		cout<<"\n\nCredits:"<<"\nAswath - Programming"
		<<"\nParesh - Documentation"
		<<"\nVarush - Ideas";
	}
	getch();
}

int xmax=getmaxx();

void Game2(){
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode,"c:\\TURBOC3\\BGI");

	int pressed=0;
	destroyEnemy(0);
	destroyEnemy(1);
	destroyEnemy(2);
	delay(2000);
	setbkcolor(4);
	do{
	gotoxy(1,1);cout<<"Life: "<<life<<"\t\t"<<"Score: "<<currentScore;
		if(kbhit()){
			in = getch();
			switch(in){
				case 'a':x = x>r+20 ? x-=10: x; break;
			    case 'd':x = x<=getmaxx()-r-20 ? x += 10: x; break;
			    case ' ':if(pressed == 0){ pressed=1; fire(); } break;
			}
		}
	pressed=0;

	line(x+scale*0,   y+scale*1.75, x+scale*0.5, y+scale*1.5);
	line(x+scale*0.5, y+scale*1.5,  x+scale*0.5, y+scale*0.5);
	line(x+scale*0.5, y+scale*0.5,  x+scale*2,   y+scale*0);
	line(x+scale*2,   y+scale*0,    x+scale*1.5, y+scale*-1);
	line(x+scale*1.5, y+scale*-1,   x+scale*0.5, y+scale*-1);
	line(x+scale*0.5, y+scale*-1,   x+scale*0.25,y+scale*-1.25);
	line(x+scale*0.25,y+scale*-1.25, x+scale*0,   y+scale*-1.25);

	line(x+scale*-0,   y+scale*1.75, x+scale*-0.5, y+scale*1.5);
	line(x+scale*-0.5, y+scale*1.5,  x+scale*-0.5, y+scale*0.5);
	line(x+scale*-0.5, y+scale*0.5,  x+scale*-2,   y+scale*0);
	line(x+scale*-2,   y+scale*0,    x+scale*-1.5, y+scale*-1);
	line(x+scale*-1.5, y+scale*-1,   x+scale*-0.5, y+scale*-1);
	line(x+scale*-0.5, y+scale*-1,   x+scale*-0.25,y+scale*-1.25);
	line(x+scale*-0.25,y+scale*-1.25,x+scale*-0,   y+scale*-1.25);

	//Stripes
	line(x+scale*1.25,y+scale*0.25, x+scale*0.75, y+scale*-1);
	line(x+scale*1.5, y+scale*0.125, x+scale*1, y+scale*-1);
	line(x+scale*-1.25,y+scale*0.25, x+scale*-0.75, y+scale*-1);
	line(x+scale*-1.5, y+scale*0.125, x+scale*-1, y+scale*-1);

	//Flames
	line(x+scale*0.25,                y+scale*-1.25,                   x+scale*0.125*sin(e[0].y/5),  y+scale*-1.5+1.5*sin(e[0].y/5));
	line(x+scale*0.125*sin(e[0].y/5),y+scale*-1.5+1.5*sin(e[0].y/5), x+scale*0,                     y+scale*-1.35);
	line(x+scale*-0.25,               y+scale*-1.25,                   x+scale*-0.125*sin(e[1].y/5), y+scale*-1.5);
	line(x+scale*-0.125*sin(e[1].y/5),y+scale*-1.5,                   x+scale*-0,                    y+scale*-1.35);

	moveEnemy();
	moveProjectile();
	checkCollision();
	delay(20);
	nosound();
	cleardevice();
	}while(in!='q');

	closegraph();

}
int newX=0;

void moveEnemy(){

	int i=0;
	for(i=0;i<3;i++)
	{
		if(e[i].y>getmaxy())
		{
			destroyEnemy(i);
			}
			else{
			//Level 7
			if(currentScore>25){e[i].y+=vE+currentScore/6;e[i].x+=6*sin(e[i].y/30);setbkcolor(3+2*sin(e[0].y/40));}
			//Level 6
			else if(currentScore>22){e[i].y+=vE; e[i].x+=-(x-newX)/5;}
			//Level 5
			else if(currentScore>19){e[i].y+=vE; e[i].x+=(x-newX)/5;}
			//Level 4
			else if(currentScore>16){e[i].y+=vE+currentScore/12+3*sin(e[i].x); e[i].x+=5*sin(e[i].y);}
			//Level 3
			else if(currentScore>12){e[i].y+=vE+currentScore/6;e[i].x+=3*sin(e[i].y/30);}
			//Level 2
			else if(currentScore>7){e[i].y+=vE;e[i].x+=5*sin(e[i].y/10);sound(e[0].x);setbkcolor(1+5*sin(e[0].x));}
			//Level 1
			else if(currentScore>3){e[i].y+=vE+currentScore/3;}
			else{e[i].y+=vE;}
		}
		circle(e[i].x,e[i].y,e[i].r);
	}
	newX=x;
}

void moveProjectile()
{
	int i = 0;
	for(i = 0; i < 4; i++)
	{
		if(p[i].fire == 1)
		{
			sound(p[i].y > 370 ? 300 : 0);
			p[i].y -= 5;
		}
		else
		{
			switch(i)
			{
				case 0: p[i].x = x+scale*0.75; p[i].y = y+scale*0.65; break;
				case 1: p[i].x = x-scale*0.75; p[i].y = y+scale*0.65; break;
				case 2: p[i].x = x+scale*1; p[i].y = y+scale*0.37; break;
				case 3: p[i].x = x-scale*1; p[i].y = y+scale*0.37; break;
			}
		}
		circle(p[i].x, p[i].y, p[i].r);
		setfillstyle(1, YELLOW);
		floodfill(p[i].x, p[i].y, WHITE);
		if(p[i].y < 0)
		{ 
			p[i].fire = 0;
		}
	}
}

void fire()
{
	int i = 0;
	for(i=0; i<4; i++)
	{
		if(p[i].fire == 0)
		{
			p[i].fire =1 ;
		break;
		}
	}
}

void checkCollision(){
	int i;
	//bw player n enemy
		for(i = 0; i < 3; i++){
			if(pow(x-e[i].x, 2) + pow(y-e[i].y, 2) < pow(r+e[i].r, 2) )
			{
				--life;
				destroyEnemy(i);
				sound(100);
			if(life < 1)
			{
				in='q';
			}
		}
	}

	//bw enemy n projectile
	for(i = 0;i < 4;i++){
		for(int j = 0; j < 3;j++){
			if(pow(p[i].x - e[j].x, 2) + pow(p[i].y - e[j].y, 2)< pow(p[i].r + e[j].r, 2))
			{
				++currentScore;
				p[i].fire = 0;
				destroyEnemy(j);
				sound(-4*e[j].y);
			}
		}
	}
}

void destroyEnemy(int i)
{
	int spawnx;
	int dx = getmaxx()/3;
	e[i].y = -e[i].r-random(70);
	switch(i)
	{
		case 0: spawnx = 0*dx+dx/2; break;
		case 1: spawnx = 1*dx+dx/2; break;
		case 2: spawnx = 2*dx+dx/2; break;
		case 3: spawnx = 3*dx+dx/2; break;
	}
	e[i].x = (spawnx) + random(dx/2) * pow(-1,random(2));
}

void dispScore()
{
	clrscr();
	cout<<"Game over\nScore: "<<currentScore<<endl;
	storeScore();
	showLeaderboard();
}

//Leaderboard
void showLeaderboard()
{
	ifstream in("score.dat");
	cout<<"\n\nLeaderboard: "<<endl;
	cout << "Name: " << "\t\t\t" << "Score:"<<endl;
	while(!in.eof())
	{
		in.read((char*)&obj,sizeof(obj));
		if(!in.eof())
		{
			obj.ShowData();
		}
	}
	cout<<"End of Leaderboard"<<endl;
	in.close();
}

//File Handling
void storeScore()
{
	ifstream in("score.dat");
	while(!in.eof())
	{
		in.read((char*) &obj, sizeof(obj));
		if((obj.GetScore()<currentScore)&&(strcmp(currentPlayerName, obj.GetPlayerName()) == 0))
		{
			in.close();
			deletePlayer();
			break;
		}
	}
}

void deletePlayer(){
	int copied=0;
	ifstream in("score.dat");
	ofstream out("temp.dat",ios::out);
	Player tempobj;
	while(!in.eof())
	{
		in.read((char*)&obj,sizeof(obj));
		if(!in.eof())
		{
			if(currentScore > obj.GetScore() && copied == 0)
			{
				tempobj.PutData();
				out.write((char*)&tempobj, sizeof(tempobj));
				copied = 1;
			}
			if(!(strcmp(obj.GetPlayerName(), currentPlayerName) == 0))
			{
				out.write((char*)&obj,sizeof(obj));
			}
		}
	}
	if(copied == 0)
	{
		obj.PutData();
		out.write((char*)&obj, sizeof(obj));
	}
	out.close();
	in.close();
	remove("score.dat");
	rename("temp.dat","score.dat");
}

void addPlayer()
{
	ifstream in("score.dat");
	int flag = -1;
	while(!in.eof())
	{
		in.read((char*)&obj,sizeof(obj));
		if(strcmp(obj.GetPlayerName(), currentPlayerName) == 0)
		{
			cout<<"Welcome back "<<currentPlayerName;
			flag = 0;
			break;
		}
	}
	in.close();

	if(flag == -1)
	{       
		ofstream out("score.dat", ios::app);
		obj.PutData();
		out.write((char*)&obj, sizeof(obj));
		cout<<"New player account created "<<obj.GetPlayerName();
		out.close();
	}

	getch();
}
