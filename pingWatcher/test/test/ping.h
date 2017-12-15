#ifndef PING_H_INCLUDED
#define PING_H_INCLUDED
#include <ctime>
#include <fstream>

int ping()
{
    int i = 1;
    printf ("Checking if processor is available...");
    if (system(NULL)) puts ("Ok");
        else exit (EXIT_FAILURE);
    printf ("Pinging...\n");
    i=system ("ping 172.217.12.110 >> %USERPROFILE%\\Desktop\\pingWatcherTest\\pingout.txt");
    printf ("Ping returned: %d.\n",i);
    struct tm newtime;
    time_t ltime;
    char buf[50];
    ltime=time(&ltime);
    localtime_r(&ltime, &newtime);
    asctime_r(&newtime, buf);
    std::ofstream out("pingout.txt", std::ios::app);
    out << buf;
    return 0;
}

#endif // PING_H_INCLUDED
