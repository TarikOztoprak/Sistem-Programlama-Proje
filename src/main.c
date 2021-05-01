#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include "jrb.h"
#include "fields.h"
#include "main.h"

void kilitOKu()
{
   IS is;
   is =  new_inputstruct("./.kilit"); 
   if (is == NULL){ 
     perror("hata"); 
     exit(1);
   }
   get_line(is);
   while(get_line(is) > 0)
     {
       printf("%s \n" ,is -> fields[0]);
       printf("%s \n" , is-> fields[1]);
     }
   
}

int main(int argc, char **argv)
{
  IS is;
  IS is2;
  
  if( argc != 4)
    {
      fprintf(stderr, "HATALI GİRİŞ!");
      exit(1);
    }
  
   is = new_inputstruct(argv[2]); 
   if (is == NULL){ 
     perror(argv[2]); 
     exit(1);
   }

   is2 = new_inputstruct(argv[3]);
   if(is2 == NULL){ 
     perror(argv[3]); 
     exit(1);
   }

   if(strcmp(argv[1], "-d") == 0)
     {
       kilitOKu();
     }
   else if(strcmp(argv[1],"-e") == 0)
     {
       kilitOKu();
     }
   else
     {
       perror("Hatalı Giriş!");
       exit(1);
     }
  
  return 0;
}


