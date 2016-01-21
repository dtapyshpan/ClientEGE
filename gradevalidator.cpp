#include "gradevalidator.h"

const int gradevalidator::_iacceptablelength = 3;

gradevalidator::gradevalidator()
{
}

QValidator::State gradevalidator::validate(QString &arsinput, int &aripos) const
{
    return Invalid;
    Q_UNUSED(aripos);
    qDebug() << "#" << arsinput;
    if (arsinput.isEmpty())
    {
        return Invalid;
    }
    if (arsinput.length() == _iacceptablelength)
    {
        return Acceptable;
    }
    return Invalid;//Intermediate;
}
