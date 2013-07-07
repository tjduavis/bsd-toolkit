                  #include <stdio.h>
                  main(int argc, char *argv[])
                  {
                      FILE *fp;
                      int ch, i, counts[26];

                      if (argc < 2)
                          printf("Usage: %s FILENAME\n", argv[0]);
                      else
                          if (NULL == (fp = fopen(argv[1], "r")))
                              printf("Cannot read %s\n", argv[1]);
                          else {
                              /**** loop one ****/
                              for (i = 0; i < 26; i++)
                                  counts[i] = 0;
                              /**** loop two ****/
                              while (EOF != (ch = fgetc(fp))) {
                                  if ('a' <= ch && ch <= 'z')
                                      counts[ch - 'a']++;
                                  else if ('A' <= ch && ch <= 'Z')
                                      counts[ch - 'A']++;
                              }
                              /**** loop three ****/
                              for (i = 0; i < 26; i++) 
                                  if (counts[i])
                                      printf("%c appears %d times\n",
                                        'A'+i, counts[i]);


                              fclose(fp);
                  }