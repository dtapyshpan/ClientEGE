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
    }
    for (int i = 0; i < _config.getexamcnt(); ++i)
    {
        ui->examComboBox->addItem(_config.getexam(i).title);
    }
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

bool MainWindow::gradecheck()
{
    QString sgrade = ui->gradeLineEdit->text();
    if (sgrade.length() < 2) return false;
    if (sgrade[0].isDigit() == false || sgrade[1].isDigit() == false) return false;
    int igrade = sgrade[0].digitValue() * 10 + sgrade[1].digitValue();
    if (igrade != 11 && igrade != 12) return false;
    return true;
}

void MainWindow::on_saveButton_clicked()
{
    if (ui->gradeLineEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissinggrade);
        return;
    }
    if (gradecheck() == false)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_swronggrade);
        return;
    }
    if (ui->secondNameEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingsecondname);
        return;
    }
    if (ui->middleNameEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingmiddlename);
        return;
    }
    if (ui->firstNameEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, Messages::_swarningtitle, Messages::_smissingfirstname);
        return;
    }
}

void MainWindow::initpointform(int aiexamid)
{
    while (ui->pointsGridLayout->takeAt(0));
    ui->pointsGridLayout->update();
    for (int i = 0; i < _config.getexam(aiexamid).point.size(); ++i)
    {
        _cpointform[i]._cspinbox->setMaximum(_config.getexam(aiexamid).point[i]);
    }
    for (int i = 0; i < _config.getexam(aiexamid).point.size(); ++i)
    {
        ui->pointsGridLayout->addLayout(_cpointform[i]._clayout, i/10, i%10);
    }
}

void MainWindow::on_examComboBox_currentIndexChanged(int aiindex)
{
    initpointform(aiindex);
}
