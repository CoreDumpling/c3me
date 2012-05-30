#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c3c.h"

#define ADMIN_PW_LENGTH 256 /* appears to actually be limited to 228 characters,
                             * but we'll make it 256 to be safe */

int main(int argc, char **argv)
{
    /* current admin password */
    char adminpw[256];
    /* new admin password (to be set) */
    char newpw[256];

    if (!FindC3C()) {
        return 1;
    }

    /* First get current admin password */
    if (!ReadC3CMemory(ADMIN_PW_ADDR, adminpw, ADMIN_PW_LENGTH)) {
        printf("Unable to read admin password.\n");
        printf("-- Press any key to exit --\n");
        getch();
        return 1;
    }

    /* Prompt for current admin password */
    printf("Enter current admin password: ");
    fgets(newpw, ADMIN_PW_LENGTH, stdin);
    if (newpw[strlen(newpw) - 1] == '\n') {
        newpw[strlen(newpw) - 1] = '\0';
    }
    if (strncmp(adminpw, newpw, ADMIN_PW_LENGTH)) {
        printf("Incorrect password.\n");
        printf("-- Press any key to exit --\n");
        getch();
        return 0;
    }

    /* Prompt for new password */
    printf("Enter new admin password: ");
    fgets(newpw, ADMIN_PW_LENGTH, stdin);
    if (newpw[strlen(newpw) - 1] == '\n') {
        newpw[strlen(newpw) - 1] = '\0';
    }
    if (!WriteC3CMemory(ADMIN_PW_ADDR, newpw, ADMIN_PW_LENGTH)) {
        printf("Unable to set admin password.\n");
        printf("-- Press any key to exit --\n");
        getch();
        return 1;
    } else {
        printf("New admin password has been set.\n");
        printf("-- Press any key to exit --\n");
        getch();
        return 0;
    }
}
