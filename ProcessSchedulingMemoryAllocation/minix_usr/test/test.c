#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <unistd.h>
#include <limits.h>
int getgroup(int pid)
{
	message m;
	m.m1_i1 = pid;
	return _syscall(MM, GETGROUP, &m);
	}
int setgroup(int pid, int group)
{
	message m;
	m.m1_i1 = pid;
	m.m2_l2 = group;
	return _syscall(MM, SETGROUP, &m);
}
int main(int argc, char *argv[])
{
	int i, j;
	pid_t pid = getpid();
	int group;
	if(argc != 2)
	{
		printf("invalid argument\n");
		return 1;
	}
	group = getgroup(pid);
	printf("przed wywolaniem:\npid: %d group: %d\n", pid, group);
	if(group != 0 && group != 1)
	{
		printf("invalid group\n");
		return 1;
	}
	group = atoi(argv[1]);
	printf("zmiana grupy na: %d\n", group);
	setgroup(pid, group);
	group = getgroup(pid);
	printf("po wywolaniu:\npid: %d group: %d\n", pid, group);
	for(i = 0; i < INT_MAX; i++);
	printf("process group %d finished\n", group);
	return 0;
}
