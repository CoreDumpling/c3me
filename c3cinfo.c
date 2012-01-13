#include "c3c.h"

int main(int argc, char **argv)
{
    Bic bic;
    int i;

    if (!FindC3C()) {
	return 1;
    }
    if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	return 1;
    }

    printf("Number of citizen types: %d\n", bic.nCitizens);
    CitizenRule *citizenRules =
	(CitizenRule *) malloc(bic.nCitizens * sizeof(CitizenRule));
    if (!ReadC3CMemory(bic.citizensPtr, citizenRules,
		       bic.nCitizens * sizeof(CitizenRule))) {
	return 1;
    }
    for (i = 0; i < bic.nCitizens; ++i) {
	printf("Citizen type %s: +%d lux +%d sci +%d tax "
	       "+%d pol +%d eng\n",
	       citizenRules[i].name, citizenRules[i].luxury,
	       citizenRules[i].science, citizenRules[i].tax,
	       citizenRules[i].corruption, citizenRules[i].construction);
    }

    uint32_t nRaces;
    /* number of races appears right before address pointed by racesPtr */
    if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
		       sizeof(uint32_t))) {
	return 1;
    }
    printf("Number of races: %d\n", nRaces);
    RaceRule *raceRules = (RaceRule *) malloc(nRaces * sizeof(RaceRule));
    if (!ReadC3CMemory(bic.racesPtr, raceRules, nRaces * sizeof(RaceRule))) {
	return 1;
    }
    for (i = 0; i < nRaces; ++i) {
	printf("Civ #%02d - %s:\n", i, raceRules[i].civName);
    }

    TechRule *techRules =
	(TechRule *) malloc(bic.nTechs * sizeof(TechRule));
    if (!ReadC3CMemory(bic.techsPtr, techRules,
		       bic.nTechs * sizeof(TechRule))) {
	return 1;
    }
    for (i = 0; i < bic.nTechs; ++i) {
	printf("Tech %d: %s\n", i, techRules[i].name);
    }

    /* there are always 4 combat experience levels */
    ExpRule expRule[4];
    if (!ReadC3CMemory(bic.experiencePtr, &expRule, sizeof(expRule))) {
	return 1;
    }
    for (i = 0; i < 4; ++i) {
	printf("Experience level: %s (%d hp, %d retreat)\n",
	       expRule[i].name, expRule[i].hp, expRule[i].retreatBonus);
    }

    CultureRule *cultureRules =
	(CultureRule *) malloc(bic.nCulturalOpinions *
			       sizeof(CultureRule));
    if (!ReadC3CMemory
	(bic.culturePtr, cultureRules,
	 bic.nCulturalOpinions * sizeof(CultureRule))) {
	return 1;
    }
    for (i = 0; i < bic.nCulturalOpinions; ++i) {
	printf("Cultural opinion \"%s\" (%d:%d)\n",
	       cultureRules[i].opinion,
	       cultureRules[i].cultureRatioNumerator,
	       cultureRules[i].cultureRatioDenominator);
    }

    DifficultyRule *difficultyRules =
	(DifficultyRule *) malloc(bic.nDifficultyLevels *
				  sizeof(DifficultyRule));
    if (!ReadC3CMemory(bic.difficultyPtr, difficultyRules,
		       bic.nDifficultyLevels * sizeof(DifficultyRule))) {
	return 1;
    }
    for (i = 0; i < bic.nDifficultyLevels; ++i) {
	printf("Difficulty level: %s (cost factor %d)\n",
	       difficultyRules[i].name, difficultyRules[i].costFactor);
    }

    /* there are always 9 diplomatic / espionage missions */
    SpyRule spyRules[9];
    if (!ReadC3CMemory(bic.espionagePtr, spyRules, sizeof(spyRules))) {
	return 1;
    }
    for (i = 0; i < 9; ++i) {
	printf("Diplomatic/Espionage mission: %s\n", spyRules[i].name);
    }

    /* there are always 4 eras */
    EraRule eraRules[4];
    if (!ReadC3CMemory(bic.erasPtr, eraRules, sizeof(eraRules))) {
	return 1;
    }
    for (i = 0; i < 4; ++i) {
	printf("Era: %s\n", eraRules[i].name);
    }

    /* there seem to be 7 flavors, always */
    FlavorRule flavorRules[7];
    uint32_t flavorPtr;
    /* actual flavor ptr is stored at flavorsPtrPtr + 0x10 */
    if (!ReadC3CMemory
	(bic.flavorsPtrPtr + 0x10, &flavorPtr, sizeof(uint32_t))) {
	return 1;
    }
    if (!ReadC3CMemory(flavorPtr, &flavorRules, sizeof(flavorRules))) {
	return 1;
    }
    for (i = 0; i < 7; ++i) {
	printf("Flavor: %s\n", flavorRules[i].name);
    }

    uint32_t nGovts;
    /* number of govts appears right before address pointed by govtsPtr */
    if (!ReadC3CMemory(bic.govtsPtr - sizeof(uint32_t), &nGovts,
		       sizeof(uint32_t))) {
	return 1;
    }
    printf("Number of governments: %d\n", nGovts);
    GovtRule *govtRules = (GovtRule *) malloc(nGovts * sizeof(GovtRule));
    if (!ReadC3CMemory(bic.govtsPtr, govtRules, nGovts * sizeof(GovtRule))) {
	return 1;
    }
    for (i = 0; i < nGovts; ++i) {
	printf("Government #%02d - %s:\n", i, govtRules[i].name);
    }

    BuildingRule *bldgRules =
	(BuildingRule *) malloc(bic.nBuildings * sizeof(BuildingRule));
    if (!ReadC3CMemory(bic.buildingsPtr, bldgRules,
		       bic.nBuildings * sizeof(BuildingRule))) {
	return 1;
    }
    for (i = 0; i < bic.nBuildings; ++i) {
	printf("Building #%03d: %s (%d shields)\n",
	       i, bldgRules[i].name, bldgRules[i].cost * 10);
    }

    printf("Number of resources: %d\n", bic.nResources);
    ResourceRule *resRules =
	(ResourceRule *) malloc(bic.nResources * sizeof(ResourceRule));
    if (!ReadC3CMemory(bic.resourcesPtr, resRules,
		       bic.nResources * sizeof(ResourceRule))) {
	return 1;
    }
    for (i = 0; i < bic.nResources; ++i) {
	printf("%s: %s\n", resRules[i].name, resRules[i].pedia);
    }

    /* there are always 14 terrain types */
    TerrainRule terrainRules[14];
    if (!ReadC3CMemory(bic.terrainPtr, terrainRules, sizeof(terrainRules))) {
	return 1;
    }
    for (i = 0; i < 14; ++i) {
	printf("Terrain #%02d: %s (%df %ds %dg)\n", i,
	       terrainRules[i].name, terrainRules[i].food,
	       terrainRules[i].shields, terrainRules[i].commerce);
    }

    uint32_t nUnits;
    /* number of units appears right before address pointed by unitsPtr */
    if (!ReadC3CMemory(bic.unitsPtr - sizeof(uint32_t), &nUnits,
		       sizeof(uint32_t))) {
	return 1;
    }
    printf("Number of units: %d\n", nUnits);
    UnitRule *unitRules = (UnitRule *) malloc(nUnits * sizeof(UnitRule));
    if (!ReadC3CMemory(bic.unitsPtr, unitRules, nUnits * sizeof(UnitRule))) {
	return 1;
    }
    for (i = 0; i < nUnits; ++i) {
	printf("Unit #%03d - %s (%d.%d.%d) / %d shields:\n",
	       i, unitRules[i].name,
	       unitRules[i].attack, unitRules[i].defense,
	       unitRules[i].movement, unitRules[i].shieldCost);
    }

    /* there are always 13 worker jobs */
    WorkerRule workerRules[13];
    if (!ReadC3CMemory
	(bic.workerJobsPtr, workerRules, sizeof(workerRules))) {
	return 1;
    }
    for (i = 0; i < 13; ++i) {
	printf("Worker job #%02d: %s\n", i, workerRules[i].name);
    }

    /* there are always 5 world sizes */
    WorldSizeRule wsizRules[5];
    if (!ReadC3CMemory(bic.worldSizesPtr, wsizRules, sizeof(wsizRules))) {
	return 1;
    }
    for (i = 0; i < 5; ++i) {
	printf("World size #%d: %s (%dx%d)\n", i, wsizRules[i].name,
	       wsizRules[i].width, wsizRules[i].height);
    }

    uint32_t nPlayers;
    /* number of players appears right before address pointed by playersPtr */
    if (!ReadC3CMemory(bic.playersPtr - sizeof(uint32_t), &nPlayers,
		       sizeof(uint32_t))) {
	return 1;
    }
    printf("Number of players: %d\n", nPlayers);
    PlayerData *playerData =
	(PlayerData *) malloc(nPlayers * sizeof(PlayerData));
    /* no idea what the first 4 bytes are, but they don't match a player */
    if (!ReadC3CMemory(bic.playersPtr + sizeof(uint32_t), playerData,
		       nPlayers * sizeof(PlayerData))) {
	return 1;
    }
    for (i = 0; i < nPlayers; ++i) {
	/* the index i starts at zero, but counts from "Player 1" */
	printf("Player #%02d - %s (%s):\n", i + 1,
	       raceRules[playerData[i].civId].civName,
	       govtRules[playerData[i].government].name);
    }

    /* There is always a block of memory that holds 32 leaders, even though not
     * all of them are valid (invalid ones will have -1 nationality) */
    Leader leaders[32];
    if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	return 1;
    }
    for (i = 0; i < 32; ++i) {
	if (leaders[i].nationality == -1)
	    break;
	printf("Leader #%02d - %s\n", i,
	       raceRules[leaders[i].nationality].civName);
    }

    /* In-game units are stored as an array of pointers to the unit data,
     * with an integer before each pointer indicating if it is valid total
     * number of units in-game stored at NUM_UNITS_ADDR */
    uint32_t unitsPtr;
    uint32_t unitValid;
    uint32_t unitPtr;
    uint32_t unitCount;
    if (!ReadC3CMemory(NUM_UNITS_ADDR, &unitCount, sizeof(uint32_t))) {
	return 1;
    }
    printf("Units in game: %d\n", unitCount);
    if (!ReadC3CMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(uint32_t))) {
	return 1;
    }
    for (i = 0; i < unitCount; unitsPtr += sizeof(uint32_t)) {
	ReadC3CMemory(unitsPtr, &unitValid, sizeof(uint32_t));
	unitsPtr += sizeof(uint32_t);
	if (unitValid != 0xffffffff) {
	    continue;
	}
	ReadC3CMemory(unitsPtr, &unitPtr, sizeof(uint32_t));
	if (!unitPtr) {
	    continue;
	}
	/* if we get this far, it's a valid unit in-game */
	Unit unit;
	ReadC3CMemory(unitPtr, &unit, sizeof(Unit));
	printf("Unit #%04d - %s, %s (%d,%d):\n",
	       unit.id,
	       raceRules[leaders[unit.owner].nationality].civName,
	       unitRules[unit.type].name, unit.x, unit.y);
	++i;
    }

    uint32_t citiesPtr;
    uint32_t cityValid;
    uint32_t cityPtr;
    if (!ReadC3CMemory(CITIES_BEGIN_ADDR, &citiesPtr, sizeof(uint32_t))) {
	return 1;
    }
    printf("%x\n", citiesPtr);
    do {
	ReadC3CMemory(citiesPtr, &cityValid, sizeof(uint32_t));
	citiesPtr += sizeof(uint32_t);
	if (cityValid != 0xffffffff) {
	    continue;
	}
	ReadC3CMemory(citiesPtr, &cityPtr, sizeof(uint32_t));
	if (cityPtr == 0) {
	    break;
	}
	City city;
	ReadC3CMemory(cityPtr, &city, sizeof(City));
	printf("City #%03d - %s (%d,%d), pop %d:\n",
	       city.id, city.name, city.x, city.y, city.population);
	citiesPtr += sizeof(uint32_t);

	/* read citizen data */
	uint32_t citizensPtr = city.citizenPtr;
	uint32_t citizenValid;
	uint32_t citizenPtr;
	int citizenCount = 0;
	while (citizenCount < city.population) {
	    ReadC3CMemory(citizensPtr, &citizenValid, sizeof(uint32_t));
	    citizensPtr += sizeof(uint32_t);
	    ReadC3CMemory(citizensPtr, &citizenPtr, sizeof(uint32_t));
	    citizensPtr += sizeof(uint32_t);
	    if (citizenValid == 0xffffffff && citizenPtr != 0) {
		Citizen citizen;
		ReadC3CMemory(citizenPtr, &citizen, sizeof(Citizen));
		printf("\tCitizen type: %d\n", citizen.type);
		citizenCount++;
	    }
	}
    } while (!(cityValid == 0xffffffff && cityPtr == 0));

    free(citizenRules);
    free(raceRules);
    free(cultureRules);
    free(difficultyRules);
    free(govtRules);
    free(bldgRules);
    free(resRules);
    free(unitRules);
    free(playerData);
    return 0;
}
