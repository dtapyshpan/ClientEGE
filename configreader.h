#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QTextCodec>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

struct exam
{
    QString title;
    QVector<int> point;
};

class configreader
{
public:
    configreader();

    bool deserialize(const QString &acsfilename);
    exam getexam(int aiexamid);
    int getexamcnt();

private:
    QVector<exam> _cexam;
};

#endif // CONFIGREADER_H
