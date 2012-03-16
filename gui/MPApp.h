#ifndef MPAPP_H
#define MPAPP_H

#include "c3c.h"
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class MPApp : public QApplication {
    Q_OBJECT

    private:
	// bitmask for which players are human-controlled
	uint32_t mask;
	// flag for whether or not multiplayer is enabled
	char mpFlag;
	// flag for whether or not play by e-mail is enabled
	char pbemFlag;
	Bic bic;
	uint32_t nRaces;
	RaceRule *raceRules;
	Leader leaders[32];

	// UI elements
	QWidget widget;
	QVBoxLayout vboxLayout;
	QHBoxLayout topButtonLayout;
	QRadioButton hotseatButton;
	QRadioButton pbemButton;
	QButtonGroup buttonGroup;
	QGroupBox groupBox;
	QGridLayout gridLayout;
	QCheckBox boxes[32]; // one per leader, not all will be used
	QHBoxLayout bottomButtonLayout;
	QPushButton refreshButton;
	QPushButton saveChangesButton;

    public:
	MPApp(int argc, char *argv[]);
	~MPApp();

    public slots:
	void refresh();
	void saveChanges();
};

#endif
