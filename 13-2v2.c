#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int main()
{
  FILE *fi,*fo;
  int ch;
  char finame[40];
  char foname[40];
  char line[MAX];
  size_t s;
  printf("Please enter the input file name:");
  gets(finame);
  if((fi=fopen(finame,"r"))==NULL)
  {
    fprintf(stderr,"can't open the file %s.",finame);
    exit(0);
  }
  printf("Please enter the output file name:");
  gets(foname);
  fo=fopen(foname,"w");
  setvbuf(fi,NULL,_IOFBF,MAX);
  while((s=fread(line,sizeof(char),MAX,fi))>0)
  {
    fwrite(line,sizeof(char),s,fo);
  }
  fclose(fi);
  fclose(fo);
}
