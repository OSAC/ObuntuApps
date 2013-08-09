#include<stdio.h>
#include<stdlib.h>
int main()
{
system("cp /usr/share/doc/o-notice/.onotice ~/.onotice");
int dwnsus=0;
printf("*******************  Obuntu NOTICE Board  ************************\n");
dwnsus = system("wget http://www.bishnu.comli.com/osacnotice.zip -o log.txt");
if(dwnsus == 0)
	{
	system(" mv -f osacnotice.zip ~/.onotice");
	}
system(" cat ~/.onotice");
printf("************************************ Customized by OSAC Lerners **\n");
remove("log.txt");
return 0;
}
