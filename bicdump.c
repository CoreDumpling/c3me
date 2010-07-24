#include "c3c.h"

#define BIC_PRINT_STR(bic, field) \
        do { \
                printf("BIC+%04x (%s): %s\n", \
                       (int) &bic.field - (int) &bic, #field, bic.field); \
        } while (0);
#define BIC_PRINT_DWORD_BUF(bic, field) \
        do { \
                DWORD* ptr = bic.field; \
                DWORD* end = ptr + sizeof(bic.field) / sizeof(DWORD); \
                while (ptr != end) { \
                        printf("BIC+%04x (%s): %x\n", \
                               (int) ptr - (int) &bic, #field, *ptr); \
                        ++ptr; \
                } \
        } while (0);

int main(int argc, char** argv) {
        Bic bic;
        int i;
        int* ptr;

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        BIC_PRINT_STR(bic, BIC);
        BIC_PRINT_DWORD_BUF(bic, no_idea_1);
        /*
        for (i = 0; i < szBic; i += 4) {
                printf("BIC+%04x: %x\n", i, *ptr);
                ++ptr;
        }
        */
        return 0;
}
