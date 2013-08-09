#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int is_prime(long int n)
{
int prime = 1;
long int i;
for(i = (long double)sqrt(n); i>1; i--)
      if(n%i == 0)
	{
	prime = 0;
	break;	
	}
return prime;
}
int main(int argc,char * argv[])
{
long int bot,top,i,j;
long int temp,count=0;
if(argc != 3)
{
printf("Usage:  %s <from> <to>\n",argv[0]);
exit(0);
}
bot = atoi(argv[1]);
top = atoi(argv[2]);
if(bot > top)
	{
	temp = bot;
	bot = top;
	top = temp;
	}
for( i = bot; i<= top ;i++)
{
if(! (i&1))	//checking even, if it is no prime hecne continue;
	continue;
if( is_prime(i) )
	{
	count ++;
	printf("%ld\t",i); }
}
printf("\nThere are  %ld primes in the given range ",count );
printf("\n=============== Obuntu by OSAC ===================\n");
return 0;
}
