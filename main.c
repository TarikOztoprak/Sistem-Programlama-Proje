#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "jrb.c"
#include "jval.c"
#include "fields.c"

void kilitOKu()
{
   IS is;
   JRB b;
   JRB bn;

   b = make_jrb();
   
   const char *delp;
   const char *delp2;
   is =  new_inputstruct("./.kilit"); 
   if (is == NULL){ 
     perror("hata"); 
     exit(1);
   }
     
   while(get_line(is)>0){   
     delp = strtok(is -> fields[0] ,"\" : { } ; ,");
     delp2 = strtok(is -> fields[1], "\" : { } ; ,");
     while(delp != NULL){
       jrb_insert_str(b,strdup(delp), new_jval_v(NULL));
       delp = strtok(NULL , "\" : { } ; ,");
       delp2 = strtok(NULL, "\" : { } ; ,");
     }
   }

   jrb_rtraverse(bn, b){
     printf("%s", bn ->key.s);
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
