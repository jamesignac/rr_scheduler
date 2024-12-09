#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Process structure
struct Process {
    int pid;               // Process ID
    int arrivalTime;       // Arrival time
    int burstTime;         // Burst time
    int remainingTime;     // Remaining burst time
    int completionTime;    // Completion time
    int waitingTime;       // Waiting time
    int turnaroundTime;    // Turnaround time
};

// Function to clear input buffer in case of invalid input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to validate integer input
int getValidatedInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < 0) {
            cout << "Invalid input! Please enter a non-negative integer.\n";
            clearInput();
        } else {
            return value;
        }
    }
}

// Function to calculate metrics
void calculateMetrics(vector<Process>& processes, int totalTime, int contextSwitchTime) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    int n = processes.size();

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& process : processes) {
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
        cout << "P" << process.pid << "\t"
             << process.arrivalTime << "\t"
             << process.burstTime << "\t"
             << process.completionTime << "\t"
             << process.turnaroundTime << "\t"
             << process.waitingTime << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n << endl;
    cout << "Average Waiting Time: " << totalWaitingTime / n << endl;
    cout << "CPU Utilization: " << fixed << setprecision(2)
         << ((double)(totalTime - (contextSwitchTime * (n - 1))) / totalTime) * 100 << "%\n";
}

// Round Robin Scheduling function
void roundRobinScheduler(vector<Process>& processes, int quantum, int contextSwitchTime) {
    int n = processes.size();
    queue<int> readyQueue;
    int time = 0, completed = 0;

    // Enqueue processes based on arrival time
    vector<bool> isInQueue(n, false);
    for (int i = 0; i < n; ++i) {
        if (processes[i].arrivalTime <= time) {
            readyQueue.push(i);
            isInQueue[i] = true;
        }
    }

    while (completed < n) {
        if (readyQueue.empty()) {
            // No process ready, increment time
            time++;
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        // Execute the process
        int executionTime = min(quantum, processes[idx].remainingTime);
        processes[idx].remainingTime -= executionTime;
        time += executionTime;

        // Check if process has completed
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = time;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }

        // Add new arrivals to the queue
        for (int i = 0; i < n; ++i) {
            if (!isInQueue[i] && processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                readyQueue.push(i);
                isInQueue[i] = true;
            }
        }

        // Requeue process if not completed
        if (processes[idx].remainingTime > 0) {
            readyQueue.push(idx);
        }

        // Increment time for context switch if queue is not empty
        if (!readyQueue.empty()) {
            time += contextSwitchTime;
        }
    }

    calculateMetrics(processes, time, contextSwitchTime);
}

// Main function
int main() {
    int n, quantum, contextSwitchTime;

    n = getValidatedInput("Enter number of processes: ");

    vector<Process> processes(n);

    // Input process details, give each process a unique Process ID
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ":\n";
        processes[i].arrivalTime = getValidatedInput("  Arrival time: ");
        processes[i].burstTime = getValidatedInput("  Burst time: ");
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Input simulation details
    quantum = getValidatedInput("Enter time quantum: ");
    contextSwitchTime = getValidatedInput("Enter context switch time: ");

    roundRobinScheduler(processes, quantum, contextSwitchTime);

    return 0;
}