# rr_scheduler
Round Robin Scheduler simulator for my Operating Systems (CISC 3595) course, Fall 2024.

# Round Robin Scheduling Simulator

This program simulates a **Round Robin Scheduling Algorithm** with user-defined parameters, including time quantum and context switch time. It calculates various process metrics such as waiting time, turnaround time, and completion time, and provides insights into the system's performance, including CPU utilization.

## Features
- Handles **n processes** with customizable arrival times and burst times.
- Incorporates **context switching** and calculates its effect on CPU utilization.
- Displays process metrics:
  - Completion Time (CT)
  - Turnaround Time (TAT)
  - Waiting Time (WT)
- Computes **average waiting time**, **average turnaround time**, and **CPU utilization**.

---

## Getting Started

### Prerequisites
- A C++ compiler that supports C++11 or later (e.g., `g++`).

### Installation
1. Clone or download the source code file.
2. Save the code in a file named `round_robin.cpp`.

---

## Compilation and Execution

### Compile the Program
To compile the program, open a terminal or command prompt and run the following command:
```bash
g++ -o round_robin round_robin.cpp

./round_robin

