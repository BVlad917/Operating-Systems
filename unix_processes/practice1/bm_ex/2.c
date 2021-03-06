nclude<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
/**
 *   2. Write a C program that will compute a Fibonnaci sequence using recursion
 *     and each recursive step will be computed by a child process (child-ception :) )
 *      * */
int fibo(int n)
{
	if(n==0||n==1)
		return n;
	int c1[2],c2[2];
	pipe(c1);pipe(c2);
	int pid1=fork();
	if(pid1==0)
	{
		close(c2[0]);
		close(c2[1]);
		close(c1[0]);
		int res1 = fibo(n-1);
		write(c1[1],&res1,sizeof(int));
		close(c1[1]);
		exit(0);
	}
	int pid2=fork();
	if(pid2==0)
	{
		close(c1[0]);
		close(c1[1]);
		close(c2[0]);
		int res2 = fibo(n-2);
		write(c2[1],&res2,sizeof(int));
		close(c2[1]);
		exit(0);
	}
	wait(0);wait(0);
	int res1,res2;
	close(c1[1]);
	close(c2[1]);
	read(c1[0],&res1,sizeof(int));
	read(c2[0],&res2,sizeof(int));
	close(c1[0]);
	close(c2[0]);
	return res1+res2;
}
int main(int argc,char*argv[])
{
	int n;
	printf("Enter n: ");
	scanf("%d",&n);
	printf("Fibo %d is: %d\n",n,fibo(n));
	return 0;
}
