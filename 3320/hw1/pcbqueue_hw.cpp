#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// MAX size of PCB queue
const int MAX_PCB_SIZE = 10;

// PCB structure (PCD dictionary)
struct PCB {
    int pid;
    char status[MAX_PCB_SIZE];
    int priority;
};

// PCB Queue class
class PCBQueue {
    private:
        PCB queue[MAX_PCB_SIZE]; // array to hold PCBs
        int first, last, count; // first and last index, count of PCBs in queue

    public:
        PCBQueue(){
            first = 0;
            last = -1;
            count = 0;
        }

        bool isEmpty() {
            return count == 0;
        }

        bool isFull() {
            return count == MAX_PCB_SIZE;
        }

        // func to add to the queue
        void add(const PCB& pcb) {
            if (isFull()) {
                cout << "Queue is full, cannot add PCB" << endl;
                return;
            }
            last = (last + 1) % MAX_PCB_SIZE; // circular list (if last becomes MAX then it goes to 0)
            queue[last] = pcb; // add pcd to the queue at new last
            count++; // increment to compare with isEmpty and isFull
        }

        // func to remove from queue
        void remove() {
            if (isEmpty()) {
                cout << "Queue is empty, cannot remove PCB" << endl;
                return;
            }
            first = (first + 1) % MAX_PCB_SIZE; // circular list (if first becomes MAX then it goes to 0)
            count--; // decrement to compare with isEmpty and isFull
        }

        void printQueue() {
            if (isEmpty()) {
                cout << "Queue is empty" << endl;
                return;
            }
            cout << "PCB Queue: " << endl;
            cout << left << setw(7) << "PID:" 
                 << left << setw(12) << "| Status:"
                 << left << setw(12) << "| Priority:" << endl;
            for (int i = 0; i < count; i++) {
                int index = (first + i) % MAX_PCB_SIZE; // circular indexing
                cout << left << setw(7) << queue[index].pid << "| "
                     << left << setw(10) << queue[index].status << "| "
                     << left << setw(10) << queue[index].priority << endl;
            }
        }
    };

int main(){
    //declaration
    PCBQueue pcbQueue;
    ifstream infile("data.txt");

    //if file not found == cout error
    if(!infile){
        cout << "Error opening file" << endl;
        return 1;
    }

    PCB newPCB;
    //loop to read from a file and assign values to newPCB(pid, status, priority)
    while(infile >> newPCB.pid >> newPCB.status >> newPCB.priority){
        pcbQueue.add(newPCB);
    }
    pcbQueue.printQueue();
    infile.close();
    return 0;
}