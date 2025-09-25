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
};

// PCB Queue class
class PCBQueue{
    private:
        PCB queue[MAX_PCB_SIZE]; // array to hold MAX_PCB_SIZE amount of processes in queue
        int first, last, count; // first and last index, count of processes in queue

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

        // func to add process to the queue
        void add(const PCB& pcb){
            if (isFull()){
                cout << "Queue is full, cannot add process: " 
                     << "PID: " << pcb.pid << " | " 
                     << "Status: " << pcb.status << " | " 
                     << "Priority: " << pcb.priority << endl << endl;
                return;
            }
            last = (last + 1) % MAX_PCB_SIZE; // extend the tail in circular list (if last becomes MAX then it goes to 0)
            queue[last] = pcb; // add pcd to the queue at new last
            count++; // increment to compare with isEmpty and isFull
        }

        // func to remove process from the queue
        void remove(){
            if (isEmpty()){
                cout << "Queue is empty, cannot remove process" << endl << endl;
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
    };

int main(){
    //declaration
    PCBQueue pcbQueue;
    ifstream infile("data.txt"); //file should be in the same folder as .cpp file or enter the full path

    //if file not found == cout error
    if(!infile){
        cout << "Error opening file" << endl;
        return 1;
    }

    PCB filePCB;
    //loop to read from a file and assign values to filePCB(pid, status, priority)
    //then add the PCB object to the queue
    //repeat while end of the file is not reached and print the queue at the end of the loop
    while(infile >> filePCB.pid >> filePCB.status >> filePCB.priority){
        pcbQueue.add(filePCB);
    }
    infile.close();
    pcbQueue.printQueue();

    //removing first three added processes
    pcbQueue.remove();
    pcbQueue.remove();
    pcbQueue.remove();

    //adding new processes to the queue
    PCB newPCB = {12997, "READY", 6};
    pcbQueue.add(newPCB);
    newPCB = {12998, "RUNNING", 3};
    pcbQueue.add(newPCB);
    newPCB = {12999, "BLOCKED", 9};
    pcbQueue.add(newPCB);

    //this process should not be added since its already 10 processes in the queue
    newPCB = {13000, "READY", 1};
    pcbQueue.add(newPCB);

    pcbQueue.printQueue();

    //to clear the queue (this could be a function)
    while(!pcbQueue.isEmpty()){
        pcbQueue.remove();
    }
    pcbQueue.printQueue();

    cout << "test";

    return 0;
}