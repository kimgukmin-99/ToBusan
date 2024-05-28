


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define LEN_MIN		15
#define LEN_MAX		50
#define PROB_MIN	10
#define PROB_MAX	90

void print_Board(int, int, int, int);
void print_intro();
void print_outtro(bool);

int main()
{
	print_intro();
	int train_length;
	int probability;
	srand((unsigned)time(NULL));
	printf("tranin length(15 ~ 50) : ");  scanf_s("%d", &train_length);
	printf("percentile probability 'p' (10 ~ 90) : ");  scanf_s("%d", &probability);
	int random;
	int c = train_length - 7;
	int z = train_length - 4;
	int m = train_length - 3;
	bool a = true;
	bool b;
	if (train_length < LEN_MIN or train_length > LEN_MAX) {
		printf("잘못된 입력 입니다.");
		exit(-1);
	}
	if (probability < PROB_MIN or probability > PROB_MAX) {
		printf("잘못된 입력 입니다.");
		exit(-1);
	}
	print_Board(train_length, c, z, m);
	printf("\n");
	printf("\n");

	while (1)
	{

		random = rand() % 100 + 1; // 1 ~ 100
		printf("%d%%\n", random);
		if (random > probability) {
			int _c = c;
			c--;
			print_Board(train_length, c, z, m);
			printf("citizen: %d -> %d\n", _c + 1, c + 1);
			if (!a) {
				printf("zombie: stay %d (cannot move)\n", z + 1);
			}
			else {
				printf("zombie: stay %d\n", z + 1);
			}
			Sleep(4000);

			if (c == 0) {
				printf("SUCCESS!\n");
				printf("citizen(s) escaped to the next train\n");
				b = true;
				break;
			}
		}
		else {
			if (a) {
				int _z = z;
				z--;
				print_Board(train_length, c, z, m);
				printf("citizen: stay %d\n", c + 1);
				printf("zombie: %d -> %d\n", _z + 1, z + 1);
				Sleep(4000);

				if (z == c + 1) {
					printf("GAME OVER!\n");
					printf("Citizen(s) has(have) been attacked by a zombie\n");
					b = false;
					break;
				}
			}
			else {
				print_Board(train_length, c, z, m);
				printf("citizen: stay %d\n", c + 1);
				printf("zombie: stay %d (cannot move)\n", z + 1);
				Sleep(4000);

			}
		}

		a = !a;
		printf("\n");
	}
	print_outtro(b);
	return 0;
}




void print_Board(int train_length, int c, int z, int m) {
	for (int i = 1; i < train_length + 1; i++) {
		printf("#");
	}
	printf("\n");
	printf("#");
	for (int i = 0; i < train_length - 2; i++) {
		if (i == c) {
			printf("C");
		}
		else if (i == z) {
			printf("Z");
		}
		else if (i == m) {
			printf("M");
		}
		else {
			printf(" ");
		}
	}
	printf("#");
	printf("\n");
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");


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