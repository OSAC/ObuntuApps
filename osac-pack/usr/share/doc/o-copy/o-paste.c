#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <termios.h>
#include <unistd.h>
int getch()
{
struct termios oldt,newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag&= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO,TCSANOW,&newt );
ch = getchar();
tcsetattr( STDIN_FILENO,TCSANOW,&oldt );
return ch;
}
int main(int argc,char** argv)
{
char fname[20],endm[5],cut_cp[7];
FILE *source,*dest;
int iscut=0;
unsigned int cha;
char opt;


source = fopen("/tmp/.vmlinuz","rb");
if(source == NULL)
{
	printf("Can't open buffer to read\n");
	exit(0);
	}
fscanf(source,"%s %s %s ",fname,cut_cp,endm);
if( strcmp(endm,"ENDN")!=0)
	{
		printf("Buffer Currepted\n");
		return 1;
		}
if(strcmp(cut_cp,"CUT")==0)
	iscut = 1;
else if(strcmp(cut_cp,"COPY")==0)
	iscut = 0;

if (argc == 2)
	strcpy(fname,argv[1]);
	
dest = fopen(fname,"rb");
if(dest != NULL )
	{
		printf("A file with same name exists.\nDo you Want to replace it(Y/n)? ");
		opt = getch();
		if(opt == 'Y'){ fclose(dest);}
		else 
		{ fclose(dest); 
		printf("\n");
		exit(0); }
		}


dest = fopen(fname,"wb");
if(dest == NULL )
	{
		printf("Error opening output file\n");
		return 0;
		}
do
{
	cha = fgetc(source);
	if(cha == EOF)
		break;
	fputc(cha,dest);
	}while(1);
fclose(source);
fclose(dest);
if(iscut)
	remove("/tmp/.vmlinuz");
return 0;
}

