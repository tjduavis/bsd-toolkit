        /* this is the first line of the source file: q1.c */
        #include <stdio.h>
        void q1get(FILE *file, char *s, int count)
        {
            int i;
            for (i = 0; i < count; i++)
                s[i] = fgetc(file);
            s[i] = '\0';
        }
        main()
        {
            FILE *fp;
            char s1[10], s2[10], ch;
            int keepatit = 1;

            fp = fopen("q1.c", "r");
            while (keepatit) {
                if ('*' == (ch = fgetc(fp))) {
                    q1get(fp, s1, 5);
                    q1get(fp, s2, 3);
                    fclose(fp);
                    keepatit = 0;
                }
            }
            printf("Well,%s%s it?!?\n", s2, s1);
        }
        
