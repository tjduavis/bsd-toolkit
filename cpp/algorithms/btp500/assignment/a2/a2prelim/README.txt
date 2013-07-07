There are 2 programs in this preliminary  main.  
indexer and searcher.

indexer creates an index of the words found in 8 files.
It keeps track of how many times each word appears in 
each of the files.  Once that is complete, you can perform
searches with the searcher program.
                                                    
That program will allow you to search for that word.
If found it will print out how many times each word 
appeared in the files it was found in.  If not      
It will print out that it was not found             
                                                    
NOTE:  If you run the indexer more than twice, all  
       the counts will double so you need to remove 
       the old data file before running this again  

Put your source in this directory before you compile
I have a compilation script compile.bat which uses the 
bcc32 compiler.

There is a good chance that you don't have the file size
quota needed to test this on phobos.