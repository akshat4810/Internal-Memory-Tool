#include "MemTool.h"

#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#if defined(__arm__)
#define process_readv_syscall 376
#define process_writev_syscall 377
#elif defined(__aarch64__)
#define process_readv_syscall 270
#define process_writev_syscall 271
#elif defined(__i386__)
#define process_readv_syscall 347
#define process_writev_syscall 348
#else
#define process_readv_syscall 310
#define process_writev_syscall 311
#endif

#define READ_TYPE 0

struct sAddr {
	long int addr;
	long int taddr;
};

int ISize = sizeof(int);
int LSize = sizeof(mlong);
int FSize = sizeof(float);
int DSize = sizeof(double);
int BSize = sizeof(mbyte);
int ULSize = sizeof(ulong);
int GAME_PID = -1;

size_t page_size = 0;

std::list<sAddr> *DataList = new std::list<sAddr>;
std::list<sAddr> *MapList = new std::list<sAddr>;

int pr(void * buff, size_t len, long int addr, long int offset) {
#if READ_TYPE == 0
	struct iovec iov_ReadBuffer[1];
    struct iovec iov_ReadOffset[1];
    iov_ReadBuffer[0].iov_base = buff;
    iov_ReadBuffer[0].iov_len = len;
    iov_ReadOffset[0].iov_base = (void *)(addr + offset);
    iov_ReadOffset[0].iov_len = len;
	/*iovec iov_ReadBuffer {}, iov_ReadOffset {};
	iov_ReadBuffer.iov_base = buff;
	iov_ReadBuffer.iov_len = len;
	iov_ReadOffset.iov_base = (void *)(addr + offset);
	iov_ReadOffset.iov_len = len;*/
	return (int) syscall(process_readv_syscall, GAME_PID, & iov_ReadBuffer, 1, & iov_ReadOffset, 1, 0);
#else
	if (memcpy(buff, (void *)(addr + offset), len) != nullptr)
		return len;
#endif
}

int pw(void * buff, size_t len, long int addr, long int offset) {
#if READ_TYPE == 0
	struct iovec iov_WriteBuffer[1];
    struct iovec iov_WriteOffset[1];
    iov_WriteBuffer[0].iov_base = buff;
    iov_WriteBuffer[0].iov_len = len;
    iov_WriteOffset[0].iov_base = (void *)(addr + offset);
    iov_WriteOffset[0].iov_len = len;
	/*iovec iov_WriteBuffer {}, iov_WriteOffset {};
	iov_WriteBuffer.iov_base = buff;
	iov_WriteBuffer.iov_len = len;
	iov_WriteOffset.iov_base = (void *)(addr + offset);
	iov_WriteOffset.iov_len = len;*/
	return (int) syscall(process_writev_syscall, GAME_PID, & iov_WriteBuffer, 1, & iov_WriteOffset, 1, 0);
#else
	if (memcpy((void *)(addr + offset), buff, len) != nullptr)
		return len;
#endif
	return 0;
}

void MSearchFloat(float value) {
	sAddr pmap {0, 0};
	int c;
	int buffSize = 0x1000 / FSize;
	auto * buff = new float[buffSize];
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = MapList->begin(); pmapsit != MapList->end(); ++pmapsit) {
		c = (int)(pmapsit->taddr - pmapsit->addr) / 0x1000;
		for (int j = 0; j < c; j += 1) {
			pr(buff, 0x1000, pmapsit->addr, j * 0x1000);
			for (int i = 0; i < buffSize; i += 1) {
				if (buff[i] == value) {
					pmap.addr = pmapsit->addr + (j * 0x1000) + (i * FSize);
					DataList->push_back(pmap);
				}
			}
		}
	}
	delete[] buff;
}


void MSearchDword(int value) {
	sAddr pmap {0, 0};
	int c;
	int buffSize = 0x1000 / ISize;
	int * buff = new int[buffSize];
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = MapList->begin(); pmapsit != MapList->end(); ++pmapsit) {
		c = (int)(pmapsit->taddr - pmapsit->addr) / 0x1000;
		for (int j = 0; j < c; j += 1) {
			pr(buff, 0x1000, pmapsit->addr, j * 0x1000);
			for (int i = 0; i < buffSize; i += 1) {
				if (buff[i] == value) {
					pmap.addr = pmapsit->addr + (j * 0x1000) + (i * ISize);
					DataList->push_back(pmap);
				}
			}
		}
	}
	delete[] buff;
}

void MSearchQword(mlong value) {
	sAddr pmap {0, 0};
	int c;
	int buffSize = 0x1000 / LSize;
	auto * buff = new mlong[buffSize];
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = MapList->begin(); pmapsit != MapList->end(); ++pmapsit) {
		c = (int)(pmapsit->taddr - pmapsit->addr) / 0x1000;
		for (int j = 0; j < c; j += 1) {
			pr(buff, 0x1000, pmapsit->addr, j * 0x1000);
			for (int i = 0; i < buffSize; i += 1) {
				if (buff[i] == value) {
					pmap.addr = pmapsit->addr + (j * 0x1000) + (i * LSize);
					DataList->push_back(pmap);
				}
			}
		}
	}
	delete[] buff;
}

void MSearchDouble(double value) {
	sAddr pmap {0, 0};
	int c;
	int buffSize = 0x1000 / DSize;
	auto * buff = new double[buffSize];
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = MapList->begin(); pmapsit != MapList->end(); ++pmapsit) {
		c = (int)(pmapsit->taddr - pmapsit->addr) / 0x1000;
		for (int j = 0; j < c; j += 1) {
			pr(buff, 0x1000, pmapsit->addr, j * 0x1000);
			for (int i = 0; i < buffSize; i += 1) {
				if (buff[i] == value) {
					pmap.addr = pmapsit->addr + (j * 0x1000) + (i * DSize);
					DataList->push_back(pmap);
				}
			}
		}
	}
	delete[] buff;
}

void MSearchByte(mbyte value) {
	sAddr pmap {0, 0};
	int c;
	int buffSize = 0x1000 / BSize;
	auto * buff = new mbyte[buffSize];
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = MapList->begin(); pmapsit != MapList->end(); ++pmapsit) {
		c = (int)(pmapsit->taddr - pmapsit->addr) / 0x1000;
		for (int j = 0; j < c; j += 1) {
			pr(buff, 0x1000, pmapsit->addr, j * 0x1000);
			for (int i = 0; i < buffSize; i += 1) {
				if (buff[i] == value) {
					pmap.addr = pmapsit->addr + (j * 0x1000) + (i * BSize);
					DataList->push_back(pmap);
				}
			}
		}
	}
	delete[] buff;
}

void MOffset(const mbyte * value, long offset, int type, int len) {
	mbyte buf[len];
	auto pmapsit = DataList->begin();
	while (pmapsit != DataList->end()) {
		pr(buf, len, pmapsit->addr, (int) offset);
		bool isMatch = false;
		if (type == MEM_DWORD) {
			int buf_val = * (int *) buf;
			int val = * (int *) value;
			if (buf_val == val) {
				isMatch = true;
			}
		} else if (type == MEM_QWORD) {
			mlong buf_val = * (mlong *) buf;
			mlong val = * (mlong *) value;
			if (buf_val == val) {
				isMatch = true;
			}
		} else if (type == MEM_FLOAT) {
			float buf_val = * (float *) buf;
			float val = * (float *) value;
			if (buf_val == val) {
				isMatch = true;
			}
		} else if (type == MEM_DOUBLE) {
			double buf_val = * (double *) buf;
			double val = * (double *) value;
			if (buf_val == val) {
				isMatch = true;
			}
		} else if (type == MEM_BYTE) {
			mbyte buf_val = * buf;
			mbyte val = * value;
			if (buf_val == val) {
				isMatch = true;
			}
		}
		if (isMatch) {
			++pmapsit;
		} else {
			pmapsit = DataList->erase(pmapsit);
		}
	}
}

void readmaps_all() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp)) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_bad() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "kgsl-3d0")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_c_alloc() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "[anon:libc_malloc]")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_c_bss() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "[anon:.bss]")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_c_data() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "/data/app/")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}

	fclose(fp);
}

void readmaps_c_heap() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "[heap]")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_java_heap() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "anon:dalvik-main")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_a_anonmyous() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && (strlen(buff) < 46)) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_code_system() {
	sAddr pmaps {0, 0};
	FILE * fp;
	int i = 0, flag = 1;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "/system")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_stack() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "[stack]")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_ashmem() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "/dev/ashmem/") && !strstr(buff, "dalvik")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_code_app() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "r-xp") != nullptr && !feof(fp) && strstr(buff, "/data/app/")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_v_video() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "/dev/kgsl-3d0")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void readmaps_other() {
	sAddr pmaps {0, 0};
	FILE * fp;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", GAME_PID);
	fp = fopen(lj, "r");
	if (fp == nullptr) {
		return;
	}
	while (!feof(fp)) {
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "rw") != nullptr && !feof(fp) && strstr(buff, "[anon:thread signal stack]")) {
			sscanf(buff, "%lx-%lx", & pmaps.addr, & pmaps.taddr);
			MapList->push_back(pmaps);
		}
	}
	fclose(fp);
}

void MemTool::initMemTool() {
	GAME_PID = getpid();
	page_size = sysconf(_SC_PAGESIZE);
}

void MemTool::SetSearchRange(Range range) {
	ClearMap();
	switch (range) {
	case ALL:
		readmaps_all();
		break;
	case B_BAD:
		readmaps_bad();
		break;
	case C_ALLOC:
		readmaps_c_alloc();
		break;
	case C_BSS:
		readmaps_c_bss();
		break;
	case C_DATA:
		readmaps_c_data();
		break;
	case C_HEAP:
		readmaps_c_heap();
		break;
	case JAVA_HEAP:
		readmaps_java_heap();
		break;
	case A_ANONMYOUS:
		readmaps_a_anonmyous();
		break;
	case CODE_SYSTEM:
		readmaps_code_system();
		break;
	case STACK:
		readmaps_stack();
		break;
	case ASHMEM:
		readmaps_ashmem();
		break;
	case CODE_APP:
		readmaps_code_app();
		break;
	case V_VIDEO:
		readmaps_v_video();
		break;
	case OTHER:
		readmaps_other();
	}
}

void MemTool::MemorySearch(const char * value, Type type) {
	ClearResults();
	if (MapList->empty()) {
		return;
	}
	switch (type) {
	case MEM_DWORD: {
		int val = atoi(value);
		MSearchDword(val);
	}
	break;
	case MEM_QWORD: {
		mlong val = atoll(value);
		MSearchQword(val);
	}
	break;
	case MEM_FLOAT: {
		float val = atof(value);
		MSearchFloat(val);
	}
	break;
	case MEM_DOUBLE: {
		double val = atof(value);
		MSearchDouble(val);
	}
	break;
	case MEM_BYTE: {
		mbyte val = atoi(value);
		MSearchByte(val);
	}
	break;
	}
}

void MemTool::MemoryOffset(const char * value, long int offset, Type type) {
	mbyte * buff = nullptr;
	switch (type) {
	case MEM_DWORD: {
		int val = atoi(value);
		buff = new mbyte[ISize];
		memcpy(buff, & val, ISize);
		MOffset(buff, offset, type, ISize);
	}
	break;
	case MEM_QWORD: {
		mlong val = atoll(value);
		buff = new mbyte[LSize];
		memcpy(buff, & val, LSize);
		MOffset(buff, offset, type, LSize);
	}
	break;
	case MEM_FLOAT: {
		float val = atof(value);
		buff = new mbyte[FSize];
		memcpy(buff, & val, FSize);
		MOffset(buff, offset, type, FSize);
	}
	break;
	case MEM_DOUBLE: {
		double val = atof(value);
		buff = new mbyte[DSize];
		memcpy(buff, & val, DSize);
		MOffset(buff, offset, type, DSize);
	}
	break;
	case MEM_BYTE: {
		mbyte val = atoi(value);
		buff = new mbyte[BSize];
		memcpy(buff, & val, BSize);
		MOffset(buff, offset, type, BSize);
	}
	break;
	}
	delete[] buff;
}

void MemTool::MemoryWrite(const char * value, long int offset, Type type) {
	mbyte * buff;
	int len = 0;
	switch (type) {
	case MEM_DWORD: {
		int val = atoi(value);
		buff = new mbyte[ISize];
		memcpy(buff, & val, ISize);
		len = ISize;
	}
	break;
	case MEM_QWORD: {
		mlong val = atoll(value);
		buff = new mbyte[LSize];
		memcpy(buff, & val, LSize);
		len = LSize;
	}
	break;
	case MEM_FLOAT: {
		float val = atof(value);
		buff = new mbyte[FSize];
		memcpy(buff, & val, FSize);
		len = FSize;
	}
	break;
	case MEM_DOUBLE: {
		double val = atof(value);
		buff = new mbyte[DSize];
		memcpy(buff, & val, DSize);
		len = DSize;
	}
	break;
	case MEM_BYTE: {
		mbyte val = atoi(value);
		buff = new mbyte[BSize];
		memcpy(buff, & val, BSize);
		len = BSize;
	}
	break;
	}
	std::list<sAddr>::iterator pmapsit;
	for (pmapsit = DataList->begin(); pmapsit != DataList->end(); ++pmapsit) {
		pw(buff, len, pmapsit->addr, offset);
	}
}

void MemTool::ClearResults() {
	DataList->clear();
}

void MemTool::ClearMap() {
	MapList->clear();
}
