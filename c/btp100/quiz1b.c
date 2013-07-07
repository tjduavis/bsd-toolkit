 #include <stdio.h>
 long long turn(long long string, int nDigits);
 int compute(long long string);

 #define STRN 53575645425047LL
 #define NDIG 100
 #define ZERO 48
 #define NINE 57
 #define ADD  43
 #define SUB  45
 #define MUL  42
 #define DIV  47
 #define MOD  37

 int main() {
	long long string = STRN, rString;
	int result;

	rString = turn(string, NDIG);
	printf("string  is %lld\nrString is %lld\n", string, rString);
	result = compute(rString);
	printf("Result  is %d\n", result);

	return 0;
 }

 long long turn(long long string, int nDigits) {
	long long result;
	int value;

	result = 0;
	while (string != 0) {
		value = string % nDigits;
		result = result * nDigits + value;
		string /= nDigits;
	}

	return result;
 }

 int compute(long long string) {
	int nops, value, opnd, pOpnd, ppOpnd;

	nops = 0;
	opnd = 0;
	pOpnd = 0;
	ppOpnd = 0;
	while (string != 0) {
		value = string % 100;
		if (value >= ZERO && value <= NINE) {
			ppOpnd = pOpnd;
			pOpnd = opnd;
			opnd = value - ZERO;
			nops++;
		} else {
			if (nops == 0)
				printf("No operands entered\n");
			else if (nops == 1) {
				switch(value) {
				case ADD:
					opnd = opnd;
					break;
				case SUB:
					opnd = - opnd;
					break;
				default:
					printf("Unknown operator\n");
				}
				nops--;
			} else {
				switch(value) {
				case MOD:
					opnd = pOpnd % opnd;
					break;
				case MUL:
					opnd = pOpnd * opnd;
					break;
				case ADD:
					opnd = pOpnd + opnd;
					break;
				case SUB:
					opnd = pOpnd - opnd;
					break;
				case DIV:
					opnd = pOpnd / opnd;
					break;
				default:
					printf("Cannot interpret %d\n", value);
				}
				pOpnd = ppOpnd;
				nops--;
			}
		}
		string /= 100;
	}

	return opnd;
 }
