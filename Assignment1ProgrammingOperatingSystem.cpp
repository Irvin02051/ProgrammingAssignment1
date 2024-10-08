#include <iostream>
#include <vector>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iomanip>  // For std::setw

// Constants for memory management
const int TOTAL_PAGES = 100;             // Total number of pages available
const int PAGE_SIZE_MB = 160;            // Size of each page in MB
const int MEMORY_SIZE_MB = TOTAL_PAGES * PAGE_SIZE_MB;  // Total memory in MB
const int STARTING_ADDRESS = 2000;       // Starting memory address
const int MAX_PROCESS_PAGES = 30;        // Max number of pages a process can take
const int PAGE_UNIT = 80;                // Each random number unit represents 80 MB

// Structure to hold process information
struct Process {
    int id;
    int sizeMB;
    int pagesRequired;
    int startingAddress;
    int unusedSpace;
};

// Function to allocate memory for processes
void userMemoryAllocation(std::vector<int>& memory, std::vector<Process>& processes) {
    int currentAddress = STARTING_ADDRESS;
    int processId = 1;
    
    while (true) {
        // Generate a random size for the process (in terms of memory pages)
        int randomPages = (rand() % MAX_PROCESS_PAGES) + 1; // Random between 1 to 30
        int processSizeMB = randomPages * PAGE_UNIT;
        
        // Calculate number of pages required to store the process
        int pagesRequired = (processSizeMB + PAGE_SIZE_MB - 1) / PAGE_SIZE_MB;  // Round up

        // Check if enough pages are available in memory
        int freePages = 0;
        for (int i = 0; i < TOTAL_PAGES; i++) {
            if (memory[i] == 0) freePages++;
        }
        
        if (freePages < pagesRequired) {
            std::cout << "Memory full! No more processes can be allocated.\n";
            break;  // Exit the loop if not enough pages are available
        }

        // Allocate pages to the process
        int allocatedPages = 0;
        for (int i = 0; i < TOTAL_PAGES && allocatedPages < pagesRequired; i++) {
            if (memory[i] == 0) {
                memory[i] = processId;
                allocatedPages++;
            }
        }

        // Calculate unused space
        int totalAllocatedMB = pagesRequired * PAGE_SIZE_MB;
        int unusedSpaceMB = totalAllocatedMB - processSizeMB;

        // Store process information
        Process proc;
        proc.id = processId;
        proc.sizeMB = processSizeMB;
        proc.pagesRequired = pagesRequired;
        proc.startingAddress = currentAddress;
        proc.unusedSpace = unusedSpaceMB;

        processes.push_back(proc);

        // Update the next process starting address
        currentAddress += totalAllocatedMB;
        processId++;
    }
}

// Function to print the summary report
void printSummaryReport(const std::vector<Process>& processes) {
    std::cout << "\nSummary Report:\n";
    std::cout << std::setw(15) << "Process Id" 
              << std::setw(30) << "Starting Memory Address" 
              << std::setw(30) << "Size of the Process MB" 
              << std::setw(30) << "Unused Space MB\n";
    std::cout << std::string(105, '-') << "\n";

    for (const auto& proc : processes) {
        std::cout << std::setw(15) << proc.id 
                  << std::setw(30) << proc.startingAddress 
                  << std::setw(30) << proc.sizeMB 
                  << std::setw(30) << proc.unusedSpace << "\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Memory array where 0 means free and any other number indicates the process ID occupying the page
    std::vector<int> memory(TOTAL_PAGES, 0); 

    // Vector to store the processes
    std::vector<Process> processes;

    // Allocate memory for processes
    userMemoryAllocation(memory, processes);

    // Print the summary report
    printSummaryReport(processes);

    return 0;
}





















