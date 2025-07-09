#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include "decor.h"
#define BUFFER_SIZE 10240
#define MAX_LINES_STDIN 100000
char buffer[BUFFER_SIZE];
struct stat stat1 ,stat2;


//fetches the line character-by-character and stores it in a buffer of size 
void reverse_file(FILE* fptr,bool valid_out , FILE *fout){

    fseek(fptr,0,SEEK_END);
    long lr = ftell(fptr);
    if(!lr){
        fprintf(stderr,"%s%sFile is Empty\n%s",FG_RED,ITALIC,RESET);
        exit(2);
    }
    lr--;
     bool last_line = false;
    int idx=0;
    while(lr>0){
        lr--;
        if(lr ==0){
            last_line = true;
        }
        fseek(fptr,lr,SEEK_SET);
        char letter = fgetc(fptr);
        if(letter == '\n' ){
            for(--idx;idx>=0;idx--)
            {
                valid_out?fprintf(fout,"%c",buffer[idx]):(printf("%c",buffer[idx]));}
            valid_out?fprintf(fout,"\n") :printf("\n");
            idx =0;
        }
        else{
            buffer[idx++] = letter;
        } 
        if(idx >=BUFFER_SIZE-1){
            fprintf(stderr," %sBUFFER_FAULT : buffer overflow%s\n",FG_RED,RESET);
            exit(1);
        } 
    }
    if(last_line)
    {
        for(--idx;idx>=0;idx--)
    {
        valid_out?fprintf(fout,"%c",buffer[idx]):(printf("%c",buffer[idx]));
    }
    valid_out?fprintf(fout,"\n"):printf("\n");
}
}

int main (int argc, char *argv[]){
    if(argc ==1){
        char *lines[MAX_LINES_STDIN];
        int count=0;   
        while(fgets(buffer,sizeof(buffer),stdin) != NULL){
            if(count<MAX_LINES_STDIN){
            lines[count] =strdup(buffer);
            count++;}
            else{
                fprintf(stderr,"%s%sError : standard input is very long__(MAX_line_limit_reached)%s \n",ITALIC,FG_RED,RESET);
                exit(1);
            }
        } 
        for(--count;count>=0;count--){
            printf("%s",lines[count]);
        }    
    }

    if(argc>=2 && argc<4){
      
        FILE *fptr =fopen(argv[1],"r");
        if(fptr ==NULL){
            fprintf(stderr,"%s%sreverse: cannot open file %s'%s'%s\n",ITALIC,FG_RED,UNDERLINE,argv[1],RESET);
            exit(1); 
        }
        
       
        if (argc == 3){
            FILE *fout = fopen(argv[2],"w");
            if(fout == NULL){
                exit(1);
            }
           
            if(stat(argv[1],&stat1 ) ==0 && stat(argv[2],&stat2) ==0){
                if(stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev ){
                    fprintf(stderr,"%s%sreverse: input and output file must differ%s\n",ITALIC,FG_RED,RESET);
                        exit(1);
                }
            }
              
         reverse_file(fptr,true,fout);
        }
        else if(argc == 2)
        {reverse_file(fptr,false,NULL);}
    }
    else if(argc>3){
        fprintf(stderr,"%s%susage: reverse <input> <output>%s\n",ITALIC,FG_RED,RESET);
        exit(1);
    }
 return 0;
}