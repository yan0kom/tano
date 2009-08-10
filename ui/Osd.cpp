#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "Osd.h"

Osd::Osd(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::ToolTip);

	connect(ui.buttonPlay, SIGNAL(clicked()), this, SIGNAL(play()));
	connect(ui.buttonStop, SIGNAL(clicked()), this, SIGNAL(stop()));
	connect(ui.buttonBack, SIGNAL(clicked()), this, SIGNAL(back()));
	connect(ui.buttonNext, SIGNAL(clicked()), this, SIGNAL(next()));
	connect(ui.buttonMute, SIGNAL(clicked()), this, SIGNAL(mute()));

	connect(ui.labelNow, SIGNAL(linkActivated(QString)), this, SIGNAL(linkActivated(QString)));
	connect(ui.labelNext, SIGNAL(linkActivated(QString)), this, SIGNAL(linkActivated(QString)));
}

Osd::~Osd()
{

}

void Osd::showOsd()
{
	int w = QApplication::desktop()->width();
	int h = QApplication::desktop()->height();
	this->resize(w*0.75,this->height());
	this->move(w/2-this->width()/2,h-this->height());
	this->show();
}

void Osd::hideOsd()
{
	this->hide();
}

void Osd::setNumber(int n)
{
	ui.channelNumber->display(n);
}


void Osd::setMuted(bool mute)
{
	ui.buttonMute->setChecked(mute);
	ui.volumeSlider->setDisabled(mute);
}

void Osd::setStatus(bool status)
{
	if(status)
		hideOsd();
	else
		showOsd();
}

void Osd::setInfo(QString channel, QString language)
{
	ui.labelChannel->setText(channel);
	ui.labelLanguage->setText(language);
}

void Osd::setEpg(bool status, QString now, QString next)
{
	if(status) {
		ui.labelNow->show();
		ui.labelNext->show();
		ui.labelS2->show();
		ui.labelS3->show();
		ui.labelNow->setText(now);
		ui.labelNext->setText(next);
	} else {
		ui.labelNow->hide();
		ui.labelNext->hide();
		ui.labelS2->hide();
		ui.labelS3->hide();
	}
}

void Osd::disableRecorder()
{
	ui.buttonRecord->hide();
}
