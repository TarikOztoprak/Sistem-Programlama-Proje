#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
typedef struct{
char* sozcuk;
char* sayi;
} Kelime;

JRB t;
JRB tmp;
Kelime *kelime;
int nsize;
int i;


void Decode(char *dosya, char *cikti)
{
   IS is;
   const char *delp;
   const char *delp2;
   is =  new_inputstruct("./.kilit");
   if (is == NULL){
     perror("hata");
     exit(1);
   }
   
   t=make_jrb();
   
   while(get_line(is)>0){
   delp = strtok(is -> fields[0] ,"\" : { } ; ,");
   delp2 = strtok(is -> fields[1], "\" : { } ; ,");
   if(is->NF > 1){
    kelime = malloc(sizeof(Kelime));
    //kelime->sayi = atoi(delp2);
    nsize = strlen(delp2);
   
    for(i = 1; i<is->NF-1; i++){ nsize += (strlen(is->fields[i])); }
   
    kelime->sayi = (char*) malloc(sizeof(char)*(nsize+1));
    strcpy(kelime->sayi, delp2);
   
    jrb_insert_str(t, kelime->sayi, new_jval_v((void *) kelime));
   
    nsize = strlen(delp);
   
    for(i = 0; i<is->NF; i++){ nsize += (strlen(is->fields[i])+1); }
   
    kelime->sozcuk = (char*) malloc(sizeof(char)*(nsize+1));
    strcpy(kelime->sozcuk, delp);
   
    jrb_insert_str(t, kelime->sayi, new_jval_v((void*) kelime));
   }
 
   }

   IS is2;
   int kontrol = 0;
   is2= new_inputstruct(dosya);
   FILE *cikti_dosyasi = fopen(cikti, "w");
   while(get_line(is2)>=0){
     for(int i= 0;i< is2->NF; i++){
         jrb_traverse(tmp,t){

kelime = (Kelime *) tmp->val.v;
 if(strcmp(kelime->sayi, is2->fields[i])==0){//atoi gerek yok silindi
   fprintf(cikti_dosyasi, "%s " , kelime->sozcuk);
 
  kontrol = 0;
  break;
 }
 else
   {
     kontrol = 1;
   }
}
if(kontrol == 1){
  fprintf(cikti_dosyasi, "%s " , is2->fields[i]);
}

     }
   
   }
 
     fclose(cikti_dosyasi);
}

void Encode(char *dosya, char *cikti)
{
   IS is;
   const char *delp;
   const char *delp2;
   is =  new_inputstruct("./.kilit");
   if (is == NULL){
     perror("hata");
     exit(1);
   }
   
   t=make_jrb();
   
   while(get_line(is)>0){
   delp = strtok(is -> fields[0] ,"\" : { } ; ,");
   delp2 = strtok(is -> fields[1], "\" : { } ; ,");
   if(is->NF > 1){
    kelime = malloc(sizeof(Kelime));
    //kelime->sayi = atoi(delp2);
    nsize = strlen(delp2);
   
    for(i = 1; i<is->NF-1; i++){ nsize += (strlen(is->fields[i])); }
   
    kelime->sayi = (char*) malloc(sizeof(char)*(nsize+1));
    strcpy(kelime->sayi, delp2);
   
    jrb_insert_str(t, kelime->sayi, new_jval_v((void *) kelime));
    nsize = strlen(delp);
   
    for(i = 0; i<is->NF; i++){ nsize += (strlen(is->fields[i])+1); }
   
    kelime->sozcuk = (char*) malloc(sizeof(char)*(nsize+1));
    strcpy(kelime->sozcuk, delp);
   
    jrb_insert_str(t, kelime->sozcuk, new_jval_v((void *) kelime));
   }
 
   }

   IS is2;
   int kontrol = 0;
   is2= new_inputstruct(dosya);
   FILE *cikti_dosyasi = fopen(cikti, "w");
   while(get_line(is2)>=0){
     for(int i= 0;i< is2->NF; i++){
         jrb_traverse(tmp,t){

kelime = (Kelime *) tmp->val.v;
 if(strcmp(kelime->sozcuk,is2->fields[i])==0){
   fprintf(cikti_dosyasi, "%s " , kelime->sayi);//%d degil %s
 
  kontrol = 0;
  break;
 }
 else
   {
     kontrol = 1;
   }
}
if(kontrol == 1){
  fprintf(cikti_dosyasi, "%s " , is2->fields[i]);//%d degil %s
}

     }
   
   }
 
     fclose(cikti_dosyasi);
}

int main(int argc, char **argv)
{
  IS is;
 
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

   if(strcmp(argv[1], "-d") == 0)
     {
       Decode(argv[2],argv[3]);
     }
   else if(strcmp(argv[1],"-e") == 0)
     {
       Encode(argv[2],argv[3]);
     }
   else
     {
       perror("Hatalı Giriş!");
       exit(1);
     }

  return 0;
}
