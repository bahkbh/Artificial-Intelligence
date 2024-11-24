#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <cmath>
#define NUM 10           // Number of processes
#define QUANTUM 0.01     // Time quantum, in seconds (10ms)
#define sleeping_time 70000  // Sleeping time, in microseconds (0 for no sleep)

using namespace std;

// Process structure
typedef struct {
    pid_t pid;         // Process ID
    int id;
    int flag = 0;      // Flag for process state
    int context;   // Context switch count
    float CPU_time;    // Total CPU time
    float IO_time;     // Total IO time
    float turnaround;  // Turnaround time
    float waiting;     // Waiting time
    float response;    // Response time
    float CPU_burst;   // CPU burst time
    float IO_start;    // IO start time
    float IO_burst;    // IO burst time
} PROCESS;

// Process Control Block (PCB)
typedef struct {
    bool flag;         // Flag to check if CPU burst time remains
    pid_t pid;         // Child process ID
    float CPU_remain;  // Remaining CPU time
    float IO_remain;   // Remaining IO time
} PCB;

// Message structure for IPC
typedef struct {
    long msg_type;  // Message type
    PCB pcb;        // Process Control Block
} MSG;

int main() {
    PROCESS* child[NUM];                    // Array to hold child process information
    pid_t parentPID = getpid();            // Store parent process ID
    pid_t pid;                             // Variable for child process ID
    int st;                                // Status variable for process termination
    int context_num = 0;                   // Counter for context switches
    srand(static_cast<unsigned int>(getpid())); // Seed random number generator

    // Create 10 Child Processes
    for (int i = 0; i < NUM; i++) {
        child[i] = new PROCESS;
        pid = fork(); // Create a new process
        int random_number = rand() % 100;
        int rnum; // Random number for probabilistic IO occurrence (30% chance)
        if (random_number < 70) 
            rnum = 0; // No IO
        else 
            rnum = 1; // IO occurs

        child[i]->pid = pid; 
        // Assign random CPU burst time (less than 2 sec)
        child[i]->CPU_burst = 1 + 0.001 * (rand() % 1000); 
        // Determine IO start time, probabilistically near the time quantum for demonstration
        child[i]->IO_start = rnum * 0.01 * QUANTUM * (rand() % 100); 
        child[i]->IO_start = rnum * (child[i]->IO_start * 1000) / 1000.0;
        // Assign random IO burst time, typically longer than a time quantum
        child[i]->IO_burst = rnum * (QUANTUM + 0.001 * (rand() % 1000)); 
        // Initialize process times
        child[i]->CPU_time = child[i]->CPU_burst;
        child[i]->IO_time = child[i]->IO_burst;
        child[i]->flag = 0;
        child[i]->context = 0;
        child[i]->turnaround = 0.0;
        child[i]->waiting = 0.0;
        child[i]->response = 0.0;

    // Handling Child Process
    if (pid == 0) {
        int key_id; // Key ID for message queue
        long msg_type = getpid(); // Message type set to process ID
        float CPU_remain = child[i]->CPU_burst; // Remaining CPU burst time
        float IO_remain = child[i]->IO_burst; // Remaining IO time
        float IO_when = child[i]->IO_start; // IO start time
        MSG msg; // Message structure
        msg.msg_type = msg_type; // Assign message type
        key_id = msgget((key_t)1234, IPC_CREAT | 0666); // Get message queue ID

        // Check if message queue creation failed
        if (key_id == -1) {
            perror("Failed.\n");
            return -1;
        }

        while (CPU_remain > 0) {
            // Receiving messages in Child Process
            if (msgrcv(key_id, &msg, sizeof(PCB), msg_type, 0) != -1) {
                bool isQuantumRemaining = (CPU_remain > QUANTUM);

                CPU_remain -= isQuantumRemaining ? QUANTUM : CPU_remain;
                usleep(sleeping_time);

                msg.pcb.flag = isQuantumRemaining;
                msg.pcb.CPU_remain = CPU_remain;
                msg.pcb.pid = msg_type;
                msgsnd(key_id, &msg, sizeof(PCB), IPC_NOWAIT);
            }
        }
        return 0;
    }
    }
    // Log file setup
    FILE *fp = fopen("schedule_dump.txt", "a");

    // Creating queues
    queue<PROCESS*> readyQ; // Queue for ready processes
    queue<PROCESS*> waitQ; // Queue for processes waiting for I/O
    queue<PROCESS*> terminated; // Queue for terminated processes
    queue<PROCESS*> tempready; // Temporary queue for ready processes
    queue<PROCESS*> tempwait; // Temporary queue for waiting processes
    queue<PROCESS*> tempterminate; // Temporary queue for terminated processes
    queue<PROCESS*> temp; // General temporary queue
    int pid_name[NUM];
    int context_number[NUM] ={0};
    float CPU_burst_time[NUM]; // Array for CPU burst times
    float IO_burst_time[NUM]; // Array for I/O burst times
    float IO_start_time[NUM]; // Array for I/O start times
    float turnaround_time[NUM]; // Array for turnaround times
    float ntime; // Temporary variable for next time calculation
    float burst; // Temporary variable for burst time

    printf("\n[Ready Queue]\n");
    fprintf(fp, "\n[Ready Queue]\n");

    // Initializing queues and process data
    for (int i = 0; i < NUM; i++) {
        child[i]->id = i;
        readyQ.push(*(child+i));
        printf("Process NO.%d - PID: %4d - CPU Burst Time: %.3f - I/O Start Time: %.3f - I/O Burst Time: %.3f\n", i+1, child[i]->pid, child[i]->CPU_burst, child[i]->IO_start ,child[i]->IO_burst);
        fprintf(fp, "Process NO.%d - PID: %4d - CPU Burst Time: %.3f - I/O Start Time: %.3f - I/O Burst Time: %.3f\n", i+1, child[i]->pid, child[i]->CPU_burst, child[i]->IO_start ,child[i]->IO_burst);
        pid_name[i] = child[i]->pid;
        CPU_burst_time[i] = child[i]->CPU_burst;
        IO_burst_time[i] = child[i]->IO_burst;
        IO_start_time[i] = child[i]->IO_start;
    }
    printf("If any process's I/O Burst Time: 0.000 means that the process does not need I/O.\n");
    fprintf(fp, "If any process's I/O Burst Time: 0.000 means that the process does not need I/O.\n");

    // Message queue for IPC
    int key_id; 
    MSG msg;
    key_id = msgget((key_t)1234, IPC_CREAT|0666);
    if (key_id == -1) {
        perror("Failed.\n");
        return 0;
    }

    printf("\n[Process Execution]\n\n");
    fprintf(fp, "\n[Process Execution]\n\n");
    context_num = 0;

    while (!readyQ.empty() || !waitQ.empty()) {
        context_num++;
        printf("Context Switch NO.%d\n", context_num);
        fprintf(fp, "Context Switch NO.%d\n", context_num);

        // Displaying the ready queue
        if (!readyQ.empty()) {
            printf("Ready Queue: [ ");
            fprintf(fp, "Ready Queue: [ ");
            while (!readyQ.empty()) {
                printf("%d ", readyQ.front()->pid);
                fprintf(fp, "%d ", readyQ.front()->pid);
                tempready.push(readyQ.front());
                readyQ.pop();
            }
            printf("]");
            fprintf(fp, "]");
            while (!tempready.empty()) {
                readyQ.push(tempready.front());
                tempready.pop();
            }

        } else {
            printf("\nReady Queue is empty.");
            fprintf(fp, "\nReady Queue is empty");  
        }

        // Displaying the waiting queue
        if (!waitQ.empty()) {
            printf("\nWaiting Queue: [ ");
            fprintf(fp, "\nWaiting Queue: [ ");
            while (!waitQ.empty()) {
                printf("%d ", waitQ.front()->pid);
                fprintf(fp, "%d ", waitQ.front()->pid);
                tempwait.push(waitQ.front());
                waitQ.pop();
                if (waitQ.size() == 1) {
                    printf("%d ", waitQ.front()->pid);
                    tempwait.push(waitQ.front());
                    fprintf(fp, "%d ", waitQ.front()->pid);
                    waitQ.pop();
                }
            }
            while (!tempwait.empty()) {
                waitQ.push(tempwait.front());
                tempwait.pop();
            }
            printf("]");
            fprintf(fp, "]");
        } else {
            printf("\nWaiting Queue is empty.");
            fprintf(fp, "\nWaiting Queue is empty");
        }

        // Retrieving the process at the front of the ready queue
        long execute = readyQ.front()->id; 

        // Displaying information about the process currently using the CPU
        if (!readyQ.empty()) {
            // Calculate the remaining CPU burst time after this execution
            ntime = (child[execute]->IO_start - 2 * QUANTUM >= 0) ? child[execute]->CPU_burst - QUANTUM : (child[execute]->IO_start != 0) ? child[execute]->CPU_burst - child[execute]->IO_start : (child[execute]->CPU_burst - QUANTUM > 0) ? child[execute]->CPU_burst - QUANTUM : 0;

            printf("\nProcess NO.%ld [%d] has been allocated the CPU.", execute + 1, child[execute]->pid);
            fprintf(fp, "\nProcess NO.%ld [%d] has been allocated the CPU.", execute + 1, child[execute]->pid);
            printf("\nRunning Process: Process NO.%ld [%d] - Remain CPU Burst Time: %.3f => %.3f (%.3f sec) - Remain I/O Start Time: %.3f => %.3f - Remain IO burst Time: %.3f\n", execute + 1, child[execute]->pid, child[execute]->CPU_burst, ntime, child[execute]->CPU_burst - ntime, child[execute]->IO_start, (child[execute]->IO_start - QUANTUM >= 0) ? child[execute]->IO_start - QUANTUM : 0, child[execute]->IO_burst);
            fprintf(fp, "\nRunning Process: Process NO.%ld [%d] - Remain CPU Burst Time: %.3f => %.3f (%.3f sec) - Remain I/O Start Time: %.3f => %.3f - Remain IO burst Time: %.3f\n", execute + 1, child[execute]->pid, child[execute]->CPU_burst, ntime, child[execute]->CPU_burst - ntime, child[execute]->IO_start, (child[execute]->IO_start - QUANTUM >= 0) ? child[execute]->IO_start - QUANTUM : 0, child[execute]->IO_burst);
            // Update waiting and turnaround times for all processes in the ready queue
            child[execute]->turnaround -= child[execute]->CPU_burst - ntime;
            child[execute]->waiting -= child[execute]->CPU_burst - ntime;
            while (!readyQ.empty()) {
                long pop = readyQ.front()->id;
                child[pop]->turnaround += child[execute]->CPU_burst - ntime;
                child[pop]->waiting += child[execute]->CPU_burst - ntime;

                temp.push(readyQ.front());
                readyQ.pop();
            }
            readyQ = temp;
            while (!temp.empty()) temp.pop();
            context_number[execute] ++;
            child[execute]->context++;
        } else {
            printf("\nRunning Process: NONE\n");
            fprintf(fp, "\nRunning Process: NONE\n");
        }
        readyQ.pop();

        // Displaying information about the process performing I/O operations
        if (!waitQ.empty()) {
            long io = waitQ.front()->id;
            child[io]->IO_burst += QUANTUM;
            printf("Process NO.%ld [%d] is performing I/O operations.", io + 1, child[io]->pid);
            fprintf(fp, "Process NO.%ld [%d] is performing I/O operations.", io + 1, child[io]->pid);
            printf("\nI/O Process: Process NO.%ld [%d] - Remaining I/O Burst Time: %.3f => %.3f (%.3f sec)\n", io + 1, child[io]->pid, child[io]->IO_burst, (child[io]->IO_burst - QUANTUM > 0) ? child[io]->IO_burst - QUANTUM : 0, child[io]->IO_burst - ((child[io]->IO_burst - QUANTUM > 0) ? child[io]->IO_burst - QUANTUM : 0));
            fprintf(fp, "\nI/O Process: Process NO.%ld [%d] - Remaining I/O Burst Time: %.3f => %.3f (%.3f sec)\n", io + 1, child[io]->pid, child[io]->IO_burst, (child[io]->IO_burst - QUANTUM > 0) ? child[io]->IO_burst - QUANTUM : 0, child[io]->IO_burst - ((child[io]->IO_burst - QUANTUM > 0) ? child[io]->IO_burst - QUANTUM : 0));
            child[io]->IO_burst -= QUANTUM;

        } else {
            printf("I/O Process: NONE\n");
            fprintf(fp, "I/O Process: NONE\n");
        }

        // Displaying information about terminated processes
        if (!terminated.empty()) {
            printf("Terminated Process: [ ");
            fprintf(fp, "Terminated Process: [ ");
            while (!terminated.empty()) {
                printf("%d ", terminated.front()->pid);
                fprintf(fp, "%d ", terminated.front()->pid);
                tempterminate.push(terminated.front());
                terminated.pop();
                if (terminated.size() == 1) {
                    printf("%d ", terminated.front()->pid);
                    fprintf(fp, "%d ", terminated.front()->pid);
                    tempterminate.push(terminated.front());
                    terminated.pop();
                }
            }
            while (!tempterminate.empty()) {
                terminated.push(tempterminate.front());
                tempterminate.pop();
            }
            printf("]");
            fprintf(fp, "]");
        } else {
            printf("There are no terminated processes yet.\n");
            fprintf(fp, "There are no terminated processes yet.\n");
        }
        printf("\n\n");
        fprintf(fp, "\n\n");

        // Send message with process ID
        msg.msg_type = child[execute]->pid;
        msgsnd(key_id, &msg, sizeof(PCB), IPC_NOWAIT);

        // Child Process
        if (msgrcv(key_id, &msg, sizeof(PCB), child[execute]->pid, 0) != -1) {
            if (msg.pcb.flag == true) {
                if (child[execute]->CPU_burst > 0) {
                    if(child[execute]->IO_start == 0){ // If there is no I/O operation, IO Start time == 0
                        child[execute]->CPU_burst -= QUANTUM; // Reduce CPU burst time by the time quantum
                        readyQ.push(child[execute]); // Return process to ready queue after processing

                    }
                    else{ // If there is an I/O operation
                        if (child[execute]->IO_start > QUANTUM) { // If there is enough time before starting I/O
                            child[execute]->CPU_burst -= QUANTUM; // Reduce CPU burst time by the time quantum
                            child[execute]->IO_start -= QUANTUM;
                            readyQ.push(child[execute]); // Return process to ready queue after processing
                        }
                        else{
                            child[execute]->CPU_burst -= child[execute]->IO_start; // Reduce CPU time by the remaining time until I/O starts
                            child[execute]->IO_start = 0; // Set I/O start waiting time to 0
                            waitQ.push(child[execute]); // Process waits in the wait queue

                        }
                    }
                }
                if (!waitQ.empty()){
                    long io = waitQ.front()->id;
                    if (child[io]->IO_burst > 0){
                        child[io]->IO_burst -= QUANTUM;
                    }
                    else{
                        child[io]->IO_burst = 0;
                        waitQ.pop();
                        readyQ.push(child[io]);
                    }
                }
            }
            else {
                child[execute]->CPU_burst = 0;
            }
            if (child[execute]->CPU_burst <= 0) {
                child[execute]->CPU_burst = 0;
                terminated.push(child[execute]);

            }
        }
    } 
    for (int i = 0; i < NUM; i++) {
    delete child[i];
    }
    msgsnd(key_id, &msg, sizeof(PCB), IPC_NOWAIT);
    wait(&st);

    printf("All processes have terminated. CPU scheduling is concluded.\n\n");
    fprintf(fp, "All processes have terminated. CPU scheduling is concluded.\n\n");
    printf("                 [ Scheduling Result ]\n");
    fprintf(fp,"                 [ Scheduling Result ]\n");
    printf("  PID     CBT     IBT     WTT     RPT     TAT    CTS \n");
    fprintf(fp,"  PID     CBT     IBT     WTT     RPT     TAT    CTS \n");
    for (int j = 0; j <NUM ; j++){
        if (j == 0) child[j]->response = 0;
        
        child[j]->waiting -= child[j]->CPU_time;
        if (j > 0){
            child[j]->response = child[j-1]->response + QUANTUM;
            if (IO_burst_time[j-1] && IO_start_time[j-1]){
                child[j]->response -= QUANTUM;
                child[j]->response += IO_start_time[j-1];
            }
        }
        
        printf("%5d  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %5d\n",pid_name[j], child[j]->CPU_time,child[j]->IO_time,child[j]->waiting,child[j]->response,child[j]->turnaround,context_number[j]);
        fprintf(fp,"%5d  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %5d\n",pid_name[j], child[j]->CPU_time,child[j]->IO_time,child[j]->waiting,child[j]->response,child[j]->turnaround,context_number[j]);

    }
    float max_turnaround = 0;
    int sum_context = 0;
    float sum_response = 0;
    float sum_waiting = 0;
    float sum_turnaround = 0;
    for (int k = 0; k < NUM; k++){
        max_turnaround = max(max_turnaround, child[k]->turnaround);
        sum_context += context_number[k];
        sum_response += child[k]->response;
        sum_waiting += child[k]->waiting;
        sum_turnaround += child[k]->turnaround; 

    }
    printf("\nPID: Process ID\nCBT: CPU Burst Time \nIBT: I/O Burst Time \nWTT: Waiting Time\nRPT: Response Time\nTAT: Turnaround Time\nCTS: Context Switch\n\n");
    fprintf(fp, "\nPID: Process ID\nCBT: CPU Burst Time \nIBT: I/O Burst Time \nWTT: Waiting Time\nRPT: Response Time\nTAT: Turnaround Time\nCTS: Context Switch\n\n");

    printf("Total Execution Time:    %.3f\n", max_turnaround);
    printf("Total Context Switch:    %.d\n",sum_context);
    printf("Average Response Time:   %.3f\n", sum_response/(1.0 * NUM));
    printf("Average Waiting Time:    %.3f\n", sum_waiting/(1.0 * NUM));
    printf("Average Turnaround Time: %.3f\n",sum_turnaround/(1.0 * NUM));
    fprintf(fp,"Total Execution Time:    %.3f\n", max_turnaround);
    fprintf(fp,"Total Context Switch:    %.d\n",sum_context);
    fprintf(fp,"Average Response Time:   %.3f\n", sum_response/(1.0 * NUM));
    fprintf(fp,"Average Waiting Time:    %.3f\n", sum_waiting/(1.0 * NUM));
    fprintf(fp,"Average Turnaround Time: %.3f\n",sum_turnaround/(1.0 * NUM));


    fclose(fp);
    return 0;
}
