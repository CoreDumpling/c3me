#include "c3c.h"

#define BIC_PRINT_STR(bic, field) \
        do { \
                printf("BIC+%04x " #field ": %.*s\n", \
                       (int) &bic.field - (int) &bic, sizeof(bic.field), \
                       bic.field); \
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
        BIC_PRINT_DWORD_BUF(bic, no_idea_2, "0x%08x");
        BIC_PRINT_STR(bic, pathNoExt);
        BIC_PRINT_STR(bic, pathWithExt);
        BIC_PRINT_STR(bic, c3cPath);
        BIC_PRINT_STR(bic, ptwPath);
        BIC_PRINT_DWORD_BUF(bic, no_idea_3, "0x%08x");
        BIC_PRINT_STR(bic, saveTmp);
        BIC_PRINT_STR(bic, no_idea_4);
        BIC_PRINT_DWORD_BUF(bic, no_idea_5, "0x%08x");
        BIC_PRINT_DWORD(bic, nTechs, "%d");
        BIC_PRINT_DWORD(bic, nUnits, "%d");
        BIC_PRINT_DWORD(bic, nBuildings, "%d");
        BIC_PRINT_DWORD_BUF(bic, no_idea_6, "%d");
        BIC_PRINT_DWORD(bic, nResources, "%d");
        BIC_PRINT_DWORD(bic, no_idea_7, "%d");
        BIC_PRINT_DWORD(bic, nPlayers, "%d");
        BIC_PRINT_DWORD_BUF(bic, no_idea_8, "%d");
        BIC_PRINT_STR(bic, description);
        BIC_PRINT_STR(bic, scenarioTitle);
        BIC_PRINT_DWORD(bic, no_idea_9, "0x%08x");
        BIC_PRINT_DWORD(bic, buildingsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, citizensPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, cityNamesPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_10, "0x%08x");
        BIC_PRINT_DWORD(bic, culturePtr, "0x%08x");
        BIC_PRINT_DWORD(bic, difficultyPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, erasPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, espionagePtr, "0x%08x");
        BIC_PRINT_DWORD(bic, experiencePtr, "0x%08x");
        BIC_PRINT_DWORD_BUF(bic, no_idea_11, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_12_ptr, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_13_ptr, "0x%08x");
        BIC_PRINT_DWORD_BUF(bic, no_idea_14, "0x%08x");
        BIC_PRINT_DWORD(bic, victoryPointLimit, "%d");
        BIC_PRINT_DWORD(bic, cityEliminationCount, "%d");
        BIC_PRINT_DWORD(bic, cultureVictoryCity, "%d");
        BIC_PRINT_DWORD(bic, cultureVictoryCiv, "%d");
        BIC_PRINT_DWORD(bic, terrainForDomination, "%d");
        BIC_PRINT_DWORD(bic, populationForDomination, "%d");
        BIC_PRINT_DWORD(bic, wonderVP, "%d");
        BIC_PRINT_DWORD(bic, defeatUnitVP, "%d");
        BIC_PRINT_DWORD(bic, advanceVP, "%d");
        BIC_PRINT_DWORD(bic, cityConquestVP, "%d");
        BIC_PRINT_DWORD(bic, victoryPointLocationVP, "%d");
        BIC_PRINT_DWORD(bic, captureUnitVP, "%d");
        BIC_PRINT_DWORD(bic, captureUnitGold, "%d");
        BIC_PRINT_DWORD(bic, no_idea_15, "%d");
        BIC_PRINT_STR(bic, scenarioSearchFolders);
        BIC_PRINT_DWORD_BUF(bic, no_idea_16, "0x%08x");
        BIC_PRINT_STR(bic, alliance1Name);
        BIC_PRINT_STR(bic, alliance2Name);
        BIC_PRINT_STR(bic, alliance3Name);
        BIC_PRINT_STR(bic, alliance4Name);
        BIC_PRINT_DWORD_BUF(bic, no_idea_17, "0x%08x");
        BIC_PRINT_STR(bic, scenarioTitle2);
        BIC_PRINT_DWORD_BUF(bic, no_idea_18, "0x%08x");
        BIC_PRINT_DWORD(bic, racesPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, resourcesPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, govtsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, playersPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, unitsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, menuArtPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_19, "0x%08x");
        BIC_PRINT_STR(bic, citySize1);
        BIC_PRINT_STR(bic, citySize2);
        BIC_PRINT_STR(bic, citySize3);
        BIC_PRINT_DWORD_BUF(bic, no_idea_20, "0x%08x");
        BIC_PRINT_DWORD(bic, culturalLevelsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, levelMultiplier, "%d");
        BIC_PRINT_DWORD(bic, nCulturalLevels, "%d");
        BIC_PRINT_DWORD(bic, borderFactor, "%d");
        BIC_PRINT_DWORD(bic, futureTechCost, "%d");
        BIC_PRINT_DWORD_BUF(bic, no_idea_21, "0x%08x");
        BIC_PRINT_DWORD(bic, techsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, workerJobsPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_22_ptr, "0x%08x");
        BIC_PRINT_DWORD(bic, worldSizesPtr, "0x%08x");
        BIC_PRINT_DWORD(bic, no_idea_23_ptr, "0x%08x");
        BIC_PRINT_DWORD(bic, screenWidthPixels, "%d");
        BIC_PRINT_DWORD(bic, screenHeightPixels, "%d");
        BIC_PRINT_DWORD(bic, no_idea_24, "0x%08x");
        return 0;
}
