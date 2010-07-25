#include <windows.h>

// This is the title for the English edition of C3C
// You may need to change it for other editions
#define C3C_WINDOW_TITLE "Sid Meier's Civilization III: Conquests"

// Memory addresses -- be careful with these!
#define BIC_ADDR                0x009C34D0
#define NUM_UNITS_ADDR          0x00A5264C
#define UNITS_BEGIN_ADDR        0x00A52E44
#define CITIES_BEGIN_ADDR       0x00A52E2C
#define LEADERS_BEGIN_ADDR      0x00A52E60

typedef struct {
        // BIC+0x0000
        char BIC[4]; // "BIC "
        DWORD no_idea_1[3];
        DWORD biqFilenamePtr;
        DWORD no_idea_2[67];
        // BIC+0x0120
        char pathNoExt[260];
        char pathWithExt[260];
        char c3cPath[260];
        char ptwPath[260];
        // BIC+0x0530
        DWORD no_idea_3[64]; // all zero?
        char saveTmp[16]; // sometimes observed to be "save0.tmp"
        // BIC+0x0640
        char no_idea_4[512];
        DWORD no_idea_5[10];
        // BIC+0x0868
        DWORD nTechs;
        DWORD nUnits;
        DWORD nBuildings;
        DWORD no_idea_6;
	DWORD nCitizens; // number of citizen types (for citizensPtr)
        DWORD no_idea_6b;
	DWORD nCulturalOpinions;
        DWORD nDifficultyLevels;
        DWORD no_idea_6c[3];
        DWORD nResources;
        DWORD no_idea_7;
        DWORD nPlayers;
        DWORD no_idea_8[14];
        // BIC+0x08D8
        char description[640];
        char scenarioTitle[64];
        DWORD no_idea_9; // zero?
        // BIC+0x0B9C
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
        // BIC+0x0BD8
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
        // BIC+0x0C3C
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
        DWORD victoryPointLocationVP;
        DWORD captureUnitVP;
        DWORD captureUnitGold;
        DWORD no_idea_15;
        // BIC+0x0C74
        char scenarioSearchFolders[5200];
        DWORD no_idea_16[64]; // zero?
        // BIC+0x21C4
        char alliance1Name[256];
        char alliance2Name[256];
        char alliance3Name[256];
        char alliance4Name[256];
        DWORD no_idea_17[101]; // includes plague stuff
        char scenarioTitle2[260]; // padded with lots of 0xCD ???
        DWORD no_idea_18[1305];
        // BIC+0x3CC0
        DWORD racesPtr;
        DWORD resourcesPtr;
        DWORD govtsPtr;
        DWORD playersPtr;
        DWORD unitsPtr;
        DWORD menuArtPtr; // ?
        DWORD no_idea_19; // zero?
        char citySize1[32];
        char citySize2[32];
        char citySize3[32];
        // BIC+0x3D3C
        DWORD no_idea_20[42]; // general settings, mostly
        DWORD culturalLevelsPtr; // Fledgling, Weak, ..., Glorious
        DWORD levelMultiplier; // ?
        DWORD nCulturalLevels; // ?
        DWORD borderFactor; // ?
        DWORD futureTechCost;
        DWORD no_idea_21[6];
        // BIC+0x3E10
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

// Citizens tab in rules editor
typedef struct {
	DWORD no_idea_1; // zero?
	DWORD defaultCitizen;
	char name[32];
	char pedia[32];
	char plural[32];
	DWORD prerequisite;
	DWORD luxury;
	DWORD science;
	DWORD tax;
	DWORD corruption;
	DWORD construction;
} CitizenRule;

// Civilizations tab in rules editor
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
} RaceRule;

// Civilization Advances tab in rules editor
typedef struct {
	DWORD no_idea_1; // zero?
	char name[32];
	char pedia[32];
	DWORD cost;
	DWORD era;
	DWORD icon;
	DWORD x; // tech tree position on screen
	DWORD y; // tech tree position on screen
	DWORD prerequisites[4];
	DWORD flags;
	DWORD flavors;
	DWORD no_idea_2; // one?
} TechRule;

// Combat Experience tab in rules editor
typedef struct {
	DWORD no_idea_1; // zero?
	char name[32];
	DWORD hp;
	DWORD retreatBonus;
} ExpRule;

// Culture tab in rules editor
typedef struct {
	DWORD no_idea_1; // zero?
	char opinion[64];
	DWORD propagandaChance;
	DWORD cultureRatioPercentage; // 3:1 is 300, 3:4 is 75
	DWORD cultureRatioDenominator;
	DWORD cultureRatioNumerator;
	DWORD initialResistanceChance;
	DWORD continuedResistanceChance;
} CultureRule;

// Difficulty Levels tab in rules editor
typedef struct {
	DWORD no_idea_1; // zero?
	char name[64];
	DWORD bornContent;
	DWORD maxGovtTransitionTime;
	DWORD aiDefensiveLandUnits;
	DWORD aiOffensiveLandUnits;
	DWORD aiExtraStartUnit1;
	DWORD aiExtraStartUnit2;
	DWORD aiFreeSupport;
	DWORD aiBonusSupportPerCity;
	DWORD bonusVsBarbs;
	DWORD costFactor;
	DWORD percentOptimalCities;
	DWORD aiTradeRate;
	DWORD corruption; // percent
	DWORD citizensQuelledByMilitary;
} DifficultyRule;

// Diplomats and Spies tab in rules editor
typedef struct {
        DWORD no_idea_1; // zero?
        char description[128];
        char name[64];
        char pedia[32];
        DWORD performedBy; // mask: 0x0001 diplomat, 0x0002 spy
        DWORD baseCost;
} SpyRule;

// Eras tab in rules editor
typedef struct {
        DWORD no_idea_1; // zero?
        char name[64];
        char pedia[32];
        char researchers[32][5];
        DWORD nResearchers;
        DWORD no_idea_2; // one?
} EraRule;

// Governments tab in rules editor
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
} GovtRule;

// Improvements and Wonders tab in rules editor
typedef struct {
        DWORD no_idea_1; // zero?
        char description[64]; // blank?
        char name[32];
        char pedia[32];
        DWORD doublesHappinessOf;
        DWORD gainInEveryCity;
        DWORD gainInEveryCityOnContinent;
        DWORD requiredBuilding;
        DWORD cost;
        DWORD culture;
        DWORD bombardDefense;
        DWORD navalBombardDefense;
        DWORD defenseBonus;
        DWORD navalDefenseBonus;
        DWORD maintenance;
        DWORD happyFacesAllCities;
        DWORD happyFaces;
        DWORD unhappyFacesAllCities;
        DWORD unhappyFaces;
        DWORD numRequiredBuildings;
        DWORD airPower;
        DWORD navalPower;
        DWORD pollution;
        DWORD production;
        DWORD requiredGovt;
        DWORD spaceshipPart;
        DWORD requiredTech;
        DWORD obsoleteBy;
        DWORD requiredResource1;
        DWORD requiredResource2;
        DWORD improvementFlags;
        DWORD otherCharacteristics;
        DWORD smallWonderFlags;
        DWORD wonderFlags;
        DWORD numArmies;
        DWORD flavors;
        DWORD no_idea_2;
        DWORD unitProduced;
        DWORD unitFrequency;
} BuildingRule;

// Natural Resources tab in rules editor
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
} ResourceRule;

// Terrain tab in rules editor
typedef struct {
        DWORD no_idea_1[3];
        char name[32];
        char pedia[32];
        DWORD irrigationBonus;
        DWORD mineBonus;
        DWORD roadBonus;
        DWORD defenseBonus;
        DWORD movementCost;
        DWORD no_idea_2; // 0x1A? -- possibly number of resources?
        DWORD food;
        DWORD shields;
        DWORD commerce;
        DWORD workerJob; // only plant forest, clear forest, clear wetlands
        DWORD pollutionEffect;
        BYTE allowCities;
        BYTE allowColonies;
        BYTE impassable;
        BYTE impassableByWheeled;
        BYTE allowAirfields;
        BYTE allowForts;
        BYTE allowRadarTowers;
        DWORD no_idea_3; // 0x03?
        DWORD landmarkEnabled; // seems to be first byte only
        DWORD landmarkFood;
        DWORD landmarkShields;
        DWORD landmarkCommerce;
        DWORD landmarkIrrigationBonus;
        DWORD landmarkMineBonus;
        DWORD landmarkRoadBonus;
        DWORD landmarkMovementCost;
        DWORD landmarkDefenseBonus;
        char landmarkName[32];
        char landmarkPedia[32];
        DWORD no_idea_4; // 0xc0cccccc?
        DWORD diseaseStrength;
} TerrainRule;

// Units tab in rules editor
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
        DWORD ignoreMovement[4];
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
} UnitRule;

// Player data from scenario properties
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
} PlayerData;

// In-game unit informaton
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

// In-game city information
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

// In-game citizen information
typedef struct {
        DWORD no_idea_1;
        char desc[64]; // auto-generated no idea about true length
        DWORD no_idea_2[48]; // all zeros?
        DWORD no_idea_3[7];
        DWORD type; // 0 = laborer, 1 = ent, 2 = tax, 3 = sci, 4 = pol, 5 = eng
        DWORD race;
        DWORD no_idea_4[3];
} Citizen;

// In-game player ("leader") information
typedef struct {
        char LEAD[4]; // "LEAD"
        DWORD no_idea_1[4];
        DWORD id;
        DWORD nationality;
	DWORD no_idea_2[2];
        DWORD capitalCityId;
        DWORD no_idea_3[5];
        DWORD posGold; // total gold is posGold + negGold
	DWORD negGold; // negGold is a negative number
        DWORD no_idea_4[21];
	DWORD govt;
        DWORD no_idea_5[21];
        DWORD beakers;
        DWORD researchTech;
        DWORD no_idea_6[35];
        DWORD nUnits; // number of units owned by this civ
        DWORD no_idea_7[5];
        DWORD luxury;
        DWORD science;
        DWORD tax;
        DWORD no_idea_8[832];
        DWORD contacts[32];
        DWORD no_idea_9[1135];
} Leader;

extern BOOL ReadC3CMemory(DWORD lpAddress, void* buf, int len);
extern BOOL WriteC3CMemory(DWORD lpAddress, void* buf, int len);
