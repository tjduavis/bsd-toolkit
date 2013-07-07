        #include <stdio.h>

        void decode(char *s)
        {
            while (*s) {
                *s = '@' | (*s >> 1);
                s++;
            }
        }

        main()
        {
            char s1[3] = "f^", s2[5] = "KBfs";

            decode(s1);
            decode(s2);
            printf("It is %s %s!\n", s1, s2);
        }