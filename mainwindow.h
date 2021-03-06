#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include <QSqlTableModel>
#include <QItemSelection>
#include <cmath>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    void writeLogF(const QString&,const QString&);
    void writeLog(const QString&,int mode = 0);
    string getPath();
    string getStylesheet();
    string getCustompalette();
    void setAutoFxMode(int);
    int getAutoFxMode();
    void setWhiteIcons(bool b);
    bool getWhiteIcons();
    void setCustompalette(string s);
    void setColorpalette(string);
    void switchPalette(const QPalette& palette);
    void LoadPresetFile(const QString&);
    void SavePresetFile(const QString&);
    void enableSetBtn(bool on);
    void enableLogBtn(bool on);
    void enableConvBtn(bool on);
    void enablePresetBtn(bool on);
    string getColorpalette();
    bool getAutoFx();
    void setAutoFx(bool autofx);
    int getThememode();
    void setThememode(int mode);
    bool getGFix();
    void setGFix(bool);
    void setPath(string npath);
    string getTheme();
    void setTheme(string);
    void setBorderPadding(bool b);
    bool getBorderPadding();
    void setStylesheet(string);
    void loadAppConfig(bool once = false);
    void UpdatePeakSource(string source);
    explicit MainWindow(QWidget *parent = nullptr);
    void setEQ(const int *data);
    float translate(int value,int leftMin,int leftMax,float rightMin,float rightMax);
    ~MainWindow();
public slots:
    void Reset();
    void Restart();
    void reloadConfig();
    void ConfirmConf(bool restart=true);
private slots:
    void updateDDC(const QItemSelection &, const QItemSelection &);
    void DisableFX();
    void OpenPreset();
    void CopyEQ();
    void PasteEQ();
    void OnUpdate(bool = true);
    void OnRelease();
    void ResetEQ();
    void OpenSettings();
    void updateroompreset();
    void updatestereopreset();
    void updatebs2bpreset();
    void update(int,QObject*alt=nullptr);
    void update(float,QObject*alt=nullptr);
    void LoadExternalFile();
    void SaveExternalFile();
    void OpenLog();
    void reloadDDC();
    void updateDDC_file();
    void selectDDCFolder();
    void reloadIRS();
    void updateIRS_file();
    void selectIRSFolder();
    void updateIRS_fav();
    void reloadIRSFav();
    void addIRSFav();
    void renameIRSFav();
    void removeIRSFav();
private:
    bool createconnection();
    void updateWidgetUnit(QObject* sender,QString text,bool);
    void loadIcons(bool);
    void setPalette(const QColor& base,const QColor& background,const QColor& foreground,const QColor&,const QColor&,const QColor& = QColor(85,85,85));
    int loadColor(int index,int rgb_index);
    void updateeq(int,QObject*);
    void setBS2B(int,int);
    void setStereoWide(float m,float s);
    void setRoompreset(int data);
    void loadConfig(const string& key, string value);
    void decodeAppConfig(const string& key, const string& value);
    void SaveAppConfig();
    string getSurround();
    string getBass();
    string getEQ();
    string getComp();
    string getMisc();
    string getReverb();
    void ConnectActions();
    void SetStyle();
    bool is_only_ascii_whitespace(const string&);
    bool is_number(const string& s);
    void setReverbData(int, double, double, double, double, \
                double, double, double, double, double, double, double, double,  \
                double, double, double, double);
};
typedef enum
{
    SF_REVERB_PRESET_DEFAULT,
    SF_REVERB_PRESET_SMALLHALL1,
    SF_REVERB_PRESET_SMALLHALL2,
    SF_REVERB_PRESET_MEDIUMHALL1,
    SF_REVERB_PRESET_MEDIUMHALL2,
    SF_REVERB_PRESET_LARGEHALL1,
    SF_REVERB_PRESET_LARGEHALL2,
    SF_REVERB_PRESET_SMALLROOM1,
    SF_REVERB_PRESET_SMALLROOM2,
    SF_REVERB_PRESET_MEDIUMROOM1,
    SF_REVERB_PRESET_MEDIUMROOM2,
    SF_REVERB_PRESET_LARGEROOM1,
    SF_REVERB_PRESET_LARGEROOM2,
    SF_REVERB_PRESET_MEDIUMER1,
    SF_REVERB_PRESET_MEDIUMER2,
    SF_REVERB_PRESET_PLATEHIGH,
    SF_REVERB_PRESET_PLATELOW,
    SF_REVERB_PRESET_LONGREVERB1,
    SF_REVERB_PRESET_LONGREVERB2
} sf_reverb_preset;
#endif // MAINWINDOW_H
