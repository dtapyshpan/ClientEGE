#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include <QVBoxLayout>

#include "schoolnameconsts.h"
#include "configreader.h"
#include "gradevalidator.h"
#include "namevalidator.h"

namespace Ui
{
    class MainWindow;
}

struct regularexpression
{
    static const QString _sregexpgrade;
    static const QString _sregexpname;
};

struct Messages
{
    static const QString _scriticaltitle;
    static const QString _scriticalmessage;
    static const QString _swarningtitle;
    static const QString _smissinggrade;
    static const QString _smissingfirstname;
    static const QString _smissingsecondname;
    static const QString _smissingmiddlename;
    static const QString _swronggrade;
    static const QString _swrongsecondname;
    static const QString _swrongmiddlename;
    static const QString _swrongfirstname;
};

struct pntform
{
    QLabel *_clabel;
    QSpinBox *_cspinbox;
    QVBoxLayout *_clayout;

    pntform()
    {
        _clabel = new QLabel();
        _cspinbox = new QSpinBox();
        _clayout = new QVBoxLayout();
        _clayout->addWidget(_clabel);
        _clayout->addWidget(_cspinbox);
    }

    ~pntform()
    {
        Q_ASSERT(_clabel && _cspinbox && _clayout);
        delete _clabel;
        delete _cspinbox;
        delete _clayout;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_nextButtonMainView_clicked();
    void on_backButtonSecondView_clicked();
    void on_clearButtonSV_clicked();
    void on_saveButton_clicked();
    void on_examComboBox_currentIndexChanged(int aiindex);

private:
    static const QString _sprefixregname;
    static const QString _sconfigfilename;
    Ui::MainWindow *ui;
    QString _snameregion;
    int _iregionid;
    configreader _config;
    QVector<pntform> _cpointform;

    void initsecondview();
    void initpointform(int aiexamid);
};

#endif // MAINWINDOW_H
