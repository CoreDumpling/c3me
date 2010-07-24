// Utility to dump contents of Unit data structure

#include "c3c.h"
#include <stdio.h>

#define UNIT_PRINT_STR(unit, field) \
        do { \
                printf("UNIT+%04x " #field ": %.*s\n", \
                       (int) &unit.field - (int) &unit, sizeof(unit.field), \
                       unit.field); \
        } while (0);
#define UNIT_PRINT_DWORD(unit, field, fmt) \
        do { \
                printf("UNIT+%04x (" #field "): " fmt "\n", \
                       (int) &unit.field - (int) &unit, unit.field); \
        } while (0);
#define UNIT_PRINT_DWORD_BUF(unit, field, fmt) \
        do { \
                int len = sizeof(unit.field) / sizeof(DWORD); \
                int i; \
                for (i = 0; i < len; ++i) { \
                        printf("UNIT+%04x (" #field "[%d]): " fmt "\n", \
                               (int) &unit.field[i] - (int) &unit, i, \
                               unit.field[i]); \
                } \
        } while (0);

int main(int argc, char** argv) {
        Bic bic;
        int i;
        int* ptr;

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        DWORD unitsPtr;
        DWORD unitValid, unitValidPtr;
        DWORD unitPtr, unitPtrPtr;
        DWORD unitId = atoi(argv[1]);
        if (!ReadC3CMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(DWORD))) {
                return 1;
        }
        unitValidPtr = unitsPtr + unitId * 2 * sizeof(DWORD);
        if (!ReadC3CMemory(unitValidPtr, &unitValid, sizeof(DWORD))) {
                return 1;
        }
        unitPtrPtr = unitValidPtr + sizeof(DWORD);
        if (unitValid != 0xffffffff) {
                fprintf(stderr, "Invalid unit id: %d\n", unitId);
                return 1;
        } else {
                Unit unit;
                if (!ReadC3CMemory(unitPtrPtr, &unitPtr, sizeof(DWORD))) {
                        return 1;
                }
                if (!ReadC3CMemory(unitPtr, &unit, sizeof(Unit))) {
                        return 1;
                }
                UNIT_PRINT_DWORD(unit, no_idea_1, "0x%08x");
                UNIT_PRINT_DWORD(unit, id, "%d");
                UNIT_PRINT_DWORD(unit, x, "%d");
                UNIT_PRINT_DWORD(unit, y, "%d");
                UNIT_PRINT_DWORD(unit, prevx, "%d");
                UNIT_PRINT_DWORD(unit, prevy, "%d");
                UNIT_PRINT_DWORD(unit, owner, "%d");
                UNIT_PRINT_DWORD(unit, nationality, "%d");
                UNIT_PRINT_DWORD(unit, no_idea_3, "%d");
                UNIT_PRINT_DWORD(unit, type, "%d");
                UNIT_PRINT_DWORD(unit, experience, "%d");
                UNIT_PRINT_DWORD(unit, no_idea_4, "%d");
                UNIT_PRINT_DWORD(unit, damage, "%d");
                UNIT_PRINT_DWORD(unit, usedMovement, "%d");
                UNIT_PRINT_DWORD(unit, no_idea_5, "%d");
                UNIT_PRINT_DWORD(unit, workerAction, "%d");
                UNIT_PRINT_DWORD_BUF(unit, no_idea_6, "%d");
                UNIT_PRINT_DWORD(unit, fortified, "%d");
                UNIT_PRINT_DWORD(unit, endTurn, "%d");
                UNIT_PRINT_DWORD_BUF(unit, no_idea_7, "%d");
                UNIT_PRINT_STR(unit, name);
                UNIT_PRINT_DWORD_BUF(unit, no_idea_8, "%d");
                UNIT_PRINT_DWORD_BUF(unit, no_idea_9, "%d");
        }

        return 0;
}
