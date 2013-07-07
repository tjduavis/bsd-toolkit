#include <stdio.h>
#include <stdlib.h>
#define MAX 52
void most();
int getcard(int check[]);
int getvalue(int num, int *ace);

main() {
	int x;
	char answer;

	printf("\nBTP100 Black Jack\n=================\n");
	srand(time(NULL));
	do {
		most();
		do {
			printf("Another game ? ");
			scanf("%c", &answer);
			if ( answer == 'Y' || answer == 'y' ) {
				x = 1;
			} else if ( answer == 'N' || answer == 'n' ) {
				x = 0;
			} else {
				x = -1;
				printf("* Invalid selection *\n");
			}
			while ( getchar() != '\n' ) {
				;
			}
		} while ( x == -1 );
	} while ( x == 1 );
	printf("Have a nice day!");
}

void most() {
	char cards[MAX][3] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A",
			      "2","3","4","5","6","7","8","9","10","J","Q","K","A",
			      "2","3","4","5","6","7","8","9","10","J","Q","K","A",
			      "2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	int check[MAX] = {0}, dtotal, ptotal, pace, dace, value, card1, card2, card3, card4, x;
	char dealercard, answer;

	card1 = getcard(check);
	card2 = getcard(check);
	card3 = getcard(check);
	card4 = getcard(check);

	printf("Dealer : ??\n");
	printf("Dealer : %s\n", cards[card4-1]);
	printf("You drew : %s\n", cards[card1-1]);
	printf("You drew : %s\n", cards[card3-1]);
	ptotal = getvalue(card1, &pace) + getvalue(card3, &pace);
	dtotal = getvalue(card2, &dace) + getvalue(card4, &dace);

	do {
		do {
			printf("Draw ? ");
			scanf("%c", &answer);
			if ( answer == 'Y' || answer == 'y' ) {
				x = 1;
			} else if ( answer == 'N' || answer == 'n' ) {
				x = 0;
			} else {
				x = -1;
				printf("* Invalid selection *\n");
			}
			while ( getchar() != '\n' ) {
				;
			}
		} while ( x == -1 );
		if ( x == 1 ) {
			value = getcard(check);
			printf("You drew : %s\n", cards[value-1]);
			ptotal += getvalue(value, &pace);
			if ( ptotal > 21 ) {
				if ( pace > 0 ) {
					ptotal -= 10;
					pace = pace - 1;
				}
			}
		}
	} while ( x == 1 && ptotal <= 21 );

	if ( ptotal > 21 ) {
		printf("You bust %d\n", ptotal);
	} else {
		printf("You hold %d\n", ptotal);
	}

	printf("Dealer : %s\n", cards[card2-1]);
	printf("Dealer : %s\n", cards[card4-1]);

	while ( ptotal > dtotal && dtotal <= 21 && ptotal <= 21) {
		value = getcard(check);
		printf("Dealer : %s\n", cards[value-1]);
		dtotal += getvalue(value, &dace);
		if ( dtotal > 21 ) {
			if ( dace > 0 ) {
				dtotal -= 10;
				dace = dace - 1;
			}
		}
	}

	if ( ptotal == dtotal ) {
		printf("It is a tie!\n");
	} else if ( dtotal > 21) {
		printf("Dealer lost, you win!\n");
	} else if ( dtotal > ptotal ) {
		printf("You lose, dealer wins!\n");
	}
}

int getcard(int check[]) {
	int num, x = 0;

	do {
		num = 1 + rand() % (MAX);
		if ( check[num - 1] == 0 ) {
			x = 1;
		}
	} while ( x = 0 );
	check[num] = 1;
	return num;
}

int getvalue(int num, int *ace) {
	int temp;

	num = num % 13;
	if ( num > 0 && num <= 8 ) {
		temp = num + 1;
	} else if ( num > 8 && num <= 12 ) {
		temp = 10;
	} else if ( num = 0 ) {
		*ace = *ace + 1;
		temp = 11;
	}
	return temp;
}
