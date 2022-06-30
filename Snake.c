#include <stdio.h>
#include <stdlib.h>
#define MAX 13
int n=MAX-1;
struct dot{
	int dir;
	struct dot *next;
};
int hi[2]={0,0};
char m[MAX][MAX];
int score;
struct dot *head;
struct dot *cur;
struct dot *tail;
typedef struct{
	int x;
	int y;
} locate;
locate ltail;
locate lhead;
locate treat;
int count;
char mode;
void cmode()
{
	printf("Mode:\n");
	printf("\t1. Classic\n");
	printf("\t2. Modern\n");
	do
	{
		mode=getch();
	} while (mode!='1'&&mode!='2');
}
void intro()
{
	system("cls");
	printf("Instruction:\n");
	printf("\tW: Up\n");
	printf("\tS: Down\n");
	printf("\tA: Left\n");
	printf("\tD: Right\n");
	printf("Press any key to continue.\n");
	getch();
}
void screen()
{
	int i,j;
	system("cls");
	printf("Score: %d\n",score);
	for (j=0;j<MAX;j++)
	{
		for (i=0;i<MAX;i++)
			printf("%c ",m[i][j]);
		printf("\n");
	}
}
locate cdir(int dir, locate lcat)
{
	locate cat;
	switch(dir)
	{
		case -2: 
			cat.y=(lcat.y)-1;
			cat.x=lcat.x;
			break;
		case 2:
			cat.y=(lcat.y)+1;
			cat.x=lcat.x;
			break;
		case -1: 
			cat.x=(lcat.x)-1;
			cat.y=lcat.y;
			break;
		case 1:
			cat.x=(lcat.x)+1;
			cat.y=lcat.y;
			break;
	}
	return cat;
}
void wall (locate *lcat)
{
	if (lcat->x==0)
		lcat->x=n-1;
	else if (lcat->x==n)
		lcat->x=1;
	else if (lcat->y==0)
		lcat->y=n-1;
	else if (lcat->y==n)
		lcat->y=1;
}
int mhead(int in)
{
	if (head->dir==-in)
		in=head->dir;
	m[lhead.x][lhead.y]='.';
	lhead=cdir(in,lhead);
	cur=(struct dot *)malloc(sizeof(struct dot));
	cur->dir=in;
	cur->next=NULL;
	if (m[lhead.x][lhead.y]=='*')
		switch(mode)
		{
			case '1':
				wall(&lhead);
				break;
			case '2':
				return 0;
		}
	head->next=cur;
	head=head->next;
	if (m[lhead.x][lhead.y]=='.')
	{
		if (lhead.x==ltail.x&&lhead.y==ltail.y)
		{
			m[lhead.x][lhead.y]='o';
			return 2;
		}
		else return 0;
	}
	m[lhead.x][lhead.y]='o';
	return 1;
}
int eat()
{
	if (lhead.x==treat.x&&lhead.y==treat.y)
	{
		score+=5;
		count++;
		if (count==(n-1)*(n-1))
		{
			return 2;
		}
		do
		{
			treat.x=(rand()%(n-1))+1;
			treat.y=(rand()%(n-1))+1;
		} while (m[treat.x][treat.y]!=' ');
		m[treat.x][treat.y]='x';
		return 1;
	}
	return 0;
}
void mtail(int ok)
{
	if (ok==1)
	{
		m[ltail.x][ltail.y]=' ';
		cur=tail;
		tail=tail->next;
		free(cur);
	}
	else
		tail=tail->next;
	ltail=cdir(tail->dir,ltail);
	if (m[ltail.x][ltail.y]=='*')
	wall(&ltail);
}
void gameover()
{
	system("cls");
	printf("Game over!\n");
	printf("Score: %d\n",score);
	if (score>hi[(int)(mode-'1')])
		hi[mode-'1']=score;
	printf("High score: %d\n",hi[mode-'1']);
	while(tail!=NULL)
	{
		cur=tail;
		tail=tail->next;
		free(cur);
	}
	sleep(2);
}
void play()
{
	int i,j;
	char ctrl;
	int in;
	int ok;
	int e;
	for (i=1;i<n;i++)
		for (j=1;j<n;j++)
			m[i][j]=' ';
	head=(struct dot *)malloc(sizeof(struct dot));
	head->dir=1;
	head->next=NULL;
	lhead.x=n/2;
	lhead.y=n/2;
	m[lhead.x][lhead.y]='o';
	cur=(struct dot *)malloc(sizeof(struct dot));
	cur->dir=1;
	cur->next=head;
	m[lhead.x-1][lhead.y]='.';
	tail=(struct dot *)malloc(sizeof(struct dot));
	tail->dir=1;
	tail->next=cur;
	ltail.x=n/2-2;
	ltail.y=n/2;
	m[ltail.x][ltail.y]='.';
	count=3;
	for (i=0;i<MAX;i++)
		m[0][i]=m[n][i]=m[i][0]=m[i][n]='*';
	do
		{
			treat.x=(rand()%(n-1))+1;
			treat.y=(rand()%(n-1))+1;
		} while (m[treat.x][treat.y]!=' ');
		m[treat.x][treat.y]='x';
	cmode();
	intro();
	score=0;
	while(1)
	{
		screen();
		usleep((mode-'0')*100000/3);
		if(kbhit())
			ctrl=getch();
		switch(ctrl)
		{
			case 'a': case 'A': in=-1; break;
			case 'd': case 'D': in=1; break;
			case 'w': case 'W': in=-2; break;
			case 's': case 'S': in=2; break;
			default: in=head->dir;
		}
		ok=mhead(in);
		e=eat();
		if (ok==0||e==2)
		{
			gameover();
			break;
		}
		else if (e==0)
			mtail(ok);
	}
}
void menu()
{
	int o;
	system("cls");
	printf("Menu: \n");
	printf("\t1. Play\n");
	printf("\t2. High score\n");
	printf("\t3. Exit\n");
	do
		o=getch();
	while (o!='1'&&o!='2'&&o!='3');
	system("cls");
	switch(o)
	{
		case '1':
			play();
			break;
		case '2':
			printf("High score:\n");
			printf("\tClassic: %d\n",hi[0]);
			printf("\tModern: %d\n",hi[1]);
			printf("Press any key to continue.\n");
			getch();
			break;
		case '3':
			printf("Press any key to exit.\n");
			getch();
			exit(0);
	}
}
int main()
{
	while(1)
		menu();
	return 0;
}
