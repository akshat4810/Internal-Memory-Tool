# Internal-Memory-Tool
This Memory Tool is a simple utility for educational purposes to demonstrate memory manipulation techniques. It provides functionalities to search, read, write, and manipulate memory contents within specified ranges. It makes use of linux based syscall for memory reading &amp; writing.

## Features
- **Memory Search**: Search for specific data values within memory.
- **Memory Offset**: Offset memory contents by a specified amount.
- **Memory Write**: Write new data values to memory at specific offsets.
- **Memory Range Setting**: Set the search range to different memory regions.

## Usage
1. **Initialization**: Call `initMemTool()` to initialize the memory tool.
2. **Set Search Range**: Use `SetSearchRange()` to specify the memory range for search operations.
3. **Memory Search**: Invoke `MemorySearch()` to search for specific data values in memory
4. **Memory Offset**: Use `MemoryOffset()` to offset memory contents by a given amount.
5. **Memory Write**: Invoke `MemoryWrite()` to write new data values to memory at specific offsets.
6. **Clear Results**: Use `ClearResults()` to clear the results obtained from memory searches.
7. **Clear Map**: Invoke `ClearMap()` to clear the memory map.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributions
Contributions are welcome! Please open an issue or submit a pull request if you have any improvements or bug fixes.
