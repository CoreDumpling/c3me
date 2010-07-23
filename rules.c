#include "c3c.h"

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
