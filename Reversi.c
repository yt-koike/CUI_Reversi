#include<stdio.h>
#define WIDTH 8
#define HEIGHT 8
#define XY_TO_POINTER(x,y) ((x)+(y)*WIDTH)
#define BLANK '_'
#define P1 'o'
#define P2 'x'

const int mapsize=WIDTH*HEIGHT;
char map[WIDTH*HEIGHT];
void mapshow();
int count_flippable(int p,int dx,int dy,int player_number);
int count_flippable_all(int p,int player_number);

char player_char(int player_number){
	if(player_number==1)return P1;
	if(player_number==2)return P2;
	return -1;
}

void map_init(){
for(int i=0;i<mapsize;i++)map[i]='_';
map[XY_TO_POINTER(WIDTH/2-1,HEIGHT/2-1)]=P1;
map[XY_TO_POINTER(WIDTH/2,HEIGHT/2-1)]=P2;
map[XY_TO_POINTER(WIDTH/2-1,HEIGHT/2)]=P2;
map[XY_TO_POINTER(WIDTH/2,HEIGHT/2)]=P1;
return;
}

char pointed_piece(int pointer){
	if(pointer<0||pointer>mapsize-1)
		return -1;
	return map[pointer];
}

void flip(int pointer){
	     if(map[pointer]==P1)map[pointer]=P2;
   	else if(map[pointer]==P2)map[pointer]=P1;
	return;
}



int main(){
	//init start
	map_init();
	int current_player_number=1;
	int line,row;
	char input[3];
	//init end

	//main loop start
	while(1){
		mapshow();

		//input start
		printf("Current player is %d '%c':",current_player_number,player_char(current_player_number));
		scanf("%2s",input);
		//input end

		//custom function start
		if(input[0]=='q')break;
		if(input[0]=='p'){
			printf("Pass\n");
			current_player_number=3-current_player_number;
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
		int pointer=XY_TO_POINTER(line,row);

		//error detect start
		if(pointer<0||pointer>=mapsize){
			printf("Invalid input.\n");
			continue;
		}
		if(map[pointer]!=BLANK){
			printf("The space is occupied.\n");
			continue;
		}
		int flipped=count_flippable_all(pointer,current_player_number);
		if(flipped==0){
			printf("You cannot place it there.\n");
			continue;
		}
		//error detect end

		printf("flipped:%d\n",flipped);
		map[pointer]=player_char(current_player_number);

		//game_clear check start
		int occupied_space_num=0;
		for(int i=0;i<mapsize&&map[i]!='_';i++)occupied_space_num++;
		if(occupied_space_num==mapsize){
			int point1=0,point2=0;
			for(int i=0;i<mapsize;i++){
			        if(map[i]==P1)point1++;
			        if(map[i]==P2)point2++;
			}
			if(point1!=point2)
		        	printf("Player%d win!",(point1>point2)?1:2);
			else
			        printf("Draw");
			printf("END\n");
			return 0;
		}
		//game_clear check end

		current_player_number=3-current_player_number;
	}
	//main loop end
}

void mapshow(){
	printf(" ");
	for(int i=0;i<WIDTH;i++)printf("%c",i+'a');
	printf("\n");
	for(int row=0;row<HEIGHT;row++){
		printf("%d",row+1);
		for(int line=0;line<WIDTH;line++) printf("%c",map[XY_TO_POINTER(line,row)]);
		printf("\n");
	}
	return;
}

int count_flippable_all(int pointer,int player_number){
	int sum=0;
	sum+=count_flippable(pointer,+1,0,player_number);
	sum+=count_flippable(pointer,-1,0,player_number);
	sum+=count_flippable(pointer,0,+1,player_number);
	sum+=count_flippable(pointer,0,-1,player_number);
	sum+=count_flippable(pointer,+1,+1,player_number);
	sum+=count_flippable(pointer,+1,-1,player_number);
	sum+=count_flippable(pointer,-1,+1,player_number);
	sum+=count_flippable(pointer,-1,-1,player_number);
	return sum;
}

int count_flippable(int piece_pointer,int dx,int dy,int player_num){
        int p=piece_pointer;
	int dp=XY_TO_POINTER(dx,dy);
	int flippable_num=0;
	char piece;
	for(int current_pointer=piece_pointer+dp ;piece!=player_char(player_num) ;current_pointer+=dp){
		piece=map[current_pointer];
		if(piece==BLANK||piece==-1)return 0;
		flippable_num++;
	}
	for(int i=0;i<flippable_num;i++){
		p+=dp;
		map[p]=player_char(player_num);
	}
	return flippable_num;
}
