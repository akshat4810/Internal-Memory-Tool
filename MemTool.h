#ifndef MEMTOOL_H
#define MEMTOOL_H

#include <list>

typedef signed char mbyte;
typedef long long mlong;
typedef unsigned long ulong;

enum Type {
	MEM_DWORD,
	MEM_QWORD,
	MEM_FLOAT,
	MEM_DOUBLE,
	MEM_BYTE
};

enum Range {
	ALL,
	B_BAD,
	C_ALLOC,
	C_BSS,
	C_DATA,
	C_HEAP,
	JAVA_HEAP,
	A_ANONMYOUS,
	CODE_SYSTEM,
	STACK,
	ASHMEM,
	CODE_APP,
	V_VIDEO,
	OTHER
};

namespace MemTool {
    void SetSearchRange(Range range);
    void MemorySearch(const char* value, Type type);
    void MemoryOffset(const char* value, long int offset, Type type);
    void MemoryWrite(const char* value, long int offset, Type type);
    void ClearResults();
    void ClearMap();
}

#endif // MEMTOOL_H
