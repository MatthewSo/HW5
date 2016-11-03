#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void printSize(long m){
    if (m < 1000){
    printf( " Human Size: %d B\n", m);
  }
  else if (m < 1000000){
    printf( " Human Size: %f KB\n", m/1000.0);
  }
  else if (m < 1000000000){
    printf( " Human Size: %f MB\n", m/1000000.0);
  }
  else{
    printf( " Human Size: %f GB\n", m/1000000000.0);}}

int main(){
  printf("Directory Info \n");
  DIR *temp1 = opendir(".");

  
  struct dirent *i = readdir(temp1);
  
  printf("Directories: \n");
  while(i){
    if(i->d_type & DT_DIR){
      printf("\t%s\n",i->d_name);}
    i=readdir(temp1);
  }
  
  rewinddir(temp1);
  printf("Files: \n");

  int ret = 0;
  struct stat file;
  i = readdir(temp1);
  while(i){
    if (!(i->d_type & DT_DIR)){
    printf("\t%s",i->d_name);
    stat(i->d_name,&file);
    ret += file.st_size;
    printSize(file.st_size);}
    i=readdir(temp1);
  
  }
  closedir(temp1);
  printf("Total Size:");
  printSize(ret);
  return 0;

}
