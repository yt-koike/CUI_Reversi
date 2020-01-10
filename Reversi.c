#include<stdio.h>
#define WIDTH 8
#define HEIGHT 8
#define MP(x,y) ((x)+(y)*WIDTH)
#define P1 'o'
#define P2 'x'

const int mapsize=WIDTH*HEIGHT;
char map[WIDTH*HEIGHT];
void mapshow();
int check(int p,int dx,int dy,char player);
int checkall(int p,char player);

void mapinit(){
for(int i=0;i<mapsize;i++)map[i]='_';
map[MP(WIDTH/2-1,HEIGHT/2-1)]=P1;
map[MP(WIDTH/2,HEIGHT/2-1)]=P2;
map[MP(WIDTH/2-1,HEIGHT/2)]=P2;
map[MP(WIDTH/2,HEIGHT/2)]=P1;
return;
}

char c(int line,int row){
if(line<0||line>WIDTH-1||row<0||row>WIDTH-1)return -1;
return map[MP(line,row)];
}

void flip(int line,int row){
char c=map[MP(line,row)];
if(c==P1)c=P2;
else if(c==P2)c=P1;
map[MP(line,row)]=c;
return;
}


int main(){
	//init start
	mapinit();
	int player=1;
	int line,row;
	char input[3];
	//init end

	//main loop start
	while(1){
		mapshow();

		//input start
		printf("Player%d '%c':",player,(player==1)?P1:P2);
		scanf("%2s",input);
		//input end

		//custom function start
		if(input[0]=='q')break;
		if(input[0]=='p'){
			printf("Pass\n");
			player=3-player;
			continue;
		}
		if(input[0]=='r'){
			int point1=0,point2=0;
			for(int i=0;i<mapsize;i++){
				if(map[i]==P1)point1++;
				if(map[i]==P2)point2++;
			}
			printf("'%c':%d, '%c':%d\n",P1,point1,P2,point2);
			continue;
		}
		//custom function end
		line=input[0]-'a';
		row=input[1]-'1';
		int p=line+row*WIDTH;

		//error detect start
		if(p<0||mapsize-1<p){
			printf("Invalid input.\n");
			continue;
		}
		if(c(line,row)!='_'){
			printf("The space is occupied.\n");
			continue;
		}
		int flipped=checkall(line+row*WIDTH,(player==1)?P1:P2);
		if(flipped==0){
			printf("You cannot place it there.\n");
			continue;
		}
		//error detect end

		printf("flipped:%d\n",flipped);
		map[p]=(player==1)?P1:P2;

		//clear check start
		int blank=0;
		for(int i=0;i<mapsize;i++)if(map[i]=='_')blank++;
		if(blank==0)break;
		//clear check end

		player=3-player;
	}
	//main loop end
int point1=0,point2=0;
for(int i=0;i<mapsize;i++){
	if(map[i]==P1)point1++;
	if(map[i]==P2)point2++;
}
if(point1!=point2)
	printf("Player%d win!",(point1>point2)?1:2);
else
	printf("Draw");

return 0;
}

void mapshow(){
	printf(" ");
	for(int i=0;i<WIDTH;i++)printf("%c",i+'a');
	printf("\n");
	for(int i=0;i<HEIGHT;i++){
		printf("%d",i+1);
		for(int j=0;j<WIDTH;j++) printf("%c",c(j,i));
		printf("\n");
	}
	return;
}

int checkall(int p,char player){
	int sum=0;
	sum+=check(p,1,0,player);
	sum+=check(p,-1,0,player);
	sum+=check(p,0,1,player);
	sum+=check(p,0,-1,player);
	sum+=check(p,1,1,player);
	sum+=check(p,1,-1,player);
	sum+=check(p,-1,1,player);
	sum+=check(p,-1,-1,player);
	return sum;
}

int check(int p,int dx,int dy,char player){
	int x,y,count=0;
	x=p%WIDTH;
	y=p/WIDTH;
	while(1){
		x+=dx;
		y+=dy;
		if(x<0||x>WIDTH||y<0||y>HEIGHT)return 0;
		if(c(x,y)=='_')return 0;
		if(c(x,y)==player)break;
		count++;
	}
	for(int i=0;i<count;i++){
		x-=dx;
		y-=dy;
		flip(x,y);
	}
	return count;
}
