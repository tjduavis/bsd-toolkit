        #include <stdio.h>
        #define SZ 12
        void lab(int);
        void foo(int [], int);
        void cut(int [], int, int);

        main()
        {
                int nums[SZ] = { -1, 10, 150, 16, 3, 100,
                                 45, 51, 5, 82, 27, 21 };

                foo(nums, SZ);
        }

        void foo(int n[], int cnt)
        {
                int i;

                lab(cnt);
                for (i = 10; i <= 30; i += 10)
                        cut(n, cnt, i);
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
                        putchar( i/10 ? '1' : ' ');
                putchar('\n');
                for (i = 1; i <= num; i++)
                        printf("%d", i % 10);
                putchar('\n');
        }