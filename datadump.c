// Utility to dump contents of data structures

#include "c3c.h"

#define PRINT_STR(data, field) \
        do { \
                printf(#data "+%04x " #field ": %.*s\n", \
                       (int) &data.field - (int) &data, sizeof(data.field), \
                       data.field); \
        } while (0);
#define PRINT_DWORD(data, field, fmt) \
        do { \
                printf(#data "+%04x (" #field "): " fmt "\n", \
                       (int) &data.field - (int) &data, data.field); \
        } while (0);
#define PRINT_DWORD_BUF(data, field, fmt) \
        do { \
                int len = sizeof(data.field) / sizeof(DWORD); \
                int i; \
                for (i = 0; i < len; ++i) { \
                        printf(#data "+%04x (" #field "[%d]): " fmt "\n", \
                               (int) &data.field[i] - (int) &data, i, \
                               data.field[i]); \
                } \
        } while (0);

int dump_bic() {
        Bic bic;

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        PRINT_STR(bic, BIC);
        PRINT_DWORD_BUF(bic, no_idea_1, "0x%08x");
        PRINT_DWORD(bic, biqFilenamePtr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_2, "0x%08x");
        PRINT_STR(bic, pathNoExt);
        PRINT_STR(bic, pathWithExt);
        PRINT_STR(bic, c3cPath);
        PRINT_STR(bic, ptwPath);
        PRINT_DWORD_BUF(bic, no_idea_3, "0x%08x");
        PRINT_STR(bic, saveTmp);
        PRINT_STR(bic, no_idea_4);
        PRINT_DWORD_BUF(bic, no_idea_5, "0x%08x");
        PRINT_DWORD(bic, nTechs, "%d");
        PRINT_DWORD(bic, nUnits, "%d");
        PRINT_DWORD(bic, nBuildings, "%d");
        PRINT_DWORD_BUF(bic, no_idea_6, "%d");
        PRINT_DWORD(bic, nResources, "%d");
        PRINT_DWORD(bic, no_idea_7, "%d");
        PRINT_DWORD(bic, nPlayers, "%d");
        PRINT_DWORD_BUF(bic, no_idea_8, "%d");
        PRINT_STR(bic, description);
        PRINT_STR(bic, scenarioTitle);
        PRINT_DWORD(bic, no_idea_9, "0x%08x");
        PRINT_DWORD(bic, buildingsPtr, "0x%08x");
        PRINT_DWORD(bic, citizensPtr, "0x%08x");
        PRINT_DWORD(bic, cityNamesPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_10, "0x%08x");
        PRINT_DWORD(bic, culturePtr, "0x%08x");
        PRINT_DWORD(bic, difficultyPtr, "0x%08x");
        PRINT_DWORD(bic, erasPtr, "0x%08x");
        PRINT_DWORD(bic, espionagePtr, "0x%08x");
        PRINT_DWORD(bic, experiencePtr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_11, "0x%08x");
        PRINT_DWORD(bic, no_idea_12_ptr, "0x%08x");
        PRINT_DWORD(bic, no_idea_13_ptr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_14, "0x%08x");
        PRINT_DWORD(bic, victoryPointLimit, "%d");
        PRINT_DWORD(bic, cityEliminationCount, "%d");
        PRINT_DWORD(bic, cultureVictoryCity, "%d");
        PRINT_DWORD(bic, cultureVictoryCiv, "%d");
        PRINT_DWORD(bic, terrainForDomination, "%d");
        PRINT_DWORD(bic, populationForDomination, "%d");
        PRINT_DWORD(bic, wonderVP, "%d");
        PRINT_DWORD(bic, defeatUnitVP, "%d");
        PRINT_DWORD(bic, advanceVP, "%d");
        PRINT_DWORD(bic, cityConquestVP, "%d");
        PRINT_DWORD(bic, victoryPointLocationVP, "%d");
        PRINT_DWORD(bic, captureUnitVP, "%d");
        PRINT_DWORD(bic, captureUnitGold, "%d");
        PRINT_DWORD(bic, no_idea_15, "%d");
        PRINT_STR(bic, scenarioSearchFolders);
        PRINT_DWORD_BUF(bic, no_idea_16, "0x%08x");
        PRINT_STR(bic, alliance1Name);
        PRINT_STR(bic, alliance2Name);
        PRINT_STR(bic, alliance3Name);
        PRINT_STR(bic, alliance4Name);
        PRINT_DWORD_BUF(bic, no_idea_17, "0x%08x");
        PRINT_STR(bic, scenarioTitle2);
        PRINT_DWORD_BUF(bic, no_idea_18, "0x%08x");
        PRINT_DWORD(bic, racesPtr, "0x%08x");
        PRINT_DWORD(bic, resourcesPtr, "0x%08x");
        PRINT_DWORD(bic, govtsPtr, "0x%08x");
        PRINT_DWORD(bic, playersPtr, "0x%08x");
        PRINT_DWORD(bic, unitsPtr, "0x%08x");
        PRINT_DWORD(bic, menuArtPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_19, "0x%08x");
        PRINT_STR(bic, citySize1);
        PRINT_STR(bic, citySize2);
        PRINT_STR(bic, citySize3);
        PRINT_DWORD_BUF(bic, no_idea_20, "0x%08x");
        PRINT_DWORD(bic, culturalLevelsPtr, "0x%08x");
        PRINT_DWORD(bic, levelMultiplier, "%d");
        PRINT_DWORD(bic, nCulturalLevels, "%d");
        PRINT_DWORD(bic, borderFactor, "%d");
        PRINT_DWORD(bic, futureTechCost, "%d");
        PRINT_DWORD_BUF(bic, no_idea_21, "0x%08x");
        PRINT_DWORD(bic, techsPtr, "0x%08x");
        PRINT_DWORD(bic, workerJobsPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_22_ptr, "0x%08x");
        PRINT_DWORD(bic, worldSizesPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_23_ptr, "0x%08x");
        PRINT_DWORD(bic, screenWidthPixels, "%d");
        PRINT_DWORD(bic, screenHeightPixels, "%d");
        PRINT_DWORD(bic, no_idea_24, "0x%08x");
        return 0;
}

int main(int argc, char** argv) {
        return dump_bic();
}
