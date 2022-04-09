#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
  if (argc == 2 )
  {
    
  int stlen = strlen(argv[1]); // Need this to construct the key loop.
  
  for (int x=0;x<stlen;x++) //..... A loop for checking the key's validety.
  {
    if ( (argv[1][x] > 'Z' && argv[1][x] < 'a') || argv[1][x] > 'z' || argv[1][x] < 'A') 
    return 1;
  }
     printf("plaintext: ");
     string otext = GetString();
     int otlen = strlen(otext);  // Need this to construct the cypher loop. 
     int kshift[otlen + 1]; // Need this for the keyshift loop, as long as the original text. 
     
     for(int x=0, y=0;x<otlen;x++) //.............................. KEY shift LOOP
     {
        if (argv[1][y] == 0) //..... if the key reaches a null char. reset y to zero. 
                    y = 0;
                    
        if ( (otext[x] > '@' && otext[x] < '[') || (otext[x] > '`' && otext[x] <'{') ) //... stores the keyshift only when the original text is a letter.
        {
                    
        if (argv[1][y] < 91) //...... stores keyshift for CAP characters. 
           kshift[x] = argv[1][y] - 65;

        else //...................... stores keyshift for non CAP characters.
           kshift[x] = argv[1][y] - 97;
           
           printf("%d ", kshift[x]);
           y++;
        }
        
     }
     
     printf("\nciphertext: ");
     for(int x=0, y=0;x<otlen;x++) //.............................. CYPHER LOOP
     {
           if ( (otext[x] > 64 && otext[x] < 91) || (otext[x] > 96 && otext[x] < 123) ) //.... if original text is a letter
              {
                if ( (( (otext[x] + kshift[y]) > 90) && ((otext[x] + kshift[y]) < 97)) || ( (otext[x] + kshift[y]) > 122) ) //... if the OUTCOME is not a letter reshift it back by 26. 
                   otext[x] = otext[x] - 26;
                   
                otext[x] = otext[x] + kshift[y];
                printf("%c", otext[x]);
                y++; 
              }
          else 
          printf("%c", otext[x]);
     }
     printf("\n");
  }
  else
  return 1; 
  
  return 0;
}