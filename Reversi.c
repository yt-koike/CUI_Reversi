#include <stdio.h>
#define WIDTH 8
#define HEIGHT 8
#define XY_TO_POINTER(x, y) ((x) + (y)*WIDTH)
#define BLANK '_'
#define P1 'o'
#define P2 'x'

const int mapsize = WIDTH * HEIGHT;
char map[WIDTH * HEIGHT];
void mapshow();
int flip_line(int p, int dx, int dy, int player_number);
int flip_line_all(int p, int player_number);

char player_char(int player_number)
{
	if (player_number == 1)
		return P1;
	if (player_number == 2)
		return P2;
	return -1;
}

char enemy_char(int player_number)
{
	return player_char(3 - player_number);
}

int next_player(int player_number)
{
	return 3 - player_number;
}

void map_init()
{
	for (int i = 0; i < mapsize; i++)
		map[i] = BLANK;
	map[XY_TO_POINTER(WIDTH / 2 - 1, HEIGHT / 2 - 1)] = P1;
	map[XY_TO_POINTER(WIDTH / 2, HEIGHT / 2 - 1)] = P2;
	map[XY_TO_POINTER(WIDTH / 2 - 1, HEIGHT / 2)] = P2;
	map[XY_TO_POINTER(WIDTH / 2, HEIGHT / 2)] = P1;
	return;
}

int is_pointer_valid(int pointer)
{
	return (0 <= pointer && pointer < mapsize);
}

char pointed_piece(int pointer)
{
	if (!is_pointer_valid(pointer))
		return -1;
	return map[pointer];
}

void scores(int *N1, int *N2)
{
	*N1 = *N2 = 0;
	for (int i = 0; i < mapsize; i++)
	{
		if (map[i] == P1)
			*N1 = *N1 + 1;
		if (map[i] == P2)
			*N2 = *N2 + 1;
	}
	return;
}

void flip(int pointer)
{
	if (map[pointer] == P1)
		map[pointer] = P2;
	else if (map[pointer] == P2)
		map[pointer] = P1;
	return;
}

int main()
{
	// init start
	map_init();
	int current_player_number = 1;
	int line, row;
	char input[3];
	// init end
	printf("Enter 'h' to view help.\n");

	// main loop start
	while (1)
	{
		mapshow();

		// input start
		printf("Current player is %d '%c':", current_player_number, player_char(current_player_number));
		scanf("%2s", input);
		// input end

		// custom function start
		if (input[0] == 'q')
			break;
		else if (input[0] == 'p')
		{
			printf("Pass\n");
			current_player_number = 3 - current_player_number;
			continue;
		}
		else if (input[0] == 's')
		{
			int point1, point2;
			scores(&point1, &point2);
			printf("Player1:%d, Player2:%d\n", point1, point2);
			continue;
		}
		else if (input[0] == 'h')
		{
			printf("Help:\n");
			printf("Input row and line you want to put your piece.\n");
			printf("Example: f4\n");
			printf("You can pass by entering 'p'.\n");
			printf("You can see the scores by entering 's'.\n");
			printf("\n");
		}
		// custom function end
		line = input[0] - 'a';
		row = input[1] - '1';
		int pointer = XY_TO_POINTER(line, row);
		// error detect start
		if (!is_pointer_valid(pointer))
		{
			printf("Invalid input.\n");
			continue;
		}
		if (map[pointer] != BLANK)
		{
			printf("The space is occupied.\n");
			continue;
		}
		int flipped = flip_line_all(pointer, current_player_number);
		if (flipped == 0)
		{
			printf("You cannot place it there.\n");
			continue;
		}
		// error detect end

		printf("flipped:%d\n", flipped);
		map[pointer] = player_char(current_player_number);

		// game_clear check start
		int occupied_space_num = 0;
		for (int i = 0; i < mapsize && map[i] != '_'; i++)
			occupied_space_num++;
		if (occupied_space_num == mapsize)
		{
			int point1, point2;
			scores(&point1, &point2);
			if (point1 != point2)
				printf("Player%d win!", (point1 > point2) ? 1 : 2);
			else
				printf("Draw");
			printf("END\n");
			return 0;
		}
		// game_clear check end

		current_player_number = next_player(current_player_number);
	}
	// main loop end
}

void mapshow()
{
	printf(" ");
	for (int i = 0; i < WIDTH; i++)
		printf("%c", i + 'a');
	printf("\n");
	for (int row = 0; row < HEIGHT; row++)
	{
		printf("%d", row + 1);
		for (int line = 0; line < WIDTH; line++)
			printf("%c", map[XY_TO_POINTER(line, row)]);
		printf("\n");
	}
	return;
}

int flip_line_all(int pointer, int player_number)
{
	int sum = 0;
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0)
				continue;
			sum += flip_line(pointer, dx, dy, player_number);
		}
	}
	return sum;
}

int flip_line(int piece_pointer, int dx, int dy, int player_num)
{
	int dp = XY_TO_POINTER(dx, dy);
	char player = player_char(player_num);
	char enemy = enemy_char(player_num);
	if (!(is_pointer_valid(piece_pointer + dp) && map[piece_pointer + dp] == enemy))
		return 0;
	for (int p = piece_pointer + dp + dp; map[p] != player; p += dp)
	{
		if (!is_pointer_valid(p))
		{
			return 0;
		}
		if (map[p] != enemy)
			return 0;
	}
	int flippable_num = 0;
	for (int p = piece_pointer + dp; map[p] != player; p += dp)
	{
		map[p] = player;
		flippable_num++;
	}
	return flippable_num;
}
