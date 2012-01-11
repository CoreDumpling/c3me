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
	return TRUE;
    } else if (hwnd = FindWindow(NULL, COMPLETE_WINDOW_TITLE)) {
	ADDR_OFFSET = COMPLETE_ADDR_OFFSET;
	return TRUE;
    } else {
	fprintf(stderr, "C3C process not found\n");
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
