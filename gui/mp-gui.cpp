#include <QApplication>
#include <QCheckBox>
#include <QGridLayout>
#include <QWidget>

#include <stdio.h>
#include <stdlib.h>
#include "c3c.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget widget;
    QGridLayout layout;

    /* bitmask for which players are human-controlled */
    uint32_t mask = 0;
    /* flag for whether or not multiplayer is enabled */
    char flag = 1;

    if (!FindC3C()) {
	return 1;
    }
    if (!WriteC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	fprintf(stderr, "Unable to activate multiplayer mode.\n");
	return 1;
    }

    /* First get current multiplayer settings */
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	fprintf(stderr, "Unable to verify multiplayer settings.\n");
	return 1;
    }

    /* Read BIC data block */
    Bic bic;
    if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	fprintf(stderr, "Unable to read BIC data.\n");
	return 1;
    }

    /* Read RACE data for proper names of each civ */
    uint32_t nRaces;
    if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
		       sizeof(uint32_t))) {
	fprintf(stderr, "Unable to read number of civilizations.\n");
	return 1;
    }
    RaceRule *raceRules = (RaceRule *) malloc(nRaces * sizeof(RaceRule));
    if (!ReadC3CMemory(bic.racesPtr, raceRules, nRaces * sizeof(RaceRule))) {
	fprintf(stderr, "Unable to read RACE data.\n");
	return 1;
    }

    /* Read LEAD data for civs in current game */
    Leader leaders[32];
    if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	fprintf(stderr, "Unable to read LEAD data.\n");
	return 1;
    }

    QCheckBox boxes[32];
    for (int i = 0; i < 32; ++i) {
	if (leaders[i].nationality == -1) {
	     /* invalid leader -- not actually in game */
	     break;
	}
	boxes[i].setText(raceRules[leaders[i].nationality].civName);
	boxes[i].setChecked(1 << i & mask);
	layout.addWidget(&boxes[i], i % 8, i / 8);
    }
    widget.setLayout(&layout);
    widget.show();
    return app.exec();
}
