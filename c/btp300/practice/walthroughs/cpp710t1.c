        #include <stdio.h>
        #define SZ 12

        void lab(int);
        void foo(int [], int);
        void cut(int [], int, int);

        main()
        {
                int nums[SZ] = { 100, 10, 25, 16, 30, 1,
                                 45, 5, 52, 28, 17, 41 };

                foo(nums, SZ);
        }

        void foo(int n[], int cnt)
        {
                int i;

                for (i = 30; i > 0; i -= 10)
                        cut(n, cnt, i);
                lab(cnt);
        }
                
        void cut(int n[], int sz, int lim)
        {
                int i;

                for (i = 0; i < sz; i++)
                        putchar(n[i] < lim ? ' ' : '*');
                putchar('\n');
        }

        void lab(int num)
        {
                int i;
                for (i = 1; i <= num; i++)
                        putchar(i/10 ? '1' : ' ');
                putchar('\n');
                for (i = 1; i <= num; i++)
                        printf("%d", i % 10);
                putchar('\n');
        }