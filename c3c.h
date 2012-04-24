#ifndef C3C_H
#define C3C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This is the title for the English edition of C3C
 * You may need to change it for other editions */
#define CONQUESTS_WINDOW_TITLE "Sid Meier's Civilization III: Conquests"
#define COMPLETE_WINDOW_TITLE "Sid Meier's Civilization III: Complete"

/* Memory addresses -- be careful with these! */
extern uint32_t ADDR_OFFSET;	/* address offset of Complete vs. Conquests */
#define BIC_ADDR                (0x009C34D0 + ADDR_OFFSET)
#define NUM_UNITS_ADDR          (0x00A5264C + ADDR_OFFSET)
#define PLAYER_MASK_ADDR        (0x00A5267C + ADDR_OFFSET)
#define PBEM_FLAG_ADDR          (0x00A52774 + ADDR_OFFSET)
#define MP_FLAG_ADDR            (0x00A52951 + ADDR_OFFSET)
#define UNITS_BEGIN_ADDR        (0x00A52E44 + ADDR_OFFSET)
#define CITIES_BEGIN_ADDR       (0x00A52E2C + ADDR_OFFSET)
#define LEADERS_BEGIN_ADDR      (0x00A52E60 + ADDR_OFFSET)

typedef struct {
    /* BIC+0x0000 */
    char BIC[4];		/* "BIC " */
    uint32_t no_idea_1[3];
    uint32_t biqFilenamePtr;
    uint32_t no_idea_2[67];
    /* BIC+0x0120 */
    char pathNoExt[260];
    char pathWithExt[260];
    char c3cPath[260];
    char ptwPath[260];
    /* BIC+0x0530 */
    uint32_t no_idea_3[64];	/* all zero? */
    char saveTmp[16];		/* sometimes observed to be "save0.tmp" */
    /* BIC+0x0640 */
    char no_idea_4[512];
    uint32_t no_idea_5[10];
    /* BIC+0x0868 */
    uint32_t nTechs;
    uint32_t nUnits;
    uint32_t nBuildings;
    uint32_t no_idea_6;
    uint32_t nCitizens;		/* number of citizen types (for citizensPtr) */
    uint32_t no_idea_6b;
    uint32_t nCulturalOpinions;
    uint32_t nDifficultyLevels;
    uint32_t no_idea_6c[3];
    uint32_t nResources;
    uint32_t no_idea_7;
    uint32_t nPlayers;
    uint32_t no_idea_8[14];
    /* BIC+0x08D8 */
    char description[640];
    char scenarioTitle[64];
    uint32_t no_idea_9;		/* zero? */
    /* BIC+0x0B9C */
    uint32_t buildingsPtr;
    uint32_t citizensPtr;
    uint32_t cityNamesPtr;	/* ??? */
    uint32_t no_idea_10;
    uint32_t culturePtr;
    uint32_t difficultyPtr;
    uint32_t erasPtr;
    uint32_t espionagePtr;
    uint32_t experiencePtr;
    uint32_t no_idea_11[2];	/* zero? */
    uint32_t no_idea_12_ptr;	/* points to a sequence of uint32_tS, 01-1f */
    uint32_t no_idea_13_ptr;
    uint32_t no_idea_14[2];
    /* BIC+0x0BD8 */
    uint32_t autoPlaceCaptureUnits;
    uint32_t autoPlaceKingUnits;
    uint32_t autoPlaceVictoryLocations;
    uint32_t useDebugMode;
    uint32_t useTimeLimits;
    uint32_t baseTimeUnit;	/* 0 = years, 1 = months, 2 = weeks */
    uint32_t startMonth;	/* 1-12 */
    uint32_t startWeek;		/* 1-52 */
    int32_t startYear;		/* negative if BC */
    uint32_t timeLimitMinutes;
    uint32_t timeLimitTurns;
    uint32_t timeScaleTurns[7];
    uint32_t timeScaleUnits[7];
    /* BIC+0x0C3C */
    uint32_t victoryPointLimit;
    uint32_t cityEliminationCount;
    uint32_t cultureVictoryCity;
    uint32_t cultureVictoryCiv;
    uint32_t terrainForDomination;
    uint32_t populationForDomination;
    uint32_t wonderVP;
    uint32_t defeatUnitVP;
    uint32_t advanceVP;
    uint32_t cityConquestVP;
    uint32_t victoryPointLocationVP;
    uint32_t captureUnitVP;
    uint32_t captureUnitGold;
    uint32_t no_idea_15;
    /* BIC+0x0C74 */
    char scenarioSearchFolders[5200];
    uint32_t no_idea_16[64];	/* zero? */
    /* BIC+0x21C4 */
    char alliance1Name[256];
    char alliance2Name[256];
    char alliance3Name[256];
    char alliance4Name[256];
    uint32_t no_idea_17[101];	/* includes plague stuff */
    char scenarioTitle2[260];	/* padded with lots of 0xCD ??? */
    uint32_t no_idea_18[1305];
    /* BIC+0x3CC0 */
    uint32_t racesPtr;
    uint32_t resourcesPtr;
    uint32_t govtsPtr;
    uint32_t playersPtr;
    uint32_t unitsPtr;
    uint32_t menuArtPtr;	/* ? */
    uint32_t no_idea_19;	/* zero? */
    char citySize1[32];
    char citySize2[32];
    char citySize3[32];
    /* BIC+0x3D3C */
    uint32_t no_idea_20[42];	/* general settings, mostly */
    uint32_t culturalLevelsPtr;	/* Fledgling, Weak, ..., Glorious */
    uint32_t levelMultiplier;	/* ? */
    uint32_t nCulturalLevels;	/* ? */
    uint32_t borderFactor;	/* ? */
    uint32_t futureTechCost;
    uint32_t no_idea_21[6];
    /* BIC+0x3E10 */
    uint32_t techsPtr;
    uint32_t workerJobsPtr;
    uint32_t terrainPtr;
    uint32_t no_idea_22_ptr;
    uint32_t worldSizesPtr;
    uint32_t flavorsPtrPtr;	/* actual flavorPtr is at flavorsPtrPtr+0x10 */
    uint32_t screenWidthPixels;
    uint32_t screenHeightPixels;
    uint32_t no_idea_24;
} Bic;

/* Citizens tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    uint32_t defaultCitizen;
    char name[32];
    char pedia[32];
    char plural[32];
    uint32_t prerequisite;
    uint32_t luxury;
    uint32_t science;
    uint32_t tax;
    uint32_t corruption;
    uint32_t construction;
} CitizenRule;

/* Civilizations tab in rules editor */
typedef struct {
    uint32_t no_idea_1[5];
    uint32_t cityNamesPtr;
    uint32_t milLeadersPtr;
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
    uint32_t cultureGroup;
    uint32_t leaderGender;
    uint32_t civGender;
    uint32_t aggressionLevel;
    uint32_t civCounter;
    uint32_t shunnedGovt;
    uint32_t favoriteGovt;
    uint32_t numCityNames;
    uint32_t numMilLeaders;
    uint32_t defaultColor;
    uint32_t alternateColor;
    uint32_t freeTech1;
    uint32_t freeTech2;
    uint32_t freeTech3;
    uint32_t freeTech4;
    uint32_t traits;
    uint32_t governorSettings;
    uint32_t buildNever;
    uint32_t buildOften;
    uint32_t plurality;
    uint32_t kingUnit;
    uint32_t flavors;
    uint32_t no_idea_2;
    uint32_t dipTextIndex;
    uint32_t numSciLeaders;
    uint32_t sciLeadersPtr;
} RaceRule;

/* Civilization Advances tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char name[32];
    char pedia[32];
    uint32_t cost;
    uint32_t era;
    uint32_t icon;
    uint32_t x;			/* tech tree position on screen */
    uint32_t y;			/* tech tree position on screen */
    uint32_t prerequisites[4];
    uint32_t flags;
    uint32_t flavors;
    uint32_t no_idea_2;		/* one? */
} TechRule;

/* Combat Experience tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char name[32];
    uint32_t hp;
    uint32_t retreatBonus;
} ExpRule;

/* Culture tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char opinion[64];
    uint32_t propagandaChance;
    uint32_t cultureRatioPercentage;	/* 3:1 is 300, 3:4 is 75 */
    uint32_t cultureRatioDenominator;
    uint32_t cultureRatioNumerator;
    uint32_t initialResistanceChance;
    uint32_t continuedResistanceChance;
} CultureRule;

/* Difficulty Levels tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char name[64];
    uint32_t bornContent;
    uint32_t maxGovtTransitionTime;
    uint32_t aiDefensiveLandUnits;
    uint32_t aiOffensiveLandUnits;
    uint32_t aiExtraStartUnit1;
    uint32_t aiExtraStartUnit2;
    uint32_t aiFreeSupport;
    uint32_t aiBonusSupportPerCity;
    uint32_t bonusVsBarbs;
    uint32_t costFactor;
    uint32_t percentOptimalCities;
    uint32_t aiTradeRate;
    uint32_t corruption;	/* percent */
    uint32_t citizensQuelledByMilitary;
} DifficultyRule;

/* Diplomats and Spies tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char description[128];
    char name[64];
    char pedia[32];
    uint32_t performedBy;	/* mask: 0x0001 diplomat, 0x0002 spy */
    uint32_t baseCost;
} SpyRule;

/* Eras tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char name[64];
    char pedia[32];
    char researchers[32][5];
    uint32_t nResearchers;
    uint32_t no_idea_2;		/* one? */
} EraRule;

/* Flavors tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* one? */
    char name[256];
    uint32_t numFlavors;	/* always 7? */
    uint32_t no_idea_2;		/* one? */
    uint32_t relationsPtr;	/* pointer to 7 ints, one for each flavor */
    uint32_t no_idea_3;		/* pointer? */
    uint32_t no_idea_4;		/* same pointer repeated? */
} FlavorRule;

/* Governments tab in rules editor */
typedef struct {
    uint32_t no_idea_1[3];
    uint32_t defaultType;
    uint32_t transitionType;
    uint32_t requiresMaintainence;
    uint32_t no_idea_2;
    uint32_t standardTilePenalty;
    uint32_t standardTradeBonus;
    uint32_t no_idea_3[2];
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
    uint32_t corruption;
    uint32_t immune;
    uint32_t diplomats;
    uint32_t spies;
    uint32_t vsGovtPtr;
    uint32_t hurry;
    uint32_t assimilation;
    uint32_t draftLimit;
    uint32_t militaryPoliceLimit;
    uint32_t numGovts;		/* for vsGovtPtr */
    uint32_t numTitlePairs;
    uint32_t prerequisiteTech;
    uint32_t scienceCap;
    uint32_t workerRate;
    uint32_t no_idea_4;
    uint32_t no_idea_5;
    uint32_t freeUnits;
    uint32_t allUnitsFree;	/* -1 = yes, 0 = no */
    uint32_t freeUnitsPerTown;
    uint32_t freeUnitsPerCity;
    uint32_t freeUnitsPerMetro;
    uint32_t costPerUnit;
    uint32_t warWeariness;
} GovtRule;

/* Improvements and Wonders tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char description[64];	/* blank? */
    char name[32];
    char pedia[32];
    uint32_t doublesHappinessOf;
    uint32_t gainInEveryCity;
    uint32_t gainInEveryCityOnContinent;
    uint32_t requiredBuilding;
    uint32_t cost;
    uint32_t culture;
    uint32_t bombardDefense;
    uint32_t navalBombardDefense;
    uint32_t defenseBonus;
    uint32_t navalDefenseBonus;
    uint32_t maintenance;
    uint32_t happyFacesAllCities;
    uint32_t happyFaces;
    uint32_t unhappyFacesAllCities;
    uint32_t unhappyFaces;
    uint32_t numRequiredBuildings;
    uint32_t airPower;
    uint32_t navalPower;
    uint32_t pollution;
    uint32_t production;
    uint32_t requiredGovt;
    uint32_t spaceshipPart;
    uint32_t requiredTech;
    uint32_t obsoleteBy;
    uint32_t requiredResource1;
    uint32_t requiredResource2;
    uint32_t improvementFlags;
    uint32_t otherCharacteristics;
    uint32_t smallWonderFlags;
    uint32_t wonderFlags;
    uint32_t numArmies;
    uint32_t flavors;
    uint32_t no_idea_2;
    uint32_t unitProduced;
    uint32_t unitFrequency;
} BuildingRule;

/* Natural Resources tab in rules editor */
typedef struct {
    uint32_t no_idea_1;
    char name[16];
    uint32_t no_idea_2;
    uint32_t no_idea_3;
    char pedia[32];
    uint32_t type;
    uint32_t appearance;
    uint32_t disappearance;
    uint32_t icon;
    uint32_t prerequisite;
    uint32_t food;
    uint32_t shields;
    uint32_t commerce;
} ResourceRule;

/* Terrain tab in rules editor */
typedef struct {
    uint32_t no_idea_1[3];
    char name[32];
    char pedia[32];
    uint32_t irrigationBonus;
    uint32_t mineBonus;
    uint32_t roadBonus;
    uint32_t defenseBonus;
    uint32_t movementCost;
    uint32_t no_idea_2;		/* 0x1A? -- possibly number of resources? */
    uint32_t food;
    uint32_t shields;
    uint32_t commerce;
    uint32_t workerJob;		/* plant forest, clear forest & wetlands */
    uint32_t pollutionEffect;
    uint8_t allowCities;
    uint8_t allowColonies;
    uint8_t impassable;
    uint8_t impassableByWheeled;
    uint8_t allowAirfields;
    uint8_t allowForts;
    uint8_t allowRadarTowers;
    uint32_t no_idea_3;		/* 0x03? */
    uint32_t landmarkEnabled;	/* seems to be first byte only */
    uint32_t landmarkFood;
    uint32_t landmarkShields;
    uint32_t landmarkCommerce;
    uint32_t landmarkIrrigationBonus;
    uint32_t landmarkMineBonus;
    uint32_t landmarkRoadBonus;
    uint32_t landmarkMovementCost;
    uint32_t landmarkDefenseBonus;
    char landmarkName[32];
    char landmarkPedia[32];
    uint32_t no_idea_4;		/* 0xc0cccccc? */
    uint32_t diseaseStrength;
} TerrainRule;

/* Units tab in rules editor */
typedef struct {
    uint32_t no_idea_1;
    uint32_t zone_of_control;
    char name[32];
    char pedia[32];
    uint32_t bombard;
    uint32_t bombardRange;
    uint32_t capacity;
    uint32_t shieldCost;
    uint32_t defense;
    uint32_t iconIndex;
    uint32_t attack;
    uint32_t operationalRange;
    uint32_t popCost;
    uint32_t rateOfFire;
    uint32_t movement;
    uint32_t requiredTech;
    uint32_t upgradeTo;
    uint32_t requiredResource1;
    uint32_t requiredResource2;
    uint32_t requiredResource3;
    uint32_t unitAbilities;
    uint32_t aiStrategy;
    uint32_t availableTo;
    uint32_t specialActions;
    uint32_t airMissions;
    uint32_t unitClass;
    uint32_t otherStrategy;
    int32_t hpBonus;
    uint32_t standardOrdersPTW;
    uint32_t specialActionsPTW[2];
    uint32_t airMissionsPTW;
    uint32_t actionsMix;
    uint32_t bombardEffects;
    uint32_t ignoreMovement[4];
    uint32_t requireSupport;
    uint32_t no_idea_2[4];
    uint32_t enslaveResults;
    uint32_t no_idea_3;
    uint32_t numStealthTargets;
    uint32_t no_idea_4[2];
    uint32_t createCraters;
    uint32_t workerStrength;
    uint32_t no_idea_5;
    uint32_t airDefense;
    uint32_t no_idea_6[12];
} UnitRule;

/* Worker Jobs tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    char name[32];
    char pedia[32];
    uint32_t turns;
    uint32_t requiredTech;
    uint32_t requiredResource1;
    uint32_t requiredResource2;
    char order[32];
} WorkerRule;

/* World Sizes tab in rules editor */
typedef struct {
    uint32_t no_idea_1;		/* zero? */
    uint32_t ocn;		/* optimal city number */
    uint32_t techRate;
    uint32_t no_idea_2[6];	/* zero? */
    char name[32];
    uint32_t height;
    uint32_t distanceBetweenCivs;
    uint32_t numCivs;
    uint32_t width;
} WorldSizeRule;

/* Player data from scenario properties */
typedef struct {
    uint32_t customCivData;
    uint32_t humanPlayer;
    char leaderName[32];
    uint32_t no_idea_1[2];
    uint32_t numStartUnits;
    uint32_t no_idea_2;
    uint32_t startTechsPtr;
    uint32_t difficulty;
    uint32_t initialEra;
    uint32_t startGold;
    uint32_t government;
    uint32_t numStartTechs;
    uint32_t no_idea_3;
    uint32_t civId;
    uint32_t color;
    uint32_t no_idea_4[4];
} PlayerData;

/* In-game unit informaton */
typedef struct {
    uint32_t no_idea_1;
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t prevx;
    uint32_t prevy;
    uint32_t owner;
    uint32_t nationality;
    uint32_t no_idea_3;
    uint32_t type;
    uint32_t experience;
    uint32_t no_idea_4;
    uint32_t damage;
    uint32_t usedMovement;
    uint32_t no_idea_5;
    uint32_t workerAction;
    uint32_t no_idea_6[2];
    uint32_t fortified;
    uint32_t endTurn;
    uint32_t no_idea_7[2];
    char name[32];
    uint32_t no_idea_8[7];	/* all 0000's */
    uint32_t no_idea_9[4];	/* all FFFF's */
} Unit;

/* In-game city information */
typedef struct {
    uint32_t no_idea_1;
    uint32_t id;
    uint16_t x;
    uint16_t y;
    uint32_t owner; /* value seems to be only least significant byte? */
    uint32_t no_idea_2[5];
    uint32_t currentFood;
    uint32_t currentShields;
    uint32_t no_idea_3;
    uint32_t currentBuild;
    uint32_t currentBuildType;	/* 1 = building, 2 = unit */
    uint32_t no_idea_4[23];
    uint32_t BINF;		/* "BINF" */
    uint32_t no_idea_5[11];
    uint32_t citizenPtr;
    uint32_t no_idea_6[21];
    uint32_t population;
    uint32_t culturePerTurn;
    uint32_t culture[32]; /* one culture value for each civ */
    uint32_t no_idea_8[8];
    char name[24];
} City;

/* In-game citizen information */
typedef struct {
    uint32_t no_idea_1;
    char desc[64];		/* auto-generated no idea about true length */
    uint32_t no_idea_2[48];	/* all zeros? */
    uint32_t no_idea_3[7];
    uint32_t type;		/* 0 = laborer, 1 = entertainer,
				 * 2 = tax collector, 3 = scientist,
				 * 4 = policeman, 5 = civil engineer */
    uint32_t race;
    uint32_t no_idea_4[3];
} Citizen;

/* In-game player ("leader") information */
typedef struct {
    /* LEAD+0x0000 */
    char LEAD[4];		/* "LEAD" */
    uint32_t no_idea_1[4];
    uint32_t id;
    uint32_t nationality;
    uint32_t no_idea_2[2];
    uint32_t capitalCityId;
    uint32_t no_idea_3[5];
    int32_t posGold;		/* total gold is posGold + negGold */
    int32_t negGold;		/* negGold is a negative number */
    uint32_t no_idea_4[21];
    /* LEAD+0x0098 */
    uint32_t govt;
    uint32_t no_idea_5[21];
    uint32_t beakers;
    uint32_t researchTech;
    uint32_t no_idea_6[35];
    /* LEAD+0x0184 */
    uint32_t nUnits;		/* number of units owned by this civ */
    uint32_t no_idea_7[5];
    uint32_t luxury;		/* scale of 0-10 */
    uint32_t science;		/* scale of 0-10 */
    uint32_t tax;		/* scale of 0-10 */
    uint32_t no_idea_8[832];
    /* LEAD+0x0EA8 */
    uint32_t contacts[32];	/* 1 or 0 for contact with each other leader */
    uint32_t no_idea_9[114];
    /* LEAD+0x10F0 */
    uint32_t color;		/* in-game color, not derived from rules */
    char leaderName[32];	/* user-input name */
    char leaderTitle[24];	/* user-input title */
    char civName[40];		/* user-input civ name */
    char noun[40];		/* user-input civ, collective noun */
    char adjective[40];		/* user-input civ, adjective */
    uint32_t no_idea_10[2];	/* singular/plural? gender? */
    /* LEAD+0x11AC */
    uint32_t no_idea_11[4];	/* non-zero values */
    uint32_t no_idea_12[16];	/* zeros? */
    char password[256];		/* size of 256 is just a guess, may be wrong */
    uint32_t no_idea_13[890];
} Leader;

extern int FindC3C();
extern int ReadC3CMemory(uint32_t lpAddress, void *buf, int len);
extern int WriteC3CMemory(uint32_t lpAddress, void *buf, int len);

#ifdef __cplusplus
}
#endif

#endif
