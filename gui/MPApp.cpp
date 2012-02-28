#include "MPApp.h"
#include <QMessageBox>

MPApp::MPApp(int argc, char *argv[]) : QApplication (argc, argv) {
    mask = 0;
    flag = 1;
    raceRules = NULL;
}

MPApp::~MPApp() {
    delete [] raceRules;
}

void MPApp::refresh() {
    /* First get current multiplayer settings */
    if (!ReadC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read multiplayer settings.");
    }
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read multiplayer settings.");
    }

    /* Read BIC data block */
    if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read BIC data.");
    }

    /* Read RACE data for proper names of each civ */
    if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
		       sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read number of civilizations.");
    }
    raceRules = new RaceRule[nRaces];
    if (!ReadC3CMemory(bic.racesPtr, raceRules, nRaces * sizeof(RaceRule))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read RACE data.");
    }

    /* Read LEAD data for civs in current game */
    Leader leaders[32];
    if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read LEAD data.");
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

void MPApp::update() {
    mask = 0;
    flag = 1;
    for (int i = 0; i < 32; ++i) {
	if (boxes[i].isChecked()) {
	    mask |= 1 << i;
	}
    }

    if (!WriteC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read RACE data.");
    }
    if (!WriteC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read RACE data.");
    }
}
