#include <QString>
#include <QVariant>

struct PrjGroupAddrbookAnswer
{
    PrjGroupAddrbookAnswer(){ }

    PrjGroupAddrbookAnswer(int prj_group_addrbook_id, QString  family, QString  first_name){
        this->prj_group_addrbook_id = prj_group_addrbook_id;
        this->family = family;
        this->first_name = first_name;
        this->prj_group_id = -1;
    }

    PrjGroupAddrbookAnswer(int prj_group_addrbook_id, QString  family, QString  first_name,int prj_group_id){
        this->prj_group_addrbook_id = prj_group_addrbook_id;
        this->family = family;
        this->first_name = first_name;
        this->prj_group_id = prj_group_id;
    }

    int  prj_group_addrbook_id;
    QString  family;
    QString  first_name;
    int prj_group_id;

    operator QString() { return (family + " " + first_name); }
};

Q_DECLARE_METATYPE(PrjGroupAddrbookAnswer);

struct PrjGroupAnswer
{
    PrjGroupAnswer(){ }

    PrjGroupAnswer(int prj_group_id, QString  name){
        this->prj_group_id = prj_group_id;
        this->name =  name;
    }

    int  prj_group_id;
    QString  name;

    operator QString() { return name; }
};

Q_DECLARE_METATYPE(PrjGroupAnswer);
