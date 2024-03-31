#include <stdio.h>
#include <stdlib.h>
//final
// Structure to represent a process
struct Process {
    int processNumber;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int remainingBurstTime;
    int priority;
    int completionTime;
    float responseTime;
    int firsttime; // response

};




struct Process* sjfNonPreemptive(struct Process* processes, int n) ;
struct Process* fcfs(struct Process* processes, int n);
struct Process* RR(struct Process* processes, int n, int quantum) ;
void printGanttChart(struct Process* processes, int n);
void printSchedule(struct Process* processes, int n);
float calculateAverageTurnaroundTime(struct Process* processes, int n);
float calculateAverageWaitingTime(struct Process* processes, int n);
struct Process* priorityNonPreemptive(struct Process* processes, int n);
struct Process* sjfPreemptive(struct Process* processes, int n);




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Process* sjfPreemptive(struct Process* processes, int n) {
  struct Process*  processesN = malloc(n * sizeof(struct Process));// holds the new order
    struct Process*  processesN2 = malloc(n * sizeof(struct Process));// == ORIGINAL
      for (int i = 0; i < n; i++) {
        processesN2[i] = processes[i];
    }

    int currentTime = 0;
    int completedProcesses = 0;
    int order=0;
    processesN2->firsttime=0;
    float totalaresponse=0;


  //remaining = burst time
    while (completedProcesses < n) {
        int shortestJob = -1;
        int shortestBurstTime = INT_MAX;


        for (int i = 0; i < n; i++) {
            if (processesN2[i].arrivalTime <= currentTime && processesN2[i].remainingBurstTime < shortestBurstTime && processesN2[i].remainingBurstTime > 0) {
                shortestJob = i;
                shortestBurstTime = processesN2[i].remainingBurstTime;
            }
        }

        if (shortestJob == -1) {// no process arrives yet
            currentTime++;
            continue;
        }

        processesN2[shortestJob].remainingBurstTime--;

        if( processesN2[shortestJob].firsttime == 0){
        processesN2[shortestJob].responseTime=  currentTime - processesN2[shortestJob].arrivalTime;
         processesN2[shortestJob].firsttime=1;
        }



        if (processesN2[shortestJob].remainingBurstTime == 0) {//finished
    totalaresponse +=  processesN2[shortestJob].responseTime;

            completedProcesses++;
            processesN2[shortestJob].turnAroundTime = currentTime + 1 - processesN2[shortestJob].arrivalTime;
            processesN2[shortestJob].waitingTime = processesN2[shortestJob].turnAroundTime - processesN2[shortestJob].burstTime;
            processesN2[shortestJob].responseTime=  currentTime- processesN2[shortestJob].arrivalTime;
            processesN[order]= processesN2[shortestJob];
            order++;
        }

        currentTime++;
    }

processesN->responseTime=totalaresponse/n; // mkansh radi yzbot zay el paqi
return processesN;

}

///////////////////////////////////////////////////////////


struct Process* sjfNonPreemptive(struct Process* processes, int n) {
    struct Process* processesj = malloc(n * sizeof(struct Process)); // holds the new order
    struct Process* processesj2 = malloc(n * sizeof(struct Process)); // == ORIGINAL

    for (int i = 0; i < n; i++) {
        processesj2[i] = processes[i];
    }
    // Sort the processes based on arrival time (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processesj2[j].arrivalTime > processesj2[j + 1].arrivalTime) {
                // Swap processes
                struct Process temp = processesj2[j];
                processesj2[j] = processesj2[j + 1];
                processesj2[j + 1] = temp;
            }}}

    int currentTime = 0;
    int completedProcesses = 0;
    int order = 0;

    // remaining = burst time
    while (completedProcesses < n) {

        int shortestJob = -1;
        int shortestBurstTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if ( processesj2[i].arrivalTime <= currentTime && processesj2[i].remainingBurstTime < shortestBurstTime && processesj2[i].remainingBurstTime > 0) {
                shortestJob = i;
                shortestBurstTime = processesj2[i].remainingBurstTime;
            }
        }

        if (shortestJob == -1) { // no process arrives yet
            currentTime++;
            continue;
        }


 while (processesj2[shortestJob].remainingBurstTime>0){

        processesj2[shortestJob].remainingBurstTime--;
                currentTime++;

 }
             processesj2[shortestJob].responseTime=  ((currentTime-  processesj2[shortestJob].burstTime )- processesj2[shortestJob].arrivalTime);


        if (processesj2[shortestJob].remainingBurstTime == 0) { // finished
            completedProcesses++;
            processesj2[shortestJob].turnAroundTime = currentTime  - processesj2[shortestJob].arrivalTime;
            processesj2[shortestJob].waitingTime = processesj2[shortestJob].turnAroundTime - processesj2[shortestJob].burstTime;
            processesj[order] = processesj2[shortestJob];
            order++;
        }


    }

    return processesj;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Process*  fcfs(struct Process* processes, int n) {
      struct Process*  processesf = malloc(n * sizeof(struct Process));// holds the new order
      int completiontime=0;

  for (int i = 0; i < n; i++) {
        processesf[i] = processes[i];
    }


        // Sort the processes based on arrival time (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processesf[j].arrivalTime > processesf[j + 1].arrivalTime) {
                // Swap processes
                struct Process temp = processesf[j];
                processesf[j] = processesf[j + 1];
                processesf[j + 1] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time for the first process
    processesf[0].waitingTime = 0;
    processesf[0].turnAroundTime = processesf[0].burstTime;
    processesf[0].responseTime = 0;


    completiontime += processes[0].burstTime;

    // Calculate waiting time and turnaround time for each process
    for (int i = 1; i < n; i++) {
    processesf[i].responseTime=  completiontime- processesf[i].arrivalTime;

    completiontime += processes[i].burstTime;

                    // Turnaround time is the sum of burst time and waiting time
        processesf[i].turnAroundTime = completiontime - processes[i].arrivalTime;


        // Waiting time for the current process is the completion time of the previous process minus its arrival time
        processesf[i].waitingTime = processesf[i].turnAroundTime - processesf[i].burstTime;



    }

    processesf->completionTime=completiontime;
    return processesf;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Process*  RR(struct Process* processes, int n, int quantum)
{
      struct Process*  processesr = malloc(n * sizeof(struct Process));// holds the new order
        for (int i = 0; i < n; i++) {
        processesr[i] = processes[i];
    }

   processesr->arrivalTime=0;


    // Find waiting time and turn around time using Round Robin algorithm
       // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = processesr[i].burstTime;

    int t = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++)
        {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    // how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }
                else
                {
                    // how much time a process has been processed
                    t += rem_bt[i];

                    // Waiting time is current time minus time
                    // used by this process
                    processesr[i].waitingTime = t - processesr[i].burstTime;

                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }



        }

        // If all processes are done
        if (done == 1)
            break;


    }



   // findTurnAroundTime(processes, n);
    for (int i = 0; i < n; i++){
        processesr[i].turnAroundTime = processesr[i].burstTime + processesr[i].waitingTime;
        processesr[i].responseTime= t - processesr[i].arrivalTime;


}
        return processesr;

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Process*  priorityNonPreemptive(struct Process* processes, int n) {
      struct Process*  processesp = malloc(n * sizeof(struct Process));// holds the new order
            struct Process*  processesp2 = malloc(n * sizeof(struct Process));
            processesp2->firsttime=0;
            float totalaresponse=0;



        for (int i = 0; i < n; i++) {
        processesp2[i] = processes[i];
    }
        // Sort the processes based on their priority (lowest first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processesp[i].priority> processesp2[j].priority) {
                struct Process temp = processesp2[i];
                processesp2[i] = processesp2[j];
                processesp2[j] = temp;
            }
        }
    }

    int currentTime = 0;
    int completedProcesses = 0;
    int order = 0;

    // remaining = burst time
    while (completedProcesses < n) {

        int highprindex = -1;
        int highpri = INT_MAX;

        for (int i = 0; i < n; i++) {
            if ( processesp2[i].arrivalTime <= currentTime && processesp2[i].priority < highpri && processesp2[i].remainingBurstTime > 0) {
                highprindex = i;
                highpri = processesp2[i].priority;



            }


        }


        if (highprindex == -1) { // no process arrives yet
            currentTime++;
            continue;
        }

 while (processesp2[highprindex].remainingBurstTime>0){

        processesp2[highprindex].remainingBurstTime--;
                currentTime++;

 }





        if (processesp2[highprindex].remainingBurstTime == 0) { // finished
            completedProcesses++;
            totalaresponse +=  (currentTime -  processesp2[highprindex].burstTime)- processesp2[highprindex].arrivalTime;// because it is after the execution ->(currentTime-  processesp2[shortestJob].burstTime

            processesp2[highprindex].turnAroundTime = currentTime  - processesp2[highprindex].arrivalTime;
            processesp2[highprindex].waitingTime = processesp2[highprindex].turnAroundTime - processesp2[highprindex].burstTime;
            processesp2[highprindex].responseTime=  currentTime- processesp2[highprindex].arrivalTime;
            processesp[order] = processesp2[highprindex];
            order++;
        }


    }

    processesp->responseTime=totalaresponse/n; // mkansh radi yzbot zay el paqi

    return processesp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void printGanttChart(struct Process* processes, int n) {
    printf("\nGantt Chart:\n");

    // Print top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    // Print process numbers
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime - 1; j++)
            printf(" ");
        printf("P%d", processes[i].processNumber);
        for (int j = 0; j < processes[i].burstTime - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");

    // Print bottom bar
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    // Print the time line
    int currentTime = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++)
            printf("  ");
        currentTime += processes[i].burstTime;
        if (currentTime > 9)
            printf("\b");  // Backspace
        printf("%d", currentTime);
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printSchedule(struct Process* processes, int n) {
    printf("\nProcess Schedule:\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processNumber, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnAroundTime);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




float calculateAverageTurnaroundTime(struct Process* processes, int n) {
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].turnAroundTime;
    }
    return (float)totalTurnaroundTime / n;
}

float calculateAverageWaitingTime(struct Process* processes, int n) {
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
    }
    return (float)totalWaitingTime / n;

}

float calculateAverageResponseTime(struct Process* processes, int n) {
    int total_response_time = 0;

    for (int i = 0; i < n; i++) {
        total_response_time += processes[i].responseTime;
    }
    return   (float)    total_response_time / n;

}


float calculateAverageThroughputTime(struct Process* processes, int n) { // # of processes complete their execution per time unit.
    int total_execution_time = 0;

    for (int i = 0; i < n; i++) {
        total_execution_time += processes[i].burstTime;
    }

   // return   (float) total_execution_time/n;
        return   (float) n ;


}

float calculateCPUUtilizationTime(struct Process* processes, int n) {
    int totalBurstTime = 0;

    // Calculate the total burst time of all processes
    for (int i = 0; i < n; i++) {
        totalBurstTime += processes[i].burstTime;
    }

    // Calculate the CPU utilization time
    float cpuUtilizationTime = (float) totalBurstTime;

    return cpuUtilizationTime*0.01;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    system("Title CPU Scheduling");

    int n, i, quantum;
    struct Process* processes = NULL;

    // Ask for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Allocate memory for the processes
    processes = malloc(n * sizeof(struct Process));

    // Get the burst time and arrival time for each process
    // Get the burst time and arrival time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the arrival time of Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
          if(processes[i].arrivalTime < 0){
          printf("Error,Enter positive number\n");
          scanf("%d", &processes[i].arrivalTime);
          }

        printf("Enter the burst time of Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        if(processes[i].burstTime < 0){
          printf("Error,Enter positive number\n");
          scanf("%d", &processes[i].burstTime);
          }
        printf("Enter the priority of Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);

        if(processes[i].priority < 0){
          printf("Error,Enter positive \n");
          scanf("%d", &processes[i].priority);
          }

        // Assign process number
        processes[i].processNumber = i + 1;
        processes[i].remainingBurstTime = processes[i].burstTime;

    }

    // Ask for the quantum
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);







                            /////////////////////////////////////////////////////////////////////////////////////////

    printf("                                 ****************************************\n");




  // Apply FCFS algorithm
      struct Process*  processesf = malloc(n * sizeof(struct Process));// holds the new order

   processesf= fcfs(processes, n);

    // Print FCFS schedule
    printf("\nFCFS Algorithm:\n");
    printGanttChart(processesf, n);
    printSchedule(processesf, n);
    float fcfsAvgTurnaroundTime = calculateAverageTurnaroundTime(processesf, n);
    float fcfsAvgWaitingTime = calculateAverageWaitingTime(processesf, n);
    float fcfsAvgResponseTime = calculateAverageResponseTime(processesf, n);
    float fcfsAvgThroughputTime = calculateAverageThroughputTime(processesf, n);
    float fcfsAvgCPUUtilizationTime = calculateCPUUtilizationTime(processesf, n);

    printf("Average Turnaround Time: %.2f\n", fcfsAvgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", fcfsAvgWaitingTime);
    printf("Average Response Time: %.2f\n", fcfsAvgResponseTime);
    printf("Average Throughput Time: %.2f per time unit\n", fcfsAvgThroughputTime);
    printf("Average CPU Utilization: %.2f\n",fcfsAvgCPUUtilizationTime );





  /////////////////////////////
      // Apply SJF algorithm
        struct Process*  processesj = malloc(n * sizeof(struct Process));// holds the new order

processesj=sjfNonPreemptive(processes, n);


    // Print SJF schedule
   printf("\nSJF Algorithm Non-Preemptive:\n");
    printGanttChart(processesj, n);
    printSchedule(processesj, n);
    float sjfAvgTurnaroundTime = calculateAverageTurnaroundTime(processesj, n);
    float sjfAvgWaitingTime = calculateAverageWaitingTime(processesj, n);
    float sjfAvgResponseTime = calculateAverageResponseTime(processesj, n);
    float sjfAvgThroughputTime = calculateAverageThroughputTime(processesj, n);
    float sjfAvgCPUUtilizationTime = calculateCPUUtilizationTime(processesj, n);
    printf("Average Turnaround Time: %.2f\n", sjfAvgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", sjfAvgWaitingTime);
    printf("Average Response Time: %.2f\n", sjfAvgResponseTime);
    printf("Average Throughput Time: %.2f per time unit\n", sjfAvgThroughputTime);
    printf("Average CPU Utilization: %.2f\n",sjfAvgCPUUtilizationTime );

////////////////////////////////

    // Apply SJF Preemptive algorithm
    struct Process*  processesN = malloc(n * sizeof(struct Process));// holds the new order
  processesN=sjfPreemptive(processes, n);

    // Print SJF Preemptive schedule
    printf("\nSJF Preemptive Algorithm(SRF):\n");
    printGanttChart(processesN, n);
    printSchedule(processesN, n);
    float sjfPPAvgTurnaroundTime = calculateAverageTurnaroundTime(processesN, n);
    float sjfPPAvgWaitingTime = calculateAverageWaitingTime(processesN, n);
     float sjfPPAvgResponseTime = processesN->responseTime;
     float sjfPPAvgThroughputTime = calculateAverageThroughputTime(processesN, n);
     float sjfPPAvgCPUUtilizationTime = calculateCPUUtilizationTime(processesN, n);
    printf("Average Turnaround Time: %.2f\n", sjfPPAvgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", sjfPPAvgWaitingTime);
    printf("Average Response Time: %.2f\n", processesN->responseTime);
    printf("Average Throughput Time: %.2f per time unit\n", sjfPPAvgThroughputTime);
    printf("Average CPU Utilization: %.2f\n",sjfPPAvgCPUUtilizationTime );
free(processesN);


////////////////////////////////////

        // Apply RR algorithm
    struct Process*  processesR = malloc(n * sizeof(struct Process));// holds the new order

    processesR=RR(processes, n, quantum);

    // Print RR schedule
    printf("\nRound Robin Algorithm( Same Arrival Time = 0):\n");
    printGanttChart(processesR, n);
    printSchedule(processesR, n);
    float rrAvgTurnaroundTime = calculateAverageTurnaroundTime(processesR, n);
    float rrAvgWaitingTime = calculateAverageWaitingTime(processesR, n);
    float rrAvgResponseTime = calculateAverageResponseTime(processesR, n);
    float rrAvgThroughputTime = calculateAverageThroughputTime(processesR, n);
    float rrAvgCPUUtilizationTime = calculateCPUUtilizationTime(processesR, n);


    printf("Average Turnaround Time: %.2f\n", rrAvgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", rrAvgWaitingTime);
    printf("Average Ressponse Time: %.2f\n", rrAvgResponseTime);
    printf("Average Throughput Time: %.2f per time unit\n ", rrAvgThroughputTime);
    printf("Average CPU Utilization Time: %.2f\n", rrAvgCPUUtilizationTime);


///////////////////////////

///////////////////////////////////




    // apply priority algorithm
        struct Process*  processesp = malloc(n * sizeof(struct Process));// holds the new order


processesp=priorityNonPreemptive(processes, n);

        // Print priority schedule
    printf("\npriority Algorithm :\n");
    printf("\n-> 0 is the Highest priority <-\n");

    printGanttChart(processesp, n);
    printSchedule(processesp, n);
    float priAvgTurnaroundTime = calculateAverageTurnaroundTime(processesp, n);
    float priAvgWaitingTime = calculateAverageWaitingTime(processesp, n);
     float priAvgResponseTime = processesp->responseTime;
     float priAvgThroughputTime = calculateAverageThroughputTime(processesp, n);
      float priAvgCPUUtilizationTime = calculateCPUUtilizationTime(processesp, n);
    printf("Average Turnaround Time: %.2f\n", priAvgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", priAvgWaitingTime);
    printf("Average Response Time: %.2f\n", processesp->responseTime);
    printf("Average Throughput Time: %.2f per time unit\n", priAvgThroughputTime);
    printf("Average CPU Utilization: %.2f\n",priAvgCPUUtilizationTime );




    printf("                                  COMPARISON\n                           ");


                                                ///////////////////////////////////////////////////////
                     // Find the algorithm with the minimum average turnaround time
    float minAvgTurnaroundTime = fcfsAvgTurnaroundTime;
    int minAvgTurnaroundTimeIndex = 0;
    if (sjfAvgTurnaroundTime < minAvgTurnaroundTime) {
        minAvgTurnaroundTime = sjfAvgTurnaroundTime;
        minAvgTurnaroundTimeIndex = 1;
    }
    if (rrAvgTurnaroundTime < minAvgTurnaroundTime) {
        minAvgTurnaroundTime = rrAvgTurnaroundTime;
        minAvgTurnaroundTimeIndex = 2;
    }
    if (priAvgTurnaroundTime < minAvgTurnaroundTime) {
        minAvgTurnaroundTime = priAvgTurnaroundTime;
        minAvgTurnaroundTimeIndex = 3;
    }

        if (sjfPPAvgTurnaroundTime < minAvgTurnaroundTime) {
        minAvgTurnaroundTime = sjfPPAvgTurnaroundTime;
        minAvgTurnaroundTimeIndex = 4;
    }


    // Print the algorithm with the minimum average turnaround time
    printf("\nAlgorithm with Minimum Average Turnaround Time: ");
    switch (minAvgTurnaroundTimeIndex) {
        case 0:
            printf("FCFS");
            break;
        case 1:
            printf("SJF Non-Preemptive");
            break;
        case 2:
            printf("Round Robin");
            break;
        case 3:
            printf("Priority Scheduling");
            break;
        case 4:
            printf("SJF Preemptive Scheduling");
            break;
    }
        printf("\n");


    // Find the algorithm with the minimum average waiting time
    float minAvgWaitingTime = fcfsAvgWaitingTime;
    int minAvgWaitingTimeIndex = 0;
    if (sjfAvgWaitingTime < minAvgWaitingTime) {
        minAvgWaitingTime = sjfAvgWaitingTime;
        minAvgWaitingTimeIndex = 1;
    }
    if (rrAvgWaitingTime < minAvgWaitingTime) {
        minAvgWaitingTime = rrAvgWaitingTime;
        minAvgWaitingTimeIndex = 2;
    }
    if (priAvgWaitingTime < minAvgWaitingTime) {
        minAvgWaitingTime = priAvgWaitingTime;
        minAvgWaitingTimeIndex = 3;
    }
    if (sjfPPAvgWaitingTime < minAvgWaitingTime) {
        minAvgWaitingTime = sjfPPAvgWaitingTime;
        minAvgWaitingTimeIndex = 4;
    }

    // Print the algorithm with the minimum average waiting time
    printf("Algorithm with Minimum Average Waiting Time: ");
    switch (minAvgWaitingTimeIndex) {
        case 0:
            printf("FCFS");
            break;
        case 1:
            printf("SJF Non-Preemptive");
            break;
        case 2:
            printf("Round Robin");
            break;
        case 3:
            printf("Priority Scheduling");
            break;
        case 4:
            printf("SJF Preemptive Scheduling");
            break;


    }
                printf("\n");


//printf("Round Robin algorithm has the better (Minimum )Response Time ");

 // Find the algorithm with the minimum average response time
    float minAvgResponseTime = fcfsAvgResponseTime;
    int minAvgResponseTimeIndex = 0;
    if (sjfAvgResponseTime < minAvgResponseTime) {
        minAvgResponseTime = sjfAvgResponseTime;
        minAvgResponseTimeIndex = 1;
    }
    if (rrAvgResponseTime < minAvgResponseTime) {
        minAvgResponseTime = rrAvgResponseTime;
        minAvgResponseTimeIndex = 2;
    }
    if (priAvgResponseTime < minAvgResponseTime) {
        minAvgResponseTime = priAvgResponseTime;
        minAvgResponseTimeIndex = 3;
    }
    if (sjfPPAvgResponseTime < minAvgResponseTime) {
        minAvgResponseTime = sjfPPAvgResponseTime;
        minAvgResponseTimeIndex = 4;
    }

    // Print the algorithm with the minimum average response time
    printf("Algorithm with Minimum Average response Time: ");
    switch (minAvgResponseTimeIndex) {
        case 0:
            printf("FCFS");
            break;
        case 1:
            printf("SJF Non-Preemptive");
            break;
        case 2:
            printf("Round Robin");
            break;
        case 3:
            printf("Priority Scheduling");
            break;
        case 4:
            printf("SJF Preemptive Scheduling");
            break;


    }
                printf(" It should be RR\n");


/*
     // Find the algorithm with the minimum average throughput time
    float minAvgThroughputTime = fcfsAvgThroughputTime;
    int minAvgThroughputTimeIndex = 0;
    if (sjfAvgThroughputTime < minAvgThroughputTime) {
        minAvgThroughputTime = sjfAvgThroughputTime;
        minAvgResponseTimeIndex = 1;
    }
    if (rrAvgThroughputTime < minAvgThroughputTime) {
        minAvgThroughputTime = rrAvgThroughputTime;
        minAvgThroughputTimeIndex = 2;
    }
    if (priAvgThroughputTime < minAvgThroughputTime) {
        minAvgThroughputTime = priAvgThroughputTime;
        minAvgThroughputTimeIndex = 3;
    }
    if (sjfPPAvgThroughputTime < minAvgThroughputTime) {
        minAvgThroughputTime = sjfPPAvgThroughputTime;
        minAvgThroughputTimeIndex = 4;
    }


    // Print the algorithm with the minimum average throughput time
    printf("Algorithm with Maximum  Throughput Time: ");
    switch (minAvgThroughputTimeIndex) {
        case 0:
            printf("FCFS");
            break;
        case 1:
            printf("SJF Non-Preemptive");
            break;
        case 2:
            printf("Round Robin");
            break;
        case 3:
            printf("Priority Scheduling");
            break;
        case 4:
            printf("SJF Preemptive Scheduling");


            break;
    }
                printf("\n");

 // Find the algorithm with the minimum average cpu utilization time
    float minAvgCPUUtilizationTime = fcfsAvgCPUUtilizationTime;
    int minAvgCPUUtilizationTimeIndex = 0;
    if (sjfAvgCPUUtilizationTime < minAvgCPUUtilizationTime) {
        minAvgCPUUtilizationTime = sjfAvgCPUUtilizationTime;
        minAvgResponseTimeIndex = 1;
    }
    if (rrAvgCPUUtilizationTime < minAvgCPUUtilizationTime) {
        minAvgCPUUtilizationTime = rrAvgCPUUtilizationTime;
        minAvgCPUUtilizationTimeIndex = 2;
    }
    if (priAvgCPUUtilizationTime < minAvgCPUUtilizationTime) {
        minAvgCPUUtilizationTime = priAvgCPUUtilizationTime;
        minAvgCPUUtilizationTimeIndex = 3;
    }
    if (sjfPPAvgCPUUtilizationTime < minAvgCPUUtilizationTime) {
        minAvgCPUUtilizationTime = sjfPPAvgCPUUtilizationTime;
        minAvgCPUUtilizationTimeIndex = 4;
    }


    // Print the algorithm with the minimum average cpu utilization time
    printf("Algorithm with Maximum  CPU Time: ");
    switch (minAvgCPUUtilizationTimeIndex) {
        case 0:
            printf("FCFS");
            break;
        case 1:
            printf("SJF Non-Preemptive");
            break;
        case 2:
            printf("Round Robin");
            break;
        case 3:
            printf("Priority Scheduling");
            break;
        case 4:
            printf("SJF Preemptive Scheduling");
            break;


    }
                printf("\n");

*/


    // Free allocated memory

    printf("\n                                   THE END\n ");
    free(processes);

    return 0;
}

/*
void printGanttChartRR(struct Process* processes, int n, int quantum) {

    int sum = 0;
    for(int i = 0; i < n ; i++){
        int q = processes[i].burstTime;
        while(q > 0){
            q -= quantum;
            sum += 1;
        }
    }


   int max_burstTime = processes[0].burstTime;

   for(int i = 0; i < n ; i++){

       if(processes[i].burstTime > max_burstTime){
           max_burstTime = processes[i].burstTime;
       }

   }

   int nums [n][max_burstTime];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < max_burstTime; ++j) {
            nums[i][j] = 0;

        }
    }

    for (int i = 0; i < n; ++i) {
        int b = processes[i].burstTime;
        for (int j = 0; j < max_burstTime; ++j) {
            if(b >= quantum){
                nums[i][j] = quantum;
            }
            else if(b <= 0 && b < quantum){
                nums[i][j] = b;

            } else{
                nums[i][j] = 0;

            }
        }
    }



    printf("\nGantt Chart:\n");






   /* printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");








    for (int i = 0 ; i < sum;i++){
        for(int j = 0 ; j < max_burstTime ; j++){
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < nums[k][j]; ++l) {
                    printf(" ");
                }
                printf("P%d", processes[n].processNumber);

                for (int l = 0; l < nums[k][j]; ++l) {
                    printf(" ");
                }
                printf("|");


            }
        }
    }
    printf("\n ");




    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime - 1; j++)
            printf(" ");
        printf("P%d", processes[i].processNumber);
        for (int j = 0; j < processes[i].burstTime - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");


}
 */
