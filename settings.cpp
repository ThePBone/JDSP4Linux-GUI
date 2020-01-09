#include "settings.h"
#include "ui_settings.h"
#include "main.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QDialog>

#include <QCloseEvent>
#include <cstdio>
#include <cstdlib>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>
#include "palette.h"

using namespace std;
static bool lockslot = false;
settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings){
    ui->setupUi(this);

    lockslot = true;
    connect(ui->styleSelect,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(changeStyle(const QString&)));
    connect(ui->paletteSelect,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(changePalette(const QString&)));

    char result[100] = "Z:/JamesDSP/audio.conf";

    string path = mainwin->getPath();
    string style_sheet = mainwin->getStylesheet();
    int thememode = mainwin->getThememode();
    string palette = mainwin->getColorpalette();
    int autofxmode = mainwin->getAutoFxMode();
    string theme = mainwin->getTheme();

    if(path.empty()) ui->path->setText(QString::fromUtf8(result));
    else ui->path->setText(QString::fromStdString(path));

    ui->autofx->setChecked(mainwin->getAutoFx());
    ui->glavafix->setChecked(mainwin->getGFix());
    ui->addpadding->setChecked(mainwin->getWhiteIcons());

    connect(ui->close, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->github, SIGNAL(clicked()), this, SLOT(github()));
    connect(ui->glavafix_help, SIGNAL(clicked()), this, SLOT(glava_help()));
    connect(ui->uimode_css, SIGNAL(clicked()), this, SLOT(changeThemeMode()));
    connect(ui->uimode_pal, SIGNAL(clicked()), this, SLOT(changeThemeMode()));

    connect(ui->aa_instant, SIGNAL(clicked()), this, SLOT(updateAutoFxMode()));
    connect(ui->aa_release, SIGNAL(clicked()), this, SLOT(updateAutoFxMode()));

    connect(ui->themeSelect, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateTheme()));
    connect(ui->glavafix, SIGNAL(clicked()), this, SLOT(updateGLava()));
    connect(ui->addpadding, SIGNAL(clicked()), this, SLOT(updateWhiteIcons()));
    connect(ui->autofx, SIGNAL(clicked()), this, SLOT(updateAutoFX()));
    connect(ui->savepath, SIGNAL(clicked()), this, SLOT(updatePath()));

    ui->styleSelect->addItem("Default","default");
    ui->styleSelect->addItem("Black","amoled");
    ui->styleSelect->addItem("Blue","blue");
    ui->styleSelect->addItem("Breeze Light","breeze_light");
    ui->styleSelect->addItem("Breeze Dark","breeze_dark");
    ui->styleSelect->addItem("MacOS","aqua");
    ui->styleSelect->addItem("Material Dark","materialdark");
    ui->styleSelect->addItem("Ubuntu","ubuntu");
    ui->styleSelect->addItem("Visual Studio Dark","vsdark");
    ui->styleSelect->addItem("Visual Studio Light","vslight");

    ui->paletteSelect->addItem("Default","default");
    ui->paletteSelect->addItem("Black","black");
    ui->paletteSelect->addItem("Blue","blue");
    ui->paletteSelect->addItem("Dark","dark");
    ui->paletteSelect->addItem("Dark Blue","darkblue");
    ui->paletteSelect->addItem("Dark Green","darkgreen");
    ui->paletteSelect->addItem("Honeycomb","honeycomb");
    ui->paletteSelect->addItem("Gray","gray");
    ui->paletteSelect->addItem("Purple","purple");
    ui->paletteSelect->addItem("Silver","silver");
    ui->paletteSelect->addItem("Solarized","solarized");
    ui->paletteSelect->addItem("White","white");
    ui->paletteSelect->addItem("Custom","custom");

    for ( const auto& i : QStyleFactory::keys() )
        ui->themeSelect->addItem(i);

    QString qvT(QString::fromStdString(theme));
    int index = ui->themeSelect->findText(qvT);
    if ( index != -1 ) {
       ui->themeSelect->setCurrentIndex(index);
    }else{
        int index_fallback = ui->themeSelect->findText("Fusion");
        if ( index_fallback != -1 )
           ui->themeSelect->setCurrentIndex(index_fallback);
    }

    QVariant qvS(QString::fromStdString(style_sheet));
    int indexT = ui->styleSelect->findData(qvS);
    if ( indexT != -1 ) {
       ui->styleSelect->setCurrentIndex(indexT);
    }

    QVariant qvS2(QString::fromStdString(palette));
    int index2 = ui->paletteSelect->findData(qvS2);
    if ( index2 != -1 ) {
       ui->paletteSelect->setCurrentIndex(index2);
    }


    ui->styleSelect->setEnabled(!thememode);
    ui->paletteConfig->setEnabled(thememode && palette=="custom");
    ui->paletteSelect->setEnabled(thememode);

    ui->uimode_css->setChecked(!thememode);//If 0 set true, else false
    ui->uimode_pal->setChecked(thememode);//If 0 set false, else true

    ui->addpadding->setEnabled(!thememode || palette=="custom");

    ui->aa_instant->setChecked(!autofxmode);//same here..
    ui->aa_release->setChecked(autofxmode);

    lockslot = false;
}
settings::~settings(){
    delete ui;
}
void settings::updateWhiteIcons(){
    mainwin->setWhiteIcons(ui->addpadding->isChecked());
}
void settings::updateAutoFX(){
    mainwin->setAutoFx(ui->autofx->isChecked());
}
void settings::updatePath(){
    mainwin->setPath(ui->path->text().toUtf8().constData());
}
void settings::updateGLava(){
    mainwin->setGFix(ui->glavafix->isChecked());
}
void settings::updateAutoFxMode(){
    if(lockslot)return;
    int mode = 0;
    if(ui->aa_instant->isChecked())mode=0;
    else if(ui->aa_release->isChecked())mode=1;
    mainwin->setAutoFxMode(mode);
}
void settings::updateTheme(){
    if(lockslot)return;
    mainwin->setTheme(ui->themeSelect->itemText(ui->themeSelect->currentIndex()).toUtf8().constData());
}
void settings::changeThemeMode(){
    if(lockslot)return;

    int mode = 0;
    if(ui->uimode_css->isChecked())mode=0;
    else if(ui->uimode_pal->isChecked())mode=1;
    ui->addpadding->setEnabled(!mode || mainwin->getColorpalette()=="custom");
    ui->styleSelect->setEnabled(!mode);
    ui->paletteSelect->setEnabled(mode);
    ui->paletteConfig->setEnabled(mode && mainwin->getColorpalette()=="custom");
    mainwin->setThememode(mode);
}
void settings::changePalette(const QString&){
    if(lockslot)return;
    mainwin->setColorpalette(ui->paletteSelect->itemData(ui->paletteSelect->currentIndex()).toString().toUtf8().constData());
    ui->paletteConfig->setEnabled(mainwin->getColorpalette()=="custom");
    ui->addpadding->setEnabled(mainwin->getColorpalette()=="custom");
}
void settings::openPalConfig(){
    auto c = new class palette(this);
    c->setFixedSize(c->geometry().width(),c->geometry().height());
    c->show();
}
void settings::changeStyle(const QString& style){
    if(lockslot)return;
    mainwin->setStylesheet(ui->styleSelect->itemData(ui->styleSelect->currentIndex()).toString().toUtf8().constData());
}
void settings::github(){
    QDesktopServices::openUrl(QUrl("https://github.com/ThePBone/JDSP4Linux-GUI"));
}
void settings::reject()
{
    mainwin->enableSetBtn(true);
    QDialog::reject();
}
void settings::glava_help(){
    QMessageBox *msgBox = new QMessageBox(this);
     msgBox->setText("This fix kills GLava (desktop visualizer) and restarts it after a new config has been applied.\nThis prevents GLava to switch to another audio sink, while JDSP is restarting.");
     msgBox->setStandardButtons(QMessageBox::Ok);
     msgBox->setDefaultButton(QMessageBox::Ok);
     msgBox->exec();
}
