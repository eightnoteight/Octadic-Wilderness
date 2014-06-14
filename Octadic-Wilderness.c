#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <setjmp.h>
#include <signal.h>
#include <ncurses.h>
#define UP_KEY 259
#define DOWN_KEY 258
#define LEFT_KEY 260
#define RIGHT_KEY 261
#define ENTER 10
int matrix[]={0,1,2,3,4,5,6,7,8};
typedef enum { False, True } boool;
const boool number[][64] ={
     {1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1},
     {1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1},
     {1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,1},
     {1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1},
     {1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1},
     {1,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1},
     {1,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1},
     {1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1},
     {1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1},
     {1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1},
};
int row, col;
typedef struct {
	int x;
	int y;
} coor;
void swap(int *p, int *q){
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}
void shuffle(int *data,int size){
	int i,j;
	srand(time(NULL));
	for (i = 0; i < size-1; ++i)
	{
		j=rand()%(size-i) + i;
		swap(data+i,data+j);
	}
}
void geekyreaper(int ro,int co,int val) {
	int i,j;
	attron(A_STANDOUT);
	mvprintw(ro,co,"xxxxxxxxxxxxxx");
	mvprintw(ro+1,co,"xx");
	mvprintw(ro+1,co+12,"xx");
	attroff(A_STANDOUT);
	j=co;
	for (i = 0; i < 70; ++i,++j)
	{
		if (j==co+14)
		{
			j=co;
			ro++;
		}
		if (number[val][i/2])
		{
			attron(A_STANDOUT);
	    	bkgdset(COLOR_PAIR(number[val][i/2]));
	    	mvaddch(ro+2,j,'x');
	    	attroff(A_STANDOUT);
		}
		else 
			mvaddch(ro+2,j,' ');
		
	}
	attron(A_STANDOUT);
	mvprintw(ro+3,co,"xx");
	mvprintw(ro+3,co+12,"xx");
	mvprintw(ro+4,co,"xxxxxxxxxxxxxx");
	attroff(A_STANDOUT);

}
void kidreaper(int ro,int co,int val) {
	int i,j;
	attron(A_STANDOUT);
	mvprintw(ro,co,"              ");
	mvprintw(ro+1,co,"  ");
	mvprintw(ro+1,co+12,"  ");
	attroff(A_STANDOUT);
	j=co;
	for (i = 0; i < 70; ++i,++j)
	{
		if (j==co+14)
		{
			j=co;
			ro++;
		}
		if (number[val][i/2])
		{
			attron(A_STANDOUT);
	    	bkgdset(COLOR_PAIR(number[val][i/2]));
	    	mvaddch(ro+2,j,' ');
	    	attroff(A_STANDOUT);
		}
		else 
			mvaddch(ro+2,j,' ');
		
	}
	attron(A_STANDOUT);
	mvprintw(ro+3,co,"  ");
	mvprintw(ro+3,co+12,"  ");
	mvprintw(ro+4,co,"              ");
	attroff(A_STANDOUT);
}
/* meas =  measurements */
/*  reaper had this habit of keeping his secret flag 
	somewhere in the wilderness. To recognize his 
	architecture */
void reaper(int tools[], int meas, coor sflag){
	int worh=sqrt(meas),i,j,k=0;
	int totwor=worh*14 + worh -1;
	int totorh=worh*9 +worh -1;
	for (i = 0; i < worh; ++i)
	{
		for (j = 0; j < worh; ++j)
		{
			if ((sflag.y==i)&&(sflag.x==j))
				geekyreaper((row-totorh)/2 + i*10 +2, (col-totwor)/2 + j*15, tools[k++]);
			else
				kidreaper((row-totorh)/2 + i*10 +2,  (col-totwor)/2 + j*15, tools[k++]);
		}
	}
}
int findzero(int dat[]){
	int i;
	for (i = 0; i < 9; ++i)
		if (dat[i]==0)
			return i;
}
void moveint(int dat[], coor pint){
	int z=findzero(dat),sp=(pint.x) + ((pint.y)*3);
	swap(dat+sp,dat+z);
}
boool isgoalmatrix(){
	int i;
	int gmat[]={1,2,3,8,0,4,7,6,5};
	for (i = 0; i < 9; ++i)
		if (matrix[i]!=gmat[i])
			return 1;
	return 0;
}
boool gameinit(){
	int i,c;
	coor zero;
	zero.x=0;
	zero.y=0;
	shuffle(matrix,9);
	while(*(matrix+4)==0)
		shuffle(matrix,9);
	reaper(matrix, 9, zero); /* reaper is the architect of wilderness */
	refresh();
	while(isgoalmatrix())
	{
		c=getch();
		switch(c)
		{
			case UP_KEY:
				if (zero.y==0)
					zero.y=2;
				else
					zero.y--;
				reaper(matrix,9,zero);
				refresh();
				break;
			case DOWN_KEY:
				if (zero.y==2)
					zero.y=0;
				else
					zero.y++;
				reaper(matrix,9,zero);
				refresh();
				break;
			case LEFT_KEY:
				if (zero.x==0)
					zero.x=2;
				else
					zero.x--;
				reaper(matrix,9,zero);
				refresh();
				break;
			case RIGHT_KEY:
				if (zero.x==2)
					zero.x=0;
				else
					zero.x++;
				reaper(matrix,9,zero);
				refresh();
				break;
			case ENTER:
				moveint(matrix,zero);
				reaper(matrix,9,zero);
				refresh();
				break;
			case 27:
				return 0;
		}
	}
	return 1;
}
void Loser(){
	clear();
	mvprintw(row/2,(col-17)/2, "ARAGOG - WINNER :(");
}

void Winner(){
	clear();
	mvprintw(row/2,(col-10)/2, "WINNER! :)");
}
int main(int argc, char const *argv[]){
	int i;
	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);
	getmaxyx(stdscr,row,col);
	attron(A_BOLD);
	mvprintw(0,(col-34)/2,"Welcome to the Octadic Wilderness.\n\n");
	for (i = 0; i < col; ++i)
		printw("-");
	attroff(A_BOLD);
	if(gameinit())
		Winner();
	else 
		Loser();
	getch();
	endwin();
	return 0;
}