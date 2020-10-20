#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define SHORT 0;
#define LONG 1;
#define STANDARD 2;

void sampleLoadAvg(char lineBuf[256], int LB_SIZE, int iteration, int interval); //Sample the load avg

int main(int argc, char* argv[]) {
        char repTypeName[30]; //Whether standard, long or short
        char lineBuf[256]; //What file is going to be inputting into 
        struct timeval now; //to find time
        char c1, c2; //if there are more args than 1
        
        int interval, duration; //duration and interval for Part D
        int iteration = 0; //For part D
        int LB_SIZE = 255;
        FILE* thisProcFile; //File to be opened
        
        //Determine report type
        int reportType = STANDARD;
        duration = -1; //set to -1 if part b or c
        interval = -1; //set to -1 if part b or c
        strcpy(repTypeName, "Standard");

        if(argc > 1) { //if there are more than 1 arguments
                sscanf(argv[1], "%c%c", &c1, &c2);
                if(c1 != '-') { //if it's just a -, then quit and print error
                        fprintf(stderr, "usage: observer [-s][-l int dur]\n");
                        exit(1);
                }
                if(c2 == 's') {  //if part C
                        reportType = SHORT;
                        strcpy(repTypeName, "Short");
                }
                if(c2 == 'l') { //for part D
                        reportType = LONG;
                        strcpy(repTypeName, "Long");
                        interval = atoi(argv[2]);
                        duration = atoi(argv[3]);
                } 
        }
        
        //CPU INFO
        char* fileName = "/proc/cpuinfo";
        if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                perror("fopen()\n");
                return EXIT_FAILURE;
        }
        
        int n;
        n = 0;
        char *temp = NULL;
        //iterate through the file and find model name
        while(getline(&temp, &n, thisProcFile) > 0) {
                if(strstr(temp, "model name")) {
                        printf("\nCPU Model: %s\n", temp);
                        break;
                }
        }
        fclose(thisProcFile); //close file 


        //KERNEL VERSION
        fileName = "/proc/version";
        if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                perror("fopen()\n");
                return EXIT_FAILURE;
        }
        
        fgets(lineBuf, LB_SIZE+1, thisProcFile); //write the files of size lb_size+1 into linebuf
        printf("Kernel Version: %s\n", lineBuf);
        fclose(thisProcFile);

        //SYSTEM UPTIME
        fileName = "/proc/uptime";
        if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                perror("fopen()\n");
                return EXIT_FAILURE;
        }
        
        fgets(lineBuf, LB_SIZE+1, thisProcFile); //write the files of size lb_size+1 into linebuf
        printf("System Uptime: %s (the first number)\n\n", lineBuf);
        fclose(thisProcFile);

        gettimeofday(&now, NULL); //get the time of day
        printf("Status report type %s at %s \n", repTypeName, ctime(&(now.tv_sec))); 
       
        //Get the host filename and print
        fileName = "/proc/sys/kernel/hostname";
        if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                perror("fopen()\n");
                return EXIT_FAILURE;
        }
      
        fgets(lineBuf, LB_SIZE+1, thisProcFile); //write the files of size lb_size+1 into linebuf
      
        printf("Machine hostname: %s \n", lineBuf);
        fclose(thisProcFile); //close the file
       
       //PART C-------------------------------------------------
       if(reportType == 0) {
                //CPU time spent in user, system, idle 
                fileName = "/proc/stat";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find time
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "cpu")) {
                                printf("\nCPU times: %s", temp);
                                printf("(1st number is user time, third is System mode, and fourth is idle.)\n");
                                break;
                        }
                }   
                fclose(thisProcFile); //close file
                
                //Number of read/writes 
                fileName = "/proc/diskstats";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find SDA
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "sda")) {
                                printf("\nDisk Read/Writes: %s", temp);
                                printf("(1st number AFTER sda is number total reads, fifth is # of writes.)\n");
                                break;
                        }
                }   
                fclose(thisProcFile); //close file
                
                 
                //Number of Context switches 
                fileName = "/proc/stat";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find SDA
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "ctxt")) {
                                printf("\nNumber of Context Switches: %s", temp);
                                break;
                        }
                }   
                fclose(thisProcFile); //close file
                
                
                //Number of Processes 
                fileName = "/proc/stat";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find SDA
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "processes")) {
                                printf("\nNumber of %s", temp);
                                break;
                        }
                }   
                fclose(thisProcFile); //close file
        }
         
            
           //PART D ------------------------------------------
        if(reportType = 1) {
                
                //Total number of memory 
                fileName = "/proc/meminfo";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find SDA
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "MemTotal")) {
                                printf("\nNumber of %s\n", temp);
                                break;
                        }
                }   
                fclose(thisProcFile); //close file

                
                //MEMORY availible 
                fileName = "/proc/meminfo";
                if((thisProcFile = fopen(fileName, "r")) == NULL) { //make sure file exists
                        perror("fopen()\n");
                        return EXIT_FAILURE;
                }
                n = 0;
                temp = NULL;
                //iterate through the file and find SDA
                while(getline(&temp, &n, thisProcFile) > 0) {
                        if(strstr(temp, "MemFree")) {
                                printf("\nNumber of %s\n", temp);
                                break;
                        }
                }   
                fclose(thisProcFile); //close file

                //Reading relevant /proc files
                if(interval != -1 && duration != -1) { //if not Part D just skip this
                        while(iteration < duration) {
                                sleep(interval); //sleep
                                sampleLoadAvg(lineBuf, LB_SIZE, iteration, interval); //get avg and print
                                iteration += interval;
                        }
                }
        }
        exit(0);   
}

void sampleLoadAvg(char lineBuf[256], int LB_SIZE, int iteration, int interval) { //Sample the load avg
    FILE* thisProcFile1 = fopen("/proc/loadavg", "r"); //open file
    fgets(lineBuf, LB_SIZE+1, thisProcFile1); //get the avg
    printf("Iteration #%d (time%d): %s", iteration, iteration * interval, lineBuf); //print it       
}
