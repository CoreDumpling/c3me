#include "c3c.h"
#include <stdio.h>
#include <windows.h>

/* Handle to C3C window */
HWND hwnd = 0;

/* Address offset of Complete vs. Conquests */
uint32_t ADDR_OFFSET = 0;
const uint32_t COMPLETE_ADDR_OFFSET = 0x40;

int FindC3C()
{
    hwnd = FindWindow(NULL, CONQUESTS_WINDOW_TITLE);
    if (hwnd) {
	ADDR_OFFSET = 0;
    } else if (hwnd = FindWindow(NULL, COMPLETE_WINDOW_TITLE)) {
	ADDR_OFFSET = COMPLETE_ADDR_OFFSET;
    } else {
	fprintf(stderr, "C3C process not found\n");
	return FALSE;
    }

    /* Some versions of C3C have the memory addresses offset differently.
     * To try to handle this, check to see if the BIC header is present at the
     * expected location, and if not, scan the nearby memory addresses in an
     * attempt to find it. */
    char BIC[4];
    if (ReadC3CMemory(BIC_ADDR, BIC, 4)) {
	if (!strncmp("BIC ", BIC, 4)) {
	    /* BIC header found at expected location */
	    return TRUE;
	} else {
	    uint32_t scan;
	    for (scan = BIC_ADDR + 4; scan < BIC_ADDR + 0x10000;
		 scan += (BIC_ADDR - scan) * 2 + (scan < BIC_ADDR ? 4 : 0)) {
		if (!ReadC3CMemory(scan, BIC, 4)) {
		    fprintf(stderr, "Unable to read BIC header\n");
		    return FALSE;
		}
		if (!strncmp("BIC ", BIC, 4)) {
		    /* BIC header found elsewhere, recompute memory offset */
		    ADDR_OFFSET = scan - (BIC_ADDR - ADDR_OFFSET);
		    return TRUE;
		}
	    }
	    fprintf(stderr, "Unable to locate BIC header\n");
	    return FALSE;
	}
    } else {
	fprintf(stderr, "Unable to read BIC header\n");
	return FALSE;
    }
}

int ReadC3CMemory(uint32_t lpAddress, void *buf, int len)
{
    if (hwnd) {
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	ReadProcessMemory(hProc, (void *) lpAddress, buf, len, 0);
	CloseHandle(hProc);
	return TRUE;
    } else {
	return FALSE;
    }
}

int WriteC3CMemory(uint32_t lpAddress, void *buf, int len)
{
    if (hwnd) {
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	SIZE_T wlen;
	WriteProcessMemory(hProc, (void *) lpAddress, buf, len, &wlen);
	CloseHandle(hProc);
	if (len == wlen) {
	    return TRUE;
	} else {
	    fprintf(stderr, "Memory write error\n");
	    return FALSE;
	}
    } else {
	return FALSE;
    }
}
