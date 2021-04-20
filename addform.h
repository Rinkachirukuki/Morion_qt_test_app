#ifndef ADDFORM_H
#define ADDFORM_H

#include "dbconnector.h"

#include <QWidget>

namespace Ui {
class AddForm;
}

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr);

    void setTitle(QString title);
    void setPrjGroupId(int prj_group_id);
    void setPrjGroupAddrbookId(int prj_group_addrbook_id);
    void setFamily(QString family);
    void setFirstName(QString fname);
    void setButtonText(QString text);

    ~AddForm();

private slots:
    void on_pushButton_clicked();

    void mainFormCloseHandler();

signals:
    void addPrjGroupAddrbook(PrjGroupAddrbookAnswer item);

private:
    Ui::AddForm *ui;

    int prj_group_id = -1;
    int prj_group_addrbook_id = -1;

};

#endif // ADDFORM_H
