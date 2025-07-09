// this program is not optimal and consumes more memory(hundred of MBs) in very very large input files.
// And also not support standard input (through command line or piping)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct rline
{
    char  *line;
    struct rline *prev;
}rline;

void reverse (FILE* fptr,bool out_file,FILE *fout){

    char buffer[300];
    rline *head = NULL;
    while((fgets(buffer,sizeof(buffer),fptr)) != NULL){
      printf("fetched..\n");
       rline *entry = (rline*) malloc(sizeof(rline));
        if(!entry){
            fprintf(stderr,"malloc failed\n");
            exit(1);
        }
       entry->line = strdup(buffer);
       entry->prev = head;
       head = entry;
       rline *reverseline = head;  
    }
       rline *point = head;
       while(point!=NULL){
        out_file ? fprintf(fout,"%s",point->line) : printf("%s",point->line);    
        rline *temp = point;
        point = point->prev;
        free(temp->line);
        free(temp);
       }
}

int main(int argc , char *argv[]){
    if(argc==1){
      printf("Error : no input file\n");
        exit(1);
    }
    if(argc>3){
        fprintf(stderr,"usage: reverse <input> <output>\n");
        exit(1);
    }
    if(argc>=2)
    {
        if(argc ==3 && strcmp(argv[1],argv[2]) ==0){
                fprintf(stderr,"Input and output file must differ\n");
                exit(1);
        }
            FILE *fptr = fopen(argv[1],"r");
            if(fptr == NULL){
                fprintf(stderr,"error: cannot open file 'input.txt'\n");
                exit(1);
            }
        if(argc ==3)
        { 
            FILE* fout = fopen(argv[2],"w");
            if(fout == NULL){
                fprintf(stderr,"error: cannot open file 'input.txt'\n");
                exit(1);
            }
            reverse(fptr, 1,fout);
        }
        else if(argc ==2)
        {     
            reverse(fptr,0,NULL);
        }
    }
return 0;
}
