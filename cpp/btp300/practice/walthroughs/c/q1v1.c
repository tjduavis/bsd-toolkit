/* OOP344CE Winter 2003 Test #1 */
/* q1v1.c */
#include <stdio.h>

/*#define T*/
#define SZ 6
#define CH(a) (a) ^ 32

typedef enum { AIX, HPUX, OSX=5, IRIX, SOLARIS, LINUX } OS;
typedef struct {
	char *p;
	unsigned pos:4;
	OS type;
} mfr;

void init(mfr *, char[][10], int);
void proc(mfr *);

int main() {
	char data[SZ][10] = { "Macintosh", "IBMachine", "HewlettPa",
	                      "GPLicense", "SunMicros", "SiliconGX" };
	mfr list[SZ];
	OS x;
	int i, index, shift[9] = {3, 6, -16, 4, 5, 1, -3, -6};
	
	init(list, data, SZ);
	printf("%d",SZ);
	for (i=0, x=LINUX; x>AIX; x--, i++) {
		index = (x >= SZ) ? x-OSX : x;
		printf("%c", index == 4 ? CH(list[index].p[list[index].type] + shift[i]) :
		                          list[index].p[list[index].type] + shift[i]);
    }
    printf("%d",AIX);
    return 0;
}

void init(mfr *p_mfr, char s[][10], int n) {
	for(--n; n>=0; n--) {
		p_mfr->p	= s[n];
		p_mfr->pos	= n;
		p_mfr->type = n < 4 ? OSX + n : OSX - n;
		printf("init[%s:%d;%d]\n",p_mfr->p, p_mfr->pos, p_mfr->type);
		
		#ifdef T
			proc(p_mfr);
		#endif
		p_mfr++;
	}
}

void proc(mfr *p_mfr) {
	p_mfr->p[p_mfr->type] += p_mfr->pos;
	printf("proc[%s:%d:%d]\n",p_mfr->p, p_mfr->pos, p_mfr->type);
}