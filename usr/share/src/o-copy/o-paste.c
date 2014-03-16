#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define infoFile "/tmp/ocopy_queue.que"
void usage(char* progname){
	printf("Usage:\n");
	printf("%s <dest_path>\tdest_path is optional, when omitted the `pwd` is used\n",progname);
	printf("%s --help\t\tto display this info\n",progname);
	exit(0);
}
int main(int argc, char* argv[]){
FILE *bufferFile;
char dest_path[100], final_command[300];
char ch;
char command[5], com_opt[100], src_file[100];
int is_com_opt, is_move=0;
char operation[5];
struct stat file_info;
if(argc==2){
	if((strcmp(argv[1],"--help")==0)||(strcmp(argv[1],"-h")==0))
		usage(argv[0]);

	strcpy(dest_path, argv[1]);// custom paste location

	if( stat(dest_path,&file_info)==-1){
		printf("provide valid destination directory to paste\n");
		exit(0);
	}else if (! (file_info.st_mode&S_IFDIR)){
		printf("destination directory is required not destination file\n");
		exit(0);
	}

}else if(argc>2){
	usage(argv[0]);
} else {
	strcpy(dest_path, ".");
}

bufferFile = fopen(infoFile, "r");
if(bufferFile == NULL){
	printf("Nothing to paste\no-copy or o-cut first to paste throug o-paste\n");
	return 1;
}

do{

	if( fscanf(bufferFile,"%s %s",command, com_opt) == EOF){
		break;
	}
	if(strcmp(command,"mv")==0)
		is_move = 1;

	if(com_opt[0]!='-'){
		strcpy(src_file, com_opt);
		is_com_opt=0;
	}else {
		fscanf(bufferFile,"%s", src_file);
		is_com_opt=1;
	}
if(is_com_opt){
	sprintf(final_command,"%s %s %s %s", command, com_opt, src_file, dest_path);
	printf("%s\n",final_command);
	system(final_command); // no need to reinvent the wheel, just understand it and use it
} else {
	sprintf(final_command,"%s %s %s", command, src_file, dest_path);
	printf("%s\n",final_command);
	system(final_command);
}

}while(1);

fclose(bufferFile);

if( is_move){
/* if any of those commands are move command, we just remove the buffer_file file making unable to paste again */
/* but what happend if we remove only move command and keep the copy command??*/
	remove(infoFile);
}
return 0;
}
