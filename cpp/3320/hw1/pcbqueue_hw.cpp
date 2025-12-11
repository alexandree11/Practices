/***********************************************************************************
 * Author: Aleksandr An 
 * Date: 9/24/25
 * Program: CPU Queue Sim
 * This program simulates a queue of processes using PCB objects with
 * process id(pid), status and priority. The functions are: add a process
 * (from a file or separately), remove a process, print the queue, clear the
 * queue(not a function, but a separate block for now)
 **********************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// MAX size of PCB queue
const int MAX_PCB_SIZE = 10;

// PCB structure (PCB dictionary)
struct PCB{
    int pid;
    string status;
    int priority;
    int burstTime;
    int arrivalTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    int remainingBurst;
    int base;
    int limit;
};

// PCB Queue class
class PCBQueue{
    private:
        PCB queue[MAX_PCB_SIZE]; // array to hold MAX_PCB_SIZE amount of processes in queue
        int first, last, count; // first and last index, count of processes in queue
        double totalTurnaround, totalWaiting, totalResponse = 0.0;
        double avgTurnaround, avgWaiting, avgResponse;

    public:
        PCBQueue(){
            first = 0;
            last = -1;
            count = 0;
        }

        bool isEmpty(){
            return count == 0;
        }

        bool isFull(){
            return count == MAX_PCB_SIZE;
        }

        int getCount(){
            return count;
        }

        // func to add process to the queue
        void add(const PCB& pcb){
            if (isFull()){
                cout << "Queue is full, cannot add process: " 
                     << "PID: " << pcb.pid << " | " 
                     << "Status: " << pcb.status << " | " 
                     << "Priority: " << pcb.priority << endl;
                return;
            }
            last = (last + 1) % MAX_PCB_SIZE; // extend the tail in circular list (if last becomes MAX then it goes to 0)
            queue[last] = pcb; // add pcd to the queue at new last
            count++; // increment to compare with isEmpty and isFull
        }

        // func to remove process from the queue
        void remove(){
            if (isEmpty()){
                cout << "Queue is empty, cannot remove process" << endl;
                return;
            }
            first = (first + 1) % MAX_PCB_SIZE; // circular list (if first becomes MAX then it goes to 0)
            count--; // decrement to compare with isEmpty and isFull
        }

        void printQueue(){
            if (isEmpty()){
                cout << "Queue is empty" << endl;
                return;
            }
            cout << "PCB Queue: " << endl;
            cout << left << setw(7) << "PID:" 
                 << left << setw(12) << "| Status:"
                 << left << setw(12) << "| Priority:" << endl;
            for (int i = 0; i < count; i++){
                int index = (first + i) % MAX_PCB_SIZE; // circular indexing
                cout << left << setw(7) << queue[index].pid << "| "
                     << left << setw(10) << queue[index].status << "| "
                     << left << setw(10) << queue[index].priority << endl;
            }
            cout << endl;
        }

        void clearQueue(){
            count = 0;
            first = 0;
            last = -1;
        }

        // func to print the scheduler info for fifo
        void saveResults(){
            if (isEmpty()){
                cout << "No ready processes in" << endl;
                return;
            }

            ofstream outfile("table_sjf.txt"); // create a table_fifo.txt file to save the results

            if(!outfile)
                cout << "Something went wrong with the file" << endl;

            outfile << left << setw(7) << "PID:" 
                 << left << setw(10) << "| Burst"
                 << left << setw(11) << "| Arrival" 
                 << left << setw(14) << "| Completion"
                 << left << setw(14) << "| Turnaround"
                 << left << setw(11) << "| Waiting" 
                 << left << setw(12) << "| Response" << endl;
            for (int i = 0; i < count; i++){
                int index = (first + i) % MAX_PCB_SIZE; // circular indexing
                outfile << left << setw(7) << queue[index].pid << "| "
                     << left << setw(8) << queue[index].burstTime << "| "
                     << left << setw(9) << queue[index].arrivalTime << "| "
                     << left << setw(12) << queue[index].completionTime << "| " 
                     << left << setw(12) << queue[index].turnaroundTime << "| "
                     << left << setw(9) << queue[index].waitingTime << "| "
                     << left << setw(10) << queue[index].responseTime << endl;
            }

            outfile << "Average turnaround time: " << avgTurnaround << endl;
            outfile << "Average waiting time: " << avgWaiting << endl;
            outfile << "Average response time: " << avgResponse << endl;

            outfile.close();
        }

        void saveResultsFIFO() { saveResultsTo("table_fifo.txt"); }
        void saveResultsRR()   { saveResultsTo("table_rr.txt"); }
        void saveResultsSJF()  { saveResultsTo("table_sjf.txt"); }
        // func to compute the timings for fifo
        // completion = end = arrival + wait + burst
        // turnaround = end - arrival
        // wait time = end - arrival - burst
        // response = wait + arrival
        void computeTimesFifo(){
            int currentTime = 0;
            for(int i = 0; i < count; i++){
                int index = (first + i) % MAX_PCB_SIZE;
                if(currentTime < queue[index].arrivalTime)
                    currentTime = queue[index].arrivalTime;

                queue[index].completionTime = currentTime + queue[index].burstTime;
                queue[index].turnaroundTime = queue[index].completionTime - queue[index].arrivalTime;
                queue[index].waitingTime = queue[index].completionTime - queue[index].burstTime - queue[index].arrivalTime;
                queue[index].responseTime = queue[index].waitingTime + queue[index].arrivalTime;
                currentTime = queue[index].completionTime;
                totalTurnaround += queue[index].turnaroundTime;
                totalWaiting += queue[index].waitingTime;
                totalResponse += queue[index].responseTime;
            }
            avgTurnaround = totalTurnaround/count;
            avgWaiting = totalWaiting/count;
            avgResponse = totalResponse/count;
        }

        void computeTimesRR() {
            int timeSlice = 2;
            int currentTime = 0;
            int countCompleted = 0;

            // reset totals
            totalTurnaround = totalWaiting = totalResponse = 0;

            // initialize processes
            for(int i = 0; i < count; i++) {
                int index = (first + i) % MAX_PCB_SIZE;
                queue[index].remainingBurst = queue[index].burstTime;
                queue[index].responseTime = -1;
                queue[index].status = "READY";
            }

            while(countCompleted < count) {

                for(int i = 0; i < count; i++) {
                    int index = (first + i) % MAX_PCB_SIZE;

                    if(queue[index].status == "COMPLETED")
                        continue;

                    if(queue[index].arrivalTime > currentTime)
                        continue;

                    // response time on FIRST service
                    if(queue[index].responseTime == -1)
                        queue[index].responseTime = currentTime - queue[index].arrivalTime;

                    if(queue[index].remainingBurst > timeSlice) {
                        queue[index].remainingBurst -= timeSlice;
                        currentTime += timeSlice;
                    }
                    else {
                        currentTime += queue[index].remainingBurst;
                        queue[index].remainingBurst = 0;

                        queue[index].completionTime = currentTime;
                        queue[index].turnaroundTime = currentTime - queue[index].arrivalTime;
                        queue[index].waitingTime = queue[index].turnaroundTime - queue[index].burstTime;

                        queue[index].status = "COMPLETED";

                        totalTurnaround += queue[index].turnaroundTime;
                        totalWaiting += queue[index].waitingTime;
                        totalResponse += queue[index].responseTime;

                        countCompleted++;
                    }
                }
            }

            avgTurnaround = totalTurnaround / count;
            avgWaiting = totalWaiting / count;
            avgResponse = totalResponse / count;
        }

        void computeTimesSJF() {
            int currentTime = 0;
            int countCompleted = 0;

            totalTurnaround = totalWaiting = totalResponse = 0;

            // initialize
            for (int i = 0; i < count; i++) {
                int index = (first + i) % MAX_PCB_SIZE;
                queue[index].remainingBurst = queue[index].burstTime;
                queue[index].responseTime = -1;
                queue[index].status = "READY";
            }

            while (countCompleted < count) {

                int bestIndex = -1;
                int bestBurst = 999999;        // VERY LARGE NUMBER

                // find the shortest available job
                for (int i = 0; i < count; i++) {
                    int index = (first + i) % MAX_PCB_SIZE;

                    if (queue[index].status == "COMPLETED")
                        continue;

                    if (queue[index].arrivalTime <= currentTime &&
                        queue[index].burstTime < bestBurst)
                    {
                        bestBurst = queue[index].burstTime;
                        bestIndex = index;
                    }
                }

                // If no job has arrived yet → jump currentTime
                if (bestIndex == -1) {
                    int nextArrival = 999999;   // VERY LARGE NUMBER

                    for (int i = 0; i < count; i++) {
                        int index = (first + i) % MAX_PCB_SIZE;

                        if (queue[index].status != "COMPLETED" &&
                            queue[index].arrivalTime > currentTime)
                        {
                            // manually compare instead of min()
                            if (queue[index].arrivalTime < nextArrival)
                                nextArrival = queue[index].arrivalTime;
                        }
                    }

                    currentTime = nextArrival;
                    continue;
                }

                // set response time on first run
                if (queue[bestIndex].responseTime == -1)
                    queue[bestIndex].responseTime = currentTime - queue[bestIndex].arrivalTime;

                // run to completion
                currentTime += queue[bestIndex].burstTime;

                queue[bestIndex].completionTime = currentTime;
                queue[bestIndex].turnaroundTime = currentTime - queue[bestIndex].arrivalTime;
                queue[bestIndex].waitingTime = queue[bestIndex].turnaroundTime - queue[bestIndex].burstTime;

                queue[bestIndex].status = "COMPLETED";

                totalTurnaround += queue[bestIndex].turnaroundTime;
                totalWaiting += queue[bestIndex].waitingTime;
                totalResponse += queue[bestIndex].responseTime;

                countCompleted++;
            }

            avgTurnaround = totalTurnaround / count;
            avgWaiting = totalWaiting / count;
            avgResponse = totalResponse / count;
        }
    };

bool loadQueueFromFile(const string &filename, PCBQueue &q) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    q.clearQueue();

    PCB filePCB;
    // try to read 5 or 6 fields: if LIMIT is present it's read, otherwise default limit=0
    while (infile >> filePCB.pid >> filePCB.status >> filePCB.priority >> filePCB.burstTime >> filePCB.arrivalTime) {
        // attempt to read limit if present (peek)
        // we'll set default limit = 0 so it doesn't break previous code
        filePCB.limit = 0;
        filePCB.base = -1;
        filePCB.completionTime = 0;
        filePCB.turnaroundTime = 0;
        filePCB.waitingTime = 0;
        filePCB.responseTime = -1;
        filePCB.remainingBurst = 0;
        filePCB.status = filePCB.status; // keep as read (NEW or READY)
        q.add(filePCB);
    }
    infile.close();
    return true;
}

int main(){
    //declaration
    PCBQueue scheduledQueue;
    ifstream infile("data_rr_sjf.txt"); //file should be in the same folder as .cpp file or enter the full path

    //if file not found == cout error
    if(!infile){
        cout << "Error opening file" << endl;
        return 1;
    }

    PCB filePCB;
    //loop to read from a file and assign values to filePCB(pid, status, priority)
    //then add the PCB object to the queue
    //repeat while end of the file is not reached and print the queue at the end of the loop
    while(infile >> filePCB.pid >> filePCB.status >> filePCB.priority >> filePCB.burstTime >> filePCB.arrivalTime){
        scheduledQueue.add(filePCB);
    }
    infile.close();

    // scheduledQueue.computeTimesFifo();
    scheduledQueue.computeTimesSJF();
    scheduledQueue.saveResults();

    // scheduledQueue.clearQueue();

    // scheduledQueue.printFifo();

    return 0;
}