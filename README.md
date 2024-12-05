# Internal-Memory-Tool
This Memory Tool is a simple utility for educational purposes to demonstrate memory manipulation techniques. It provides functionalities to search, read, write, and manipulate memory contents within specified ranges. It makes use of linux based syscall for memory reading &amp; writing.

## Features
- **Memory Range Setting**: Set the search range to different memory regions.
- **Memory Search**: Search for specific data values within memory.
- **Memory Offset**: Offset memory contents by a specified amount.
- **Memory Write**: Write new data values to memory at specific offsets.

## Usage
1. **Set Search Range**: Use `SetSearchRange()` to specify the memory range for search operations.
2. **Memory Search**: Invoke `MemorySearch()` to search for specific data values in memory
3. **Memory Offset**: Use `MemoryOffset()` to offset memory contents by a given amount.
4. **Memory Write**: Invoke `MemoryWrite()` to write new data values to memory at specific offsets.
5. **Clear Results**: Use `ClearResults()` to clear the results obtained from memory searches.
6. **Clear Map**: Invoke `ClearMap()` to clear the memory map.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributions
Contributions are welcome! Please open an issue or submit a pull request if you have any improvements or bug fixes.
