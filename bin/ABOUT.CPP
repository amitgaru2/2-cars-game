#include<stdio.h>
#include<conio.h>
#include<graphics.h>
void main()
{
clrscr();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..//bgi");
	float midx,midy;
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	setcolor(RED);
	line(midx-50,50,midx+50,50);
	line(midx-50,100,midx+50,100);
	setcolor(WHITE);
	outtextxy(midx-25,75,"2 CARS GAME");
	setcolor(WHITE);
	outtextxy(midx-25,125,"CREDITS");
	setcolor(RED);
	line(midx-26,137,midx+30,137);
	setcolor(GREEN);
	outtextxy(midx-75,147,"Developed by: Amit Garu");
	outtextxy(midx+28,162,"Bibin Vinduwa");
	setcolor(WHITE);
	outtextxy(midx-35,248,"ABOUT 2 CARS GAME");
	setcolor(RED);
	line(midx-36,260,midx+60,260);
	setcolor(GREEN);
	outtextxy(150,272,"2 cars game is a simple game in which player has to avoid the ");
	outtextxy(150,284,"circle blocks. A player has to control the two cars i.e  ");
	outtextxy(150,296,"red and blue without striking the round blocks.");
	setcolor(WHITE);
	outtextxy(midx-35,346,"PLAYING TIPS");
	setcolor(RED);
	line(midx-36,358,midx+60,358);
	setcolor(GREEN);
	outtextxy(150,370,"1.Control the two cars. ");
	outtextxy(150,382,"2.Avoid the round blocks in road track.");
	outtextxy(150,394,"3.Score as many as pssible ");



getch();
}