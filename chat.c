/*
--For each message sent their will be a name, time sent, and messaege data
*/



#include <stdio.h>
#include <time.h>
int main(){
FILE *fp;


fp = fopen("chat_data.txt", "a");
 fprintf(fp, "This is testing for fprintf...\n");
fclose(fp);


}
