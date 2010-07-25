#include "c3c.h"

int main(int argc, char** argv) {
        Bic bic;
        int i;

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        printf("Number of citizen types: %d\n", bic.nCitizens);
        CitizenRule* citizenRules =
            (CitizenRule*) malloc(bic.nCitizens * sizeof(CitizenRule));
        if (!ReadC3CMemory(bic.citizensPtr, citizenRules,
                           bic.nCitizens * sizeof(CitizenRule))) {
                return 1;
        }
        for (i = 0; i < bic.nCitizens; ++i) {
                printf("Citizen type %s: +%d lux +%d sci +%d tax "
                       "+%d pol +%d eng\n",
                       citizenRules[i].name, citizenRules[i].luxury,
                       citizenRules[i].science, citizenRules[i].tax,
                       citizenRules[i].corruption,
                       citizenRules[i].construction);
        }

        DWORD nRaces;
        // number of races appears right before address pointed by racesPtr
        if (!ReadC3CMemory(bic.racesPtr - sizeof(DWORD), &nRaces,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of races: %d\n", nRaces);
        RaceRule* raceRecs = (RaceRule*) malloc(nRaces * sizeof(RaceRule));
        if (!ReadC3CMemory(bic.racesPtr, raceRecs,
                           nRaces * sizeof(RaceRule))) {
                return 1;
        }
        for (i = 0; i < nRaces; ++i) {
                printf("Civ #%02d - %s:\n", i, raceRecs[i].civName);
        }

        printf("Number of resources: %d\n", bic.nResources);
        ResourceRule* resRecs =
            (ResourceRule*) malloc(bic.nResources * sizeof(ResourceRule));
        if (!ReadC3CMemory(bic.resourcesPtr, resRecs,
                           bic.nResources * sizeof(ResourceRule))) {
                return 1;
        }
        for (i = 0; i < bic.nResources; ++i) {
                printf("%s: %s\n", resRecs[i].name, resRecs[i].pedia);
        }

        DWORD nGovts;
        // number of govts appears right before address pointed by govtsPtr
        if (!ReadC3CMemory(bic.govtsPtr - sizeof(DWORD), &nGovts,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of governments: %d\n", nGovts);
        GovtRule* govtRecs = (GovtRule*) malloc(nGovts * sizeof(GovtRule));
        if (!ReadC3CMemory(bic.govtsPtr, govtRecs,
                           nGovts * sizeof(GovtRule))) {
                return 1;
        }
        for (i = 0; i < nGovts; ++i) {
                printf("Government #%02d - %s:\n", i, govtRecs[i].name);
        }

        DWORD nPlayers;
        // number of players appears right before address pointed by playersPtr
        if (!ReadC3CMemory(bic.playersPtr - sizeof(DWORD), &nPlayers,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of players: %d\n", nPlayers);
        PlayerData* playerRecs =
            (PlayerData*) malloc(nPlayers * sizeof(PlayerData));
        // no idea what the first 4 bytes are, but they don't match a player
        if (!ReadC3CMemory(bic.playersPtr + sizeof(DWORD), playerRecs,
                           nPlayers * sizeof(PlayerData))) {
                return 1;
        }
        for (i = 0; i < nPlayers; ++i) {
                // the index i starts at zero, but counts from "Player 1"
                printf("Player #%02d - %s (%s):\n", i + 1,
                       raceRecs[playerRecs[i].civId].civName,
                       govtRecs[playerRecs[i].government].name);
        }

        Leader leaders[32];
        if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
                return 1;
        }
        for (i = 0; i < 32; ++i) {
               printf("Leader #%02d - %s\n", i,
                       raceRecs[leaders[i].nationality].civName);
        }

        DWORD nUnits;
        // number of units appears right before address pointed by unitsPtr
        if (!ReadC3CMemory(bic.unitsPtr - sizeof(DWORD), &nUnits,
                           sizeof(DWORD))) {
                return 1;
        }
        printf("Number of units: %d\n", nUnits);
        UnitRule* unitRecs = (UnitRule*) malloc(nUnits * sizeof(UnitRule));
        if (!ReadC3CMemory(bic.unitsPtr, unitRecs,
                           nUnits * sizeof(UnitRule))) {
                return 1;
        }
        for (i = 0; i < nUnits; ++i) {
                printf("Unit #%03d - %s (%d.%d.%d) / %d shields:\n",
                       i, unitRecs[i].name,
                       unitRecs[i].attack, unitRecs[i].defense,
                       unitRecs[i].movement, unitRecs[i].shieldCost);
        }

        // there are always 4 combat experience levels
        ExpRule exp[4];
        if (!ReadC3CMemory(bic.experiencePtr, &exp, sizeof(exp))) {
                return 1;
        }
        for (i = 0; i < 4; ++i) {
                printf("Experience level: %s (%d hp, %d retreat)\n",
                       exp[i].name, exp[i].hp, exp[i].retreatBonus);
        }

        // in-game units are stored as an array of pointers to the unit data,
        // with an integer before each pointer indicating if it is valid
        // total number of units in-game stored at NUM_UNITS_ADDR
        DWORD unitsPtr;
        DWORD unitValid;
        DWORD unitPtr;
        DWORD unitCount;
        if (!ReadC3CMemory(NUM_UNITS_ADDR, &unitCount, sizeof(DWORD))) {
                return 1;
        }
        printf("Units in game: %d\n", unitCount);
        if (!ReadC3CMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(DWORD))) {
                return 1;
        }
        for (i = 0; i < unitCount; unitsPtr += sizeof(DWORD)) {
                ReadC3CMemory(unitsPtr, &unitValid, sizeof(DWORD));
                unitsPtr += sizeof(DWORD);
                if (unitValid != 0xffffffff) {
                        continue;
                }
                ReadC3CMemory(unitsPtr, &unitPtr, sizeof(DWORD));
                if (!unitPtr) {
                        continue;
                }

                // if we get this far, it's a valid unit in-game
                Unit unit;
                ReadC3CMemory(unitPtr, &unit, sizeof(Unit));
                printf("Unit #%04d - %s, %s (%d,%d):\n",
                       unit.id,
                       raceRecs[leaders[unit.owner].nationality].civName,
                       unitRecs[unit.type].name, unit.x, unit.y);
                ++i;
        }

        DWORD citiesPtr;
        DWORD cityValid;
        DWORD cityPtr;
        if (!ReadC3CMemory(CITIES_BEGIN_ADDR, &citiesPtr, sizeof(DWORD))) {
                return 1;
        }
        printf("%x\n", citiesPtr);
        do {
                ReadC3CMemory(citiesPtr, &cityValid, sizeof(DWORD));
                citiesPtr += sizeof(DWORD);
                if (cityValid != 0xffffffff) {
                        continue;
                }
                ReadC3CMemory(citiesPtr, &cityPtr, sizeof(DWORD));
                if (cityPtr == 0) {
                        break;
                }
                City city;
                ReadC3CMemory(cityPtr, &city, sizeof(City));
                printf("City #%03d - %s (%d,%d), pop %d:\n",
                       city.id, city.name, city.x, city.y, city.population);
                citiesPtr += sizeof(DWORD);

                // read citizen data
                DWORD citizensPtr = city.citizenPtr;
                DWORD citizenValid;
                DWORD citizenPtr;
                int citizenCount = 0;
                while (citizenCount < city.population) {
                        ReadC3CMemory(citizensPtr, &citizenValid,
                                      sizeof(DWORD));
                        citizensPtr += sizeof(DWORD);
                        ReadC3CMemory(citizensPtr, &citizenPtr, sizeof(DWORD));
                        citizensPtr += sizeof(DWORD);
                        if (citizenValid == 0xffffffff && citizenPtr != 0) {
                                Citizen citizen;
                                ReadC3CMemory(citizenPtr, &citizen,
                                              sizeof(Citizen));
                                printf("\tCitizen type: %d\n", citizen.type);
                                citizenCount++;
                        }
                }
        } while (!(cityValid == 0xffffffff && cityPtr == 0));

        free(citizenRules);
        free(raceRecs);
        free(resRecs);
        free(unitRecs);
        free(playerRecs);
        free(govtRecs);
        return 0;
}
