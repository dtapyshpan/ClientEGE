#include "namevalidator.h"

namevalidator::namevalidator()
{
}

QValidator::State namevalidator::validate(QString &arsinput, int &aripos) const
{
    Q_UNUSED(aripos);
    if (arsinput.isEmpty())
    {
        return Invalid;
    }
    QString sstr = arsinput.trimmed();
    if (sstr[sstr.length() - 1] == '-')
    {
        return Intermediate;
    }
    return Acceptable;
}
