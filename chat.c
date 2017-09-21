/*
--For each message sent their will be a name, time sent, and messaege data
*/



#include <stdio.h>
#include <time.h>
int main(){
FILE *fp;


fp = fopen("test.txt", "r");

  char time_sent[255];
  char msg[255];

  while( fgets(time_sent,255,(FILE*)fp)){
     fgets(msg,255,(FILE*)fp);
     printf("time: %s, msg: %s\n",time_sent,msg);
   }
}
