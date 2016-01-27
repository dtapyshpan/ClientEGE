#ifndef PUPIL_H
#define PUPIL_H

#include <QString>
#include <QVector>
#include <QPair>

class pupil
{
public:
    void setfirstname(QString asfirstname);
    void setmiddlename(QString asmiddlename);
    void setsecondname(QString assecondname);
    void setid(int aiid);
    void setregion(QString asregionname);
    void setcodeoo(int aicodeoo);
    void setschoolname(QString asschoolname);
    void setclass(QString asclass);
    QString getfirstname();
    QString getmiddlename();
    QString getsecondname();
    int getid();
    QString getregion();
    int getcodeoo();
    QString getschoolname();
    QString getclass();

private:
    int _iid;
    QString _sfirstname;
    QString _smiddlename;
    QString _ssecondname;
    QString _sregionname;
    int _icodeoo;
    QString _sschoolname;
    QString _sclass;
    QVector<QPair<QString, QVector<int>>> exam;
    //bd name, points
};

#endif // PUPIL_H
