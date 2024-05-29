#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//기차 길이, 확률
#define LEN_MIN		15
#define LEN_MAX		50
#define PROB_MIN	10
#define PROB_MAX	90
//마동석
#define STM_MIN 0 //체력
#define STM_MAX 5 
#define MOVE_LEFT 1 //이동방향
#define MOVE_STAY 0
#define ACTION_REST 0 //행동
#define ACTION_PROVOKE 1 
#define ACTION_PULL 2
//좀비
#define ATK_NONE 0 
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
//어그로 범위
#define AGGRO_MIN 0 
#define AGGRO_MAX 5

//마동석 시민 좀비 구조체 생성
typedef struct {
	int x;
	int stamina;
	int aggro;
} Madongseok;
typedef struct {
	int x;
	int aggro;
} Citizen;

typedef struct {
	int x;
	bool turn = false;
} Zombie;


void print_intro(); //인트로 함수
void print_outtro(bool); //아웃트로 함수
int set_train_length(int, int); //기차길이 설정
int set_ma_stamina(int, int); //마동석 체력 결정
int set_probability(int, int); // 확률 설정
void print_board(int, Madongseok *, Citizen*, Zombie*); //보드판 출력
void set_position(int, Madongseok*, Citizen*, Zombie*); //초기위치 설정
void move_phase(int,int,  Madongseok*, Citizen*, Zombie*); //이동페이즈
void action_phase();//행동페이즈




int main()
{
	srand((unsigned)time(NULL));
	print_intro();
	//마동석 시민 좀비 생성
	Madongseok ma{};
	Citizen cit{};
	Zombie zom{};
	//입력받기
	int train_length = set_train_length(LEN_MIN, LEN_MAX);
	ma.stamina = set_ma_stamina(STM_MIN, STM_MAX);
	int propability = set_probability(PROB_MIN, PROB_MAX);
	//초기세팅 및 초기 기차상태 출력
	set_position(train_length, &ma, &cit, &zom);
	print_board(train_length, &ma, &cit, &zom);

	while (1)
	{
		int random = rand() % 100 + 1; // 1 ~ 100
		move_phase(random,propability, &ma, &cit, &zom); //이동페이즈 구현
		break;

	}
	return 0;
}





void print_intro() {

	printf("______                              _                          \n");
	printf("| ___ \\                            | |                         \n");
	Sleep(1000);
	printf("| |_/ / _   _  ___   __ _  _ __    | |__    __ _  _ __    __ _ \n");
	printf("| ___ \\| | | |/ __| / _` || '_ \\   | '_ \\  / _` || '_ \\  / _` |\n");
	Sleep(1000);
	printf("| |_/ /| |_| |\\__ \\| (_| || | | |  | | | || (_| || | | || (_| |\n");
	printf("\\____/  \\__,_||___/ \\__,_||_| |_|  |_| |_| \\__,_||_| |_| \\__, |\n");
	Sleep(1000);
	printf("                                                          __/ |\n");
	printf("                                                         |___/ \n");

}
void print_outtro(bool b) {
	if (b) {
		printf(" _____                                    \n");
		printf("/  ___|                                   \n");
		Sleep(1000);
		printf("\\ `--.  _   _   ___   ___   ___  ___  ___ \n");
		printf(" `--. \\| | | | / __| / __| / _ \\/ __|/ __|\n");
		Sleep(1000);
		printf("/\\__/ /| |_| || (__ | (__ |  __/\\__ \\__ \\ \n");
		printf("\\____/  \\__,_| \\___| \\___| \\___||___/|___/\n");
	}
	else {
		printf("______         _  _ \n");
		printf("|  ___|       (_)| |\n");
		Sleep(1000);
		printf("| |_     __ _  _ | |\n");
		printf("|  _|   / _` || || |\n");
		Sleep(1000);
		printf("| |    | (_| || || |\n");
		printf("\\_|     \\__,_||_||_|\n");
	}

}
int set_train_length(int min, int max) {

	while (1) {
		int input;
		printf("train length(%d~%d)>> ", min, max);
		scanf_s("%d", &input);
		if (input >= min && input <= max) {
			return input;
		}
	}
	
}
int set_ma_stamina(int min, int max) {
	while (1) {
		int input;
		printf("madongseok stamina(%d~%d)>> ", min, max);
		scanf_s("%d", &input);
		if (input >= min && input <= max) {
			return input;
		}
	}
}
int set_probability(int min , int max) {
	while (1) {
		int input;
		printf("percentile probability p(%d~%d)>> ", min, max);
		scanf_s("%d", &input);
		if (input >= min && input <= max) {
			return input;
		}
	}
}
void print_board(int length, Madongseok *ma, Citizen *cit , Zombie *zom) {

	for (int i = 1; i < length + 1; i++) {
		printf("#");
	}
	printf("\n");
	printf("#");
	for (int i = 0; i < length - 2; i++) {
		if (i == cit->x) {
			printf("C");
		}
		else if (i == zom->x) {
			printf("Z");
		}
		else if (i == ma->x) {
			printf("M");
		}
		else {
			printf(" ");
		}
	}
	printf("#");
	printf("\n");
	for (int i = 0; i < length; i++) {
		printf("#");
	}
	printf("\n");

}
void set_position(int length, Madongseok *ma, Citizen *cit, Zombie *zom) {
	ma->x = length - 3;
	cit->x = length - 7;
	zom->x = length - 4;
};
void move_phase(int random, int pro, Madongseok* ma, Citizen* cit, Zombie* zom) {
	//시민이동
	int cit_x = cit->x;
	int zom_x = zom->x;
	if (random > pro) {
		cit->x--;
	}
	if (zom->turn) {
		//좀비 turn에 따라서 이동하고 말고 결정해야함
		zom->x--;
	}
	zom->turn = !(zom->turn);
	printf("citizen: %d -> %d (aggro: %d)\n", cit_x, cit->x, cit->aggro);
	printf("zombie: %d -> %d\n", zom_x, zom->x);

	while (1){
		int ma_move;
		printf("madongseok move(0:stay, 1:left)>> ");
		scanf_s("%d", &ma_move);
		if (ma_move == 1) {
			ma->x--;
			printf("madongseok: move %d(aggro: %d, stamina: %d)", ma->x, ma->aggro, ma->stamina);
			break;
		}
		else if (ma_move == 0) {
			printf("madongseok: move %d(aggro: %d, stamina: %d)", ma->x, ma->aggro, ma->stamina);
			break;
		}
		else {
			continue;
		}
	}
	
	

	
}