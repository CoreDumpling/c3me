#ifndef MPAPP_H
#define MPAPP_H

#include "c3c.h"
#include <QApplication>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class MPApp : public QApplication {
    Q_OBJECT

    private:
	// bitmask for which players are human-controlled
	uint32_t mask;
	// flag for whether or not multiplayer is enabled
	char flag;
	Bic bic;
	uint32_t nRaces;
	RaceRule *raceRules;
	Leader leaders[32];

	// UI elements
	QWidget widget;
	QGridLayout layout;
	QCheckBox boxes[32]; // one per leader, not all will be used
	QPushButton refreshButton;

    public:
	MPApp(int argc, char *argv[]);
	~MPApp();

    public slots:
	void refresh();
	void update();
};

#endif
