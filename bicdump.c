#include "c3c.h"

#define BIC_PRINT_STR(bic, field) \
        do { \
                printf("BIC+%04x " #field ": %s\n", \
                       (int) &bic.field - (int) &bic, bic.field); \
        } while (0);
#define BIC_PRINT_DWORD(bic, field, fmt) \
        do { \
                printf("BIC+%04x (" #field "): " fmt "\n", \
                       (int) &bic.field - (int) &bic, bic.field); \
        } while (0);
#define BIC_PRINT_DWORD_BUF(bic, field, fmt) \
        do { \
                int len = sizeof(bic.field) / sizeof(DWORD); \
                int i; \
                for (i = 0; i < len; ++i) { \
                        printf("BIC+%04x (" #field "[%d]): " fmt "\n", \
                               (int) &bic.field[i] - (int) &bic, i, \
                               bic.field[i]); \
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
        BIC_PRINT_DWORD_BUF(bic, no_idea_1, "0x%08x");
        BIC_PRINT_DWORD(bic, biqFilenamePtr, "0x%08x");
        /*
        for (i = 0; i < szBic; i += 4) {
                printf("BIC+%04x: %x\n", i, *ptr);
                ++ptr;
        }
        */
        return 0;
}
