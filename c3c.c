#include "c3c.h"

BOOL ReadC3CMemory(DWORD lpAddress, void* buf, int len) {
        HWND hwnd = FindWindow(NULL, C3C_WINDOW_TITLE);
        if (hwnd) {
                DWORD pid;
                GetWindowThreadProcessId(hwnd, &pid);
                HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                ReadProcessMemory(hProc, (void*) lpAddress, buf, len, 0);
                CloseHandle(hProc);
                return TRUE;
        } else {
                printf("C3C process not found\n");
                return FALSE;
        }
}

BOOL WriteC3CMemory(DWORD lpAddress, void* buf, int len) {
        HWND hwnd = FindWindow(NULL, C3C_WINDOW_TITLE);
        if (hwnd) {
                DWORD pid;
                GetWindowThreadProcessId(hwnd, &pid);
                HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                SIZE_T wlen;
                WriteProcessMemory(hProc, (void*) lpAddress, buf, len, &wlen);
                CloseHandle(hProc);
                if (len == wlen) {
                        return TRUE;
                } else {
                        printf("Memory write error\n");
                        return FALSE;
                }
        } else {
                printf("C3C process not found\n");
                return FALSE;
        }
}
