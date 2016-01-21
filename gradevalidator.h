#ifndef GRADEVALIDATOR_H
#define GRADEVALIDATOR_H

#include <QValidator>
#include <QDebug>

class gradevalidator : public QValidator
{
    Q_OBJECT

public:
    gradevalidator();
    virtual State validate(QString &arsinput, int &aripos) const;

private:
    static const int _iacceptablelength;
};

#endif // GRADEVALIDATOR_H
