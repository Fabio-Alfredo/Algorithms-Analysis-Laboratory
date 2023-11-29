
#ifndef PCB_HPP
#define PCB_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class PCB
{
private:
    int process_id;
    int virtual_runtime;
    int time_to_complete;

    int RandomProcessID();
    int RandomVirtualRuntime();
    int RandomTimeToComplete(int virtual_runtime);

public:
    PCB();
    // setters
    void SetProcessID(int process_id) { this->process_id = process_id; }
    void SetVirtualRuntime(int virtual_runtime) { this->virtual_runtime = virtual_runtime; }
    void SetTimeToComplete(int time_to_complete) { this->time_to_complete = time_to_complete; }

    // getters
    int GetProcessID() { return process_id; }
    int GetVirtualRuntime() { return virtual_runtime; }
    int GetTimeToComplete() { return time_to_complete; }

    void DisplayPCB();

    void RecalculateTimeToComplete(int time_slice);
    void RecalculateVirtualRuntime(int time_slice);
};



PCB::PCB()
{
    process_id = RandomProcessID();
    virtual_runtime = RandomVirtualRuntime();
    time_to_complete = RandomTimeToComplete(virtual_runtime);
}



// Function to recalculate the time needed to complete a process, taking into account a time slice.
void PCB::RecalculateTimeToComplete(int time_slice) {
    // Check if there is still time left to complete the process
    if (time_to_complete > time_slice) {
        // If time to complete is greater than the time slice, deduct the time slice.
        time_to_complete -= time_slice;
    } else {
        // If the time to complete is less than or equal to the time slice, set it to zero, indicating completion.
        time_to_complete = 0;
    }
}

// Function to update the virtual runtime of a process by adding the time slice.
void PCB::RecalculateVirtualRuntime(int time_slice) {
    // Add the time slice to the virtual runtime to keep track of the process's execution progress.
    virtual_runtime += time_slice;
}



int PCB::RandomProcessID()
{
    return rand() % 10000 + 1;
}

int PCB::RandomVirtualRuntime()
{
    return rand() % 1000 + 1;
}

int PCB::RandomTimeToComplete(int virtual_runtime)
{
    return rand() % 10000 + virtual_runtime;
}

void PCB::DisplayPCB()
{
    cout << "Process ID: " << process_id << endl;
    cout << "Virtual Runtime: " << virtual_runtime << endl;
    cout << "Time to Complete: " << time_to_complete << endl;
}



#endif