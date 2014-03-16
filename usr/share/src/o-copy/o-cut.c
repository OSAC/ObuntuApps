#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define infoFile "/tmp/ocopy_queue.que"

void usage(char* progname){
	printf("Usage:\n");
	printf("%s [opt] [files/folders]\n",progname);
	printf("\t -a\t\t to append to last copy/cut operation.\n");
        printf("\t -h/--help\t to display this info\n");
	exit(0);
}
int main(int argc, char* argv[]){

FILE *bufferFile;
int i,no_of_files; 
char prev_command[5];
char current_dir[100];
char opt;
int is_append=0;
char command[10];
struct stat file_info;
if(argc < 2)
	usage(argv[0]);

if(strcmp(argv[1],"-a")==0){
is_append=1;
}else if((strcmp(argv[1],"--help")==0)||(strcmp(argv[1],"-h")==0)){
        usage(argv[0]);
}

if(!is_append)
	bufferFile = fopen(infoFile,"w+");
else
	bufferFile = fopen(infoFile,"a+");
//strcpy(current_dir,"/home/me");

getcwd(current_dir,100);
//printf("current Dir = %s\n", current_dir);
int start_index=1;
if(is_append)
	start_index=2;

for( i=start_index;i<argc;i++){

if( stat(argv[i],&file_info)==-1){
	printf("\"%s\" is non-existance File/directory. i m skipping it.\n",argv[i]);
	continue;
}

fprintf(bufferFile,"mv ");

if(argv[i][0]=='/' || argv[i][0]=='~'){ //absoulte path is given
        fprintf(bufferFile,"%s\n",argv[i]);
} else if(argv[i][0]=='.' && (strlen(argv[i])>=2)){
        if(argv[i][1]=='/') /* if it is ./ */
                fprintf(bufferFile,"%s%s\n",current_dir, argv[i]+1); // trick to ommit the $
        else /* it can be givein hiden file or dir */
                fprintf(bufferFile,"%s/%s\n",current_dir, argv[i]);
}else {
   fprintf(bufferFile,"%s/%s\n",current_dir,argv[i]);
}

}
fclose(bufferFile);
return 0;
}
