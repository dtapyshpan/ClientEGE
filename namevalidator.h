#ifndef NAMEVALIDATOR_H
#define NAMEVALIDATOR_H

#include <QValidator>

class namevalidator : public QValidator
{
    Q_OBJECT

public:
    namevalidator();
    virtual State validate(QString &arsinput, int &aripos) const;
};

#endif // NAMEVALIDATOR_H
