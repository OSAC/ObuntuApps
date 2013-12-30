#include <stdio.h>
#include <string.h>
#include <malloc.h>
int sep(int argc,char** argv,int ask_pass,char* pass)
{
FILE *image,*text,*merg;
int lenpass;
unsigned int cha;
unsigned int cha1;
unsigned int cha2;
unsigned int cha3;
int i;

if( ask_pass == 1 )
	lenpass = strlen(pass);

merg=fopen(argv[2],"rb");
image=fopen(argv[3],"wb");
text=fopen(argv[4],"wb");

cha3=fgetc(merg);
cha2=fgetc(merg);
cha1=fgetc(merg);
cha=fgetc(merg);
while(1)
{
i=0;
if( ask_pass == 1 )
{
if( (cha3-pass[i]) == 'E') 
        {i = (i+1)%lenpass;  
         if( (cha2-pass[i]) == 'N')  
        	{i = (i+1)%lenpass;
	         if( (cha1-pass[i]) == 'D' )
        	 	{i = (i+1)%lenpass;
 	 		 if( (cha-pass[i]) == 'I' )
			        {i = (i+1)%lenpass;
         			 break;
				}
			  }
		  }
	   }
}
else if( ask_pass == 0)
	if((cha3=='E') && (cha2 == 'N') && (cha1 == 'D') && (cha == 'I') )
		break; 

if(cha3==EOF)
break;

fputc(cha3,image);

cha3=cha2;
cha2=cha1;
cha1=cha;
cha = fgetc(merg);
}
fclose(image);


while(1)
{
cha=fgetc(merg);
if(cha ==EOF)
break;
if( ask_pass == 1 )//encrypt only of -p is present
{
cha -= pass[i];
i = (i+1)%lenpass;
}
fputc(cha,text);
}
fcloseall();
return 0;
}

int merge(int argc,char** argv,int ask_pass,char* pass)
{
FILE *image,*text,*merg;
unsigned int cha,lenpass;
int i;
image = fopen(argv[2],"rb");
text = fopen(argv[3],"rb");
merg = fopen(argv[4],"wb");

if( ask_pass == 1 )
	lenpass = strlen(pass);

while(1)
{
cha=fgetc(image);
if(cha==EOF)
break;
fputc(cha,merg);
} // finished reading 1st file.
i=0;
if( ask_pass == 1 )
{
fputc('E'+pass[i],merg);
i = (i+1) %lenpass;
fputc('N'+pass[i],merg);
i = (i+1) %lenpass;
fputc('D'+pass[i],merg);
i = (i+1) %lenpass;
fputc('I'+pass[i],merg);
i = (i+1) %lenpass;
}
else if( ask_pass == 0)
{
fputc('E',merg);
fputc('N',merg);
fputc('D',merg);
fputc('I',merg);
}
while(1)
{
cha=fgetc(text);
if(cha==EOF)
break;
/// Encript the text file here ////
if( ask_pass == 1 ){
cha += pass[i];
i = (i+1)%lenpass;
}

fputc(cha,merg);
}
fcloseall();
return 0;
}

int main(int argc,char** argv)
{
int error_code=0;
int ask_pass=0,res=0;
char *pass;
pass = (char *)malloc(sizeof(char)*60);
if( (strcmp(argv[1],"-m")!=0) && (strcmp(argv[1],"-s")!=0) )
	error_code = 1;
if(argc < 5)
	error_code = 1;

if( (argc == 6) && (strcmp(argv[5],"-p") != 0) )
	error_code = 1;
if( (argc == 6) && (strcmp(argv[5],"-p") == 0) )
	{
	ask_pass = 1;
	printf("( password ) : ");
	scanf("%s",pass);
	}
if(error_code != 1)
{

if(strcmp(argv[1],"-m")==0)
	res = merge(argc,argv,ask_pass,pass);
if(strcmp(argv[1],"-s")==0)
	res = sep(argc,argv,ask_pass,pass);
}
else if(error_code==1)
{
printf("Syntax Error \n");
printf("hide-file -m <host_file> <guest_file> <output_file> -p   //merge\n\t -p can be omitted if you don't want to encrypt guest_file via password\n");
printf("\t\t\tOR\n");
printf("hide-file -s <merged_file> <output_img_file> <output_txt_file> -p   //separate\n\t -p can be omitted if the merged_file was not encrypted via password\n");
}
if(res == -1)
	printf("Run-time Error\n");
return 0;
}
