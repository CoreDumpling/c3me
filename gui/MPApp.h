#ifndef MPAPP_H
#define MPAPP_H

#include "c3c.h"
#include <QApplication>
#include <QCheckBox>
#include <QGridLayout>
#include <QWidget>

class MPApp : public QApplication {
    Q_OBJECT
    private:
	QWidget widget;
	QGridLayout layout;
	uint32_t mask;
	char flag;
	Bic bic;
	uint32_t nRaces;
	RaceRule *raceRules;
	Leader leaders[32];
	QCheckBox boxes[32];

    public:
	MPApp(int argc, char *argv[]);
	~MPApp();
    public slots:
	void update();
};

#endif
