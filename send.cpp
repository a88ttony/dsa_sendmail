#include <stdio.h>
#include <string.h>
# include<stdlib.h>
#include <iostream>
# include<string>
using namespace std;

int main (int argc, char** argv) {
    string receiver = "a88ttony@gmail.com";
    string content = "hihihi";

    // cout << "receiver: ";
    // cin >> receiver;
    // cout << "content: ";
    // cin >> content;
    char cmd[100];  

    char to[1024]; 
    strncpy(to, receiver.c_str(), sizeof(to));
    to[sizeof(to) - 1] = 0;

    char body[1024]; 
    strncpy(body, content.c_str(), sizeof(body));
    to[sizeof(body) - 1] = 0;   

    char tempFile[100];     

    strcpy(tempFile,tempnam("/tmp","sendmail")); 

    FILE *fp = fopen(tempFile,"w"); 
    fprintf(fp,"%s\n",body);     
    fclose(fp);           

    sprintf(cmd,"echo \"Subject: Testing\" | cat - %s | sendmail -F me@here.com -t %s ",tempFile,to); 
    system(cmd);    

    return 0;
}