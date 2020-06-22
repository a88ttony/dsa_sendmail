#include <ctime>
#include <iostream>
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


int main()
{
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
    cout <<  date << endl;

}