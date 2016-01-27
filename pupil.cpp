#include "pupil.h"

void pupil::setfirstname(QString asfirstname)
{
    _firstname = asfirstname;
}

void pupil::setmiddlename(QString asmiddlename)
{
    _middlename = asmiddlename;
}

void pupil::setsecondname(QString assecondname)
{
    _secondname = assecondname;
}

void pupil::setid(int aiarg)
{
    _iid = aiarg;
}

void pupil::setregion(QString asregionname)
{
    _sregionname = asregionname;
}

void pupil::setcodeoo(int aicodeoo)
{
    _icodeoo = aicodeoo;
}

void pupil::setschoolname(QString asschoolname)
{
    _sschoolname = asschoolname;
}

void pupil::setclass(QString asclass)
{
    _sclass = asclass;
}

QString pupil::getfirstname()
{
    return _sfirstname;
}

QString pupil::getmiddlename()
{
    return _smiddlename;
}

QString pupil::getsecondname()
{
    return _ssecondname;
}

int pupil::getid()
{
    return _iid;
}

QString pupil::getregion()
{
    return _sregionname;
}

int pupil::getcodeoo()
{
    return _icodeoo;
}

QString pupil::getschoolname()
{
    return _sschoolname;
}

QString pupil::getclass()
{
    return _sclass;
}
