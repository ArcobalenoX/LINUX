#include<stdio.h>
#include<strings.h>
#include<string.h>
int main(int argc ,char *argv[])
{
	
	char  buf[]="+asdfghjkl";
	FILE *fp=NULL;
	fp=fopen(argv[1],"a+");
	if(fp==NULL)
	{
		perror("fopen file");
		return -1;
	}
	fwrite(buf,strlen(buf),1,fp);

	fclose(fp);
	
	return 0;
}