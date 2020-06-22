#include <stdio.h>
#include <string.h>
# include<stdlib.h>
#include <iostream>
# include<string>
#include <dirent.h>
#include <fstream> 
#include <chrono>
#include <ctime>
#include <unordered_map>
using namespace std;


void setMonthTable (unordered_map <int, string> &monthTable) {
	monthTable[1] = "January";
	monthTable[2] = "February";
	monthTable[3] = "March";
	monthTable[4] = "April";
	monthTable[5] = "May";
	monthTable[6] = "June";
	monthTable[7] = "July";
	monthTable[8] = "August";
	monthTable[9] = "September";
	monthTable[10] = "October";
	monthTable[11] = "November";
	monthTable[12] = "December";
}

int main (int argc, char** argv) {
    // string receiver = "a88ttony@gmail.com";
    // string content = "hihihi";
    string receiver;
    string content;
    string subject;
    string sender;
    cout << "sender: ";
    cin >> sender;
    cout << "receiver: ";
    cin >> receiver;
    cout << "subject: ";
    cin >> subject;
    cout << "content: ";
    cin >> content;
    char cmd[100];  

    char topic[1024]; 
    strncpy(topic, subject.c_str(), sizeof(topic));
    topic[sizeof(topic) - 1] = 0;

    char from[1024]; 
    strncpy(from, sender.c_str(), sizeof(from));
    from[sizeof(from) - 1] = 0;

    char to[1024]; 
    strncpy(to, receiver.c_str(), sizeof(to));
    to[sizeof(to) - 1] = 0;

    char body[1024]; 
    strncpy(body, content.c_str(), sizeof(body));
    body[sizeof(body) - 1] = 0;   

    char tempFile[100];     

    strcpy(tempFile,tempnam("/tmp","sendmail")); 

    FILE *fp = fopen(tempFile,"w"); 
    fprintf(fp,"%s\n",body);     
    fclose(fp);           

    sprintf(cmd,"echo \"Subject: %s\" | cat - %s | sendmail -F %s -t %s ", topic, tempFile, from, to); 
    system(cmd);    

    // 把信存起來 - 目前的mail_id
    struct dirent *de;
    char db_path[] = "db";
    DIR *dir = opendir(db_path);

    int count = 0;
    while(de = readdir(dir)){
        ++count;
    }
    closedir(dir);
    // printf("%lu\n", count - 2);

    // 處理目前時間
    time_t currentTime;
    struct tm *localTime;

    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time
    int year =  localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int min = localTime->tm_min;
    unordered_map <int, string> monthTable;
    setMonthTable(monthTable);
    string day_str = to_string(day);
    string hour_str = to_string(hour);
    if (day < 10) {
        day_str = "0" + to_string(day);
    } 
    if (hour < 10) {
        hour_str = "0" + to_string(hour);
    } 
    string date = day_str + " " + monthTable[month] +  " " + to_string(year) + " at " + hour_str + ":" + to_string(min);

    // 把信存起來 - 把信寫進去
    string path(db_path);
    ofstream outfile (path+"/mail"+ to_string(count - 1));

    outfile << "From: "<< sender << endl;
    outfile << "Date: " << date << endl;
    outfile << "Message-ID: " << to_string(count - 1) <<endl;
    outfile << "Subject: " << subject << endl;
    outfile << "To: " << receiver << endl;
    outfile << "Content: " <<  endl;
    outfile << content <<  endl;

    outfile.close();

    // add function

    return 0;
}