#include "c3c.h"
#include <stdio.h>
#include <windows.h>

int ReadC3CMemory(uint32_t lpAddress, void *buf, int len)
{
    HWND hwnd = FindWindow(NULL, CONQUESTS_WINDOW_TITLE);
    if (!hwnd) {
	hwnd = FindWindow(NULL, COMPLETE_WINDOW_TITLE);
    }
    if (hwnd) {
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	ReadProcessMemory(hProc, (void *) lpAddress, buf, len, 0);
	CloseHandle(hProc);
	return TRUE;
    } else {
	fprintf(stderr, "C3C process not found\n");
	return FALSE;
    }
}

int WriteC3CMemory(uint32_t lpAddress, void *buf, int len)
{
    HWND hwnd = FindWindow(NULL, CONQUESTS_WINDOW_TITLE);
    if (!hwnd) {
	hwnd = FindWindow(NULL, COMPLETE_WINDOW_TITLE);
    }
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
	fprintf(stderr, "C3C process not found\n");
	return FALSE;
    }
}
