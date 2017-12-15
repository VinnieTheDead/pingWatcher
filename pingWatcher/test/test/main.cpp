#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <conio.h>
#include <windows.h>
#include "ping.h"
#include <ctime>

using namespace std;

int parsePingData();
int pingSortData();

int main(){
	double startTime = GetTickCount();
	ping();

	while(true){
        Sleep(1000);
		double currentTime = GetTickCount() - startTime;
		if( currentTime >= 30000 ){
		    ping();
			//Reset the timer.
			startTime = GetTickCount();
		}
		char key = ' ';
		if( _kbhit() )
			key = _getch();
		if( key == 13 ){
            parsePingData();
			break;
		}
	}
	pingSortData();
    return 0;
}

int parsePingData(){
    ifstream pingRawData;
    pingRawData.open("pingout.txt");
    if(!pingRawData){
        printf ("ERROR: Failed to acquire input file!");
        return 1;
    }
    ofstream pingParsedData;
    pingParsedData.open("pingParsed.txt");
    if(!pingParsedData){
        printf ("ERROR: Failed to acquire output file!");
        return 1;
    }
    string buffer = "";
    int linecount = 0;
    while(pingRawData){
        pingRawData.ignore(4);
        getline(pingRawData, buffer);
        if(buffer[0]=='M'){
            pingParsedData << buffer;
            getline(pingRawData, buffer);
            pingParsedData << ", " << buffer << endl;
            linecount++;
            linecount++;
        }
    }
    cout << "Parsed " << linecount << " useful lines!" << endl;
    pingRawData.close();
    pingParsedData.close();
    return 0;
}

int pingSortData(){
    ifstream pingParsedData;
    ofstream pingSortedData;
    string buffer = "";
    string garbage = "";

    pingParsedData.open("pingParsed.txt");
    pingSortedData.open("pingSorted.csv");
    if(!pingParsedData){printf("Failed to open input file!"); return 1;}
    if(!pingSortedData){printf("Failed to open output file!"); return 1;}

    pingSortedData << "Minimum, Maximum, Average\n";

    while(getline(pingParsedData, garbage, '=')){
            pingParsedData.ignore();
            getline(pingParsedData, buffer, 'm'); //Load min into buffer.
            pingSortedData << buffer << ",";
            pingParsedData.ignore(13);
            getline(pingParsedData, buffer, 'm'); //Load max into buffer.
            pingSortedData << buffer << ",";
            pingParsedData.ignore(13);
            getline(pingParsedData, buffer, 'm'); //Load average into buffer.
            pingSortedData << buffer;
            pingParsedData.ignore();
            getline(pingParsedData, buffer);
            pingSortedData << buffer << "\n";
        }
    pingParsedData.close();
    pingSortedData.close();
    return 0;
}
