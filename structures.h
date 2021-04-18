#include <QString>
#include <QVariant>

struct prj_group_addrbook_answer
{
    prj_group_addrbook_answer(){ }

    prj_group_addrbook_answer(QString prj_group_addrbook_id, QString  family, QString  first_name){
        this->prj_group_addrbook_id = prj_group_addrbook_id;
        this->family = family;
        this->first_name = first_name;
    }
    QString  prj_group_addrbook_id;
    QString  family;
    QString  first_name;

    operator QString() { return (family + " " + first_name); }
};

Q_DECLARE_METATYPE(prj_group_addrbook_answer);
