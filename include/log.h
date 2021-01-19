#ifndef SIMPLE_DB_LOG
#define SIMPLE_DB_LOG

#include <ctime>
#include <iostream>
#include <cstdio>

using namespace std;

void logger(const char *log)
{
    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);
    FILE *fp;
    fp = fopen("../log.txt", "a+");
    fprintf(fp, "SimpleDB: %d:%d:%d:%d:%d:%d\t", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
    fprintf(fp, log);
    fprintf(fp, "\n");
    fclose(fp);
    cout << log << endl;
}

#endif