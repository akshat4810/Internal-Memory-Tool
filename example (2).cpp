using namepsace MemTool;

void memwrite() {
    SetSearchRange(Range::A_ANONMYOUS);
	MemorySearch("0.0060901641845703125", Type::MEM_FLOAT);
	MemoryOffset("2.2840499877929688E-4", -4, Type::MEM_FLOAT);
	MemoryOffset("23.52225685119629", -8, Type::MEM_FLOAT);
	MemoryWrite("200", -4, Type::MEM_FLOAT);
	MemoryWrite("100", -8, Type::MEM_FLOAT);
	ClearResults();
}

void * main_thread(void *) {
	initMemTool();
	sleep(3);
	memwrite();
	return 0;
}

__attribute__((constructor)) void _init() {
    std::thread mainThread(main_thread, nullptr);
    mainThread.detach();
}