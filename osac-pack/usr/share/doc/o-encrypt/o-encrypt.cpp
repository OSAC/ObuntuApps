#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{
FILE *text,*out;
unsigned int ch;
int i,encrypt=0,decrypt=0,lenpass;
char pass[50];
if(argc == 4){
text = fopen(argv[2],"rb");
out = fopen(argv[3],"wb");
}
else{
	system("info encrypt");
	exit(0);
	}
if(strcmp(argv[1],"-e")==0 ) //if encrypt
{ encrypt = 1;}
else if(strcmp(argv[1],"-d")==0) //if decryption
{decrypt = 1;}
else{
system("info encrypt"); 
exit(0);
}

if( (encrypt==1) || (decrypt == 1) )
{
printf("[ Password ] : ");
scanf("%s",pass );
lenpass = strlen(pass);
}

i=0;
if(encrypt)
while(1)
{
ch = fgetc(text);
if(ch == EOF )
break;
ch += pass[i];
i = (i+1)%lenpass;
fputc(ch,out);
}
else if(decrypt)
while(1)
{
ch = fgetc(text);
if(ch == EOF )
break;
ch -= pass[i];
i = (i+1)%lenpass;
fputc(ch,out);
}
fcloseall();
return 0;
}
