#include <stdio.h>
#include <dirent.h>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    struct dirent *de;
    char db_path[] = "db";
    DIR *dir = opendir(db_path);

    int count = 0;
    while(de = readdir(dir)){
        ++count;
    }

    closedir(dir);
    printf("%lu\n", count - 2);

    return 0;
}