#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
FILE *source,*dest;
unsigned int cha;
char opt;
dest = fopen("/tmp/.vmlinuz","rb");
if(dest != NULL )
	{
		printf("A file is previously copied to Buffer.\nDo you Want to replace it(Y/n)? ");
		opt = getch();
		if(opt == 'Y'){ fclose(dest);}
		else 
		{ fclose(dest); 
		printf("\n");
		exit(0); }
		}
if(argc == 1)
{
	printf("Please provide the file to copy\n");
	exit(0);
	}	
source = fopen(argv[1],"rb");
if(source == NULL)
{
	printf("Error while opening file to be copied\n");
	return 0;
	}
dest = fopen("/tmp/.vmlinuz","wb");
if(dest == NULL )
	{
		printf("Error while opening Buffer\n");
		return 0;
		}
fprintf(dest,"%s %s %s ",argv[1],"COPY","ENDN");
do{
cha = fgetc(source);
if(cha==EOF)
	break;
fputc(cha,dest);
}while(1);
fclose(source);
fclose(dest);
return 0;
}

