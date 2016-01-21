#define DEBUG

#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::_sprefixregname = tr("Кожуун: ");
const QString MainWindow::_sconfigfilename = tr("config.json");

const QString Messages::_scriticaltitle = "Критическая ошибка";
const QString Messages::_scriticalmessage = "Не могу прочитать конфигурационный файл.\n"
                                            "Обратитесь в РЦОИ.";
const QString Messages::_swarningtitle = "Ошибка";
const QString Messages::_smissinggrade = "Введите класс.";
const QString Messages::_smissingfirstname = "Введите имя.";
const QString Messages::_smissingsecondname = "Введите фамилию.";
const QString Messages::_smissingmiddlename = "Введите отчество.";
const QString Messages::_swronggrade = "Класс введен неправильно.\n"
                                       "Формат ввода: номер класса(11 или 12) буква(если есть).\n"
                                       "Например: 11а, 11, 12б, 12.";
const QString Messages::_swrongsecondname = "Фамилия введена неправильно.";
const QString Messages::_swrongmiddlename = "Отчество введено неправильно.";
const QString Messages::_swrongfirstname = "Имя введено неправильно.";

const QString regularexpression::_sregexpgrade = "[1][1-2][а-я]?";
const QString regularexpression::_sregexpname = "[А-Я][а-я]*|"
                                                "[А-Я][а-я]*-[А-Я]?[а-я][а-я]*|"
                                                "[А-Я][а-я]*-[А-Я]?[а-я][а-я]* [А-Я]?[а-я]*|"
                                                "[А-Я][а-я]* [А-Я]?[а-я]*";

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainView->show();
    ui->secondView->hide();
    if (_config.deserialize(_sconfigfilename) != true)
    {
        QMessageBox::critical(this, Messages::_scriticaltitle, Messages::_scriticalmessage);
        exit(EXIT_FAILURE);
    }
    int cntpoints = 0;
    for (int i = 0; i < _config.getexamcnt(); ++i)
    {
        cntpoints = qMax(cntpoints, _config.getexam(i).point.size());
    }
    _cpointform.resize(cntpoints);
    for (int i = 0; i < _cpointform.size(); ++i)
    {
        _cpointform[i]._clabel->setText(QString::number(i + 1));
        ui->pointsGridLayout->addLayout(_cpointform[i]._clayout, i/10, i%10);
    }
    for (int i = 0; i < _config.getexamcnt(); ++i)
    {
        ui->examComboBox->addItem(_config.getexam(i).title);
    }
    QRegExp cgrade(regularexpression::_sregexpgrade);
    gradevalidator *cgradeval = static_cast<gradevalidator*>(static_cast<QValidator*>(new QRegExpValidator(cgrade, this)));
    ui->gradeLineEdit->setValidator(cgradeval);
    QRegExp cname(regularexpression::_sregexpname);
    namevalidator *cnameval = static_cast<namevalidator*>(static_cast<QValidator*>(new QRegExpValidator(cname, this)));
    ui->secondNameEdit->setValidator(cnameval);
    ui->middleNameEdit->setValidator(cnameval);
    ui->firstNameEdit->setValidator(cnameval);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextButtonMainView_clicked()
{
    _snameregion = ui->regionsComboBox->currentText();
    _iregionid = ui->regionsComboBox->currentIndex();
    ui->mainView->hide();
    ui->secondView->show();
    initsecondview();
}

void MainWindow::initsecondview()
{
    ui->schoolsComboBox->clear();
    for (int i = 0; i < schoolCnt[_iregionid]; ++i)
    {
        ui->schoolsComboBox->addItem(schoolName[_iregionid][i].first);
    }
    ui->schoolsComboBox->setCurrentIndex(0);
    ui->regionName->setText(_sprefixregname + _snameregion);
    ui->examComboBox->setCurrentIndex(0);
    initpointform(ui->examComboBox->currentIndex());
}

void MainWindow::on_backButtonSecondView_clicked()
{
    ui->schoolsComboBox->clear();
    ui->regionName->setText("");
    ui->mainView->show();
    ui->secondView->hide();
    ui->regionsComboBox->setCurrentIndex(0);
}

void MainWindow::on_clearButtonSV_clicked()
{
    ui->gradeLineEdit->setText("");
    ui->secondNameEdit->setText("");
    ui->middleNameEdit->setText("");
    ui->firstNameEdit->setText("");
}

void MainWindow::on_saveButton_clicked()
{
    QString sstr = ui->gradeLineEdit->text();
    int ipos = 0;
    QValidator::State cstate = ui->gradeLineEdit->validator()->validate(sstr, ipos);
    qDebug() << "grade " << sstr;
    if (cstate == QValidator::Invalid)
    {
        qDebug() << "1";
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissinggrade);
        return;
    }
    if (cstate == QValidator::Intermediate)
    {
        qDebug() << "2";
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_swronggrade);
        return;
    }

    sstr = ui->secondNameEdit->text();
    cstate = ui->secondNameEdit->validator()->validate(sstr, ipos);
    if (cstate == QValidator::Invalid)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingsecondname);
        return;
    }
    if (cstate == QValidator::Intermediate)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_swrongsecondname);
        return;
    }

    sstr = ui->middleNameEdit->text();
    cstate = ui->middleNameEdit->validator()->validate(sstr, ipos);
    if (cstate == QValidator::Invalid)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingmiddlename);
        return;
    }
    if (cstate == QValidator::Intermediate)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_swrongmiddlename);
        return;
    }

    sstr = ui->firstNameEdit->text();
    cstate = ui->firstNameEdit->validator()->validate(sstr, ipos);
    if (cstate == QValidator::Invalid)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingfirstname);
        return;
    }
    if (cstate == QValidator::Intermediate)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_swrongfirstname);
        return;
    }
}

void MainWindow::initpointform(int aiexamid)
{
    for (int i = 0; i < _cpointform.size(); ++i)
    {
        _cpointform[i]._clabel->hide();
        _cpointform[i]._cspinbox->hide();
    }
    for (int i = 0; i < _config.getexam(aiexamid).point.size(); ++i)
    {
        _cpointform[i]._cspinbox->setMaximum(_config.getexam(aiexamid).point[i]);
    }
    for (int i = 0; i < _config.getexam(aiexamid).point.size(); ++i)
    {
        _cpointform[i]._clabel->show();
        _cpointform[i]._cspinbox->show();
    }
}

void MainWindow::on_examComboBox_currentIndexChanged(int aiindex)
{
    initpointform(aiindex);
}
