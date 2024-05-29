//1-1 ??여기다가 뭘 써야 하는지 모르겠다???
//1-2
//1-3
//1-4
//1-5


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
	bool turn;
} Zombie;


void print_intro(); //인트로 함수
void print_outtro(bool); //아웃트로 함수
int set_train_length(int, int); //기차길이 설정
int set_ma_stamina(int, int); //마동석 체력 결정
int set_probability(int, int); // 확률 설정
void print_board(int, Madongseok *, Citizen*, Zombie*); //보드판 출력
void set_position(int, Madongseok*, Citizen*, Zombie*); //초기위치 설정
void move_phase(int,int,  Madongseok*, Citizen*, Zombie*); //이동페이즈
void action_phase(Madongseok*, Citizen*, Zombie*);//행동페이즈
int check_aggro(int, int, int);//어그로 관리 함수
void set_aggro(Madongseok*, Citizen*);//어그로 초기설정
int train_length;
int propability;

int main()
{
	srand((unsigned)time(NULL));
	//print_intro();
	//마동석 시민 좀비 생성
	Madongseok ma{};
	Citizen cit{};
	Zombie zom{};
	//입력받기
	train_length = set_train_length(LEN_MIN, LEN_MAX);
	ma.stamina = set_ma_stamina(STM_MIN, STM_MAX);
	propability = set_probability(PROB_MIN, PROB_MAX);
	//초기세팅 및 초기 기차상태 출력
	set_aggro(&ma, &cit);
	set_position(train_length, &ma, &cit, &zom);
	print_board(train_length, &ma, &cit, &zom);
	printf("==============Let's Go Game!!=============\n\n");
	while (1)
	{
		int random = rand() % 100 + 1; // 1 ~ 100
		move_phase(random,propability, &ma, &cit, &zom); //이동페이즈 구현
		//행동페이즈 구현해야댐
		action_phase(&ma, &cit, &zom); //행동 페이즈 구현
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
int check_aggro(int aggro, int min, int max) {
	if (aggro > max) {
		
		return max;
	}
	else if (aggro < min) {

		return min;
	}
	else {
		return aggro;
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
	zom->turn = 1;
	
};
void move_phase(int random, int pro, Madongseok* ma, Citizen* cit, Zombie* zom) {
	//시민이동
	printf("===========Start Move Phase===========\n\n");
	int cit_x = cit->x;
	int zom_x = zom->x;
	int cit_aggro = cit->aggro;
	int ma_aggro = ma->aggro;
	if (random > pro) {
		cit->x--;
		cit->aggro++;
		cit->aggro = check_aggro(cit->aggro, AGGRO_MIN, AGGRO_MAX);
	}
	else {
		cit->aggro--;
		cit->aggro = check_aggro(cit->aggro, AGGRO_MIN, AGGRO_MAX);
	}
	//좀비 turn에 따라서 이동하고 말고 결정해야함
	if (zom->turn) {
		if (cit->aggro >= ma->aggro) {
			zom->x--;
			if (zom->x == cit->x) {
				zom->x++;
			}
		}
		else {
			zom->x++;
			if (zom->x == ma->x) {
				zom->x--;
			}
		}
		
	}
	print_board(train_length, ma, cit, zom);
	printf("citizen: %d -> %d (aggro: %d -> %d)\n", cit_x, cit->x, cit_aggro ,cit->aggro);
	if (zom->turn) {
		printf("zombie: %d -> %d\n\n", zom_x, zom->x);
	}
	else {
		printf("zombie: %d -> %d (don't move turn)\n\n", zom_x, zom->x);
	}
	zom->turn = !(zom->turn);

	while (1){
		int ma_move;
		if (ma->x - 1 == zom->x) {
			printf("madongseok move(0:stay)>> ");
			scanf_s("%d", &ma_move);
			if (ma_move != 0) {
				continue;
			}
		}
		else {
			printf("madongseok move(0:stay, 1:left)>> ");
			scanf_s("%d", &ma_move);
		}
		if (ma_move == 1) {
			ma->x--;
			ma->aggro++;
			ma->aggro = check_aggro(ma->aggro, AGGRO_MIN, AGGRO_MAX);
			print_board(train_length, ma, cit, zom);
			printf("madongseok: move %d(aggro: %d -> %d, stamina: %d)\n\n", ma->x, ma_aggro, ma->aggro, ma->stamina);
			break;
		}
		else if (ma_move == 0) {
			print_board(train_length, ma, cit, zom);
			ma->aggro--;
			ma->aggro = check_aggro(ma->aggro, AGGRO_MIN, AGGRO_MAX);
			printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n\n", ma->x, ma_aggro,ma->aggro, ma->stamina);
			break;
		}
		else {
			continue;
		}
	}


	printf("===========End Move Phase===========\n\n");
}
void set_aggro(Madongseok *ma, Citizen *cit) {
	ma->aggro = 1;
	cit->aggro = 1;
}
void action_phase(Madongseok *ma, Citizen* cit, Zombie* zom) {

	printf("==============ACTION PHASE START!!=============\n\n");
	if (cit->x == 0) {
		printf("YOU WIN!...");
		exit(-1);
	}
	printf("citizen does nothing.\n");
	if (zom->x-1 == cit->x && zom->x + 1 == ma->x) {
		if (cit->aggro >= ma->aggro) {
			//둘다 인접하고 어그로도 같을경우도 생각해서 함
			printf("GAME OVER! citizen dead...\n");
			exit(-1);
		}
		else {
			printf("zombie attacked madongseok (aggro: %d vs %d,  madongseok stamina: %d -> %d\n)", cit->aggro, ma->aggro, ma->stamina, ma->stamina - 1);
			ma->stamina--;
			if (ma->stamina <= STM_MIN) {
				printf("GAME OVER! madongseok dead...\n");
				exit(-1);
			}
		}
	} //둘이 위치 같을경우부터
	else if (zom->x - 1 == cit->x) {
		printf("GAME OVER! citizen dead...");
		exit(-1);
	}
	else if (zom->x + 1 == ma->x) {
		ma->stamina--;
		if (ma->stamina <= STM_MIN) {
			printf("GAME OVER! madongseok dead...");
			exit(-1);
		}
		else {
			printf("zombie attacked madongseok, madongseok stamina: %d -> %d\n", ma->stamina + 1, ma->stamina);
		}
	}
	else {
		printf("zombie attacked nobody.\n");
	}

	if (ma->x - 1 > zom->x) {
		while (1) {
			printf("madongseok action(0: rest, 1: provoke)>> "); int action = scanf_s("%d", &action);
			if (action == 0) {
				int ma_aggro = ma->aggro;
				int ma_stamina = ma->stamina;
				ma->aggro--;
				ma->aggro = check_aggro(ma->aggro, AGGRO_MIN, AGGRO_MAX);
				ma->stamina++;
				ma->stamina = check_aggro(ma->stamina, STM_MIN, STM_MAX);
				printf("madongseok rests...\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", ma->x, ma_aggro, ma->aggro, ma_stamina, ma->stamina);

				break;
			}
			if (action == 1) {
				int ma_aggro = ma->aggro;
				ma->aggro = AGGRO_MAX;
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n", ma->x, ma_aggro, ma->aggro, ma->stamina);
				break;
			}
			else {
				printf("다시 입력해주세요.\n");
			}
		}
	}
	else {
		while (1) {
			printf("madongseok action(0: rest, 1: provoke, 2: pull)>> "); 
			int action;
			scanf_s("%d", &action);
			printf("%d\n", action);
			if (action == 0) {
				int ma_aggro = ma->aggro;
				int ma_stamina = ma->stamina;
				ma->aggro--;
				ma->aggro = check_aggro(ma->aggro, AGGRO_MIN, AGGRO_MAX);
				ma->stamina++;
				ma->stamina = check_aggro(ma->stamina, STM_MIN, STM_MAX);
				printf("madongseok rests...\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", ma->x, ma_aggro, ma->aggro, ma_stamina, ma->stamina);

				break;

			}
			else if (action == 1) {
				int ma_aggro = ma->aggro;
				ma->aggro = AGGRO_MAX;
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n", ma->x, ma_aggro, ma->aggro, ma->stamina);
				break;
			}
			else if(action == 2) {
				int ma_aggro = ma->aggro;
				int ma_stamina = ma->stamina;
				ma->aggro = ma->aggro + 2;
				ma->aggro = check_aggro(ma->aggro, AGGRO_MIN, AGGRO_MAX);
				ma->stamina--;
				ma->stamina = check_aggro(ma->stamina, STM_MIN, STM_MAX);
				int random = rand() % 100 + 1; // 1 ~ 100
				if (random > propability) {
					//성공시
					zom->turn = 0;
					printf("madongseok pulled zombie... Next turn, it can't move\n");
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", ma->x, ma_aggro, ma->aggro, ma_stamina, ma->stamina);

				}
				else {
					printf("madongseok failed to pull zombie");
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", ma->x, ma_aggro, ma->aggro, ma_stamina, ma->stamina);

				}
				break;
			}
			else {
				printf("다시 입력해주세요.\n");
			}
		}
		
	}
	printf("==============ACTION PHASE END!!=============\n\n");
}