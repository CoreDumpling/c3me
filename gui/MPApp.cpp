#include "MPApp.h"
#include <stdio.h>
#include <stdlib.h>

MPApp::MPApp(int argc, char *argv[]) : QApplication (argc, argv) {
    raceRules = NULL;
    flag = 1;

    if (!WriteC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	fprintf(stderr, "Unable to activate multiplayer mode.\n");
    }

    /* First get current multiplayer settings */
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	fprintf(stderr, "Unable to verify multiplayer settings.\n");
    }

    /* Read BIC data block */
    if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	fprintf(stderr, "Unable to read BIC data.\n");
    }

    /* Read RACE data for proper names of each civ */
    if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
		       sizeof(uint32_t))) {
	fprintf(stderr, "Unable to read number of civilizations.\n");
    }
    raceRules = new RaceRule[nRaces];
    if (!ReadC3CMemory(bic.racesPtr, raceRules, nRaces * sizeof(RaceRule))) {
	fprintf(stderr, "Unable to read RACE data.\n");
    }

    /* Read LEAD data for civs in current game */
    Leader leaders[32];
    if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	fprintf(stderr, "Unable to read LEAD data.\n");
    }

    for (int i = 0; i < 32; ++i) {
	if (leaders[i].nationality == -1) {
	     /* invalid leader -- not actually in game */
	     break;
	}
	boxes[i].setText(raceRules[leaders[i].nationality].civName);
	boxes[i].setChecked(1 << i & mask);
	connect(&boxes[i], SIGNAL(released()), this, SLOT(update()));
	layout.addWidget(&boxes[i], i % 8, i / 8);
    }
    widget.setLayout(&layout);
    widget.show();
}

MPApp::~MPApp() {
    delete [] raceRules;
}

void MPApp::update() {
    mask = 0;
    for (int i = 0; i < 32; ++i) {
	if (boxes[i].isChecked()) {
	    mask |= 1 << i;
	}
    }

    if (!WriteC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	fprintf(stderr, "Unable to modify multiplayer settings.\n");
    }
}
