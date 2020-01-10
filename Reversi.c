#include<stdio.h>
#define WIDTH 8
#define HEIGHT 8
#define MP(x,y) (x+y*WIDTH)
#define P1 'o'
#define P2 'x'

char map[WIDTH*HEIGHT];
void show();
int check(int line,int row,int player);


char c(int line,int row){
return map[MP(line,row)];
}

void flip(int line,int row){
char c=map[MP(line,row)];
if(c==P1)c=P2;
else if(c==P2)c=P1;
map[MP(line,row)]=c;
//printf("%d %d",line,row);
return;
}


int main(){
//init
const int size=WIDTH*HEIGHT;
for(int i=0;i<size;i++)map[i]='_';
map[MP(3,3)]=P1;
map[MP(4,3)]=P2;
map[MP(3,4)]=P2;
map[MP(4,4)]=P1;
int player=1;
int line,row;
char input[3];
//main
while(1){
show();
printf("Player%d '%c':",player,(player==1)?P1:P2);
scanf("%2s",input);
if(input[0]=='q')break;
if(input[0]=='r'){
int point1=0,point2=0;
for(int i=0;i<size;i++){
	if(map[i]==P1)point1++;
	if(map[i]==P2)point2++;
}
printf("'%c':%d, '%c':%d\n",P1,point1,P2,point2);
continue;
}

line=input[0]-'a';
row=input[1]-'1';
int p=line+row*WIDTH;
if(p<0||size-1<p){
printf("Invalid input.\n");
continue;
}
if(c(line,row)!='_'){
printf("The space is occupied.\n");
continue;
}
int flipped=check(line,row,player);
if(flipped==0){
printf("You cannot place it there.\n");
continue;
}
printf("flipped:%d\n",flipped);
map[p]=(player==1)?P1:P2;
player=3-player;
}
return 0;
}

void show(){
printf(" ");
for(int i=0;i<WIDTH;i++)printf("%c",i+'a');
printf("\n");
for(int i=0;i<HEIGHT;i++){
 printf("%d",i+1);
 for(int j=0;j<WIDTH;j++)
  printf("%c",map[j+i*WIDTH]);
 printf("\n");
}
return;
}

int check(int line,int row,int player){
int flipped=0;
char player_char=(player==1)?P1:P2;
char enemy=(player==1)?P2:P1;
int x,y,temp;
//left
x=line;
y=row;
temp=0;
x--;
while(x>0){
	if(c(x,y)=='_')break;
	if(c(x,y)==enemy)temp++;
	if(c(x,y)==player_char){
		flipped+=temp;
		x++;
		for(int i=x;i<line;i++)flip(i,y);
		break;
	}
	x--;
}
//right
x=line;
y=row;
temp=0;
x++;
while(x<WIDTH){
	if(c(x,y)=='_')break;
	if(c(x,y)==enemy)temp++;
	if(c(x,y)==player_char){
		flipped+=temp;
		x--;
		for(int i=x;i>0;i--)flip(i,y);
		break;
	}
	x++;
}
//up
x=line;
y=row;
temp=0;
y--;
while(y>0){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                y++;
                for(int i=y;i<HEIGHT;i++)flip(x,i);
                break;
        }
        y--;
}
//down
x=line;
y=row;
temp=0;
y++;
while(y<HEIGHT){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                y--;
                for(int i=y;i>0;i--)flip(x,i);
                break;
        }
        y++;
}
//left up
x=line;
y=row;
temp=0;
x--;
y--;
while(x>0&&y>0){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                for(int i=1;i<temp+1;i++)flip(x+i,y+i);
                break;
        }
        x--;
	y--;
}
//left down
x=line;
y=row;
temp=0;
x--;
y++;
while(x>0&&y<HEIGHT){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                for(int i=1;i<temp+1;i++)flip(x+i,y-i);
                break;
        }
        x--;
        y++;
}

//right up
x=line;
y=row;
temp=0;
x++;
y--;
while(x<WIDTH&&y>0){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                for(int i=1;i<temp+1;i++)flip(x-i,y+i);
                break;
        }
        x++;
        y--;
}

//right down
x=line;
y=row;
temp=0;
x++;
y++;
while(x<WIDTH&&y<HEIGHT){
	if(c(x,y)=='_')break;
        if(c(x,y)==enemy)temp++;
        if(c(x,y)==player_char){
                flipped+=temp;
                for(int i=1;i<temp+1;i++)flip(x-i,y-i);
                break;
        }
        x++;
        y++;
}



return flipped;
}
