#include "c3c.h"

int main(int argc, char** argv) {
        Bic bic;
        int i;
        int* ptr = (int*) &bic;
        int szBic = sizeof(Bic);

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        for (i = 0; i < szBic; i += 4) {
                printf("BIC+%04x: %x\n", i, *ptr);
                ++ptr;
        }
        return 0;
}
