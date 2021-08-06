#include<stdio.h>
#include<strings.h>
#include<string.h>
int main(int argc ,char *argv[])
{
	char buf[48]="0";
	FILE *fp=NULL;
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		perror("fopen file");
		return -1;
	}
	
	fseek(fp,0,SEEK_SET);

	
		fgets(buf,48,fp);
		printf("%s\n",buf);
	
	if(feof(fp)!=0)
	{
		fclose(fp);
	
		return 0;
		
	}

}