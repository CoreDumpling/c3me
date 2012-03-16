#include "MPApp.h"
#include <QMessageBox>

MPApp::MPApp(int argc, char *argv[]) : QApplication (argc, argv) {
    mask = 0;
    mpFlag = 1;
    pbemFlag = 0;
    raceRules = NULL;

    refreshButton.setText("Refresh");
    connect(&refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    saveChangesButton.setText("Save Changes");
    connect(&saveChangesButton, SIGNAL(clicked()), this, SLOT(saveChanges()));

    hotseatButton.setText("Hotseat");
    hotseatButton.setChecked(true);
    pbemButton.setText("Play by e-mail");
    buttonGroup.addButton(&hotseatButton);
    buttonGroup.addButton(&pbemButton);
    topButtonLayout.addWidget(&hotseatButton);
    topButtonLayout.addWidget(&pbemButton);
    vboxLayout.addLayout(&topButtonLayout);
    groupBox.setTitle("Select Human Civs");
    groupBox.setLayout(&gridLayout);
    vboxLayout.addWidget(&groupBox);
    bottomButtonLayout.addWidget(&refreshButton);
    bottomButtonLayout.addWidget(&saveChangesButton);
    vboxLayout.addLayout(&bottomButtonLayout);
    widget.setLayout(&vboxLayout);
    widget.setWindowTitle("C3C Multiplayer Tool v1.0");
    widget.show();
}

MPApp::~MPApp() {
    delete [] raceRules;
}

void MPApp::refresh() {
    /* First get current multiplayer settings */
    if (!ReadC3CMemory(MP_FLAG_ADDR, &mpFlag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read multiplayer settings.");
	return;
    }
    if (!ReadC3CMemory(PBEM_FLAG_ADDR, &pbemFlag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read multiplayer settings.");
	return;
    }
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read multiplayer settings.");
	return;
    }

    /* Read BIC data block */
    if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read BIC data.");
	return;
    }

    /* Read RACE data for proper names of each civ */
    if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
		       sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read number of civilizations.");
	return;
    }
    raceRules = new RaceRule[nRaces];
    if (!ReadC3CMemory(bic.racesPtr, raceRules, nRaces * sizeof(RaceRule))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read RACE data.");
	return;
    }

    /* Read LEAD data for civs in current game */
    Leader leaders[32];
    if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to read LEAD data.");
	return;
    }

    /* Update radio buttons with current multiplayer mode */
    hotseatButton.setChecked(!pbemFlag);
    pbemButton.setChecked(pbemFlag);

    /* Build checkbox grid */
    while (gridLayout.takeAt(0));
    for (int i = 0; i < 32; ++i) {
	if (leaders[i].nationality == 0xffffffff) {
	    /* invalid leader -- not actually in game */
	    boxes[i].setChecked(false);
	    boxes[i].hide();
	    continue;
	}
	boxes[i].setText(raceRules[leaders[i].nationality].civName);
	boxes[i].setChecked(1 << i & mask);
	boxes[i].show();
	gridLayout.addWidget(&boxes[i], i % 8, i / 8);
    }
}

void MPApp::saveChanges() {
    mask = 0;
    mpFlag = 1;
    for (int i = 0; i < 32; ++i) {
	if (boxes[i].isChecked()) {
	    mask |= 1 << i;
	}
    }

    if (!WriteC3CMemory(MP_FLAG_ADDR, &mpFlag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to write multiplayer settings.");
    }
    pbemFlag = pbemButton.isChecked();
    if (!WriteC3CMemory(PBEM_FLAG_ADDR, &pbemFlag, sizeof(char))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to write multiplayer settings.");
    }
    if (!WriteC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	QMessageBox::warning(NULL, "Operation failed",
	    "Unable to write multiplayer settings.");
    }
}
