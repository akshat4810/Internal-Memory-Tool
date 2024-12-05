// Include the MemTool header file to access its functionalities
#include "MemTool.h"

// Import the MemTool namespace for easier access to its functions
using namespace MemTool;

// Function to perform memory write operations
void memwrite() {
  SetSearchRange(Range::A_ANONMYOUS); // Set the search range to anonymous memory regions
	MemorySearch("0.0060901641845703125", Type::MEM_FLOAT); // Search for a specific floating-point value in the memory
	MemoryOffset("2.2840499877929688E-4", -4, Type::MEM_FLOAT); // Offset the memory by a certain value and type
	MemoryOffset("23.52225685119629", -8, Type::MEM_FLOAT);
	MemoryWrite("200", -4, Type::MEM_FLOAT); // Write new values to memory at specific offsets and type
	MemoryWrite("100", -8, Type::MEM_FLOAT);
	ClearResults(); // Clear the results obtained from memory searches
}

// Main thread function
void * main_thread(void *) {
	memwrite();
	return 0;
}

// Constructor function to automatically start the main thread when the library is loaded
__attribute__((constructor)) void _init() {
    // Create a new thread to execute the main_thread function and detach it
    std::thread mainThread(main_thread, nullptr);
    mainThread.detach();
}
