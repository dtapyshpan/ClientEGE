#include "configreader.h"

configreader::configreader()
{
}

bool configreader::deserialize(const QString &acsfilename)
{
    QFile file(acsfilename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text) == false) return false;
    QTextStream in(&file);
    QString str;
    while (!in.atEnd())
    {
        str += in.readLine();
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QByteArray doc = codec->fromUnicode(str);
    QJsonParseError jerror;
    QJsonDocument jDocument = QJsonDocument::fromJson(doc, &jerror);
    if (jerror.error != QJsonParseError::NoError) return false;
    QJsonObject jRoot = jDocument.object();
    if (jRoot["exams"] == QJsonValue::Undefined) return false;
    QJsonArray examarray = jRoot["exams"].toArray();
    QJsonObject examobj;
    for (int i = 0; i < examarray.size(); ++i)
    {
        exam currexam;
        examobj = examarray[i].toObject();
        if (examobj["title"] == QJsonValue::Undefined) return false;
        currexam.title = examobj["title"].toString();
        if (examobj["points"] == QJsonValue::Undefined) return false;
        QJsonArray pointsarray = examobj["points"].toArray();
        QJsonObject pointobj;
        for (int j = 0; j < pointsarray.size(); ++j)
        {
            currexam.point.push_back(pointsarray[j].toInt());
        }
        _cexam.push_back(currexam);
    }

    return true;
}

exam configreader::getexam(int aiexamid)
{
    Q_ASSERT(_cexam.size() > aiexamid);
    return _cexam[aiexamid];
}

int configreader::getexamcnt()
{
    return _cexam.size();
}
