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

#define AGGRO_MIN 0 //어그로 범위
#define AGGRO_MAX 5





void print_intro(); //인트로 함수
void print_outtro(bool); //아웃트로 함수
int set_train_length(int, int); //기차길이 설정
int set_ma_stamina(int, int); //마동석 체력 결정
int set_probability(int, int); // 확률 설정
void print_board(); //보드판 출력



int main()
{
	print_intro();
	int train_length;
	
	train_length = set_train_length(LEN_MIN, LEN_MAX);
	printf("%d", train_length);
	while (1)
	{
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
void print_board() {

}