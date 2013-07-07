	#include <stdio.h>
	#include <string.h>
	struct password {
	    char str[81];
	    int len;
	};
	void decode(struct password *pw, char *s)
	{
	    int i, j = 0;
	    for (i = 0; s[i]; i++) {
		s[i] = s[i] ^ pw->str[j];
		if (pw->len == ++j)
		    j = 0;
	    }
	}
	main()
	{
	    struct password x;
	    char data[11];

	    strcpy(data, "-#00A6&75C");
	    strcpy(x.str, "abcd");
	    x.len = 4;
	    decode(&x, data);
	    puts(data);
	}