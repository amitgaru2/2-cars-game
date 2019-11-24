#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<iostream.h>
#include<dos.h>
#include<process.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<fstream.h>
#include<string.h>



#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define A 65
#define SMALLA 97
#define D 68
#define SMALLD 100


struct highscore{
	char name[7];
	double score;
};


class Car
{

  public:
  float maxx, maxy, one3x, one4x, midx, midy, carTopHeight;
  float  midRightLeft, midRightRight, carRightMid, midLeftLeft, midLeftRight, carLeftMid;
  int gameOver, level, speed1, speed2, speed3, speed4;
  double score, highScore;
  char highScorer[7];
  int blocksRight[5][2], blocksCountRight;
  int blocksLeft[5][2], blocksCountLeft;
  int posRightCar, posLeftCar; 		// (1) Right , (0) Left
  char startingBlockAtRight;
  void initializeData();
  void showTracks(int);

  void showCar(float);
  void initCarRight();
  void initCarLeft();

  void animateBlocks();
  void initAnimate();
  void animate();
  void drawBlock(int, int);
  void displayBlocksRight();
  void displayBlocksLeft();
  void moveRightCarLeft();
  void moveRightCarRight();
  void moveLeftCarLeft();
  void moveLeftCarRight();
  void showBoomRight(float, float);
  void showBoomLeft(float, float);
  int checkGameOver();
  void displayGameOver();
  void showScore();
  void readHighScore();

};


void Car::initializeData()
{
	srand ( time(NULL) );
	maxx=getmaxx()-170;
	maxy=getmaxy();
	one4x=maxx/4;
	midx=maxx/2;
	midy = getmaxy()/2;
	one3x=3*maxx/4;

	/* track mid positions */
	midRightLeft = (2*one4x+50+3*one4x+50)/2.0;
	midRightRight = (3*one4x+60+4*one4x+60)/2.0;
	midLeftLeft = (20+one4x+20)/2.0;
	midLeftRight = (one4x+30+2*one4x+30)/2.0;


	/**/

	blocksRight[0][0] = 110;
	blocksLeft[0][0] = 110;
	for(int i=1;i<=4;i++){
		blocksRight[i][0] = 0;
		blocksLeft[i][0] = 0;
	}
	blocksCountRight = 1;
	blocksCountLeft = 1;
	/* position of first block , random*/
	if(rand()%2==0) blocksRight[0][1] = 0;
	else blocksRight[0][1] = 1;
	if(rand()%2==0) blocksLeft[0][1] = 0;
	else blocksLeft[0][1] = 1;
	/* */
	posRightCar = 5;
	posLeftCar = 5;
	carTopHeight = maxy-145;
	gameOver = 0;
	level = 1;
	speed1 = 180; speed2 = 120; speed3 = 70; speed4 = 40;
	score = 0;
	highScorer[0]=' ';
	highScore=0;

	readHighScore();
}


void Car::animate()
{
	int x, i=0;
	while(!kbhit())
	{
		srand ( time(NULL) );
		x = i % 5 + 1;
		showTracks(x);
		initCarRight();
		initCarLeft();
		animateBlocks();
		showScore();
		if(checkGameOver())
		{
			gameOver = 1;
			break;
		}
		switch(level)
		{
			case 1:
				delay(speed1);
				break;
			case 2: 
				delay(speed2);
				break;
			case 3:
				delay(speed3);
				break;
			case 4:
				delay(speed4);
				break;
		}
		cleardevice();
		i++;
	}

}


void Car::initAnimate()
{
	char c;
	animate();
	if(gameOver) displayGameOver();
	else
	{
		c = getch();
		if(c==0)
		{
			switch(getch())
			{
				case LEFT:
					moveRightCarLeft();
					break;
				case RIGHT:
					moveRightCarRight();
					break;
				

				default:
					break;
			}
		}

		switch(c)
		{
			case ESC:
				exit(0);
				break;

			case A:
				moveLeftCarLeft();
				break;

			case SMALLA:
				moveLeftCarLeft();
				break;

			case D:
				moveLeftCarRight();
				break;

			case SMALLD:
				moveLeftCarRight();
				break;
		}
		

		initAnimate();
	}

}


void Car::animateBlocks()
{
	int tempBlocksCount;
	tempBlocksCount = blocksCountRight;
	// 0 position / distance 1 - Left(0) / Right(1)

	for(int i=tempBlocksCount-1;i>=0;i--)
	{
		blocksRight[i][0]+=10;
		blocksLeft[i][0]+=10;

	/* check for new block arrival */
		if(blocksRight[i][0]>=210 && blocksRight[i+1][0] == 0)
		{
			blocksRight[i+1][0] = 20;			// START NEW BLOCK FROM 20 HEIGHT
			if(rand()%2 == 0) blocksRight[i+1][1] = 0;
			else blocksRight[i+1][1] = 1;

			blocksCountRight++;
		}

		if(blocksLeft[i][0]>=210 && blocksLeft[i+1][0] == 0)
		{
			blocksLeft[i+1][0] = 20;			// START NEW BLOCK FROM 20 HEIGHT
			if(rand()%2 == 0) blocksLeft[i+1][1] = 0;
			else blocksLeft[i+1][1] = 1;

			blocksCountLeft++;
		}

	/*	*/

	/*	check if block is gone out of screen height */
		if(blocksRight[i][0]>=479)
		{
			for(int j=0;j<blocksCountRight-1;j++)
			{
				blocksRight[j][0] = blocksRight[j+1][0];
				blocksRight[j][1] = blocksRight[j+1][1];
			}
			blocksRight[j][0] = 0;
			blocksCountRight--;


			/* increment score */
			score+=level*10;
			switch(level){
				case 1:
					if(score>=2000)
						level++;
					break;
				case 2:
					if(score>=6000)
						level++;
					break;
				case 3:
					if(score>=15000)
						level++;
					break;
				default: break;
			}

		}


		if(blocksLeft[i][0]>=479)
		{
			for(int j=0;j<blocksCountLeft-1;j++)
			{
				blocksLeft[j][0] = blocksLeft[j+1][0];
				blocksLeft[j][1] = blocksLeft[j+1][1];
			}
			blocksLeft[j][0] = 0;
			blocksCountLeft--;

			
			/* increment score */
			score+=level*10;
			switch(level)
			{
				case 1:
					if(score>=150)
						level++;
					break;
				case 2:
					if(score>=400)
						level++;
					break;
				case 3:
					if(score>=800)
						level++;
					break;
				default: break;
			}

		}
		/**/

	}

	displayBlocksRight();
	displayBlocksLeft();

}

void Car::displayBlocksRight()
{
	setcolor(RED);
	for(int i=0;i<blocksCountRight;i++)
	{
		if(blocksRight[i][1] == 0) drawBlock(midRightLeft, blocksRight[i][0]);
		else drawBlock(midRightRight, blocksRight[i][0]);
	}
}


void Car::displayBlocksLeft()
{
	setcolor(BLUE);
	for(int i=0;i<blocksCountLeft;i++)
	{
		if(blocksLeft[i][1] == 0) drawBlock(midLeftLeft, blocksLeft[i][0]);
		else drawBlock(midLeftRight, blocksLeft[i][0]);
	}
}

void Car::drawBlock(int x, int y)
{
	circle(x, y, 10);
	circle(x, y, 5);
	circle(x, y, 4);
	circle(x, y, 9);
}


void Car::showTracks(int init)
{
	for ( int i = init;i < 70;i += 5 )
    {
	// leftmost track
	    setcolor( GREEN );
	    setfillstyle( 9, GREEN );
	    bar( 0, i * 8, 20, ( i + 2 ) * 8 );
	    bar( one4x+20, i * 8, one4x+30, ( i + 2 ) * 8 );

	    // left track
	    setcolor( GREEN );
	    setfillstyle( 9, GREEN );
	    bar( 2*one4x+30, i * 8, 2*one4x+50, ( i + 2 ) * 8 );


	// right track
	    setcolor( GREEN );
	    setfillstyle( 9, GREEN );
	    bar( 3*one4x+50, i * 8, 3*one4x+60, ( i + 2 ) * 8 );

	    // rightmost track
	    setcolor( GREEN );
	    setfillstyle( 9, GREEN );
	    bar( 4*one4x+60, i * 8, 4*one4x+80, ( i + 2 ) * 8 );

    }

}

void Car::initCarRight()
{
	if(posRightCar == 0 || posRightCar == 1)
	{
		if(posRightCar == 0) carRightMid = midRightLeft;
		else carRightMid = midRightRight;
	}
	else
	{
		if( rand()%2 == 0 )
		{
			posRightCar = 0;
			carRightMid = midRightLeft;
		}
		else
		{
			posRightCar = 1;
			carRightMid = midRightRight;
		}
	}

	/* display the car */
	showCar(carRightMid);
	showCar(carRightMid+1);
	/**/

		
}

void Car::initCarLeft()
{
	if(posLeftCar == 0 || posLeftCar == 1)
	{
		if(posLeftCar == 0) carLeftMid = midLeftLeft;
		else carLeftMid = midLeftRight;
	}
	else
	{
		if( rand()%2 == 0 )
		{
			posLeftCar = 0;
			carLeftMid = midLeftLeft;
		}
		else
		{
			posLeftCar = 1;
			carLeftMid = midLeftRight;
		}
	}

	/* display the car */
	showCar(carLeftMid);
	showCar(carLeftMid+1);
	/**/

		
}


void Car::showCar(float mid)
{
	if(mid<midx) setcolor(BLUE);
	else setcolor(RED);
	line(mid-15, maxy-100, mid-15, maxy-130);
	line(mid+15, maxy-100, mid+15, maxy-130);
	arc(mid, maxy-130, 0, 180, 15);		// so the carTopHeight is maxy-130-15 = maxy-145
	arc(mid, maxy-100, 180, 360, 15);
	if(mid<midx) setfillstyle( 1, BLUE );
	else setfillstyle(1, RED);
	bar(mid-6, maxy-118, mid+6, maxy-112);
	

	line(mid-6, maxy-118, mid-9, maxy-125);
	line(mid+6, maxy-118, mid+9, maxy-125);	
	line(mid-6, maxy-112, mid-9, maxy-105);
	line(mid+6, maxy-112, mid+9, maxy-105);	

	arc(mid, maxy-125, 0, 180, 10);
	arc(mid, maxy-105, 180, 360, 10);	
}




void Car::moveRightCarLeft(){
	// if car is at right position then only move to left
	if(posRightCar == 1)
	{
		posRightCar = 0;
		showCar(midRightLeft);
		showCar(midRightLeft+1);
	}

}

void Car::moveLeftCarLeft(){
	// if car is at right position then only move to left
	if(posLeftCar == 1)
	{
		posLeftCar = 0;
		showCar(midLeftLeft);
		showCar(midLeftLeft+1);
	}

}

void Car::moveRightCarRight(){
	if(posRightCar == 0){
		posRightCar = 1;
		showCar(midRightRight);
		showCar(midRightRight+1);
	}
}

void Car::moveLeftCarRight(){
	if(posLeftCar == 0){
		posLeftCar = 1;
		showCar(midLeftRight);
		showCar(midLeftRight+1);
	}
}



void Car::showBoomRight(float x, float y)
{
	setcolor(6);
	line(x+4,y+3,x+4,y+4.5);
	line(x+4,y+4.5,x+6,y);
	line(x+6,y,x+9,y+4);
	line(x+9,y+4,x+16,y);
	line(x+16,y+0,x+16,y+4.8);
	line(x+16,y+4.8,x+20,y+4.7);
	line(x+20,y+4.7,x+13,y+5.5);
	line(x+13,y+5.5,x+20,y+8);
	line(x+20,y+8,x+9,y+7);
	line(x+9,y+7,x+6,y+10);
	line(x+6,y+10,x+4,y+7);
	line(x+4,y+7,x,y+8);
	line(x,y+8,x+5,y+5.5);
	line(x+5,y+5.5,x,y+3);
}

int Car::checkGameOver()
{
	float boomRightY = 0, boomLeftY = 0, midRightCar=0, midLeftCar=0, boomRightX, boomLeftX;
	
	/* check if right car hit the block */
	if( posRightCar == blocksRight[0][1] && ( carTopHeight <= blocksRight[0][0]+10  && blocksRight[0][0] <= carTopHeight+70) )	// 15, 15 - arc, 30 - line
	{	
		if(blocksRight[0][0] > carTopHeight+15)
		{
			if(posRightCar == 0)
			{
				midRightCar = midRightLeft+20;
				boomRightX = midRightLeft+5;
			}
			else
			{
				midRightCar = midRightRight-20;
				boomRightX = midRightRight-10;
			}

			boomRightY = blocksRight[0][0]-5;

		}
		else
		{
			if(posRightCar == 0 )
			{
				midRightCar = midRightLeft;
				boomRightX = midRightLeft-10;
			}
			else
			{
				midRightCar = midRightRight;
				boomRightX = midRightRight-10;
			}
			boomRightY = blocksRight[0][0]+5;
		}			
		gameOver = 1;
	}

	/* check if left car hit the block */
	if( posLeftCar == blocksLeft[0][1] && ( carTopHeight <= blocksLeft[0][0]+10  && blocksLeft[0][0] <= carTopHeight+70) )
	{
		if(blocksLeft[0][0] > carTopHeight+15)
		{
			if(posLeftCar == 0)
			{
				midLeftCar = midLeftLeft+20;
				boomLeftX = midLeftLeft+5;
			}
			else
			{
				midLeftCar = midLeftRight-20;
				boomLeftX = midLeftRight-10;
			}

			boomLeftY = blocksLeft[0][0]-5;

		}
		else
		{
			if(posLeftCar == 0 )
			{
				midLeftCar = midLeftLeft;
				boomLeftX = midLeftLeft-10;
			}
			else
			{
				midLeftCar = midLeftRight;
				boomLeftX = midLeftRight-10;
			}
			boomLeftY = blocksLeft[0][0]+5;
		}			
		gameOver = 1;
	}

	if(gameOver)
	{
		cleardevice();
		displayBlocksRight();
		displayBlocksLeft();
		showTracks(0);
		showScore();
		if(midRightCar!=0)
		{
			showCar(midRightCar);
			showCar(midRightCar+1);
		}
		else
		{
			if(posRightCar == 0)
			{
				showCar(midRightLeft);
				showCar(midRightLeft+1);
			}
			else
			{
				showCar(midRightRight);
				showCar(midRightRight+1);
			}

		}
		if(midLeftCar!=0)
		{
			showCar(midLeftCar);
			showCar(midLeftCar+1);
		}
		else
		{
			if(posLeftCar == 0)
			{
				showCar(midLeftLeft);
				showCar(midLeftLeft+1);
			}
			else
			{
				showCar(midLeftRight);
				showCar(midLeftRight+1);
			}

		}
		/* display boom in the side where it hits block either of side or both side */
		if(boomRightY!=0)
		{	
			showBoomRight(boomRightX, boomRightY);
			showBoomRight(boomRightX+1, boomRightY);
		}
		if(boomLeftY!=0)
		{	
			showBoomRight(boomLeftX, boomLeftY);
			showBoomRight(boomLeftX+1, boomLeftY);
		}
		/**/
		return 1;
	}
	else return 0;

}



void Car::displayGameOver()
{
	setcolor(RED);
	settextstyle( 3, 0, 7 );
	outtextxy(midx-130, midy-65, "Game Over!");
	/* save if its high score */
		struct highscore s, ns;
		FILE *read, *write;
		read = fopen("highscore.txt","r");
		if(read==NULL)
		{
			fclose(read);
			getch();		
			clrscr();
			cleardevice();		
			s.score = score;
			cout<<endl<<endl<<"\t\t\tCongratulation you got highest score !";
			cout<<endl<<endl<<endl<<"\t\t\tEnter your name ";
			scanf("%s",&s.name);
			write = fopen("highscore.txt", "w+");
			fwrite(&s,sizeof(s),1,write);
			fclose(write);

		}
		else
		{
			fread(&s, sizeof(s),1, read);
			if(s.score<score)
			{
				getch();
				clrscr();
				cleardevice();
				ns.score = score;
				cout<<endl<<endl<<"\t\t\tCongratulation you got highest score !";
				cout<<endl<<endl<<endl<<"\t\t\tEnter your name ";
				scanf("%s",&ns.name);
				write = fopen("highscore.txt", "w+");
				fwrite(&ns,sizeof(s),1,write);
				fclose(write);
			}
			fclose(read);
		}
	/**/
	cout<<endl<<endl<<endl<<endl<<"\t\t\tPress ESC to exit ! ";
	while(getch() != ESC){}


}



void Car::showScore()
{
	char buf[5];
	setfillstyle(1, BLUE );
	bar(maxx+110, 30, maxx+170, 50);
	setcolor(WHITE);
	sprintf( buf, "%.0f", score );
	outtextxy(maxx+115, 40, buf );
	/*level*/
	setfillstyle(1, BROWN );
	bar(maxx+110, 70, maxx+170, 90);
	setcolor(WHITE);
	sprintf( buf, "%d", level );
	outtextxy(maxx+115, 80, buf );
	/* high score */
	if(highScore != 0)
	{
		setfillstyle(1, GREEN );
		bar(maxx+110, 110, maxx+170, 130);
		setcolor(WHITE);
		outtextxy(maxx+115, 120, highScorer);
		setfillstyle(1, RED );
		bar(maxx+110, 150, maxx+170, 170);
		setcolor(WHITE);
		sprintf( buf, "%.0f", highScore);
		outtextxy(maxx+115, 160, buf);
	}
}

void Car::readHighScore()
{
	FILE *read;
	struct highscore s;
	read = fopen("highscore.txt","r");
	if(read != NULL)
	{
		fread(&s, sizeof(s), 1, read);
		fclose(read);
		strcpy(highScorer, s.name);
		highScore = s.score;
	}
	
}



void main()
{
	clrscr();
	float x,y,a,b,c;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	Car car;
	car.initializeData();
	car.initAnimate();

}