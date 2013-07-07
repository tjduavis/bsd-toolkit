                  #include <stdio.h>
                  #include <string.h>

                  void abracadabra(char *str)
                  {
                      int i, j = 1;

                      for (i = 0; str[i]; i++)
                          if (str[i] == ' ')
                              j = 1;
                          else {
                              str[i] -= j;  /* intentional type mixing */
                              j++;
                          }
                  }

                  main()
                  {
                      char x[2][13];
                      int i;

                      strcpy(x[0], "Ujh uguq ju");
                      strcpy(x[1], "pxhv bv mcvx");
                      for (i = 0; i < 2; i++)
                          abracadabra(x[i]);
                      printf("%s %s <phew!>\n", x[0], x[1]);
                  }