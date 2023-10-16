#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int SIZE = 5;
int com[5][5] = {};
int usr[5][5] = {};
int game[5][5] = {};

int check_input(int a, int b) {
	if(a >= SIZE || a < 0 || b >= SIZE || b < 0) {
		printf("0 ~ %d, 0 ~ %d 사이의 값을 입력해주세요.\n", SIZE - 1, SIZE - 1);
		return 1;
	}
	return 0;
}

int check_location(int a, int b) {
	if(a >= SIZE || a < 0 || b >= SIZE || b < 0)
		return 0;
	return 1;
}

void set_usr_board(int length) {
	int x, y;
	printf("\n길이 %d인 함선의 위치를 정하세요.\n>> ", length);
	scanf("%d %d", &y, &x);
	if(check_input(x,y)) {
		set_usr_board(length);
		return;
	}
	if(length == 1) {
		usr[x][y] = 1;
		return;
	}
	printf("\n가로 또는 세로를 정해주세요.\n>> ");
	char direction[10];
	while (1) {
		scanf("%s", direction);
		if(!strcmp(direction, "가로")) {
			if(length + y > SIZE) {
					printf("함선이 경기장을 이탈합니다. 다시 정해주세요.\n");
					set_usr_board(length);
					return;
			}
			for(int i = 0; i < length; i++) {
				if(usr[x][i + y] == 1) {
					printf("함선의 위치가 겹칩니다. 다시 정해주세요.\n");
					set_usr_board(length);
					return;
				}
			}
			for(int i = 0; i < length; i++) {
				usr[x][i + y] = 1;
			}
			break;
		} else if(!strcmp(direction, "세로")) {
			if(length + x > SIZE) {
					printf("함선이 경기장을 이탈합니다. 다시 정해주세요.\n");
					set_usr_board(length);
					return;
			}
			for(int i = 0; i < length; i++) {
				if(usr[i + x][y] == 1) {
					printf("함선의 위치가 겹칩니다. 다시 정해주세요.\n");
					set_usr_board(length);
					return;
				}
			}
			for(int i = 0; i < length; i++) {
				usr[i + x][y] = 1;
			}
			break;
		} else {
			printf("\n가로 또는 세로를 입력해주세요.\n>>");
		}
	}
	return;
}

void set_com_board(int length) {
	int x = rand() % SIZE;
	int y = rand() % SIZE;
	int direction = rand() % 2;
	if(length == 1) {
		com[x][y] = 1;
	} else {
		while (1) {
			if(direction) {
				if(length + y > SIZE) {
					set_com_board(length);
					return;
				}
				for(int i = 0; i < length; i++) {
					if(com[x][i + y] == 1) {
						set_com_board(length);
						return;
					}
				}
				for(int i = 0; i < length; i++) {
					com[x][i + y] = 1;
				}
				break;
			} else {
				if(length + x > SIZE) {
					set_com_board(length);
					return;
				}
				for(int i = 0; i < length; i++) {
					if(com[i + x][y] == 1) {
						set_com_board(length);
						return;
					}
				}
				for(int i = 0; i < length; i++) {
					com[i + x][y] = 1;
				}
				break;
			}
		}
	}
}

void print_board() {
	printf("\n사용자의 경기장 :\n");
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
			printf("%3d", usr[i][j]);
		printf("\n");
	}
	printf("\n컴퓨터의 경기장 :\n");
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
			printf("%3d", game[i][j]);
		printf("\n");
	}
}

int check_board() {
	int usr_cnt = 0, game_cnt = 6;
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++) {
			usr_cnt += usr[i][j] == 1 ? 1 : 0;
			game_cnt -= game[i][j] == 2 ? 1 : 0;
		}
	if(!usr_cnt || !game_cnt) {
		printf("\n컴퓨터의 경기장 :\n");
		for(int i = 0; i < SIZE; i++) {
			for(int j = 0; j < SIZE; j++)
				printf("%3d", com[i][j]);
			printf("\n");
		}
		printf("%s가 이겼습니다!", !usr_cnt ? "컴퓨터" : "사용자");
		return 1;
	}
	else
		return 0;
}

void init() {
	memset(com, 0, 25 * sizeof(int));
	memset(usr, 0, 25 * sizeof(int));
	memset(game, 0, 25 * sizeof(int));
	//함선 3개, 길이 : 1, 2, 3
	set_usr_board(1);
	set_usr_board(2);
	set_usr_board(3);
	set_com_board(1);
	set_com_board(2);
	set_com_board(3);
}

void usr_attack() {
	printf("\n공격할 위치를 입력하세요.\n>> ");
	int x, y;
	scanf("%d %d", &x, &y);
	if(check_input(x,y)) return;
	printf("\n사용자가 %d %d 위치로 공격을 가하였습니다.\n", x, y);
	if(com[y][x] == 1) {
		printf("공격이 맞았습니다!");
		com[y][x] = 2;
		game[y][x] = 2;
	} else if((check_location(y - 1, x - 1) && com[y - 1][x - 1] == 1) || (check_location(y, x - 1) && com[y][x - 1] == 1) || (check_location(y + 1, x - 1) && com[y + 1][x - 1] == 1) || (check_location(y - 1, x) && com[y - 1][x] == 1) || (check_location(y + 1, x) && com[y + 1][x] == 1) || (check_location(y - 1, x + 1) && com[y - 1][x + 1] == 1) || (check_location(y, x + 1) && com[y][x + 1] == 1) || (check_location(y - 1, x + 1) && com[y - 1][x + 1] == 1)) {
		printf("공격이 근접하였습니다!");
		// com[y][x] = 3;
		game[y][x] = 3;
	} else {
		printf("공격이 빛나갔습니다.");
	}
	printf("\n");
	return;
}

void com_attack() {
	int x = rand() % SIZE;
	int y = rand() % SIZE;
	printf("\n컴퓨터가 %d %d 위치로 공격을 가하였습니다.\n", x, y);
	if(usr[x][y] == 1) {
		printf("공격이 맞았습니다!");
		usr[x][y] = 2;
	} else {
		printf("공격이 빛나갔습니다.");
	}
	printf("\n");
	return;
}

int main() {
	srand(time(NULL));
	init();
	print_board();
	while(1) {
		usr_attack();
		com_attack();
		print_board();
		if(check_board())
			break;
	}
	return 0;
}

