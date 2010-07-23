#include <windows.h>
#include <stdio.h>

// This is the title for the English edition of C3C
// You may need to change it for other editions
#define C3C_WINDOW_TITLE "Sid Meier's Civilization III: Conquests"

// Memory addresses -- be careful with these!
#define BIC_ADDR                0x009C34D0
#define UNITS_BEGIN_ADDR        0x00A52E44
#define CITIES_BEGIN_ADDR       0x00A52E2C

typedef struct {
        DWORD BIC; // "BIC "
        DWORD no_idea_1[3];
        DWORD biqFilenamePtr;
        DWORD no_idea_2[67];
        char pathNoExt[260];
        char pathWithExt[260];
        char c3cPath[260];
        char ptwPath[260];
        DWORD no_idea_3[64]; // all zero
        char saveTmp[16]; // save0.tmp
        char no_idea_4[512];
        DWORD no_idea_5[10];
        DWORD nTechs;
        DWORD nUnits;
        DWORD nBuildings;
        DWORD no_idea_6[8];
        DWORD nResources;
        DWORD no_idea_7;
        DWORD nCivs;
        DWORD no_idea_8[14];
        char description[640];
        char scenarioTitle[64];
        DWORD no_idea_9; // zero?
        DWORD buildingsPtr;
        DWORD citizensPtr;
        DWORD cityNamesPtr; // ???
        DWORD no_idea_10;
        DWORD culturePtr;
        DWORD difficultyPtr;
        DWORD erasPtr;
        DWORD espionagePtr;
        DWORD experiencePtr;
        DWORD no_idea_11[2]; // zero?
        DWORD no_idea_12_ptr; // points to a sequence of DWORDS, 01-1f
        DWORD no_idea_13_ptr;
        DWORD no_idea_14[2];
        DWORD autoPlaceCaptureUnits;
        DWORD autoPlaceKingUnits;
        DWORD autoPlaceVictoryLocations;
        DWORD useDebugMode;
        DWORD useTimeLimits;
        DWORD baseTimeUnit; // 0 = years, 1 = months, 2 = weeks
        DWORD startMonth; // 1-12
        DWORD startWeek; // 1-52
        DWORD startYear; // negative if BC
        DWORD timeLimitMinutes;
        DWORD timeLimitTurns;
        DWORD timeScaleTurns[7];
        DWORD timeScaleUnits[7];
        DWORD victoryPointLimit;
        DWORD cityEliminationCount;
        DWORD cultureVictoryCity;
        DWORD cultureVictoryCiv;
        DWORD terrainForDomination;
        DWORD populationForDomination;
        DWORD wonderVP;
        DWORD defeatUnitVP;
        DWORD advanceVP;
        DWORD cityConquestVP;
        DWORD victoryPointVP;
        DWORD captureUnitVP;
        DWORD captureUnitGold;
        DWORD no_idea_15;
        char scenarioSearchFolders[5200];
        DWORD no_idea_16[64]; // zero?
        char alliance1Name[256];
        char alliance2Name[256];
        char alliance3Name[256];
        char alliance4Name[256];
        char no_idea_17[404]; // includes plague stuff
        char scenarioTitle2[260]; // padded with lots of 0xCD ???
        char no_idea_18[5220];
        DWORD racesPtr;
        DWORD resourcesPtr;
        DWORD govtsPtr;
        DWORD playersPtr;
        DWORD unitsPtr;
        DWORD menuArtPtr;
        DWORD no_idea_19; // zero?
        char citySize1[32];
        char citySize2[32];
        char citySize3[32];
        DWORD no_idea_20[42]; // general settings, mostly
        DWORD culturalLevelsPtr; // Fledgling, Weak, ..., Glorious
        DWORD lvlMultiplier; // ?
        DWORD numCulturalLevels; // ?
        DWORD borderFactor; // ?
        DWORD futureTechCost;
        DWORD no_idea_21[6];
        DWORD techsPtr;
        DWORD workerJobsPtr;
        DWORD terrainPtr;
        DWORD no_idea_22_ptr;
        DWORD worldSizesPtr;
        DWORD no_idea_23_ptr;
        DWORD screenWidthPixels;
        DWORD screenHeightPixels;
        DWORD no_idea_24;
} Bic;

typedef struct {
        DWORD no_idea_1[5];
        DWORD cityNamesPtr;
        DWORD milLeadersPtr;
        char leaderName[32];
        char leaderTitle[24];
        char pedia[32];
        char adjective[40];
        char civName[40];
        char noun[40];
        char flcForward1[260];
        char flcForward2[260];
        char flcForward3[260];
        char flcForward4[260];
        char flcBack1[260];
        char flcBack2[260];
        char flcBack3[260];
        char flcBack4[260];
        DWORD cultureGroup;
        DWORD leaderGender;
        DWORD civGender;
        DWORD aggressionLevel;
        DWORD civCounter;
        DWORD shunnedGovt;
        DWORD favoriteGovt;
        DWORD numCityNames;
        DWORD numMilLeaders;
        DWORD defaultColor;
        DWORD alternateColor;
        DWORD freeTech1;
        DWORD freeTech2;
        DWORD freeTech3;
        DWORD freeTech4;
        DWORD traits;
        DWORD governorSettings;
        DWORD buildNever;
        DWORD buildOften;
        DWORD plurality;
        DWORD kingUnit;
        DWORD flavors;
        DWORD no_idea_2;
        DWORD dipTextIndex;
        DWORD numSciLeaders;
        DWORD sciLeadersPtr;
} RaceRec;

typedef struct {
        DWORD no_idea_1;
        char name[16];
        DWORD no_idea_2;
        DWORD no_idea_3;
        char pedia[32];
        DWORD type;
        DWORD appearance;
        DWORD disappearance;
        DWORD icon;
        DWORD prerequisite;
        DWORD food;
        DWORD shields;
        DWORD commerce;
} ResourceRec;

typedef struct {
        DWORD no_idea_1[3];
        DWORD defaultType;
        DWORD transitionType;
        DWORD requiresMaintainence;
        DWORD no_idea_2;
        DWORD standardTilePenalty;
        DWORD standardTradeBonus;
        DWORD no_idea_3[2];
        char name[64];
        char pedia[32];
        char maleRulerTitle1[32];
        char femaleRulerTitle1[32];
        char maleRulerTitle2[32];
        char femaleRulerTitle2[32];
        char maleRulerTitle3[32];
        char femaleRulerTitle3[32];
        char maleRulerTitle4[32];
        char femaleRulerTitle4[32];
        DWORD corruption;
        DWORD immune;
        DWORD diplomats;
        DWORD spies;
        DWORD vsGovtPtr;
        DWORD hurry;
        DWORD assimilation;
        DWORD draftLimit;
        DWORD militaryPoliceLimit;
        DWORD numGovts; // for vsGovtPtr
        DWORD numTitlePairs;
        DWORD prerequisiteTech;
        DWORD scienceCap;
        DWORD workerRate;
        DWORD no_idea_4;
        DWORD no_idea_5;
        DWORD freeUnits;
        DWORD allUnitsFree; // -1 = yes, 0 = no
        DWORD freeUnitsPerTown;
        DWORD freeUnitsPerCity;
        DWORD freeUnitsPerMetro;
        DWORD costPerUnit;
        DWORD warWeariness;
} GovtRec;

typedef struct {
        DWORD customCivData;
        DWORD humanPlayer;
        char leaderName[32];
        DWORD no_idea_1[2];
        DWORD numStartUnits;
        DWORD no_idea_2;
        DWORD startTechsPtr;
        DWORD difficulty;
        DWORD initialEra;
        DWORD startGold;
        DWORD government;
        DWORD numStartTechs;
        DWORD no_idea_3;
        DWORD civId;
        DWORD color;
        DWORD no_idea_4[4];
} PlayerRec;

typedef struct {
        DWORD no_idea_1;
        DWORD zone_of_control;
        char name[32];
        char pedia[32];
        DWORD bombard;
        DWORD bombardRange;
        DWORD capacity;
        DWORD shieldCost;
        DWORD defense;
        DWORD iconIndex;
        DWORD attack;
        DWORD operationalRange;
        DWORD popCost;
        DWORD rateOfFire;
        DWORD movement;
        DWORD requiredTech;
        DWORD upgradeTo;
        DWORD requiredResource1;
        DWORD requiredResource2;
        DWORD requiredResource3;
        DWORD unitAbilities;
        DWORD aiStrategy;
        DWORD availableTo;
        DWORD specialActions;
        DWORD airMissions;
        DWORD unitClass;
        DWORD otherStrategy;
        DWORD hpBonus;
        DWORD standardOrdersPTW;
        DWORD specialActionsPTW[2];
        DWORD airMissionsPTW;
        DWORD actionsMix;
        DWORD bombardEffects;
        BYTE ignoreMovement[16];
        DWORD requireSupport;
        DWORD no_idea_2[4];
        DWORD enslaveResults;
        DWORD no_idea_3;
        DWORD numStealthTargets;
        DWORD no_idea_4[2];
        DWORD createCraters;
        DWORD workerStrength;
        DWORD no_idea_5;
        DWORD airDefense;
        DWORD no_idea_6[12];
} UnitRec;

typedef struct {
        DWORD no_idea_1;
        DWORD id;
        DWORD x;
        DWORD y;
        DWORD prevx;
        DWORD prevy;
        DWORD owner;
        DWORD nationality;
        DWORD no_idea_3;
        DWORD type;
        DWORD experience;
        DWORD no_idea_4;
        DWORD damage;
        DWORD usedMovement;
        DWORD no_idea_5;
        DWORD workerAction;
        DWORD no_idea_6[2];
        DWORD fortified;
        DWORD endTurn;
        DWORD no_idea_7[2];
        char name[32];
        DWORD no_idea_8[7]; // all 0000's
        DWORD no_idea_9[4]; // all FFFF's
} Unit;

typedef struct {
        DWORD no_idea_1;
        DWORD id;
        WORD x;
        WORD y;
        DWORD owner;
        DWORD no_idea_2[5];
        DWORD currentFood;
        DWORD currentShields;
        DWORD no_idea_3;
        DWORD currentBuild;
        DWORD currentBuildType; // 1 = building, 2 = unit
        DWORD no_idea_4[23];
        DWORD BINF; // "BINF"
        DWORD no_idea_5[11];
        DWORD citizenPtr;
        DWORD no_idea_6[21];
        DWORD population;
        DWORD no_idea_7[2];
        DWORD culture;
        DWORD no_idea_8[38];
        char name[24];
} City;

typedef struct {
        DWORD no_idea_1;
        char desc[64]; // auto-generated no idea about true length
        DWORD no_idea_2[48]; // all zeros?
        DWORD no_idea_3[7];
        DWORD type; // 0 = laborer, 1 = ent, 2 = tax, 3 = sci, 4 = pol, 5 = eng
        DWORD race;
        DWORD no_idea_4[3];
} Citizen;

BOOL ReadCivMemory(DWORD lpAddress, void* buf, int len) {
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

BOOL WriteCivMemory(DWORD lpAddress, void* buf, int len) {
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

int main(int argc, char** argv) {
        Bic bic;
        int i;

        if (!ReadCivMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        DWORD nRaces;
        // number of races appears right before address pointed by racesPtr
        if (!ReadCivMemory(bic.racesPtr - sizeof(DWORD), &nRaces,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of races: %d\n", nRaces);
        RaceRec* raceRecs = (RaceRec*) malloc(nRaces * sizeof(RaceRec));
        if (!ReadCivMemory(bic.racesPtr, raceRecs,
                           nRaces * sizeof(RaceRec))) {
                return 1;
        }
        for (i = 0; i < nRaces; ++i) {
                printf("Civ #%02d - %s:\n", i, raceRecs[i].civName);
        }

        printf("Number of resources: %d\n", bic.nResources);
        ResourceRec* resRecs =
            (ResourceRec*) malloc(bic.nResources * sizeof(ResourceRec));
        if (!ReadCivMemory(bic.resourcesPtr, resRecs,
                           bic.nResources * sizeof(ResourceRec))) {
                return 1;
        }
        for (i = 0; i < bic.nResources; ++i) {
                printf("%s: %s\n", resRecs[i].name, resRecs[i].pedia);
        }

        DWORD nGovts;
        // number of govts appears right before address pointed by govtsPtr
        if (!ReadCivMemory(bic.govtsPtr - sizeof(DWORD), &nGovts,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of governments: %d\n", nGovts);
        GovtRec* govtRecs = (GovtRec*) malloc(nGovts * sizeof(GovtRec));
        if (!ReadCivMemory(bic.govtsPtr, govtRecs,
                           nGovts * sizeof(GovtRec))) {
                return 1;
        }
        for (i = 0; i < nGovts; ++i) {
                printf("Government #%02d - %s:\n", i, govtRecs[i].name);
        }

        DWORD nPlayers;
        // number of players appears right before address pointed by playersPtr
        if (!ReadCivMemory(bic.playersPtr - sizeof(DWORD), &nPlayers,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of players: %d\n", nPlayers);
        PlayerRec* playerRecs =
            (PlayerRec*) malloc(nPlayers * sizeof(PlayerRec));
        // no idea what the first 4 bytes are, but they don't match a player
        if (!ReadCivMemory(bic.playersPtr + sizeof(DWORD), playerRecs,
                           nPlayers * sizeof(PlayerRec))) {
                return 1;
        }
        for (i = 0; i < nPlayers; ++i) {
                // the index i starts at zero, but counts from "Player 1"
                printf("Player #%02d - %s (%s):\n", i + 1,
                       raceRecs[playerRecs[i].civId].civName,
                       govtRecs[playerRecs[i].government].name);
        }

        DWORD nUnits;
        // number of units appears right before address pointed by unitsPtr
        if (!ReadCivMemory(bic.unitsPtr - sizeof(DWORD), &nUnits,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of units: %d\n", nUnits);
        UnitRec* unitRecs = (UnitRec*) malloc(nUnits * sizeof(UnitRec));
        if (!ReadCivMemory(bic.unitsPtr, unitRecs,
                           nUnits * sizeof(UnitRec))) {
                return 1;
        }
        for (i = 0; i < nUnits; ++i) {
                printf("Unit #%03d - %s (%d.%d.%d) / %d shields:\n",
                       i, unitRecs[i].name,
                       unitRecs[i].attack, unitRecs[i].defense,
                       unitRecs[i].movement, unitRecs[i].shieldCost);
        }

        DWORD unitsPtr;
        DWORD unitValid;
        DWORD unitPtr;
        if (!ReadCivMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(DWORD))) {
                return 1;
        }
        printf("%x\n", unitsPtr);
        do {
                ReadCivMemory(unitsPtr, &unitValid, sizeof(DWORD));
                unitsPtr += sizeof(DWORD);
                if (unitValid != 0xffffffff) {
                        continue;
                }
                ReadCivMemory(unitsPtr, &unitPtr, sizeof(DWORD));
                if (unitPtr == 0) {
                        break;
                }
                Unit unit;
                ReadCivMemory(unitPtr, &unit, sizeof(Unit));
                printf("Unit #%04d - %s, %s (%d,%d):\n",
                       unit.id, raceRecs[playerRecs[unit.owner - 1].civId].civName,
                       unitRecs[unit.type].name, unit.x, unit.y);
                unitsPtr += sizeof(DWORD);
        } while (!(unitValid == 0xffffffff && unitPtr == 0));

        DWORD citiesPtr;
        DWORD cityValid;
        DWORD cityPtr;
        if (!ReadCivMemory(CITIES_BEGIN_ADDR, &citiesPtr, sizeof(DWORD))) {
                return 1;
        }
        printf("%x\n", citiesPtr);
        do {
                ReadCivMemory(citiesPtr, &cityValid, sizeof(DWORD));
                citiesPtr += sizeof(DWORD);
                if (cityValid != 0xffffffff) {
                        continue;
                }
                ReadCivMemory(citiesPtr, &cityPtr, sizeof(DWORD));
                if (cityPtr == 0) {
                        break;
                }
                City city;
                ReadCivMemory(cityPtr, &city, sizeof(City));
                printf("City #%03d - %s (%d,%d), pop %d:\n",
                       city.id, city.name, city.x, city.y, city.population);
                citiesPtr += sizeof(DWORD);

                // read citizen data
                DWORD citizensPtr = city.citizenPtr;
                DWORD citizenValid;
                DWORD citizenPtr;
                int citizenCount = 0;
                while (citizenCount < city.population) {
                        ReadCivMemory(citizensPtr, &citizenValid,
                                      sizeof(DWORD));
                        citizensPtr += sizeof(DWORD);
                        ReadCivMemory(citizensPtr, &citizenPtr, sizeof(DWORD));
                        citizensPtr += sizeof(DWORD);
                        if (citizenValid == 0xffffffff && citizenPtr != 0) {
                                Citizen citizen;
                                ReadCivMemory(citizenPtr, &citizen,
                                              sizeof(Citizen));
                                printf("\tCitizen type: %d\n", citizen.type);
                                citizenCount++;
                        }
                }
        } while (!(cityValid == 0xffffffff && cityPtr == 0));

        free(raceRecs);
        free(resRecs);
        free(unitRecs);
        free(playerRecs);
        free(govtRecs);
        return 0;
}
